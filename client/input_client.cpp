#include "input_client.hpp"

void input_keypresset(sf::Event& event, bool& quit_game, bool& quit)
{
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            quit_game = true;
            quit = true;
            break;
        default:
            break;
        }
}

void input_receive(sf::Event& event, bool& quit_game, bool& quit)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        quit_game = true;
        quit = true;
        break;
    case sf::Event::KeyPressed:
        input_keypresset( event, quit_game, quit );
        break;
    case sf::Event::MouseButtonPressed:
        break;
    default:
        break;
    }
}
