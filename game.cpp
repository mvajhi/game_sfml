#include "game.hpp"
#include <fstream>
#include <bits/stdc++.h>

void Game::check_2_shape_collision(Vector2f person_pos, Vector2f object_pos, bool report[], Vector2f move_size)
{
    float x = object_pos.x;
    float y = object_pos.y;

    if (person_pos.y <= y && y < person_pos.y + BLOCK_SIZE &&
        x <= person_pos.x + move_size.x + BLOCK_SIZE && person_pos.x + move_size.x + BLOCK_SIZE < x + BLOCK_SIZE)
    {
        // cout << "right\n";
        report[RIGHT] = true;
    }

    if (person_pos.x - BLOCK_SIZE <= x && x < person_pos.x + BLOCK_SIZE && y <= person_pos.y + move_size.y + BLOCK_SIZE && person_pos.y + move_size.y + BLOCK_SIZE < y + BLOCK_SIZE)
    {
        // cout << "down\n";
        report[DOWN] = true;
    }

    if (person_pos.y <= y && y < person_pos.y + BLOCK_SIZE &&
        x < person_pos.x - move_size.x && person_pos.x - move_size.x <= x + BLOCK_SIZE)
    {
        // cout << "left\n";
        report[LEFT] = true;
    }

    if (person_pos.x - BLOCK_SIZE <= x && x < person_pos.x + BLOCK_SIZE &&
        y - BLOCK_SIZE < person_pos.y - move_size.y - BLOCK_SIZE && person_pos.y - move_size.y - BLOCK_SIZE <= y)
    {
        // cout << "up\n";
        report[UP] = true;
    }
}

void Game::check_vertical_collision(FloatRect floor, float dy)
{
    bool report[4] = {false, false, false, false};

    check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 3));
    if (report[DOWN])
    {
        the_player.reset_velocity_y();
        // the_player.set_position(the_player.get_global_bound().left,
        //                         floor.top - the_player.get_global_bound().height);
        the_player.set_position(the_player.get_position().x,
                                the_player.get_position().y - dy);
    }

    check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 0));
    if (report[UP])
    {
        the_player.reset_velocity_y();
        the_player.set_position(the_player.get_position().x,
                                floor.top + the_player.get_global_bound().height + 10);
        // the_player.set_position(the_player.get_position().x,
        //                         the_player.get_position().y - dy);
    }
}

void Game::check_horizontal_collision(FloatRect floor, float dx)
{
    bool report[4] = {false, false, false, false};

    check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 0));
    if (report[RIGHT])
    {
        the_player.reset_velocity_x();
        the_player.set_position(the_player.get_position().x - dx,
                                the_player.get_position().y);
    }

    check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 0));
    if (report[LEFT])
    {
        the_player.reset_velocity_x();
        the_player.set_position(the_player.get_position().x - dx,
                                the_player.get_position().y);
    }
}

void Game::update_collisions()
{
    // if (the_player.get_global_bound().top + the_player.get_global_bound().height > the_window.get_window().getSize().y)
    // {
    //     the_player.reset_velocity_y();
    //     the_player.set_position(the_player.get_global_bound().left ,
    //                             the_window.get_window().getSize().y - the_player.get_global_bound().height / 2);
    // }
    // vector<FloatRect> floors = the_game_board.get_floors_bound();
    // for (auto floor : floors)
    // {
    //     if (floor.intersects(the_player.get_global_bound()))
    //     {
    //         float dx = the_player.get_position().x - the_player.get_pre_position().x;
    //         float dy = the_player.get_position().y - the_player.get_pre_position().y;
    //         if (std::abs(dx) > std::abs(dy))
    //         {
    //             if (dx > 0)
    //             {
    //                 // حرکت به سمت راست
    //             }
    //             else
    //             {
    //                 // حرکت به سمت چپ
    //             }
    //         }
    //         else
    //         {
    //             if (dy > 0)
    //             {
    //                 // حرکت به سمت پایین
    //                 // cout << the_player.get_global_bound().height << "floor got up\n";
    //                 the_player.reset_velocity_y();
    //                 the_player.set_position(the_player.get_global_bound().left,
    //                                         floor.top - the_player.get_global_bound().height);
    //             }
    //             else
    //             {
    //                 // حرکت به سمت بالا
    //             }
    //         }
    //         if (dy > 0)
    //         {
    //             // حرکت به سمت پایین
    //             // cout << the_player.get_global_bound().height << "floor got up\n";
    //             the_player.reset_velocity_y();
    //             the_player.set_position(the_player.get_global_bound().left,
    //                                     floor.top - the_player.get_global_bound().height);
    //         }
    //     }
    // if (
    //     (
    //         (
    //             floor.top <= the_player.get_global_bound().top &&
    //             the_player.get_global_bound().top <= floor.top + floor.height
    //         )
    //         ||
    //         (
    //             floor.top <= the_player.get_global_bound().top + the_player.get_global_bound().height &&
    //             the_player.get_global_bound().top + the_player.get_global_bound().height <= floor.top + floor.height
    //         )
    //     ) &&
    //     floor.intersects(the_player.get_global_bound()) &&
    //     true)
    // {
    //     cout << the_player.get_global_bound().width << "wall got up\n";
    //     the_player.reset_velocity_x();
    //     the_player.set_position(floor.left + the_player.get_global_bound().width ,
    //                             the_player.get_position().y
    //                              );
    // }
    //     if (
    //         (
    //             (
    //                 floor.left < the_player.get_global_bound().left &&
    //                 the_player.get_global_bound().left < floor.left + floor.width
    //             )
    //             ||
    //             (
    //                 floor.left < the_player.get_global_bound().left + the_player.get_global_bound().width &&
    //              the_player.get_global_bound().left + the_player.get_global_bound().width < floor.left + floor.width
    //             )
    //         ) &&
    //         // the_player.get_global_bound().top > floor.top &&
    //         floor.intersects(the_player.get_global_bound()) &&
    //         // the_player.get_global_bound().top + the_player.get_global_bound().height > floor.top + floor.height &&
    //         // the_player.get_global_bound().top + the_player.get_global_bound().height > floor.top &&
    //         true)
    //     {
    //         cout << the_player.get_global_bound().height << "floor got up\n";
    //         the_player.reset_velocity_y();
    //         the_player.set_position(the_player.get_global_bound().left,
    //                                 floor.top - the_player.get_global_bound().height );
    //     }
    // }

    vector<FloatRect> floors = the_game_board.get_floors_bound();
    for (auto floor : floors)
    {
        float dx = the_player.get_position().x - the_player.get_pre_position().x;
        float dy = the_player.get_position().y - the_player.get_pre_position().y;
        check_horizontal_collision(floor, dx);
        check_vertical_collision(floor, dy);
    }
}

Game::Game() : the_window(WINDOW_W, WINDOW_H, "game", this),
               the_player(PLAYER_IMG),
               menu_manager(this, the_window.get_window())
{
    menu_manager.show_menu(START_MENU);

    initilaize_font();
}

RenderWindow &Game::get_window()
{
    return the_window.get_window();
}

void Game::update()
{
    the_window.get_events();
    the_player.update();
    update_collision();
    set_score_and_health();
}

void Game::render()
{
    vector<Sprite> sprites = the_game_board.get_board();
    sprites.push_back(the_player.get_sprite());
    vector<Drawable *> output = sprites_to_drawables_ptr(sprites);
    output.push_back(&score);
    output.push_back(&health);
    the_window.render(output, the_player.get_position());
}

void Game::handel_event(Event event)
{
    if (event.type == Event::Closed)
        the_window.close();
    else if (event.type == Event::KeyPressed)
        handel_keyboard_event(event);
}

void Game::handel_keyboard_event(Event event)
{
    if (event.key.code == Keyboard::Escape)
        the_window.close();
    else if (event.key.code == Keyboard::D)
        the_player.move_handel(RIGHT);
    else if (event.key.code == Keyboard::A)
        the_player.move_handel(LEFT);
    else if (event.key.code == Keyboard::W)
        the_player.move_handel(UP);
    else if (event.key.code == Keyboard::S)
        the_player.move_handel(DOWN);
}

void Game::pre_update()
{
    the_player.save_pre_position();
}

void Game::read_level1()
{
    vector<string> text_map = read_map_file(MAP_L1);

    proccess_text_map(text_map);
}

void Game::show_menu()
{
    menu_manager.show_menu(START_MENU);
}

vector<string> Game::read_map_file(string address_file)
{
    ifstream board_file(address_file);
    string line;
    vector<string> output;
    while (getline(board_file, line))
        output.push_back(line);
    return output;
}

void Game::proccess_new_block(Vector2f position, char value)
{
    position = convert_text_to_pixle_pos(position);

    if (value == FLOOR_MAP_SYMBOLE)
        the_game_board.add_new_floor(position);
    // TODO
    else if (value == PLAYER_MAP_SYMBOLE)
        the_player.set_spawn(position.x, position.y);
    // the_player.set_position(position.x, position.y);
    // else if (value == PLAYER_MAP_SYMBOLE)
    // TODO
}

void Game::proccess_text_map(vector<string> text_map)
{
    for (size_t y = 0; y < text_map.size(); y++)
        for (size_t x = 0; x < text_map[y].length(); x++)
            proccess_new_block(Vector2f(x, y), text_map[y][x]);
}

Vector2f Game::convert_text_to_pixle_pos(Vector2f position)
{
    return Vector2f((position.x + 10.5) * BLOCK_SIZE, (position.y + 0.5) * BLOCK_SIZE);
}
vector<Drawable *> Game::sprites_to_drawables_ptr(vector<Sprite> &sprites)
{
    vector<Drawable *> output;
    for (size_t i = 0; i < sprites.size(); i++)
        output.push_back(&sprites[i]);
    return output;
}
string Game::show_score()
{
    int score_val = the_player.get_score();
    return "score : " + to_string(score_val);
}
string Game::show_health()
{
    int health_val = the_player.get_health();
    return "health : " + to_string(health_val);
}
void Game::set_score_and_health()
{
    score.setString(show_score());
    score.setOrigin(score.getGlobalBounds().width/2,score.getGlobalBounds().height/2);
    score.setPosition(the_player.get_position() + Vector2f(0, - WINDOW_H / 2 + BLOCK_SIZE / 2));
    health.setString(show_health());
    health.setOrigin(score.getGlobalBounds().width/2,score.getGlobalBounds().height/2);
    health.setPosition(the_player.get_position() + Vector2f(WINDOW_W / 2 - BLOCK_SIZE * 3 / 2, - WINDOW_H / 2 + BLOCK_SIZE / 2));

}

void Game::initilaize_font()
{
    font.loadFromFile(ADDR_FONT_2);
    score.setFont(font);
    score.setCharacterSize(FONT_SIZE);
    score.setFillColor(FONT_COLOR);
    health.setFont(font);
    health.setCharacterSize(FONT_SIZE);
    health.setFillColor(FONT_COLOR);
}
