#include "engine.hpp"
#include "../common/network_opcodes.hpp"

void Server_Engine::game_receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 local_id;
    sf::Uint8 opcode;
    for(sf::Uint8 i = 0; i <= players.size(); ++i)// <= because we are waiting for more players
    {
        socket.receive(received_packet, incomming_ip, incomming_port);
        local_id = get_player_id(incomming_ip, incomming_port);

        if(local_id == players.size())//check if we got new player
        {
            connect_player(incomming_ip, incomming_port);
            packet_to_send << (sf::Uint8)SERVER_GAME_STATUS << true;//inform player that game is started
        }

        players[local_id].reset_network_timeout();
        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch(opcode)
            {
            default:
            {
                received_packet.clear();
                break;
            }
            }//end switch
        }//end while
    }//end for
}

void Server_Engine::game_logic()
{
    time = clock.restart();

    for(sf::Uint8 i = 0; i < players.size(); )
        if(players[i].get_network_timeout() > sf::seconds(1))
            disconnect_player(i);
        else
            players[i++].add_network_timeout(time);
}
