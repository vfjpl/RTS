#ifndef NETWORK_OPCODES_HPP_INCLUDED
#define NETWORK_OPCODES_HPP_INCLUDED

#include <SFML/Main.hpp>

// ID - oznacza, że operacja dotyczy konkretnego obiektu.
// BP - oznacza, że operacja dotyczy możliwego okietu.
enum: sf::Uint8
{

    UNUSED,

    REQUEST_GAME_JOIN,//prosi o dołączenie do gry

    SERVER_STARTED_GAME,//serwer rozpoczął grę

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CLIENT OPCODES

    MOVE_UNIT,//przesunięcie jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    ATTACK,//atakuj
// [sf::Uint8 ID_jednostki_naszej] [sf::Uint8 ID_jedostki_atakowanej]

    CREATE_UNIT,//stwórz jednostkę
// [sf::Uint8 ID_budynku_z_którego_budujemy] [sf::Uint8 BP_jednostki]

    CREATE_BUILDING,//wybudowanie budynku
// [sf::Uint8 BP_budynku] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    SPECJAL_ABILITY,//umiejętność specjalna jednostki
// [sf::Uint8 ID_jednostki]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SERVER OPCODES

    ADD_UNIT_TO_GAME,//dodaj jednostke do gry
// [sf::Uint8 BP_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    REMOVE_UNIT_FROM_GAME,//usuń jednostke z gry
// [sf::Uint8 ID_jednostki]

    SET_UNIT_POSITION,//zmien pozycje jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    SET_UNIT_HEALTH,//ustaw punkty hp jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 hp]

};

#endif // NETWORK_OPCODES_HPP_INCLUDED
