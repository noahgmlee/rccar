#include <wiringPi.h>
#include <pigpio.h>

// #define LEFT1 0
// #define LEFT2 1
// #define RIGHT1 2
// #define RIGHT2 3
// #define LEFTEN 4
// #define RIGHTEN 5

#define LEFT1 17
#define LEFT2 18
#define RIGHT1 27
#define RIGHT2 22
#define LEFTEN 23
#define RIGHTEN 24

#define AXIS_RANGE 32768
#define BUFFER 1000

#define max(a, b)  (((a) > (b)) ? (a) : (b)) 
#define min(a, b)  (((a) < (b)) ? (a) : (b)) 

void GPIOsetup()
{
    gpioSetMode(LEFT1, PI_OUTPUT);
    gpioSetMode(LEFT2, PI_OUTPUT);
    gpioSetMode(RIGHT1, PI_OUTPUT);
    gpioSetMode(RIGHT2, PI_INPUT);
    gpioSetMode(LEFTEN, PI_OUTPUT);
    gpioSetMode(RIGHTEN, PI_OUTPUT);
    gpioWrite(LEFT1, 0);
    gpioWrite(LEFT2, 0);
    gpioWrite(RIGHT1, 0);
    gpioWrite(RIGHT2, 0);
}

void LeftForward()
{
    gpioWrite(LEFT1, 1);
    gpioWrite(LEFT2, 0);
}

void LeftBackward()
{
    gpioWrite(LEFT1, 0);
    gpioWrite(LEFT2, 1);
}

void LeftStop()
{
    gpioWrite(LEFT1, 0);
    gpioWrite(LEFT2, 0);
}

void RightForward()
{
    gpioWrite(RIGHT1, 1);
    gpioWrite(RIGHT2, 0);
}

void RightBackward()
{
    gpioWrite(RIGHT1, 0);
    gpioWrite(RIGHT2, 1);
}

void RightStop()
{
    gpioWrite(RIGHT1, 0);
    gpioWrite(RIGHT2, 0);
}

void DriveControl(bool left, bool right)
{
    if (right) {
        RightForward();
    }
    else {
        RightStop();
    }
    if (left) {
        LeftForward();
    }
    else {
        LeftStop();
    }
}

void DriveControl(int x, int y, bool fwd, bool reverse)
{
    if ((!fwd && !reverse) || (y < 0 - BUFFER))
    {
        gpioWrite(LEFT1, 0);
        gpioWrite(LEFT2, 0);
        gpioWrite(RIGHT1, 0);
        gpioWrite(RIGHT2, 0);
    }
    else if (reverse) {
        void RightBackward();
        void LeftBackward();
        gpioWrite(RIGHTEN, 1);
        gpioWrite(LEFTEN, 1);
    }
    else
    {
        if (y < 0)
            y = 0;
        LeftForward();
        RightForward();
        gpioWrite(RIGHTEN, 1);
        gpioWrite(LEFTEN, 1);
        /*
        if (x < 0)
        {
            float l2r_ratio = max(abs((float)x/AXIS_RANGE), 1);
            gpioPWM(RIGHTEN, 1024);
            gpioPWM(LEFTEN, (int) (1024 - (l2r_ratio * 1024)));
        }
        else
        {
            float r21_ratio = max(abs((float)x/AXIS_RANGE), 1);
            gpioPWM(LEFTEN, 1024);
            gpioPWM(RIGHTEN, (int) (1024 - (r21_ratio * 1024)));
        }
        */
    }
}
