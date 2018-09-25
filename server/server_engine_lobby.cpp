#include "server_engine.hpp"
#include "../common/network_opcodes.hpp"

void Server_Engine::lobby_logic()
{
    time = clock.restart();
    //check if all players are ready
    bool ready = true;
    for(sf::Uint8 i = 0; i < players.size(); )
    {
        if(players[i].get_network_timeout().asSeconds() > 1)//timeout disconnect
        {
            ready = false;//prevent auto staring when last non ready player timeout disconnect
            players.erase(players.begin() + i);
            packet_to_send << (sf::Uint8)SERVER_PLAYER_DISCONNECTED << i;
            set_all_players_ready_status(false);
            continue;
        }
        ready &= players[i].get_ready_status();//ready true only if all players are ready
        players[i].add_network_timeout(time);
        ++i;
    }

    if( ready && players.size() > 0 )//prevent starting when there are no players in lobby
    {
        game_loop = true;
    }
}
