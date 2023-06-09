#include "protocol.h"
#include "remoteevent.h"

QDataStream& operator>>(QDataStream &in, BlockHeader &header)
{
    in >> header.type
        >> header.dataSize;

    return in;
}

QDataStream& operator<<(QDataStream &out, const BlockHeader &header)
{
    out << header.type
        << header.dataSize;

    return out;
}

QDataStream& operator>>(QDataStream &in, DataBlock &block)
{
    in >> block.header
        >> block.data;

    return in;
}

QDataStream& operator<<(QDataStream &out, const DataBlock &block)
{
    out << block.header
        << block.data;

    return out;
}

QDataStream &operator>>(QDataStream &in, RemoteEvent &block)
{
    qint32 type;
    QPointF position;
    int key;
    in >> type >> position>>key;
    block.setType(RemoteEvent::EventType(type));
    block.setPosition(position);
    block.setKey(key);

    return in;
}

QDataStream &operator<<(QDataStream &out, const RemoteEvent &block)
{
    out << qint32(block.type())
        << block.position()
        << block.key();

    return out;
}

QDebug operator<<(QDebug debug, const BlockHeader &header)
{
    debug << "[type]: " << header.type << Qt::endl
          << "[data size]: " << header.dataSize << Qt::endl;

    return debug;
}

QDebug operator<<(QDebug debug, const DataBlock &block)
{
    debug << "[type]: " << block.header.type << Qt::endl
          << "[data size]: " << block.header.dataSize << Qt::endl;

    return debug;
}
