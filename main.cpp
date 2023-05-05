#include "define.hpp"
#include "game.hpp"

int main()
{
    Game game;

    game.read_level1();
    while (game.get_window().isOpen())
    {
        game.pre_update();
        game.update();
        game.render();
    }


    return 0;
}