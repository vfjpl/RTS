#ifndef INPUT_CLIENT_HPP_INCLUDED
#define INPUT_CLIENT_HPP_INCLUDED

#include <SFML/Window.hpp>

void input_receive(sf::Event& event, bool& quit_game, bool& quit);

#endif // INPUT_CLIENT_HPP_INCLUDED
