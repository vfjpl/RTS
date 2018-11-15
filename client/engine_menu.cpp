#include "engine.hpp"
#include "resources_manager.hpp"
#include "menu.hpp"

extern sf::RenderWindow window;
extern Resources_Manager resources_manager;
extern Menu menu;

void Client_Engine::menu_logic()
{
    time = clock.restart();
}

void Client_Engine::menu_draw_frame()
{
    window.clear();
    window.draw(resources_manager.get_background());
    menu.draw();
    window.display();
}

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
