#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include <deque>

enum Menus
{
    MENUS_NONE = -1,
    MENUS_MAIN_MENU,
    MENUS_CONNECT_MENU,
    MENUS_AUTHORS_MENU
};

enum Main_Menu_Buttons
{
    MAIN_NONE_BUTTON = -1,
    MAIN_CONNECT_BUTTON,
    MAIN_AUTHORS_BUTTON,
    MAIN_QUIT_BUTTON
};

enum Connect_Menu_Buttons
{
    CONNECT_NONE_BUTTON = -1,
    CONNECT_CONNECT_BUTTON,
    CONNECT_BACK_BUTTON
};

enum Authors_Menu_Buttons
{
    AUTHORS_NONE_BUTTON = -1,
    AUTHORS_BACK_BUTTON
};

class Menu
{
    //sort from largest to smallest!
    std::deque <sf::Text> m_texts;//80
    Menus m_state;//0
    bool m_exit;//false
    bool m_start;//false

public:
    void clear();

    void main_menu();
    void connect_menu();
    void authors_menu();

    void draw(sf::RenderWindow& window);

    void debug_show_size() const;

    void click(const sf::Event& event);

    bool isExiting();
    bool isStarting();

private:
    void add_author_text(sf::String author_name);

    sf::Uint8 get_text_id_from_mousepress(const sf::Event& event) const;
};

#endif // MENU_HPP_INCLUDED
