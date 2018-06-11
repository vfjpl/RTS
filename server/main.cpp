#include "server_engine.hpp"

int main()
{
    Server_Engine engine;
    engine.debug_show_size();

    while( engine.get_app_loop() )
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
