#include "engine.hpp"

void Server_Engine::game_logic()
{
    time = clock.restart();

    for(sf::Uint8 i = 0; i < players.size(); )
        if(players[i].get_network_timeout() > sf::seconds(1))
            disconnect_player(i);
        else
            players[i++].add_network_timeout(time);
}
