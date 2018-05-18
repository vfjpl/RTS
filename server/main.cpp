#include <SFML/Network.hpp>
#include <iostream>

#include "../common/network_opcodes.hpp"
#include "../common/player.hpp"

#ifdef linux
#include <getopt.h>
#endif // linux

void print_help()
{
    std::cout<<"-p  --port            default 7000\n"
             "-n --numberofplayers  default 1\n"
             "-h  --help            this message\n";
}
//---------------------------------------------------------------------------------------------------------------------//
int main(int argc, char** argv)
{
    //zmienne które można modyfikować argumentami z konsoli
    unsigned short local_port = 7000;//port na którym aplikacja odbiera połączenia
    sf::Uint8 number_of_players = 1;//na ilu graczy gra

#ifdef linux
    {
        static struct option longopts[] =
        {
            {"port",            required_argument, NULL, 'p'},
            {"numberofplayers", required_argument, NULL, 'n'},
            {"help",            no_argument,       NULL, 'h'},
        };

        int c;
        while( (c = getopt_long( argc, argv, "p:n:h", longopts, NULL )) != -1 )
        {
            switch (c)
            {
            case 'p':
                local_port = std::stoul( optarg, NULL, 0 );
                break;
            case 'n':
                number_of_players = std::stoul( optarg, NULL, 0 );
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

    sf::Uint8 opcode;
    sf::Uint8 players_count = 0;
    player players[2];
//---------------------------------------------------------------------------------------------------------------------//
    while ( !quit )
    {
        while( players_count < number_of_players )
        {
            socket.receive( receive_packet, incomming_ip, incomming_port );
            receive_packet >> opcode;
            if( opcode == REQUEST_GAME_JOIN )
                players[players_count++] = player( incomming_ip, incomming_port );
        }

        send_packet << SERVER_STARTED_GAME;
        for(int i = 0; i < players_count; i++)
            socket.send( send_packet, players[i].get_ip(), players[i].get_port() );
        send_packet.clear();

        sf::Time time;
        sf::Clock clock;
        while( !quit )//pętla gry
        {
            socket.receive( receive_packet, incomming_ip, incomming_port );
            time = clock.restart();

            //OBSŁUGA PAKIETÓW
            //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
            while( !receive_packet.endOfPacket() )
            {
                receive_packet >> opcode;
                switch( opcode )
                {
                case MOVE_UNIT:
                {
                    sf::Uint8 ID_jednostki;
                    sf::Uint8 x;
                    sf::Uint8 y;
                    receive_packet >> ID_jednostki >> x >> y;

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
        }//pętla gry
    }
//---------------------------------------------------------------------------------------------------------------------//
    return EXIT_SUCCESS;
}
//TODO:
//drugi gracz nie dostaje informacji o zmianie pozycji jednostki
