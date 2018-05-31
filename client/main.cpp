#include "game_client_session.hpp"

int main()
{
    Game_Client_Session session;

    while( session.get_app_loop() )
    {
        session.main_menu_receive_packets();
        session.main_menu_receive_inputs();
        session.main_menu_logic();
        session.main_menu_draw_frame();
        session.send_packets();
        while( session.get_game_loop() )
        {
            session.game_receive_packets();
            session.game_receive_inputs();
            session.game_logic();
            session.game_draw_frame();
            session.send_packets();
        }
    }

    return EXIT_SUCCESS;
}
