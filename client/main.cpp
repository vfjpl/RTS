#include "menu_client.hpp"
#include "input_client.hpp"
#include "network_client.hpp"

int main()
{
    bool quit = false;
    sf::UdpSocket socket;
    socket.setBlocking(false);

    unsigned short remote_port = 7000;
    sf::IpAddress remote_ip = "localhost";
    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

    std::vector<Player> players;

    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Kelajno" );//sf::Style::Fullscreen
    //pobierać roździelczość przez getSize()
    window.setFramerateLimit(60);
//---------------------------------------------------------------------------------------------------------------------//
    while( !quit )
    {
        menu_temp(window, socket, players, remote_ip, remote_port);

        sf::Clock clock;
        sf::Time time;
        sf::Event event;
        bool quit_game = false;
        while( !quit_game )//pętla gry
        {
            time = clock.restart();
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
