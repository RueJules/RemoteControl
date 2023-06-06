#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QDebug>
#include <QtGlobal>
#include <QDataStream>

#define INFO_TYPE   0x01
#define EVENT_TYPE  0x02
#define SCREEN_TYPE 0x03

struct BlockHeader //传输数据块的头结构
{
    qint8 type;
    qint32 dataSize;

    BlockHeader() : type(0), dataSize(0) { }
    BlockHeader(qint8 t, qint32 s) : type(t), dataSize(s) { }

    bool isEmpty() const {
        return type == 0 && dataSize == 0;
    }

    void clear() {
        type = dataSize = 0;
    }

    int size() const {
        return sizeof(type) + sizeof(dataSize) + 4;     //data为QByteArray会加4字节
    }
};

struct DataBlock  //传输的数据块结构
{
    BlockHeader header; //头
    QByteArray data;//数据
};

class RemoteEvent;

//重载操作符实现对数据和事件的读写
extern QDataStream& operator>>(QDataStream &in, BlockHeader &header);
extern QDataStream& operator<<(QDataStream &out, const BlockHeader &header);
extern QDataStream& operator>>(QDataStream &in, DataBlock &block);
extern QDataStream& operator<<(QDataStream &out, const DataBlock &block);
extern QDataStream &operator>>(QDataStream &in, RemoteEvent &event);
extern QDataStream &operator<<(QDataStream &out, const RemoteEvent &event);
extern QDebug operator<<(QDebug debug, const BlockHeader &header);
extern QDebug operator<<(QDebug debug, const DataBlock &block);

#endif // PROTOCOL_H
