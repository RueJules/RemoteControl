#include<QTime>
#include "socket.h"

Socket::Socket(QObject *parent)
    : QTcpSocket (parent)
{
    connect(this, &QTcpSocket::readyRead, this, [this]() {
        m_recvData += readAll();//QIODevice::readAll()从设备中读取所有剩余数据，并将其作为字节数组返回。
        processRecvBlock();
    });
}
Socket::~Socket()
{

}

void Socket::abort()
{
    QTcpSocket::abort();//中止当前连接并重置套接字。立即关闭套接字，丢弃写入缓冲区中的任何挂起数据
    m_recvData.clear();
    m_recvHeader.clear();
}

void Socket::connectHost(const QHostAddress &host, quint16 port)
{
    QTcpSocket::connectToHost(host,port);
}


void Socket::writeToSocket(const RemoteEvent &event)//把事件转化为信息流？？
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << event;//把event写入data中
    BlockHeader header = { EVENT_TYPE, data.size() };
    DataBlock block = { header, data };
    out.device()->seek(0);
    out << block;//再把block写入data中
    write(data);//再把data写入套接字
    flush();
}



void Socket::processRecvBlock()
{
    if (m_recvHeader.isEmpty() && m_recvData.size() > 0) {
        BlockHeader header;
        QDataStream in(&m_recvData, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_12);
        in >> header;
        if (header.isEmpty())
            return;
        m_recvHeader = header;
        m_recvData.remove(0, header.size());
    }


    if (m_recvData.size() < m_recvHeader.dataSize)
        return;


    DataBlock block;
    block.header = m_recvHeader;
    block.data = m_recvData.first(m_recvHeader.dataSize);
    m_recvData = m_recvData.sliced(m_recvHeader.dataSize);
    m_recvHeader.clear();


    emit hasScreenData(block.data);



    if (m_recvData.size() > 0)  //如果还有则继续处理
        processRecvBlock();
}
