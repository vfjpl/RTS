#include "client_engine.hpp"

int main()
{
    Client_Engine engine;
    //engine.debug_show_size();

    while( engine.get_app_loop())
    {
        engine.receive_inputs();
        engine.draw_frame();
        while( engine.get_lobby_loop() )
        {
            engine.receive_packets();
            engine.receive_inputs();
            engine.lobby_logic();
            engine.draw_frame();
            engine.send_packets();
            while( engine.get_game_loop() )
            {
                engine.receive_packets();
                engine.receive_inputs();
                engine.game_logic();
                engine.draw_frame();
                engine.send_packets();
            }
        }
    }

    return EXIT_SUCCESS;
}
