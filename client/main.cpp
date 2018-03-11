#include <SFML/Network.hpp>
#include <iostream>
#include <getopt.h>

int main(int argc, char** argv)
{
    unsigned short port = 8000;

    unsigned short remote_port = 7000;
    sf::IpAddress remote_ip = "localhost";

    {
        int c;

        static struct option longopts[] =
        {
            {"port",       required_argument, NULL, 'p'},
            {"local_port", required_argument, NULL, 'l'},
            {"ip",         required_argument, NULL, 'i'},
            {"help",       no_argument,       NULL, 'h'},
        };

        while( (c = getopt_long( argc, argv, "p:l:i:h", longopts, NULL )) != -1 )
        {
            switch (c)
            {
            case 'p':
                remote_port = std::stoul( optarg, NULL, 0 );
                break;
            case 'l':
                port = std::stoul( optarg, NULL, 0 );
                break;
            case 'i':
                remote_ip = optarg;
                break;
            case 'h':
                std::cout<<argv[0]<<"\n"
                        "-p --port       default 7000\n"
                        "-l --local_port default 8000\n"
                        "-i --ip         default localhost\n"
                        "-h --help       this message\n";
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


    sf::Thread network_thread( [&]()
        {
            while(true)
            {
                socket.receive( receive_packet, incomming_ip, port );
            }
        });

    sf::Time time;
    sf::Clock clock;
    network_thread.launch();
    while(true)
    {
        std::string message;
        std::cin >> message;
        send_packet << message;
        socket.send( send_packet, remote_ip, remote_port );
        send_packet.clear();

        sf::sleep( sf::milliseconds(100) );

        receive_packet >> message;
        std::cout<<message<<"\n";
    }

    return EXIT_SUCCESS;
}
