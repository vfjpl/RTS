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

void Client_Engine::menu_draw_frame()
{
    window.clear();
    //menu.draw(window);
    window.display();
}
