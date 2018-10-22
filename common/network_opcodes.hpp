#ifndef NETWORK_OPCODES_HPP_INCLUDED
#define NETWORK_OPCODES_HPP_INCLUDED

#include <SFML/Main.hpp>

// ID - oznacza, że operacja dotyczy konkretnego obiektu.
// BP - oznacza, że operacja dotyczy szablonu obiektu.

// SERVER - oznacza, że opcode wysyłany jest przez server.
// CLIENT - oznacza, że opcode wysyłany jest przez clienta.

// Wpisywanie rozkazów do pakietu:
// packet << (sf::Uint8)opcode;

enum: sf::Uint8
{

    UNUSED,

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    CLIENT_SET_READY_STATUS,//ustawia status gracza
// [bool ready_status]

    CLIENT_SEND_MESSAGE,//wysyła wiadomość na czat
// [std::wstring tekst]

    CLIENT_SET_NICKNAME,//ustawia nick gracza
// [std::wstring nickname]

    CLIENT_SET_TEAM,//ustawia team gracza
// [sf::Uint8 team]



    CLIENT_MOVE_UNIT,//przesunięcie jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    CLIENT_ATTACK,//atakuj
// [sf::Uint8 ID_jednostki_naszej] [sf::Uint8 ID_jedostki_atakowanej]

    CLIENT_CREATE_UNIT,//stwórz jednostkę
// [sf::Uint8 ID_budynku_z_którego_budujemy] [sf::Uint8 BP_jednostki]

    CLIENT_CREATE_BUILDING,//wybudowanie budynku
// [sf::Uint8 BP_budynku] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    CLIENT_SPECJAL_ABILITY,//użyj umiejętności specjalnej jednostki
// [sf::Uint8 ID_jednostki]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SERVER_GAME_STATUS,//serwer wysyła status gry
// [bool game_status]

    SERVER_SET_ALL_PLAYERS_READY_STATUS,//ustawia, status graczy u klienta
// [bool status]

    SERVER_PLAYER_CONNECTED,//rozsyła info, że gracz dołączył
// [sf::Uint8 ID_gracza]

    SERVER_PLAYER_DISCONNECTED,//rozsyła info, że gracz opuścił grę
// [sf::Uint8 ID_gracza]

    SERVER_PLAYER_READY_STATUS,//rozsyła status gracza
// [sf::Uint8 ID_gracza] [bool ready_status]

    SERVER_PLAYER_MESSAGE,//rozsyła wiadomość gracza
// [sf::Uint8 ID_gracza] [std::wstring tekst]

    SERVER_PLAYER_NICKNAME,//rozsyła nick gracza
// [sf::Uint8 ID_gracza] [std::wstring nickname]

    SERVER_PLAYER_TEAM,//rozsyła w jakim teamie jest gracz
// [sf::Uint8 ID_gracza] [sf::Uint8 team]



    SERVER_ADD_UNIT_TO_GAME,//dodaj jednostkę do gry
// [sf::Uint8 BP_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    SERVER_REMOVE_UNIT_FROM_GAME,//usuń jednostkę z gry
// [sf::Uint8 ID_jednostki]

    SERVER_SET_UNIT_POSITION,//zmień pozycje jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    SERVER_SET_UNIT_HEALTH,//ustaw punkty hp jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 hp]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    COUNT,

};

#endif // NETWORK_OPCODES_HPP_INCLUDED
