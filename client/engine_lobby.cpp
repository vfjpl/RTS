#include "engine.hpp"
#include "network_data.hpp"

extern Network_Data server;

void Client_Engine::lobby_receive_inputs()
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
        default:
        {
            break;
        }
        }//end switch
    }
}

void Client_Engine::lobby_logic()
{
    time = clock.restart();
    if(server.get_network_timeout().asSeconds() > 1)
    {
        return_to_menu();
        return;
    }
    server.add_network_timeout(time);
}
