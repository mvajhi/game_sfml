#include "game_board.hpp"

Game_board::Game_board(/* args */)
{
        t_floor.loadFromFile(FLOOR_IMG);
        floor.setTexture(t_floor);
        floor.setScale(FLOOR_SCALE, FLOOR_SCALE);

        t_diamond.loadFromFile(DIAMOND_IMG);
        diamond.setTexture(t_diamond);
        diamond.setScale(DIMEND_SCALE, DIMEND_SCALE);

        t_star.loadFromFile(STAR_IMG);
        star.setTexture(t_star);
        star.setScale(STAR_SCALE, STAR_SCALE);

        t_portal.loadFromFile(PORTAL_IMG);
        portal.setTexture(t_portal);
        portal.setScale(PORTAL_SCALE, PORTAL_SCALE);

        t_boy_turtle.loadFromFile(BOY_TURTLE_IMG);
        boy_turtle.setTexture(t_boy_turtle);
        boy_turtle.setScale(BOY_TURTLE_SCALE,BOY_TURTLE_SCALE);

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
        tmp_diamond.setPosition(position.x, position.y);
        diamonds.push_back(tmp_diamond);
}
void Game_board::add_new_star(Vector2f position)
{
        Sprite tmp_star = star;
        tmp_star.setPosition(position.x, position.y);
        stars.push_back(tmp_star);
}
void Game_board::add_new_boy_turtle(Vector2f position)
{
        Sprite tmp_boy_turtle = boy_turtle;
        tmp_boy_turtle.setPosition(position.x, position.y);
        boy_turtles.push_back(tmp_boy_turtle);                
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
vector<FloatRect> Game_board::get_stars_bound()
{
        vector<FloatRect> stars_;
        for (size_t i = 0; i < stars.size(); i++)
                stars_.push_back(stars[i].getGlobalBounds());

        return stars_;
}
vector<FloatRect> Game_board::get_diamonds_bound()
{
        vector<FloatRect> diamonds_;
        for (size_t i = 0; i < diamonds.size(); i++)
                diamonds_.push_back(diamonds[i].getGlobalBounds());

        return diamonds_;
}
vector<FloatRect> Game_board::get_boy_turtles_bound()
{
        vector<FloatRect> boy_turtles_;
        for (size_t i = 0; i < boy_turtles.size(); i++)
                boy_turtles_.push_back(boy_turtles[i].getGlobalBounds());

        return boy_turtles_;
}
vector<Sprite> Game_board::get_board()
{
        vector<Sprite> output;
        output.reserve(floors.size() + diamonds.size() + stars.size() + boy_turtles.size());
        output.insert(output.end(), floors.begin(), floors.end());
        output.insert(output.end(), diamonds.begin(), diamonds.end());
        output.insert(output.end(), stars.begin(), stars.end());
        output.insert(output.end(), boy_turtles.begin(), boy_turtles.end());

        output.push_back(portal);
        
        return output;
}

void Game_board::remove_dimend(int pos)
{
        diamonds.erase(diamonds.begin() + pos);
}

void Game_board::remove_star(int pos)
{
        stars.erase(stars.begin() + pos);
}
