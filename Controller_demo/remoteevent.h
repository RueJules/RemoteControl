#ifndef REMOTEEVENT_H
#define REMOTEEVENT_H

#include <QByteArray>
#include <QPointF>

class RemoteEvent
{
public:
    enum class EventType
    {
        NoType = 0,
        MouseLeftPressed,//1
        MouseLeftReleased,//2
        MouseMoved,//3
        KeyInput,//4
        KeyReleased,
        MouseEntered,
        MouseRoll,
        MouseRightPressed,
        MouseRightReleased
    };

    RemoteEvent() { }
    RemoteEvent(EventType type, const QPointF &position)
        : m_type(type), m_position(position) { }
    RemoteEvent(EventType type, const int &key)
        : m_type(type), m_key(key) { }

    EventType type() const { return m_type; }
    void setType(EventType type) { m_type = type; }

    int key() const { return m_key; }
    void setKey(int key) { m_key = key; }

    QPointF position() const { return m_position; }
    void setPosition(const QPointF &position) { m_position = position; }

    bool isEmpty() { return m_type == EventType::NoType && m_position.isNull(); }
    int size() { return sizeof(m_type) + sizeof(m_position) + sizeof(int); }//为什么加sizeof（int）

private:
    EventType m_type = EventType::NoType;
    QPointF m_position;
    int m_key;
};

#endif // REMOTEEVENT_H
