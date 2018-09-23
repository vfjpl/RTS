#include "client_engine.hpp"

int main()
{
    Client_Engine engine;
    //engine.debug_show_size();

    while( engine.get_app_loop() )
    {
        engine.lobby_receive_packets();
        engine.lobby_receive_inputs();
        engine.lobby_logic();
        engine.lobby_draw_frame();
        engine.send_packets();
        while( engine.get_game_loop() )
        {
            engine.game_receive_packets();
            engine.game_receive_inputs();
            engine.game_logic();
            engine.game_draw_frame();
            engine.send_packets();
        }
    }

    return EXIT_SUCCESS;
}
