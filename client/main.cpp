#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "network_client.hpp"
#include "input_client.hpp"

#ifdef linux
#include <getopt.h>
#endif // linux

void print_help()
{
    std::cout << "-p  --port       default: 7000\n"
              "-l  --local_port  default: sf::UdpSocket::AnyPort\n"
              "-i  --ip          default: localhost\n"
              "-h  --help        this message\n";
}
//---------------------------------------------------------------------------------------------------------------------//
int main( int argc, char** argv )
{
    //zmienne które można modyfikować argumentami z konsoli
    unsigned short local_port = sf::UdpSocket::AnyPort;//port na którym aplikacja odbiera połączenia
    unsigned short remote_port = 7000;//port do którego się łączymy
    sf::IpAddress remote_ip = "localhost";//ip do którego się łączymy

#ifdef linux
    {
        const struct option longopts[] =
        {
            { "port",       required_argument, NULL, 'p' },
            { "local_port", required_argument, NULL, 'l' },
            { "ip",         required_argument, NULL, 'i' },
            { "help",       no_argument,       NULL, 'h' },
        };

        int c;
        while ((c = getopt_long( argc, argv, "p:l:i:h", longopts, NULL )) != -1)
        {
            switch (c)
            {
            case 'p':
                remote_port = std::stoul( optarg );
                break;
            case 'l':
                local_port = std::stoul( optarg );
                break;
            case 'i':
                remote_ip = optarg;
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
    socket.setBlocking(false);
    //socket.bind(local_port);

    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

    //MODYFIKOWANIE OKNA APLIKACJI
    sf::RenderWindow window( sf::VideoMode( 1920, 1080 ), "Kelajno", sf::Style::Fullscreen );//opcja fullscreen
    //pobierać roździelczość przez getSize()
    window.setFramerateLimit(60);//ustawiam limit fps na 60
//---------------------------------------------------------------------------------------------------------------------//
    while( !quit )
    {
        //miejsce na menu

        sf::Clock clock;
        sf::Time time;
        sf::Event event;
        bool quit_game = false;
        while( !quit_game )//pętla gry
        {
            time = clock.restart();//pobranie czasu od ostatniej klatki
            while( !socket.receive( receive_packet, incomming_ip, incomming_port ) )
                network_packet_receive( receive_packet );

            while( window.pollEvent( event ) )
                input_receive( event, quit_game, quit );


            window.clear();
            window.display();

            socket.send( send_packet, remote_ip, remote_port );
            send_packet.clear();
        }//pętla gry
    }
//---------------------------------------------------------------------------------------------------------------------//
    window.close();
    return EXIT_SUCCESS;
}
//https://www.sfml-dev.org/tutorials/2.5/window-window.php
