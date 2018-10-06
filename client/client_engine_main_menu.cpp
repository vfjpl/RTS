#include "client_engine.hpp"

void Client_Engine::setup_menu()
{
    texts_to_draw.emplace_back("CONNECT", resources_manager.get_font());
    texts_to_draw.emplace_back("QUIT", resources_manager.get_font());
    texts_to_draw[1].move(0, 30);
}

void Client_Engine::menu_chose_options(sf::Uint8 id)
{
    switch(id)
    {
    case 0://CONNECT
    {
        //TEMP
        //server.set_ip_port(sf::IpAddress::LocalHost, 7000);
        lobby_loop = true;
        texts_to_draw.clear();
        break;
    }
    case 1://QUIT
    {
        quit_engine();
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}

void Client_Engine::menu_logic()
{
    time = clock.restart();
}

void Client_Engine::menu_receive_inputs()
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
        case sf::Event::TextEntered:
        {
            //TODO: handle text input
            text_buffer += event.text.unicode;
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            menu_receive_inputs_mousepress(event);
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void Client_Engine::menu_receive_inputs_mousepress(const sf::Event& event)
{
    switch(event.mouseButton.button)
    {
    case sf::Mouse::Left:
    {
        menu_chose_options(get_text_id_from_mousepress(event));
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}
