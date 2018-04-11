#include <SFML/Network.hpp>
#include <iostream>

#ifdef linux
    #include <getopt.h>
#endif // linux

void print_help()
{
    std::cout<<"-p  --port      default 7000\n"
             "-h  --help      this message\n";
}

int main(int argc, char** argv)
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //zmienne które można modyfikować argumentami z konsoli
    unsigned short local_port = 7000;

#ifdef linux
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
                local_port = std::stoul( optarg, NULL, 0 );
                break;
            case 'h':
                std::cout<<argv[0]<<"\n";
                print_help();
                return 0;
            case '?':
                return 0;
            case ':':
                return 0;
            }
        }
    }
#endif // linux
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool quit = false;
    sf::UdpSocket socket;
    socket.bind( local_port );

    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Time time;
    sf::Clock clock;
    while( !quit )
    {
        socket.receive( receive_packet, incomming_ip, incomming_port );
        time = clock.restart();

        //obsługa pakietu
        while( !receive_packet.endOfPacket() )
        {
            sf::Uint8 command;
            receive_packet >> command;

            switch( command )
            {
            case 1:
                std::cout<<"New Player!\n";
                break;
            default:
                break;
            }
        }


        socket.send( send_packet, incomming_ip, incomming_port );
        send_packet.clear();
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return EXIT_SUCCESS;
}
