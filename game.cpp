#include "game.hpp"
#include <fstream>

void Game::update_collision()
{
    // if (the_player.get_global_bound().top + the_player.get_global_bound().height > the_window.get_window().getSize().y)
    // {
    //     the_player.reset_velocity_y();
    //     the_player.set_position(the_player.get_global_bound().left ,
    //                             the_window.get_window().getSize().y - the_player.get_global_bound().height / 2);
    // }

    vector<FloatRect> floors = the_game_board.get_floors_bound();
    for (auto floor : floors)
    {
        if (floor.intersects(the_player.get_global_bound()))
        {
            float dx = the_player.get_position().x - the_player.get_pre_position().x;
            float dy = the_player.get_position().y - the_player.get_pre_position().y;

            if (std::abs(dx) > std::abs(dy))
            {
                if (dx > 0)
                {
                    // حرکت به سمت راست
                }
                else
                {
                    // حرکت به سمت چپ
                }
            }
            else
            {
                if (dy > 0)
                {
                    // حرکت به سمت پایین
                    // cout << the_player.get_global_bound().height << "floor got up\n";
                    the_player.reset_velocity_y();
                    the_player.set_position(the_player.get_global_bound().left,
                                            floor.top - the_player.get_global_bound().height);
                }
                else
                {
                    // حرکت به سمت بالا
                }
            }
            if (dy > 0)
            {
                // حرکت به سمت پایین
                // cout << the_player.get_global_bound().height << "floor got up\n";
                the_player.reset_velocity_y();
                the_player.set_position(the_player.get_global_bound().left,
                                        floor.top - the_player.get_global_bound().height);
            }
        }

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
    }
}

Game::Game() : the_window(900, 600, "game", this),
               the_player(PLAYER_IMG),
               menu_manager(this, the_window.get_window())
{
    menu_manager.show_menu(START_MENU);
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
}

void Game::render()
{
    vector<Sprite> sprites = the_game_board.get_board();
    sprites.push_back(the_player.get_sprite());
    the_window.render(sprites, the_player.get_position());
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

