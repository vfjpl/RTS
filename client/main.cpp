#include "engine.hpp"

int main()
{
    Client_Engine engine;
    engine.init();
    //engine.debug_show_size();

    while( engine.get_menu_loop())
    {
        engine.menu_receive_inputs();
        engine.menu_logic();
        engine.menu_draw_frame();
        while( engine.get_lobby_loop() )
        {
            engine.receive_packets();
            engine.lobby_receive_inputs();
            engine.lobby_logic();
            engine.draw_frame();
            engine.send_packets();
            while( engine.get_game_loop() )
            {
                engine.receive_packets();
                engine.game_receive_inputs();
                engine.game_logic();
                engine.draw_frame();
                engine.send_packets();
            }
        }
    }

    return EXIT_SUCCESS;
}
