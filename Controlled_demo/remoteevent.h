#ifndef REMOTEEVENT_H
#define REMOTEEVENT_H

#include <QByteArray>
#include <QPointF>
#include <utility>

class RemoteEvent
{
public:
    enum class EventType
    {
        NoType = 0,
        MouseLeftPressed,
        MouseLeftReleased,
        MouseMoved,
        KeyInput,
        KeyReleased,
        MouseEntered,
        MouseRoll,
        MouseRightPressed,
        MouseRightReleased
    };

    RemoteEvent() { }

    RemoteEvent(EventType type, const QPointF &position)
        : m_type(type), m_position(position) { }

    RemoteEvent(EventType type, const int key)
        : m_type(type), m_key(key) { }


    EventType type() const { return m_type; }
    void setType(EventType type) { m_type = type; }


    /*int code() const { return m_code; }
    void setCode(const int code) { m_code = code; }

    int value() const { return m_value; }
    void setValue(const int value) { m_value = value; }*/

    QPointF position() const { return m_position; }
    void setPosition(const QPointF &position) { m_position = position; }

    int key() const{return m_key;}
    void setKey(const int key){m_key = key;}

    bool isEmpty() { return m_type == EventType::NoType && m_position.isNull(); }
    int size() { return sizeof(m_type) + sizeof(m_position) + sizeof(int); }

private:
    EventType m_type = EventType::NoType;
    QPointF m_position;
    int m_key;
};

#endif // REMOTEEVENT_H
