#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void setNonBlocking(bool enable)
{
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    if (enable)
    {
        ttystate.c_lflag &= ~ICANON; // disable buffered I/O
        ttystate.c_lflag &= ~ECHO;   // turn off echo
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    }
    else
    {
        ttystate.c_lflag |= ICANON;
        ttystate.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    }
}

enum Piece
{
    EMPTY,
    P1,
    P2
};

struct Board
{
    Piece board[3][3];
};

void tick(Board b)
{
    system("clear");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            switch (b.board[i][j])
            {
            case EMPTY:
                std::cout << "#";
                break;
            case P1:
                std::cout << "X";
                break;
            case P2:
                std::cout << "O";
                break;
            }
        }
        std::cout << std::endl;
    }
}

void event(char c, Board *b, bool isTurn)
{
    if (c >= '0' && c <= '9')
    {
        int n = c - '0';
        int r = (n == 1) ? 0 : (n - 1) / 3;
        int c = (n - 1) % 3;
        (*b).board[r][c] = isTurn ? P1 : P2;
    }
}

void start()
{
    Board b;
    bool turn = true;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            b.board[i][j] = EMPTY;

    char ch;
    tick(b);
    while (true)
    {
        ch = getchar();
        if (ch != EOF)
        {
            if (ch == 'q')
                break;
            event(ch, &b, turn);
            turn = !turn;
            tick(b);
        }
    }
}

int main()
{
    setNonBlocking(true);
    start();
    setNonBlocking(false);
    return 0;
}
