
#include <iostream>
#include <cstdlib>
#include <unistd.h>

enum Piece
{
    EMPTY,
    P1,
    P2
};

enum State
{
    IDLE,
    W1,
    W2,
    DRAW
};

class Board
{
public:
    Piece board[3][3];
    Board()
    {
        for (int i; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                this->board[i][j] = EMPTY;
            }
        }
    }
};

class Game
{
private:
    Board b = Board{};
    bool isPlayerOneTurn = true;

public:
    Game()
    {
        main();
    };
    void main()
    {
        init();
        loop();
    };
    void init()
    {
        update();
    };
    void update()
    {
        clean();
        render();
    };
    void clean()
    {
        system("clear");
    }
    void render()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                renderPiece(this->b.board[i][j]);
            }
            std::cout << std::endl;
        }
    };
    void renderPiece(Piece p)
    {
        switch (p)
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
    };
    void onCharInput(char c)
    {
        if (c >= '0' && c <= '9')
        {
            std::cout << c << std::endl;
            int n = c - '0';
            int r = (n == 1) ? 0 : (n - 1) / 3;
            int c = (n - 1) % 3;

            this->b.board[r][c] = isPlayerOneTurn ? P1 : P2;
            this->isPlayerOneTurn = !isPlayerOneTurn;
        }
    };
    void loop()
    {
        while (true)
        {
            char c = getchar();
            if (c != EOF)
            {
                if (c == 'q')
                    break;
                onCharInput(c);
                update();
            }
        }
    };
};