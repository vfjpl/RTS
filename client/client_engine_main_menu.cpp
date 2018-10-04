#include "client_engine.hpp"

void Client_Engine::main_menu()
{
    while( true )
    {
        receive_inputs();
        draw_frame();
    }
}
