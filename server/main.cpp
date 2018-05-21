#include "lobby_server.hpp"
#include "network_server.hpp"

int main()
{
    bool quit = false;
    sf::UdpSocket socket;
    socket.bind(7000);

    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

    std::vector<Player> players;
//---------------------------------------------------------------------------------------------------------------------//
    while( !quit )
    {
        lobby_server(socket, players);

        sf::Clock clock;
        sf::Time time;
        bool quit_game = false;
        while( !quit_game )//pętla gry
        {
            for(sf::Uint8 i=0; i <= players.size(); i++)
            {
                socket.receive( receive_packet, incomming_ip, incomming_port );
                network_packet_receive( receive_packet );
            }


            for(sf::Uint8 i=0; i < players.size(); i++)
                socket.send( send_packet, players[i].get_ip(), players[i].get_port() );
            send_packet.clear();
        }//pętla gry
    }
//---------------------------------------------------------------------------------------------------------------------//
    return EXIT_SUCCESS;
}
