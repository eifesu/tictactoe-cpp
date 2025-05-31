#include "input.h"
#include "game.cpp"

int main()
{
    setNonBlocking(true);
    Game g = Game{};
    setNonBlocking(false);
    return 0;
}
