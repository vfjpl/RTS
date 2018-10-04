#include "client_engine.hpp"

void Client_Engine::main_menu()
{
    text_to_draw.emplace_back("QUIT", resources_manager.get_font());

    //TODO: how to exit?
    while( true )
    {
        receive_inputs();
        draw_frame();
    }
}
