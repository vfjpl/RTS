#include "game_server_session.hpp"

int main()
{
    Game_Server_Session session;
    session.debug_show_size();

    while( session.get_app_loop() )
    {
        session.lobby_receive_packets();
        session.lobby_logic();
        session.send_packets();
        while( session.get_game_loop() )
        {
            session.game_receive_packets();
            session.game_logic();
            session.send_packets();
        }
    }

    return EXIT_SUCCESS;
}
