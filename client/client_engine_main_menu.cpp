#include "client_engine.hpp"

void Client_Engine::main_menu()
{
    text_to_draw.emplace_back("CONNECT", resources_manager.get_font());

    text_to_draw.emplace_back("QUIT", resources_manager.get_font());
    text_to_draw[1].move(0, 30);

    //TODO: how to exit?
    while( menu_loop )
    {
        receive_inputs();
        draw_frame();
    }
}
