#include "keythread.h"
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
KeyThread::KeyThread(QObject *parent):QThread(parent)
{

}

void KeyThread::run()
{
    const char *dev="/dev/input/event4";
    int retval;
    fd_set readfds;
    struct timeval tv;

    int fd = open(dev, O_RDONLY);

    struct input_event event;

    if (fd < 0)
    {
        perror(dev);
    }

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        tv.tv_sec = 100;
        tv.tv_usec = 0;
        if((retval = select(fd+1, &readfds, NULL, NULL, &tv)) == 1)
        {
            if (read(fd, &event, sizeof(event)) == sizeof(event))
            {
                if (event.type == EV_KEY)
                {
                    if(event.value==1){
                        printf("keyPressed %d\n", event.code);
                        emit keyPressed(event.code);
                    }
                    if(event.value==0){
                        printf("keyReleased %d\n", event.code);
                        emit keyReleased(event.code);
                    }

                }
            }
        }
    }
    close(fd);
}
