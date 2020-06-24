#
# Kian Farsany 55375951
# Project 4
# console.py
#

import game_logic

def _user_interface() -> None:
    '''Run the main user interface'''
    print('FULL')
    game_state = _take_initial_input()
    while True:
        if game_state.game_over():
            _print_tile_totals(game_state)
            _print_board(game_state)
            winner = game_state.winner()
            if winner == game_logic.BLACK:
                print('WINNER: B')
            elif winner == game_logic.WHITE:
                print('WINNER: W')
            else:
                print('WINNER: NONE')
            break
        game_state.skip_turn_if_possible()
        _print_game_state(game_state)
        _check_valid_move(game_state)
    

def _take_initial_input() -> 'GameState':
    '''Take the input from the user and initialize the proper GameState'''
    rows = int(input())
    cols = int(input())
    first_turn = input()
    if first_turn == 'B':
        first_turn = game_logic.BLACK
    elif first_turn == 'W':
        first_turn = game_logic.WHITE
    winning_case = input()
    board = _initialize_board(rows)

    return game_logic.GameState(rows, cols, first_turn, winning_case, board)

def _initialize_board(rows: int) -> [[int]]:
    '''Take the board from the user and turn it into a [str]
    so it can be turned into a [[int]]'''
    result = []
    for i in range(rows):
        result.append(input())

    return _convert_board_to_int(result)

def _convert_board_to_int(board: [str]) -> [[int]]:
    '''Convert [[str]] to [[int]] with the proper constants'''
    result = []
    for row_str in board:
        tiles = row_str.split()
        result_row = []
        for tile in tiles:
            if tile == '.':
                result_row.append(0)
            elif tile == 'W':
                result_row.append(1)
            elif tile == 'B':
                result_row.append(2)
        result.append(result_row)
    return result

def _print_tile_totals(game_state: 'GameState') -> None:
    '''Print the tile totals for both black and white'''
    print('B: {}  W: {}'.format(game_state.count_black_tiles(),
                               game_state.count_white_tiles()))

def _print_turn(game_state: 'GameState') -> None:
    '''Print whose turn it is'''
    if game_state.turn == game_logic.BLACK:
        print('TURN: B')
    else:
        print('TURN: W')

def _print_board(game_state: 'GameState') -> None:
    '''Print the board as it currently stands'''
    board = game_state.board
    text = ''
    for i in board:
        for j in i:
            if j == game_logic.WHITE:
                text += 'W '
            elif j == game_logic.BLACK:
                text += 'B '
            elif j == game_logic.EMPTY:
                text += '. '
        text = text.rstrip() + '\n'
    print(text[:-1])

def _print_game_state(game_state: 'GameState') -> None:
    _print_tile_totals(game_state)
    _print_board(game_state)
    _print_turn(game_state)

def _take_move() -> (int, int):
    '''Take the move from the user as a tuple
    in the form (row, column)'''
    move = input().split()
    return (int(move[0]), int(move[1]))
        
def _check_valid_move(game_state: 'GameState') -> None:
    while True:
        try:
            game_state.move(_take_move())
        except game_logic.InvalidMoveError:
            print('INVALID')
        else:
            print('VALID')
            break



if __name__ == '__main__':
    _user_interface()
    
    

    
