#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "network_data.hpp"

extern sf::RenderWindow window;
extern Network_Data server;

void Client_Engine::game_receive_packets()
{

}

void Client_Engine::game_logic()
{
    time = clock.restart();

    if(server.get_network_timeout() > sf::seconds(1))
    {
        //setup_menu();//back to menu
        return;
    }
    server.add_network_timeout(time);
}

void Client_Engine::game_draw_frame()
{
    window.clear();
    window.display();
}

void Client_Engine::game_receive_inputs()
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
        default:
        {
            break;
        }
        }//end switch
    }
}
