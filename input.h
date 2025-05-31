#ifndef INPUT_H
#define INPUT_H

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

inline void setNonBlocking(bool val)
{
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if (val)
    {
        ttystate.c_lflag &= ~(ICANON | ECHO);
        ttystate.c_cc[VMIN] = 1;
    }
    else
    {
        ttystate.c_lflag |= ICANON | ECHO;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    int flags = fcntl(STDIN_FILENO, F_GETFL);
    if (val)
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    else
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

#endif