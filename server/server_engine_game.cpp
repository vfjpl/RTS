#include "server_engine.hpp"
#include "../common/network_opcodes.hpp"

void Server_Engine::game_logic()
{
    time = clock.restart();
    for(sf::Uint8 i = 0; i < players.size(); )
    {
        if(players[i].get_network_timeout().asSeconds() > 1)//timeout disconnect
        {
            players.erase(players.begin() + i);
            packet_to_send << (sf::Uint8)SERVER_PLAYER_DISCONNECTED << i;
            continue;
        }
        players[i].add_network_timeout(time);
        ++i;
    }

    //TEMP: quit game as soon as it starts
    game_loop = false;
    packet_to_send << (sf::Uint8)SERVER_GAME_STATUS << false;
    set_all_players_ready_status(false);
}
