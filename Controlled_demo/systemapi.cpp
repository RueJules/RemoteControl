#include "systemapi.h"
#include "virtualmouse.h"
#include <QCursor>
#include <QDebug>
#include <QGuiApplication>
#include <QPainter>
#include <QWindow>
#include <QScreen>

QPointF SystemApi::oldPoint={QPointF(0,0)};
SystemApi::SystemApi(){
    startPoint = QCursor::pos();
    qDebug() << "startPoint:"<<startPoint.x() << startPoint.y();
    oldPoint=startPoint;

}

void SystemApi::mousePress(const QPointF &pos)
{
    struct input_event event;
    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //按下kval键

    event.type = EV_KEY;

    event.value = 1;

    event.code = BTN_LEFT;

    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统

    event.type = EV_SYN;

    event.value = 0;

    event.code = SYN_REPORT;

    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

}

void SystemApi::mouseRelease(const QPointF &pos)
{
    struct input_event event;
    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //松开鼠标

    event.type = EV_KEY;

    event.value = 0;

    event.code = BTN_LEFT;

    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统

    event.type = EV_SYN;

    event.value = 0;

    event.code = SYN_REPORT;

    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();
}

void SystemApi::mouseMove(const QPointF &pos)
{
    //QPoint p1 = QCursor::pos();
    //qDebug() << "Begin:"<<p1.x() << p1.y();

    struct input_event event;

    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //移动鼠标X坐标
    event.type = EV_REL;
    //event.type = EV_ABS;
    event.value =(int)pos.x() - oldPoint.x();
    //event.value = pos.x();
    event.code = REL_X;
    //event.code = ABS_X;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //qDebug << "x差："<<event.value;

    //移动鼠标Y坐标
    event.type = EV_REL;
    //event.type = EV_ABS;
    event.value = (int)pos.y() - oldPoint.y();
    //event.value = pos.y();
    event.code = REL_Y;
    //event.code = ABS_Y;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    oldPoint = pos;

    //oldPoint = relVal;
    //qDebug() << "oldPoint"<<oldPoint.x() << oldPoint.y();

    //QPoint p = QCursor::pos();
    //qDebug() << p.x() << p.y();

}

void SystemApi::mouseEntered(const QPointF &pos)
{
    QPoint p1 = QCursor::pos();
    qDebug() << "Begin:"<<p1.x() << p1.y();

    struct input_event event;

    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //移动鼠标X坐标
    event.type = EV_REL;
    event.value =(int)pos.x() - oldPoint.x();
    event.code = REL_X;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //qDebug << "x差："<<event.value;

    //移动鼠标Y坐标
    event.type = EV_REL;
    event.value = (int)pos.y() - oldPoint.y();
    event.code = REL_Y;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    oldPoint = pos;
    qDebug() << "oldPoint"<<oldPoint.x() << oldPoint.y();

    QPoint p = QCursor::pos();
    qDebug() << p.x() << p.y();
}

void SystemApi::keyPressed(int keyval)
{

    qDebug() << "收到键盘按下事件" << "\n";
    qDebug() << keyval << "\n";

    struct input_event event;

    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //键盘按下
    event.type = EV_KEY;
    event.value = 1;
    event.code = keyval;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();
}

void SystemApi::keyReleased(int keyval)
{
    qDebug() << "收到键盘释放事件" << "\n";
    qDebug() << keyval << "\n";
    struct input_event event;

    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //键盘按下
    event.type = EV_KEY;
    event.value = 0;
    event.code = keyval;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();
}

void SystemApi::MouseRightPress(const QPointF &pos)
{
    struct input_event event;
    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //按下kval键

    event.type = EV_KEY;

    event.value = 1;

    event.code = BTN_RIGHT;

    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统

    event.type = EV_SYN;

    event.value = 0;

    event.code = SYN_REPORT;

    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();
}

void SystemApi::MouseRightReleased(const QPointF &pos)
{
    qDebug() << "接收到鼠标右键事件\n";
    struct input_event event;
    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //按下kval键

    event.type = EV_KEY;

    event.value = 0;

    event.code = BTN_RIGHT;

    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统

    event.type = EV_SYN;

    event.value = 0;

    event.code = SYN_REPORT;

    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();
}

/*void SystemApi::keyReleased(int keyval)
{

    struct input_event event;

    memset(&event, 0, sizeof(event));

    gettimeofday(&event.time, 0);

    //释放
    event.type = EV_KEY;
    event.value = 0;
    event.code = keyval;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();

    //同步，也就是把它报告给系统
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(VirtualMouse::device_handler, &event, sizeof(event));
    sync();
}*/

QPixmap SystemApi::grabScreen()
{
    QPixmap screen;
    screen = QGuiApplication::primaryScreen()->grabWindow(0);
    if (!screen.isNull()) {
        QPainter painter(&screen);
        painter.drawPixmap(QCursor::pos(), grabCursor());
    }
    return screen;
}

QPixmap SystemApi::grabCursor()
{
    QPixmap cursorPixmap;
    return cursorPixmap;
}
