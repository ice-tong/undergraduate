#
# Project 2
# Kian Farsany 55375951
# Darrel Belen 72866173
# connectfour_network_ui.py
#
import connectfour
import connectfour_shared_ui
import connectfour_socket

def _user_interface() -> None:
    '''Run the main user interface'''
    print('Welcome to Connect Four!')
    try:
        connection = _connect_to_server()
        connectfour_socket.hello(connection, _get_username())
        connectfour_socket.request_ai_game(connection)
        print('You will be RED and the computer will be YELLOW...')

        game_state = connectfour.new_game()
        while True:
            connectfour_shared_ui.print_board(game_state)

            user_move = connectfour_shared_ui.get_move(game_state)
            connectfour_socket.send_move(connection, user_move.move)
            game_state = user_move.gamestate

            response = connectfour_socket.handle_responses(connection)
            winner = response[0]
            move = response[1]
            if winner == 'WINNER_RED' and move == '':
                connectfour_shared_ui.print_board(game_state)
                print('RED is the winner!')
                break
            elif winner == 'WINNER_YELLOW' and move == '':
                connectfour_shared_ui.print_board(game_state)
                print('YELLOW is the winner!')
                break
            elif winner == '' and move != '':
                game_state = _execute_server_move(game_state, move)
                print('YELLOW chose to {}.'.format(move))
            elif winner != '' and move != '':
                game_state = _execute_server_move(game_state, move)
                print('YELLOW chose to {}.'.format(move))
                connectfour_shared_ui.print_board(game_state)
                if winner == 'WINNER_YELLOW':
                    print('YELLOW is the winner!')
                    break
                elif winner == 'WINNER_RED':
                    print('RED is the winner!')
                    break
                    
    except connectfour_socket.ProtocolError:
        print('There was an issue with the server. Goodbye!')
    finally:
        connectfour_socket.close(connection)    

def _get_host() -> str:
    '''Ask for and get the host from the user'''
    return input('Enter the IP address or hostname: ')

def _get_port() -> str:
    '''Ask for and get the port from the user'''
    while True:
        try:
            port = int(input('Enter the port number: '))
            if port < 0 or port > 65535:
                raise Exception
        except:
            print('That is not a valid port number.')
        else:
            return port

def _get_username() -> str:
    '''Ask for and get a username with no whitespace'''
    while True:
        username = input('Enter a UserName with no spaces or tabs: ')
        if ' ' in username or '\t' in username:
            print('That is not a valid UserName.')
        else:
            return username
        
def _connect_to_server() -> 'Connection':
    '''Show the process of connecting and handle user errors'''
    while True:
        host = _get_host()
        port = _get_port()
        print('Connecting to {} on port {} ...'.format(host, port))
        try:
            return connectfour_socket.connect(host, port)
        except:
            print('The host or port is wrong. Try again.')
            
def _execute_server_move(game_state: 'GameState', response: str) -> 'GameState':
    '''Implement the server's move to change the GameState only'''
    try:
        response_split = response.split(' ', 1)
        if response_split[0] == 'DROP' and type(int(response_split[1]) == int):
            return connectfour.drop(game_state, int(response_split[1]) - 1)
        elif response_split[0] == 'POP' and type(int(response_split[1]) == int):
            return connectfour.pop(game_state, int(response_split[1]) - 1)
        else:
            raise connectfour_socket.ProtocolError()
        
    except:
        raise connectfour_socket.ProtocolError()
        
    
if __name__ == '__main__':
    _user_interface()
    


    
