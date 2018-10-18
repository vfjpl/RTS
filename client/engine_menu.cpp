#include "engine.hpp"
#include "menu.hpp"

extern Menu menu;

void Client_Engine::menu_receive_inputs()
{
    sf::Event event;
    while( window.pollEvent(event) )
    {
        switch(event.type)
        {
        case sf::Event::Closed:
        {
            quit_engine();
            break;
        }
        case sf::Event::TextEntered:
        {
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            menu.mouse_click(event);
            break;
        }
        case sf::Event::MouseMoved:
        {
            menu.mouse_move(event);
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void Client_Engine::menu_logic()
{
    time = clock.restart();
    menu.logic(sf::Mouse::getPosition(window));
}
