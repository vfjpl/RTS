#include "client_engine.hpp"

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
        //connection to server lost, back to main menu
        lobby_loop = false;
        server.set_network_timeout( sf::Time::Zero );
        setup_menu();
        players.clear();
        return;
    }
    server.add_network_timeout(time);
}
