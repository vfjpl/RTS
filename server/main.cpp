#include <SFML/Network.hpp>
#include <iostream>

#include "network_server.hpp"

#ifdef linux
#include <getopt.h>
#endif // linux

void print_help()
{
    std::cout<<"-p  --port               default: 7000\n"
             "-n  --number_of_players  default: 1\n"
             "-h  --help               this message\n";
}
//---------------------------------------------------------------------------------------------------------------------//
int main(int argc, char** argv)
{
    //zmienne które można modyfikować argumentami z konsoli
    unsigned short local_port = 7000;//port na którym aplikacja odbiera połączenia
    sf::Uint8 number_of_players = 1;//na ilu graczy gra

#ifdef linux
    {
        const struct option longopts[] =
        {
            {"port",              required_argument, NULL, 'p'},
            {"number_of_players", required_argument, NULL, 'n'},
            {"help",              no_argument,       NULL, 'h'},
        };

        int c;
        while( (c = getopt_long( argc, argv, "p:n:h", longopts, NULL )) != -1 )
        {
            switch (c)
            {
            case 'p':
                local_port = std::stoul( optarg );
                break;
            case 'n':
                number_of_players = std::stoul( optarg );
                break;
            case 'h':
                std::cout << argv[0] << "\n";
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

    player players[2];
//---------------------------------------------------------------------------------------------------------------------//
    while( !quit )
    {
        network_players_init(socket, players, number_of_players);

        sf::Clock clock;
        sf::Time time;
        bool quit_game = false;
        while( !quit_game )//pętla gry
        {
            socket.receive( receive_packet, incomming_ip, incomming_port );
            time = clock.restart();
            network_packet_receive( receive_packet );



            socket.send( send_packet, incomming_ip, incomming_port );
            send_packet.clear();
        }//pętla gry
    }
//---------------------------------------------------------------------------------------------------------------------//
    return EXIT_SUCCESS;
}
//TODO:
//drugi gracz nie dostaje informacji o zmianie pozycji jednostki
