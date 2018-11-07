#include "engine.hpp"
#include "resources_manager.hpp"
#include "menu.hpp"
#include "network_data.hpp"
#include <iostream>

//sort from largest to smallest!
sf::RenderWindow window;//528
Client_Engine engine;//344
Resources_Manager resources_manager;//224
Menu menu;//88
Network_Data server;//24

void debug_show_size()
{
    //keep up to date!
    std::wcout << sizeof(window) << L'\n'
               << sizeof(engine) << L'\n'
               << sizeof(resources_manager) << L'\n'
               << sizeof(menu) << L'\n'
               << sizeof(server) << L'\n';
}

int main()
{
    engine.init();

    while( engine.get_menu_loop() )
    {
        engine.menu_receive_inputs();
        engine.menu_logic();
        engine.menu_draw_frame();
        while( engine.get_lobby_loop() )
        {
            engine.receive_packets();
            engine.lobby_receive_inputs();
            engine.lobby_logic();
            engine.lobby_draw_frame();
            engine.send_packets();
            while( engine.get_game_loop() )
            {
                engine.receive_packets();
                engine.game_receive_inputs();
                engine.game_logic();
                engine.game_draw_frame();
                engine.send_packets();
            }
        }
    }

    return EXIT_SUCCESS;
}
