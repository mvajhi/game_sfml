#include "menu_manager.hpp"
#include "game.hpp"

Menu_manager::Menu_manager(Game *the_game, RenderWindow &the_window)
    : window(the_window)
{
    game = the_game;

    font.loadFromFile(ADDR_FONT);
    backgroundTexture.loadFromFile(BACKGROUND_IMG);
    available_page = START_MENU;

    start_menu = new Menu(window, font, MENU_POS, backgroundTexture);
    level_menu = new Menu(window, font, MENU_POS, backgroundTexture);
    pause_menu = new Menu(window, font, MENU_POS, backgroundTexture);

    initialize_level_menu();
    initialize_start_menu();
    initialize_pause_menu();
}

Menu_manager::~Menu_manager()
{
    delete (start_menu);
    delete (level_menu);
}

void Menu_manager::show_menu(int page = DEFAULT_PAGE)
{
    available_page = page;

    while (window.isOpen())
    {
        if (available_page == SHOW_GAME)
            break;

        Menu *page = find_avail_page();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else
            {
                page->handle_event(event);
            }
        }

        window.clear();

        page->draw();

        window.setView(View(Vector2f(WINDOW_W / 2, WINDOW_H / 2), Vector2f(900, 600)));
        window.display();
    }
}

Menu *Menu_manager::find_avail_page()
{
    switch (available_page)
    {
    case START_MENU:
        return start_menu;
        break;
    case LEVEL_MENU:
        return level_menu;
        break;
    case PAUSE_MENU:
        return pause_menu;
        break;

    default:
        break;
    }
    return nullptr;
}

void Menu_manager::initialize_level_menu()
{

    Game *the_game = game;

    int &avail_menu = available_page;
    level_menu->add_button("level 1", [&the_game, &avail_menu]()
                           { cout << "level 1" << endl;
                           avail_menu = SHOW_GAME; });

    level_menu->add_button("level 2", []()
                           { cout << "level 2" << endl; });

    level_menu->add_button("return", [&avail_menu]()
                           { avail_menu = START_MENU; });
}

void Menu_manager::initialize_start_menu()
{
    int &avail_menu = available_page;
    start_menu->add_button("Start", [&avail_menu]()
                           { avail_menu = LEVEL_MENU; });

    auto &the_window = window;
    start_menu->add_button("Exit", [&the_window]()
                           { the_window.close(); });
}

void Menu_manager::initialize_pause_menu()
{
    int &avail_menu = available_page;
    pause_menu->add_button("Continue", [&avail_menu]()
                           { avail_menu = SHOW_GAME; });
    // TODO reset level
    pause_menu->add_button("return", [&avail_menu]()
                           { avail_menu = LEVEL_MENU; });
}
