#include "engine.hpp"
#include "../common/network_opcodes.hpp"

void Server_Engine::game_logic()
{
    time = clock.restart();

    for(sf::Uint8 i = 0; i < players.size(); )
    {
        if(players[i].get_network_timeout() > sf::seconds(1))
        {
            disconnect_player(i);
            continue;
        }
        players[i].add_network_timeout(time);
        ++i;
    }

    //TEMP: quit game as soon as it starts
    game_loop = false;
    packet_to_send << (sf::Uint8)SERVER_GAME_STATUS << false;
}
