#ifndef VIRTUALMOUSE_H
#define VIRTUALMOUSE_H

#include <sys/ioctl.h>
#include <linux/uinput.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <QPointF>

#define ALOGE(...) \
printf(__VA_ARGS__); \
    printf("\n")


#define UINPUT_NAME      "/dev/uinput"
#define VIR_MOUSE_NAME   "DFC Virtual Mouse"

class VirtualMouse
{
public:
    VirtualMouse();
    void install_uinput_mouse_device();
    void uninstall_uinput_mouse_device();
    //QPointF oldPoint;
    static int device_handler;
private:
    struct uinput_user_dev vir_mouse;


};

#endif // VIRTUALMOUSE_H