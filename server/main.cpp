#include <SFML/Network.hpp>
#include <iostream>
#include <unordered_map>

/*
#ifdef _WIN32
    #include <cstring>
#endif // _WIN32
*/
#ifdef linux
    #include <getopt.h>
#endif // linux

#include "../common/player.hpp"

void print_help()
{
    std::cout<<"-p  --port      default 7000\n"
               "-h  --help      this message\n";
}

int main(int argc, char** argv)
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //zmienne które można modyfikować argumentami z konsoli
    unsigned short port = 7000;

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
                port = std::stoul( optarg, NULL, 0 );
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
    bool quit;
    sf::UdpSocket socket;
    socket.bind( port );

    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;

    std::unordered_map <std::string, player> players;
    //std::vector <unit> units;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Time time;
    sf::Clock clock;
    while( !quit )
    {
        socket.receive( receive_packet, incomming_ip, port );
        time = clock.restart();

        //obsługa pakietu
        sf::Int64 usertime;
        receive_packet >> usertime;//odebranie czasu z pakietu
        send_packet << usertime;
        while(!receive_packet.endOfPacket())
        {
            sf::Uint8 command;
            receive_packet >> command;

            switch( command )
            {
            case 0:
                players.insert( {incomming_ip.toString() + std::to_string(port), player(incomming_ip,port)} );
                break;
            //od 0 do 9 zarezerwowane

            default:
                break;
            }
        }


        socket.send( send_packet, incomming_ip, port );
        send_packet.clear();
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return EXIT_SUCCESS;
}
