#ifndef NETWORK_OPCODES_HPP_INCLUDED
#define NETWORK_OPCODES_HPP_INCLUDED

#include <SFML/Main.hpp>

// ID - oznacza, że operacja dotyczy konkretnego obiektu.
// BP - oznacza, że operacja dotyczy możliwego okietu.

// Wpisywanie rozkazów do pakietu:
// packet << (sf::Uint8)opcode; LUB packet << sf::Uint8(opcode); LUB packet << (sf::Uint8)(opcode);

enum: sf::Uint8
{

    UNUSED,

    SERVER_START_GAME,//serwer rozpoczął grę

    SERVER_PLAYER_CONNECTED,//informacja o tym że dołączył ktoś do lobby
// [sf::Uint8 ID_gracza]

    SERVER_PLAYER_DISCONNECTED,
// [sf::Uint8 ID_gracza]

    SERVER_PLAYER_READY,//wskazuje gotowość gracza na rozpoczęcie gry
// [sf::Uint8 ID_gracza]

    SERVER_PLAYER_NOTREADY,//wskazuje brak gotowości gracza na rozpoczęcie gry
// [sf::Uint8 ID_gracza]

    SERVER_MESSAGE,//to samo tylko teraz serwer rozsyłą graczą
// [sf::Uint8 ID_gracza] [std::wstring tekst]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    CLIENT_JOIN_GAME,//prosi o dołączenie do gry

    CLIENT_DISCONNECT,//rozłącza się;
// [sf::Uint8 ID_gracza]

    CLIENT_READY,//wysyła informacje że gotowy do serwera
// [sf::Uint8 ID_gracza]

    CLIENT_NOTREADY,//wysyła informacje że nie gotowy do serwera
// [sf::Uint8 ID_gracza]

    CLIENT_SEND_MESSAGE,//wysyła wiadomość do serwera na czat
// [sf::Uint8 ID_gracza] [std::wstring tekst]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
