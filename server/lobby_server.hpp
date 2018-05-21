#ifndef LOBBY_SERVER_HPP_INCLUDED
#define LOBBY_SERVER_HPP_INCLUDED

void lobby_server(sf::UdpSocket& socket, Player* players, sf::Uint8 number_of_players);

#endif // LOBBY_SERVER_HPP_INCLUDED
