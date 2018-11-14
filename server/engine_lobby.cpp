#include "engine.hpp"
#include "../common/network_opcodes.hpp"

void Server_Engine::lobby_logic()
{
    time = clock.restart();

    bool ready = true;
    for(sf::Uint8 i = 0; i < players.size(); )
    {
        ready &= players[i].get_ready_status();
        if(players[i].get_network_timeout() > sf::seconds(1))
        {
            disconnect_player(i);
            continue;
        }
        players[i].add_network_timeout(time);
        ++i;
    }

    if(ready)
    {
        game_loop = true;
        set_all_players_ready_status(false);
        packet_to_send << (sf::Uint8)SERVER_GAME_STATUS << true;
    }
}
