#include <sys/ioctl.h>
#include "compatibility_utils.h"

void enable_raw_mode()
{
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
    tcsetattr(0, TCSANOW, &term);
}

void disable_raw_mode()
{
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

bool kbhit()
{
    int bytes_waiting;
    ioctl(0, FIONREAD, &bytes_waiting);
    return bytes_waiting > 0;
}
