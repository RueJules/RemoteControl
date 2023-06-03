#ifndef SYSTEMAPI_H
#define SYSTEMAPI_H

#include <QPixmap>

class SystemApi
{
public:
    /** System Event */
    static void mousePress(const QPointF &pos);
    static void mouseRelease(const QPointF &pos);
    static void mouseMove(const QPointF &pos);
    static void mouseEntered(const QPointF &pos);
    static void keyPressed(int keyval);
    static void keyReleased(int keyval);
    static void MouseRightPress(const QPointF &pos);
    static void MouseRightReleased(const QPointF &pos);
    //static void keyRealsed(int keyval);

    /** System Tools */
    SystemApi();
    static QPixmap grabScreen();
    static QPixmap grabCursor();
private:
    QPointF startPoint;
    static  QPointF oldPoint;
};

#endif
