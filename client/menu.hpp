#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include "resources_manager.hpp"
#include "network_data.hpp"
#include <deque>

extern Resources_Manager resources_manager;
extern Network_Data server;

class Menu
{
    //sort from largest to smallest!
    std::deque <sf::Text> m_texts;//80
    sf::Uint8 m_state;//1

public:
    void init();
    void clear();

    void draw(sf::RenderWindow& window);
    sf::Uint8 click(const sf::Event& event);

    void debug_show_size() const;

private:
    sf::Uint8 get_text_id_from_mousepress(const sf::Event& event) const;

    void main_menu();
    void connect_menu();
    void authors_menu();
};

#endif // MENU_HPP_INCLUDED
