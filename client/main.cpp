#include <SFML/Network.hpp>
#include <iostream>

void help()
{
    std::cout << "\n";
}

int main()
{
    sf::UdpSocket socket;
    sf::Packet packet;
    std::string message;

    while(true)
    {
        std::cin >> message;
        packet << message;
        socket.send( packet, "localhost", 7000 );
        packet.clear();
    }

    return EXIT_SUCCESS;
}
