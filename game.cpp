
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>

enum Piece
{
    EMPTY = 1,
    P1 = 2,
    P2 = 3
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
                this->board[i][j] = Piece::EMPTY;
            }
        }
    }
};

class Game
{
private:
    Board b = Board{};
    bool isPlayerOneTurn = true;
    State s = State::IDLE;

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
        updateGameState();
        render();
    };
    void clean()
    {
        system("clear");
    }
    void render()
    {
        renderHeader();
        renderBoard();
        renderFooter();
    };

    void renderFooter()
    {
        std::cout << renderGameState() << std::endl;
    }

    void renderHeader()
    {
        std::cout << "Player " << (this->isPlayerOneTurn ? "1" : "2") << "'s turn" << std::endl;
    }

    void renderBoard()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                renderPiece(this->b.board[i][j]);
            }
            std::cout << std::endl;
        }
    }
    void renderPiece(Piece p)
    {
        switch (p)
        {
        case Piece::EMPTY:
            std::cout << "#";
            break;
        case Piece::P1:
            std::cout << "X";
            break;
        case Piece::P2:
            std::cout << "O";
            break;
        }
    };

    void updateGameState()
    {
        int col[3] = {1, 1, 1};
        bool draw = true;

        for (int i = 0; i < 3; i++)
        {
            int row = 1;
            for (int j = 0; j < 3; j++)
            {
                row *= this->b.board[i][j];
                col[j] *= this->b.board[i][j];
                if (this->b.board[i][j] == Piece::EMPTY)
                {
                    draw = false;
                }
            }
            if (row == pow(Piece::P1, 3))
            {
                this->s = State::W1;
                return;
            }
            if (row == pow(Piece::P2, 3))
            {
                this->s = State::W2;
                return;
            }
        }
        if (draw)
        {
            this->s = State::DRAW;
            return;
        }

        for (auto &&i : col)
        {
            if (i == pow(Piece::P1, 3))
            {
                this->s = State::W1;
                return;
            }
            if (i == pow(Piece::P2, 3))
            {
                this->s = State::W2;
                return;
            }
        }
    }

    std::string renderGameState()
    {
        switch (this->s)
        {
        case State::IDLE:
            return "IDLE";
        case State::DRAW:
            return "DRAW";
        case State::W1:
            return "W1";
        case State::W2:
            return "W2";
        default:
            return "IDLE";
        };

        return "IDLE";
    }

    void onCharInput(char c)
    {
        if (c >= '0' && c <= '9')
        {
            std::cout << c << std::endl;
            int n = c - '0';
            int r = (n == 1) ? 0 : (n - 1) / 3;
            int c = (n - 1) % 3;

            this->b.board[r][c] = isPlayerOneTurn ? Piece::P1 : Piece::P2;
            this->isPlayerOneTurn = !isPlayerOneTurn;
        }
    };
    void loop()
    {
        while (true && this->s == State::IDLE)
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