#include <SFML/Network.hpp>
#include <iostream>
#include <queue>

#include "../common/network_opcodes.hpp"
#include "../common/unit.hpp"

#ifdef linux
#include <getopt.h>
#endif // linux

void print_help()
{
    std::cout<<"-p  --port      default 7000\n"
             "-h  --help      this message\n";
}
//---------------------------------------------------------------------------------------------------------------------//
int main(int argc, char** argv)
{
    //zmienne które można modyfikować argumentami z konsoli
    unsigned short local_port = 7000;//port na którym aplikacja odbiera połączenia

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
//---------------------------------------------------------------------------------------------------------------------//
    bool quit = false;//główny wyłącznik
    //zmienne sieciowe
    sf::UdpSocket socket;
    socket.bind( local_port );

    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

    //zmienne gry
    std::array <unit, 256> Posible_Units;//TODO: zmienić na klasę blueprint jednostek
    //podczas startu do tej bazy Posible_Units trafiają nasze zaprojektowane jednostki
    //TODO: przegadać gdzie w kodzie/pliku przechowywać nasze zaprojektowane jednostki


    std::array <unit, 256> units;//jednostki w aktualnej grze
    std::queue <sf::Uint8> place;//przechowuje wolne miejsca TODO: pogadać jak to zrobić najepiej
    for(int i = 0; i < 256; i++)
        place.push(i);

    units[place.front()] = Posible_Units[0];//tutaj jest 0 bo to 0 to blueprint np głownej bazy
    units[place.front()].set_position( (1280/32)/2, (800/32)/2 );
    send_packet << ADD_UNIT_TO_GAME << place.front() << units[place.front()].get_x() << units[place.front()].get_y();
    place.pop();//nieintuicyjne .pop() nie zwraca elementu tylko go usuwa
//---------------------------------------------------------------------------------------------------------------------//
    sf::Time time;
    sf::Clock clock;
    while( !quit )
    {
        socket.receive( receive_packet, incomming_ip, incomming_port );
        time = clock.restart();

        //OBSŁUGA PAKIETÓW
        //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        while( !receive_packet.endOfPacket() )
        {
            sf::Uint8 opcode;
            receive_packet >> opcode;

            switch( opcode )
            {
            case MOVE_UNIT:
            {
                sf::Uint8 ID_jednostki;
                sf::Uint8 x;
                sf::Uint8 y;
                receive_packet >> ID_jednostki >> x >> y;

                //na początek teleportowanie jednostki
                units[ID_jednostki].set_position( x, y );
                send_packet << SET_UNIT_POSITION << ID_jednostki << x << y;
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
                sf::Uint8 BP_jednostki;
                receive_packet >> ID_budynku >> BP_jednostki;
                break;
            }
            case CREATE_BUILDING:
            {
                sf::Uint8 BP_budynku;
                sf::Uint8 x;
                sf::Uint8 y;
                receive_packet >> BP_budynku >> x >> y;
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
//---------------------------------------------------------------------------------------------------------------------//
    return EXIT_SUCCESS;
}
//TODO:
//drugi gracz nie dostaje informacji o zmianie pozycji jednostki
