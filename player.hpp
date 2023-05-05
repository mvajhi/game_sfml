#pragma once

#include "define.hpp"

class Player
{
private:
    Sprite sprite;
    Texture texture;

    // anime
    IntRect move_frame;
    Clock animation_clock;
    IntRect IDL_frame;
    int anime_state;
    int last_anime_state;
    bool have_move;

    void update_animation();
    void update_left_animation();
    void update_right_animation();

    // move
    Vector2f pre_position;
    Vector2f velocity;
    float velocity_min;
    float velocity_max;
    float acceleration;
    float drag;
    float gravity;

    void update_move();
    void move(Vector2f dir);
    int score;
    int health;

public:
    Player(string texture_file_addr);
    void move_handel(int direct);
    void update();
    Sprite get_sprite();
    Vector2f get_position();
    void set_spawn(float x, float y);
    void save_pre_position();
    Vector2f get_pre_position();
    Vector2f get_velocity();

    // collision
    FloatRect get_global_bound();
    void reset_velocity_y();
    void reset_velocity_x();
    void set_position(float x, float y);
    void move(float x, float y);
    int get_score();
    int get_health();
};
