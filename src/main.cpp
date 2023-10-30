#include <iostream>
#include <unistd.h>
#include "Drive.h" 
#include "evdevHelper.h"

struct input_event events[8]; 

// #define DEBUG

int main()
{
    gpioTerminate();
    gpioInitialise();
    GPIOsetup();
    evdevEnable();
#ifndef DEBUG
    bool rt_down = false;
    bool lt_down = false;
    int stick_left_x = 0;
    int stick_left_y = 0;
    struct input_event event;
    while (1)
    {
        //read XBOX input
        for (int i = 0; i < 4; i++) 
        {
            int r1 = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &event);
            if (r1 == 0)
            {
                switch (event.code) {
                    // case ABS_X: { 
                    //     stick_left_x = event.value - AXIS_RANGE; //normalize 
                    //     std::cout << "LEFT STICK X IS" << event.value << std::endl;
                    // } break;
                    // case ABS_Y: { 
                    //     stick_left_y = event.value - AXIS_RANGE; //normalize
                    //     std::cout << "LEFT STICK Y IS" << event.value << std::endl;
                    // } break;
                    case ABS_GAS: {
                        rt_down = (event.value > 0) ? true : false;
                        std::cout << "RIGHT" << std::endl;
                    } break;
                    case ABS_BRAKE: {
                        lt_down = (event.value > 0) ? true : false;
                        std::cout << "LEFT" << std::endl;
                    } break;
                    case ABS_BRAKE: {
                        lt_down = (event.value > 0) ? true : false;
                        std::cout << "LEFT" << std::endl;
                    } break;
                    default:
                        break;
                }
            }
        }
        //Drive Logic
        DriveControl(lt_down, rt_down);
        //DriveControl(stick_left_x, stick_left_y, rt_down, lt_down);
    }

#else

    std::cout << "driving" << std::endl;
    RightForward();
    sleep(1);
    std::cout << "stopping" << std::endl;
    RightStop();

#endif // DEBUG

    evdevDestroy();
    gpioTerminate();

    return 0;
}
