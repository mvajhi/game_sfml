#pragma once

#include "define.hpp"
#include "window.hpp"
#include "player.hpp"
#include "game_board.hpp"
#include "menu_manager.hpp"

class Game
{
private:
    window the_window;
    Player the_player;
    Game_board the_game_board;
    Menu_manager menu_manager;

    void update_collision();

    // map file
    vector<string> read_map_file(string address_file);
    void proccess_new_block(Vector2f position, char value);
    void proccess_text_map(vector<string> text_map);
    Vector2f convert_text_to_pixle_pos(Vector2f position);

public:
    Game(/* args */);

    RenderWindow &get_window();
    void update();
    void render();
    void handel_event(Event event);
    void handel_keyboard_event(Event event);
    void pre_update();

    // map
    void read_level1();

    void show_menu();
};
