#
# Project 2
# Kian Farsany 55375951
# Darrel Belen 72866173
# connectfour_console.py
#
import connectfour
import connectfour_shared_ui

def print_whose_move(game_state: 'GameState') -> None:
    '''Print whose move it is'''
    turn = game_state.turn
    if turn == connectfour.RED:
        print("It is RED's turn")
    elif turn == connectfour.YELLOW:
        print("It is YELLOW's turn")

def check_winner(game_state: 'GameState') -> bool:
    '''Return if someone has won and print the result'''
    if connectfour.winner(game_state) == connectfour.RED:
        connectfour_shared_ui.print_board(game_state)
        print('RED is the winner!')
        return True
    elif connectfour.winner(game_state) == connectfour.YELLOW:
        connectfour_shared_ui.print_board(game_state)
        print('YELLOW is the winner!')
        return True
    return False

if __name__ == '__main__':
    print('Welcome to Connect Four!')
    game_state = connectfour.new_game()
    while True:
        connectfour_shared_ui.print_board(game_state)
        
        print_whose_move(game_state)
        
        game_state = connectfour_shared_ui.get_move(game_state).gamestate
        
        if check_winner(game_state):
            break
