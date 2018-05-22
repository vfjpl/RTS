#ifndef INPUT_CLIENT_HPP_INCLUDED
#define INPUT_CLIENT_HPP_INCLUDED

#include <SFML/Window.hpp>

void input_receive(const sf::Event& event, bool& quit_game, bool& quit);
void input_menu_receive(const sf::Event& event, bool& quit_menu, bool& quit, bool& quit_game);

#endif // INPUT_CLIENT_HPP_INCLUDED
