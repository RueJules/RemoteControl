#include "remoteevent.h"
#include "socket.h"
#include <QTime>
#include <QDebug>

Socket::Socket(QObject *parent)
    : QTcpSocket (parent)
{
    connect(this, &QTcpSocket::readyRead, this, [this]() {
        m_recvData += readAll();
        processRecvBlock();
    });
}

Socket::~Socket()
{

}

void Socket::abort()
{
    QTcpSocket::abort();
    m_recvData.clear();
    m_recvHeader.clear();
}

void Socket::writeToSocket(const DataBlock &block)
{
    //qDebug() << QTime::currentTime() ;
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << block;
    write(data);
    flush();
    //qDebug() << QTime::currentTime()<<'\n';
}
void Socket::writeToSocket(const RemoteEvent &event)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << event;
    BlockHeader header = { EVENT_TYPE, data.size() };
    DataBlock block = { header, data };
    out.device()->seek(0);
    out << block;
    write(data);
    flush();
}

void Socket::processRecvBlock()
{
    if (m_recvHeader.isEmpty() && m_recvData.size() > 0) { //先写数据块的头
        BlockHeader header;
        QDataStream in(&m_recvData, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_12);
        in >> header;

        if (header.isEmpty())  //写入失败
            return;

        m_recvHeader = header;
        m_recvData.remove(0, header.size());      //接收到的数据中移除已经记录的头
    }

    if (m_recvData.size() < m_recvHeader.dataSize) //收到的数据大小小于头中记录的大小，则放弃这一次可能不完整的数据
        return;

    DataBlock block;
    block.header = m_recvHeader; //记录的数据头写入数据块
    block.data = m_recvData.left(m_recvHeader.dataSize); //Returns a byte array that contains the first len bytes of this byte array.从左往右数最先包含这么多大小的数据
    m_recvData = m_recvData.mid(m_recvHeader.dataSize); //Returns a byte array containing len bytes from this byte array, starting at position pos.
    m_recvHeader.clear();//清空这个头，以便写入下一次数据块


    //开始识别数据类型，分类处理数据
    if (block.header.type == SCREEN_TYPE) {
        emit hasScreenData(block.data);
    } else if (block.header.type == EVENT_TYPE) {
        RemoteEvent event;
        QDataStream in(block.data);
        in.setVersion(QDataStream::Qt_5_12);
        in >> event;
        emit hasEventData(event);
    }

    if (m_recvData.size() > 0)  //如果还有则继续处理
        processRecvBlock();
}
