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
    Text score;
    Text health;
    Font font;
    Texture t_pause;
    Sprite pause;

    //collision
    void update_collisions();
    void collision_player_and_floors();
    void collision_player_and_scores();
    void check_2_shape_collision(Vector2f person_pos, Vector2f object_pos,bool report[] , Vector2f move_size);
    void check_vertical_collision(FloatRect floor, float dy);
    void check_horizontal_collision(FloatRect floor, float dx);
    bool can_jump();

    // map file
    vector<string> read_map_file(string address_file);
    void proccess_new_block(Vector2f position, char value);
    void proccess_text_map(vector<string> text_map);
    Vector2f convert_text_to_pixle_pos(Vector2f position);

    //display
    vector<Drawable *> sprites_to_drawables_ptr(vector<Sprite> &sprites);
    
    //score
    string show_score();
    string show_health();
    void set_score_and_health();

    //initilaize
    void initilaize_font();

    //events_handel
    void handel_keyboard_event(Event event);
    void handel_mouse_event(Event event);

public:
    Game(/* args */);

    RenderWindow &get_window();
    void update();
    void render();
    void handel_event(Event event);
    void pre_update();

    // map
    void read_level1();

    void show_menu();
};
