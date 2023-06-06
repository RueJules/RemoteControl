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
//封装一个虚拟的键盘和鼠标设备，注册在操作系统中，
//能够在整个电脑上响应远程的鼠标和键盘事件，就需要访问linux系统底层的系统事件机制。

#define UINPUT_NAME      "/dev/uinput"
#define VIR_MOUSE_NAME   "DFC Virtual Mouse"
#define VIR_KETBOARD_NAME   "DFC Virtual Keyboard"

class VirtualMouse
{
public:
    VirtualMouse();
    ~VirtualMouse();
    void install_uinput_mouse_device();
    void uninstall_uinput_mouse_device();
    //void install_uinput_keyboard_device();
    //QPointF oldPoint;
    static int device_handler;
    //static int keydevice_handler;
private:
    struct uinput_user_dev vir_mouse;
    //struct uinput_user_dev vir_keyboard;


};

#endif // VIRTUALMOUSE_H
