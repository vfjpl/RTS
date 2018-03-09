#include <SFML/Network.hpp>
#include <iostream>

void help()
{
    std::cout << "\n";
}

int main()
{
    sf::UdpSocket socket;
    socket.bind( 7000 );

    sf::Packet packet;
    sf::IpAddress sender;
    unsigned short port;

    std::string message;

    while(true)
    {
        socket.receive( packet, sender, port );
        packet >> message;
        std::cout << message << "\n";
    }

    return EXIT_SUCCESS;
}
