#
# Project 2
# Kian Farsany 55375951
# Darrel Belen 72866173
# connectfour_shared_ui.py
#
from collections import namedtuple
import connectfour

# A Move is composed of the GameState after the move is made and
# the string version of the move so the string can be used to converse
# with the server and the GameState can be used with the interface.
Move = namedtuple(
    'Move',
    ['gamestate', 'move'])


def print_board(game_state: 'GameState') -> None:
    '''Prints the current gameboard'''
    numbers = range(connectfour.BOARD_COLUMNS)
    for i in numbers:
        print(i+1, end = '  ')
    print()
    
    for row in range(connectfour.BOARD_ROWS):
        for col in range(connectfour.BOARD_COLUMNS):
            if game_state.board[col][row] == connectfour.NONE:
                print('.', end='  ')
            elif game_state.board[col][row] == connectfour.RED:
                print('R', end='  ')
            elif game_state.board[col][row] == connectfour.YELLOW:
                print('Y', end='  ')
        print()
    print()

def get_move(game_state: 'GameState') -> Move:
    '''Combines the GameState and the string into a Move'''
    while True:
        move = input("Enter 'DROP' or 'POP' and the desired column: ").upper()
        move_split = move.split(' ', 1)
        try:
            if move_split[0] == 'DROP' and type(int(move_split[1]) == int):
                return Move(
                    gamestate = connectfour.drop(game_state, int(move_split[1]) - 1),
                    move = move_split[0] + ' ' + move_split[1])
            elif move_split[0] == 'POP' and type(int(move_split[1]) == int):
                return Move(
                    gamestate = connectfour.pop(game_state, int(move_split[1]) - 1),
                    move = move_split[0] + ' ' + move_split[1])
            else:
                print("You did not properly enter 'POP' or 'DROP'")
        except:
            print('That is an invalid move.')
