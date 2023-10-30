#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <libevdev-1.0/libevdev/libevdev.h>

#define EVENTFILE "/dev/input/event2"
    
struct libevdev *dev;
int fd;

void evdevEnable()
{
    int rc = 1;
    fd = open(EVENTFILE, O_RDONLY|O_NONBLOCK);
	if (fd == -1) {
		fprintf(stderr, "Error opening event file: %s\n", strerror(-fd));
	}  
    rc = libevdev_new_from_fd(fd, &dev);
	if (rc != 0) {
		fprintf(stderr, "Error fetching the device info: %s\n", strerror(-rc));
	}
    printf("Input device name: \"%s\" ready\n", libevdev_get_name(dev));
}

void evdevDestroy()
{
    libevdev_free(dev);
    close(fd);
}
