#include <SFML/Network.hpp>
#include <iostream>

#include "../common/network_opcodes.hpp"

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
            sf::Uint8 opcode;
            receive_packet >> opcode;

            switch( opcode )
            {
            case MOVE_UNIT:
            {
                sf::Uint8 ID_jednostki;
                sf::Uint16 x;
                sf::Uint16 y;
                receive_packet >> ID_jednostki >> x >> y;
                break;
            }
            case ATTACK:
            {
                sf::Uint8 ID_naszej;
                sf::Uint8 ID_atakowanej;
                receive_packet >> ID_naszej >> ID_atakowanej;
                break;
            }
            case CREATE_UNIT:
            {
                sf::Uint8 ID_budynku;
                sf::Uint8 LISTA_jednostki;
                receive_packet >> ID_budynku >> LISTA_jednostki;
                break;
            }
            case CREATE_BUILDING:
            {
                sf::Uint8 LISTA_budynku;
                sf::Uint16 x;
                sf::Uint16 y;
                receive_packet >> LISTA_budynku >> x >> y;
                break;
            }
            default:
            {
                break;
            }
            }//end switch
        }


        socket.send( send_packet, incomming_ip, incomming_port );
        send_packet.clear();
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return EXIT_SUCCESS;
}
