#include "engine.hpp"

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
            switch(menu.click(event))
            {
            case 1://quit
            {
                quit_engine();
                break;
            }
            case 2://connect
            {
                menu.clear();
                lobby_loop = true;
                break;
            }
            }//end switch
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
}
