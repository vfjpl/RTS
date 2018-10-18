#include "engine.hpp"
#include "resources_manager.hpp"
#include "menu.hpp"
#include "network_data.hpp"
#include "iostream"

//sort from largest to smallest!
Client_Engine engine;
Resources_Manager resources_manager;
Menu menu;
Network_Data server;

void debug_show_size()
{
    //keep up to date!
    std::wcout << sizeof(engine) << L"\n"
               << sizeof(resources_manager) << L"\n"
               << sizeof(menu) << L"\n"
               << sizeof(server) << L"\n";
}

int main()
{
    engine.init();

    while( engine.get_menu_loop())
    {
        engine.menu_receive_inputs();
        engine.menu_logic();
        engine.draw_frame();
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
