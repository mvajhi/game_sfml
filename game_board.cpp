#include "game_board.hpp"

Game_board::Game_board(/* args */)
{
        t_floor.loadFromFile(FLOOR_IMG);
        floor.setTexture(t_floor);
        floor.setScale(FLOOR_SCALE, FLOOR_SCALE);

        t_diamond.loadFromFile(DIAMOND_IMG);
        diamond.setTexture(t_diamond);
        diamond.setScale(FLOOR_SCALE,FLOOR_SCALE);
        
        t_star.loadFromFile(STAR_IMG);
        star.setTexture(t_diamond);
        star.setScale(FLOOR_SCALE,FLOOR_SCALE);

        t_portal.loadFromFile(PORTAL_IMG);
        portal.setTexture(t_portal);
        portal.setScale(PORTAL_SCALE, PORTAL_SCALE);

        // FloatRect f_bounds = floor.getGlobalBounds();
        // floor.setOrigin(f_bounds.left + f_bounds.width / 2,
        //                 f_bounds.top + f_bounds.height / 2);
}

void Game_board::add_new_floor(Vector2f position)
{
        Sprite tmp_floor = floor;
        tmp_floor.setPosition(position.x, position.y);
        floors.push_back(tmp_floor);
}
void Game_board::add_new_diamond(Vector2f position)
{
        Sprite tmp_diamond = diamond;
        tmp_diamond.setPosition(position.x,position.y);
        diamonds.push_back(tmp_diamond);
}
void Game_board::add_new_star(Vector2f position)
{
        Sprite tmp_star = star;
        tmp_star.setPosition(position.x,position.y);
        stars.push_back(tmp_star);
}

void Game_board::set_portal(Vector2f position)
{
        portal.setPosition(position);
}

void Game_board::reset_map()
{
        floors.clear();
}

vector<FloatRect> Game_board::get_floors_bound()
{
        vector<FloatRect> board;
        for (size_t i = 0; i < floors.size(); i++)
                board.push_back(floors[i].getGlobalBounds());

        return board;
}

vector<Sprite> Game_board::get_board()
{
        vector<Sprite> output = floors;
        output.push_back(portal);
        return output;
}
