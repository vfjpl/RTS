#include "game_server_session.hpp"

int main()
{
    Game_Server_Session session;
    bool game_loop;

    while( true )
    {
        session.lobby_receive_packets();
        game_loop = session.lobby_logic();
        session.send_packets();
        while( game_loop )
        {
            session.receive_packets();
            session.game_logic();
            session.send_packets();
        }
    }

    return EXIT_SUCCESS;
}
