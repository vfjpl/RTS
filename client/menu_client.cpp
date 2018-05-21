#include "menu_client.hpp"
#include "network_client.hpp"
#include "../common/network_opcodes.hpp"

void menu_temp(sf::RenderWindow& win, sf::UdpSocket& socket,const sf::IpAddress& r_ip, unsigned short r_port)
{
    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

    bool quit_menu = false;

    send_packet<<(sf::Uint8)REQUEST_GAME_JOIN;
    socket.send( send_packet, r_ip, r_port );
    send_packet.clear();

    while( !quit_menu )
    {
        while ( !socket.receive( receive_packet, incomming_ip, incomming_port ) )
            network_menu_packet_receive( receive_packet );

        win.clear();
        win.display();

        socket.send( send_packet, r_ip, r_port );
        send_packet.clear();
    }
}
