#include "input_client.hpp"

void input_keypressed(const sf::Event& event, bool& quit_game, bool& quit)
{
    switch(event.key.code)
    {
    case sf::Keyboard::Escape:
    {
        quit_game = true;
        quit = true;
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}

void input_mousebuttonpressed(const sf::Event& event, bool& quit_game, bool& quit)
{
    switch(event.mouseButton.button)
    {
    case sf::Mouse::Middle:
    {
        quit_game = true;
        quit = true;
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}

void input_receive(const sf::Event& event, bool& quit_game, bool& quit)
{
    switch(event.type)
    {
    case sf::Event::Closed:
    {
        quit_game = true;
        quit = true;
        break;
    }
    case sf::Event::KeyPressed:
    {
        input_keypressed( event, quit_game, quit );
        break;
    }
    case sf::Event::MouseButtonPressed:
    {
        input_mousebuttonpressed( event, quit_game, quit );
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}

void input_menu_receive(const sf::Event& event, bool& quit_menu, bool& quit, bool& quit_game)
{
    switch(event.type)
    {
    case sf::Event::Closed:
    {
        quit = true;
        quit_game = true;
        quit_menu = true;
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}
