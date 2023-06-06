#include "virtualmouse.h"
#include <QCursor>
#include <QGuiApplication>
#include <QScreen>

VirtualMouse::VirtualMouse()
{
    // oldPoint = QCursor::pos();
}

VirtualMouse::~VirtualMouse()
{
    if (device_handler > 0)
    {
        ioctl(device_handler, UI_DEV_DESTROY);
        close(device_handler);
        // device_handler = ERROR_DEVICE_HANDLER;
    }
}

//QPointF VirtualMouse::oldPoint = QPointF(QGuiApplication::primaryScreen()->size().width() /2,QGuiApplication::primaryScreen()->size().height() / 2);

int VirtualMouse::device_handler = -1;

int VirtualMouse::keydevice_handler = -1;

//注册一个设备，这里本来打算为键盘和鼠标各注册一个（所以命名为mouse），其实可以只注册一个，使用同一个句柄
void VirtualMouse::install_uinput_mouse_device()
{
    if (device_handler > 0)
    {
        ALOGE("virtual mouse has been installed already.");
        //return device_handler;
    }

    //open uinput device
    if ((device_handler = open(UINPUT_NAME, O_WRONLY | O_NDELAY)) <= 0)
    {
        ALOGE("open uinput(%s) failed.", UINPUT_NAME);
        device_handler = -1;
        //return device_handler;
    }

    //setup our uinput device of virtual mouse
    memset(&vir_mouse, 0, sizeof(struct uinput_user_dev));
    strncpy(vir_mouse.name, VIR_MOUSE_NAME, UINPUT_MAX_NAME_SIZE);
    vir_mouse.id.version = 4;
    vir_mouse.id.bustype = BUS_USB;

    //if we don't do these register, it seems like not to work
    ioctl(device_handler, UI_SET_EVBIT, EV_KEY);
    for (int i = 0; i < 256; i++)
    {
        ioctl(device_handler, UI_SET_KEYBIT, i);  //setup keyboard event
    }

    //setup mouse coordinate event
    ioctl(device_handler, UI_SET_EVBIT,  EV_REL);
    ioctl(device_handler, UI_SET_RELBIT, REL_X);
    ioctl(device_handler, UI_SET_RELBIT, REL_Y);
    //ioctl(device_handler, UI_SET_EVBIT, EV_ABS);
    //ioctl(device_handler, UI_SET_EVBIT, ABS_X);
    //ioctl(device_handler, UI_SET_EVBIT, ABS_Y);

    //setup mouse button event
    ioctl(device_handler, UI_SET_KEYBIT, BTN_MOUSE);
    ioctl(device_handler, UI_SET_KEYBIT, BTN_TOUCH);
    ioctl(device_handler, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(device_handler, UI_SET_KEYBIT, BTN_RIGHT);
    ioctl(device_handler, UI_SET_KEYBIT, BTN_MIDDLE);

    //create input device into input subsystem
    write(device_handler, &vir_mouse, sizeof(vir_mouse));
    if (ioctl(device_handler, UI_DEV_CREATE))
    {
        ALOGE("install mouse uinput device failed with error(%s).", strerror(errno));
        close(device_handler);
        device_handler = -1;
    }

}

/*void VirtualMouse::install_uinput_keyboard_device()
{
    if (keydevice_handler > 0)
    {
        ALOGE("virtual mouse has been installed already.");
        //return device_handler;
    }

    //open uinput device
    if ((keydevice_handler = open(UINPUT_NAME, O_WRONLY | O_NDELAY)) <= 0)
    {
        ALOGE("open uinput(%s) failed.", UINPUT_NAME);
        keydevice_handler = -1;
        //return device_handler;
    }

    //setup our uinput device of virtual mouse
    memset(&vir_keyboard, 0, sizeof(struct uinput_user_dev));
    strncpy(vir_keyboard.name, VIR_KETBOARD_NAME , UINPUT_MAX_NAME_SIZE);
    vir_keyboard.id.version = 4;
    vir_keyboard.id.bustype = BUS_USB;

    //if we don't do these register, it seems like not to work
    ioctl(keydevice_handler, UI_SET_EVBIT, EV_KEY);
    for (int i = 0; i < 256; i++)
    {
        ioctl(keydevice_handler, UI_SET_KEYBIT, i);
    }

    //setup mouse coordinate event
    //ioctl(device_handler, UI_SET_EVBIT,  EV_REL);
    //ioctl(device_handler, UI_SET_RELBIT, REL_X);
    //ioctl(device_handler, UI_SET_RELBIT, REL_Y);
    //    ioctl(device_handler, UI_SET_EVBIT, EV_ABS);
    //    ioctl(device_handler, UI_SET_EVBIT, ABS_X);
    //    ioctl(device_handler, UI_SET_EVBIT, ABS_Y);

    //setup mouse button event
    //ioctl(device_handler, UI_SET_KEYBIT, BTN_MOUSE);
    //ioctl(device_handler, UI_SET_KEYBIT, BTN_TOUCH);
    //ioctl(device_handler, UI_SET_KEYBIT, BTN_LEFT);
   // ioctl(device_handler, UI_SET_KEYBIT, BTN_RIGHT);
    //ioctl(device_handler, UI_SET_KEYBIT, BTN_MIDDLE);

    //create input device into input subsystem
    write(device_handler, &vir_mouse, sizeof(vir_mouse));
    if (ioctl(device_handler, UI_DEV_CREATE))
    {
        ALOGE("install mouse uinput device failed with error(%s).", strerror(errno));
        close(device_handler);
        device_handler = -1;
    }

}*/

void VirtualMouse::uninstall_uinput_mouse_device()
{
    if (device_handler > 0)
    {
        ioctl(device_handler, UI_DEV_DESTROY);
        close(device_handler);
        // device_handler = ERROR_DEVICE_HANDLER;
    }
}


