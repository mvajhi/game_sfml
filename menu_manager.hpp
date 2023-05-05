#pragma once

#include "define.hpp"
#include "button.hpp"
#include "menu.hpp"

class Game;

class Menu_manager
{
private:
    RenderWindow &window;
    Game *game;
    
    Menu *start_menu;
    Menu *level_menu;

    Font font;
    Texture backgroundTexture;
    int available_page;

    Menu *find_avail_page();

    //initialize
    void initialize_level_menu();
    void initialize_start_menu();

public:
    Menu_manager(Game *the_game, RenderWindow &the_window);
    ~Menu_manager();
    void show_menu(int page);

};