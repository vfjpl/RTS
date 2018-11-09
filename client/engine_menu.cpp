#include "engine.hpp"
#include "menu.hpp"

extern sf::RenderWindow window;
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
        case sf::Event::Resized:
        {
            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            break;
        }
        case sf::Event::TextEntered:
        {
            menu.text_entered(event);
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            menu.mouse_click(window);
            break;
        }
        case sf::Event::MouseMoved:
        {
            menu.mouse_move(window);
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
    menu.draw(window);
    window.display();
}
