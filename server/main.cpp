#include "engine.hpp"
#include <iostream>

//sort from largest to smallest!
Server_Engine engine;//344

void debug_show_size()
{
    //keep up to date!
    std::wcout << sizeof(engine) << L'\n';
}

int main()
{
    engine.init();

    while( engine.get_lobby_loop() )
    {
        engine.receive_packets();
        engine.lobby_logic();
        engine.send_packets();
        while( engine.get_game_loop() )
        {
            engine.receive_packets();
            engine.game_logic();
            engine.send_packets();
        }
    }

    return EXIT_SUCCESS;
}
