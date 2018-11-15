#include "engine.hpp"
#include "resources_manager.hpp"
#include "network_data.hpp"
#include <iostream>

#include "menu.hpp"
#include "lobby.hpp"

//sort from largest to smallest!
sf::RenderWindow window;//528
Resources_Manager resources_manager;//512
Client_Engine engine;//344
Network_Data server;//24

//work in progress
Menu menu;
Lobby lobby;

void debug_show_size()
{
    //keep up to date!
    std::wcout << sizeof(window) << L'\n'
               << sizeof(engine) << L'\n'
               << sizeof(resources_manager) << L'\n'
               << sizeof(server) << L'\n';
}

int main()
{
    engine.init();
    engine.setup_game();//temp for development

    while( engine.get_menu_loop() )
    {
        engine.menu_logic();
        engine.menu_draw_frame();
        engine.menu_receive_inputs();
        while( engine.get_lobby_loop() )
        {
            engine.lobby_receive_packets();
            engine.lobby_logic();
            engine.lobby_draw_frame();
            engine.lobby_receive_inputs();
            engine.send_packets();
            while( engine.get_game_loop() )
            {
                engine.game_receive_packets();
                engine.game_logic();
                engine.game_draw_frame();
                engine.game_receive_inputs();
                engine.send_packets();
            }
        }
    }

    return EXIT_SUCCESS;
}
