#pragma once
#include "define.hpp"

class Game_board
{
private:
        vector<string> text_map;
        Texture t_floor;
        Sprite floor;
        vector<Sprite> floors;


public:
        Game_board(/* args */);
        void add_new_floor(Vector2f position);
        void reset_map();
        vector<FloatRect> get_floors_bound();
        vector<Sprite> get_board();
};
