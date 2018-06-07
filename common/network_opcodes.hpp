#ifndef NETWORK_OPCODES_HPP_INCLUDED
#define NETWORK_OPCODES_HPP_INCLUDED

#include <SFML/Main.hpp>

// ID - oznacza, że operacja dotyczy konkretnego obiektu.
// BP - oznacza, że operacja dotyczy szablonu okietu.

// Wpisywanie rozkazów do pakietu:
// packet << (sf::Uint8)opcode;

enum: sf::Uint8
{

    UNUSED,

    JOIN_GAME,//unused

    DISCONNECT,//unused


    SET_READY_STATUS,//wysyła informacje o statusie gracza
// [bool ready_status]

    SEND_MESSAGE,//wysyła wiadomość do serwera na czat
// [std::wstring tekst]

    SET_NICKNAME,//ustawia nick gracza
// [std::wstring nickname]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MOVE_UNIT,//przesunięcie jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    ATTACK,//atakuj
// [sf::Uint8 ID_jednostki_naszej] [sf::Uint8 ID_jedostki_atakowanej]

    CREATE_UNIT,//stwórz jednostkę
// [sf::Uint8 ID_budynku_z_którego_budujemy] [sf::Uint8 BP_jednostki]

    CREATE_BUILDING,//wybudowanie budynku
// [sf::Uint8 BP_budynku] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    SPECJAL_ABILITY,//użyj umiejętności specjalnej jednostki
// [sf::Uint8 ID_jednostki]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SERVER_START_GAME,//serwer rozpoczął grę
//

    SERVER_STOP_GAME,//zakonczenie gry i powrot do lobby
//

    SERVER_PLAYER_CONNECTED,//informacja o tym że dołączył ktoś do lobby
// [sf::Uint8 ID_gracza]

    SERVER_PLAYER_DISCONNECTED,//gracz opuścił grę
// [sf::Uint8 ID_gracza]

    SERVER_PLAYER_READY_STATUS,//rozsyła informacje o statusie gracza
// [sf::Uint8 ID_gracza] [bool ready_status]

    SERVER_PLAYER_MESSAGE,//serwer rozsyłą wiadomość graczą
// [sf::Uint8 ID_gracza] [std::wstring tekst]

    SERVER_PLAYER_NICKNAME,//serwer rozsyłą nick gracza
// [sf::Uint8 ID_gracza] [std::wstring nickname]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SERVER_ADD_UNIT_TO_GAME,//dodaj jednostke do gry
// [sf::Uint8 BP_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    SERVER_REMOVE_UNIT_FROM_GAME,//usuń jednostke z gry
// [sf::Uint8 ID_jednostki]

    SERVER_SET_UNIT_POSITION,//zmien pozycje jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 pozycja_x] [sf::Uint8 pozycja_y]

    SERVER_SET_UNIT_HEALTH,//ustaw punkty hp jednostki
// [sf::Uint8 ID_jednostki] [sf::Uint8 hp]

};

#endif // NETWORK_OPCODES_HPP_INCLUDED
