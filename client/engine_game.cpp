#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "../common/network_data.hpp"
#include "../common/network_opcodes.hpp"

extern sf::RenderWindow window;
extern Network_Data server;

void Client_Engine::game_receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    while ( !socket.receive(received_packet, incomming_ip, incomming_port) )
    {
        if(!server.compare(incomming_ip, incomming_port))//check if packet was send by server
            continue;//do nothing if not

        server.reset_network_timeout();
        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch(opcode)
            {
            case SERVER_GAME_STATUS:
            {
                bool game_status;
                received_packet >> game_status;

                if(!game_status)
                    setup_lobby();
                break;
            }
            default:
            {
                received_packet.clear();
                break;
            }
            }//end switch
        }//end while
    }//end while
}

void Client_Engine::game_logic()
{
    time = clock.restart();

    if(server.get_network_timeout() > sf::seconds(1))
    {
        //setup_menu();//back to menu
        return;
    }
    server.add_network_timeout(time);
}

void Client_Engine::game_draw_frame()
{
    window.clear();
    window.display();
}

void Client_Engine::game_receive_inputs()
{
    sf::Event event;
    while( window.pollEvent(event) )
    {
        switch(event.type)
        {
        case sf::Event::Closed:
        {
            quit_engine();
            break;
        }
        case sf::Event::Resized:
        {
            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}
