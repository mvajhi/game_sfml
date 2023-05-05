#pragma once

#include "define.hpp"

class Game;

class window
{
private:
    RenderWindow the_window;
    Game *the_game;

public:
    window(int page_width, int page_hight, string page_name, Game* game);
    RenderWindow &get_window();
    void get_events();
    void close();
    void render(vector<Sprite> sprites, Vector2f camera_position);
};