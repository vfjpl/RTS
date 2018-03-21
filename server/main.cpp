#include <iostream>
#include <getopt.h>

#include "../common/player.hpp"

int main(int argc, char** argv)
{
    unsigned short port = 7000;

    {
        static struct option longopts[] =
        {
            {"port",  required_argument,  NULL,  'p'},
            {"help",  no_argument,        NULL,  'h'},
        };

        int c;
        while( (c = getopt_long( argc, argv, "p:h", longopts, NULL )) != -1 )
        {
            switch (c)
            {
            case 'p':
                port = std::stoul( optarg, NULL, 0 );
                break;
            case 'h':
                std::cout<<argv[0]<<"\n"
                        "-p  --port      default 7000\n"
                        "-h  --help      this message\n";
                return 0;
            case '?':
                return 0;
            case ':':
                return 0;
            }
        }
    }

    sf::UdpSocket socket;
    socket.bind( port );

    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;

    sf::Time time;
    sf::Clock clock;
    while(true)
    {
        socket.receive( receive_packet, incomming_ip, port );
        time = clock.restart();

        send_packet = receive_packet;

        socket.send( send_packet, incomming_ip, port );
        //send_packet.clear();
    }

    return EXIT_SUCCESS;
}
