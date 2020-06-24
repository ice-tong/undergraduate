#
# Kian Farsany 55375951
# Project 5
# game_logic.py
#

#
# Constants used to replace 'W' and 'B' with ints
# for easier values to deal with
#
EMPTY = 0
WHITE = 1
BLACK = 2

#
# Exception Classes
#
class GameOverError(Exception):
    pass

class InvalidMoveError(Exception):
    pass

class NoRemainingMoves(Exception):
    pass



class GameState():

    def __init__(self, rows: int, cols: int, turn: int, winning_case: str, board: [[int]]):
        self.rows = rows
        self.cols = cols
        self.turn = turn
        self.winning_case = winning_case
        self.board = board

    def move(self, move: (int, int)) -> None:
        '''Complete a move given the desired move and column'''
        row = move[0] - 1
        col = move[1] - 1

        self._check_game_over()
        
        if self.board[row][col] != EMPTY:
            raise InvalidMoveError()
        else:
            if self._can_flip((row, col))[0]:
                self.board[row][col] = self.turn
                self._flip_all_tiles((row,col))
            else:
                raise InvalidMoveError()
        self._change_turn()
        self.skip_turn_if_possible()

    def game_over(self) -> bool:
        try:
            self._check_game_over()
        except GameOverError:
            return True
        return False

    def winner(self) -> int:
        white_total = self.count_white_tiles()
        black_total = self.count_black_tiles()
        if self.winning_case == '>':
            if white_total > black_total:
                return WHITE
            elif black_total > white_total:
                return BLACK
            else:
                return EMPTY
        elif self.winning_case == '<':
            if white_total < black_total:
                return WHITE
            elif black_total < white_total:
                return BLACK
            else:
                return EMPTY

    def _change_turn(self) -> None:
        if self.turn == BLACK:
            self.turn = WHITE
        elif self.turn == WHITE:
            self.turn = BLACK

    def count_white_tiles(self) -> int:
        result = 0
        for row in self.board:
            for tile in row:
                if tile == WHITE:
                    result += 1
        return result

    def count_black_tiles(self) -> int:
        result = 0
        for row in self.board:
            for tile in row:
                if tile == BLACK:
                    result += 1
        return result

    def _can_make_move(self) -> None:
        can_make_move = False
        for i in range(self.rows):
            for j in range(self.cols):
                if self._can_flip((i,j))[0] and self.board[i][j] == EMPTY:
                    can_make_move = True
        if not can_make_move:
            raise NoRemainingMoves()

    def skip_turn_if_possible(self) -> bool:
        try:
            self._can_make_move()
        except NoRemainingMoves:
            self._change_turn()
            return True
        return False

    def _check_game_over(self) -> None:
        if self.skip_turn_if_possible():
            if self.skip_turn_if_possible():
                raise GameOverError()

#
#
# Flipping Mechanics
#
# Organized by horizontal, vertical, and diagonal
# Also organized by directions
#
#

    def _flip_horizontal_left(self, move: (int, int)) -> bool:
        successful_flip = False
        tiles_to_flip_later = []
        row = move[0]
        col = move[1]
        for i in range(col):
            flip_count = 0
            if self.board[row][i] == self.turn:
                for j in range(i+1,col):
                    if self.board[row][j] != self.turn and self.board[row][j] != EMPTY:
                        flip_count += 1
            if flip_count == len(range(i+1,col)) and flip_count != 0:
                successful_flip = True
                for k in range(i+1, col):
                    tiles_to_flip_later.append((row, k))
        return (successful_flip, tiles_to_flip_later)

    def _flip_horizontal_right(self, move: (int, int)) -> bool:
        successful_flip = False
        tiles_to_flip_later = []
        row = move[0]
        col = move[1]
        for i in range(col+2, self.cols):
            flip_count = 0
            if self.board[row][i] == self.turn:
                for j in range(col+1,i):
                    if self.board[row][j] != self.turn and self.board[row][j] != EMPTY:
                        flip_count += 1
            if flip_count == len(range(col+1,i)) and flip_count != 0:
                successful_flip = True
                for k in range(col+1,i):
                    tiles_to_flip_later.append((row, k))
        return (successful_flip, tiles_to_flip_later)

    def _flip_vertical_up(self, move: (int, int)) -> bool:
        successful_flip = False
        tiles_to_flip_later = []
        row = move[0]
        col = move[1]
        for i in range(row):
            flip_count = 0
            if self.board[i][col] == self.turn:
                for j in range(i+1,row):
                    if self.board[j][col] != self.turn and self.board[j][col] != EMPTY:
                        flip_count += 1
            if flip_count == len(range(i+1,row)) and flip_count != 0:
                successful_flip = True
                for k in range(i+1,row):
                    tiles_to_flip_later.append((k,col))
        return (successful_flip, tiles_to_flip_later)

    def _flip_vertical_down(self, move: (int, int)) -> bool:
        successful_flip = False
        tiles_to_flip_later = []
        row = move[0]
        col = move[1]
        for i in range(row+2, self.rows):
            flip_count = 0
            if self.board[i][col] == self.turn:
                for j in range(row+1,i):
                    if self.board[j][col] != self.turn and self.board[j][col] != EMPTY:
                        flip_count += 1
            if flip_count == len(range(row+1,i)) and flip_count != 0:
                successful_flip = True
                for k in range(row+1,i):
                    tiles_to_flip_later.append((k,col))
        return (successful_flip, tiles_to_flip_later)
                                   
    def _flip_upper_left_diagonal(self, move: (int, int)) -> bool:
        successful_flip = False
        tiles_to_flip_later = []
        row = move[0]
        col = move[1]
        minimum = min(row,col)
        i,j = row - minimum,col - minimum
        while i < row and j < col:
            flip_count, total_count = 0, 0
            if self.board[i][j] == self.turn:
                x,y = i+1,j+1
                while x < row and y < col:
                    if self.board[x][y] != self.turn and self.board[x][y] != EMPTY:
                        flip_count += 1
                    total_count += 1
                    x,y = x+1,y+1
            if flip_count == total_count and flip_count != 0:
                successful_flip = True
                m,n = i+1,j+1
                while m < row and n < col:
                    tiles_to_flip_later.append((m,n))
                    m,n = m+1,n+1
            i,j = i+1,j+1             
        return (successful_flip, tiles_to_flip_later)

    def _flip_upper_right_diagonal(self, move: (int, int)) -> bool:
        successful_flip = False
        tiles_to_flip_later = []
        row = move[0]
        col = move[1]
        i,j = row-2,col+2
        while i >= 0 and j < self.cols:
            flip_count, total_count = 0, 0
            if self.board[i][j] == self.turn:
                x,y = row-1,col+1
                while x > i and y < j:
                    if self.board[x][y] != self.turn and self.board[x][y] != EMPTY:
                        flip_count += 1
                    total_count += 1
                    x,y = x-1,y+1
            if flip_count == total_count and flip_count != 0:
                successful_flip = True
                m,n = row-1,col+1
                while m > i and n < j:
                    tiles_to_flip_later.append((m,n))
                    m,n = m-1,n+1
            i,j = i-1,j+1
        return (successful_flip, tiles_to_flip_later)

    def _flip_lower_left_diagonal(self, move: (int, int)) -> bool:
        successful_flip = False
        tiles_to_flip_later = []
        row = move[0]
        col = move[1]
        i,j = row+2,col-2
        while i < self.rows and j >= 0:
            flip_count, total_count = 0,0
            if self.board[i][j] == self.turn:
                x,y = i-1,j+1
                while x > row and y < col:
                    if self.board[x][y] != self.turn and self.board[x][y] != EMPTY:
                        flip_count += 1
                    total_count += 1
                    x,y = x-1,y+1
            if flip_count == total_count and flip_count != 0:
                successful_flip = True
                m,n = i-1,j+1
                while m > row and n < col:
                    tiles_to_flip_later.append((m,n))
                    m,n = m-1,n+1
            i,j = i+1,j-1
        return (successful_flip, tiles_to_flip_later)
    
    def _flip_lower_right_diagonal(self, move: (int,int)) -> (bool, [(int,int)]):
        successful_flip = False
        tiles_to_flip_later = []
        row = move[0]
        col = move[1]
        i,j = row+2,col+2
        while i < self.rows and j < self.cols:
            flip_count, total_count = 0, 0
            if self.board[i][j] == self.turn:
                x,y = row+1,col+1
                while x < i and y < j:
                    if self.board[x][y] != self.turn and self.board[x][y] != EMPTY:
                        flip_count += 1
                    total_count += 1
                    x,y = x+1,y+1
            if flip_count == total_count and flip_count != 0:
                successful_flip = True
                m,n = row+1,col+1
                while m < i and n < j:
                    tiles_to_flip_later.append((m,n))
                    m,n = m+1,n+1
            i,j = i+1,j+1
        return (successful_flip, tiles_to_flip_later)
                       
    def _can_flip(self, move: (int, int)) -> (bool, [(int,int)]):
        result_bool = False
        tiles_to_be_flipped = []
        
        if self._flip_horizontal_left(move)[0]:
            result_bool = True
            tiles_to_be_flipped.extend(self._flip_horizontal_left(move)[1])
        if self._flip_horizontal_right(move)[0]:
            result_bool = True
            tiles_to_be_flipped.extend(self._flip_horizontal_right(move)[1])
        if self._flip_vertical_up(move)[0]:
            result_bool = True
            tiles_to_be_flipped.extend(self._flip_vertical_up(move)[1])
        if self._flip_vertical_down(move)[0]:
            result_bool = True
            tiles_to_be_flipped.extend(self._flip_vertical_down(move)[1])
        if self._flip_upper_left_diagonal(move)[0]:
            result_bool = True
            tiles_to_be_flipped.extend(self._flip_upper_left_diagonal(move)[1])
        if self._flip_upper_right_diagonal(move)[0]:
            result_bool = True
            tiles_to_be_flipped.extend(self._flip_upper_right_diagonal(move)[1])
        if self._flip_lower_left_diagonal(move)[0]:
            result_bool = True
            tiles_to_be_flipped.extend(self._flip_lower_left_diagonal(move)[1])
        if self._flip_lower_right_diagonal(move)[0]:
            result_bool = True
            tiles_to_be_flipped.extend(self._flip_lower_right_diagonal(move)[1])
        return (result_bool, tiles_to_be_flipped)

    def _flip_tile(self, move: (int, int)) -> None:
        if self.board[move[0]][move[1]] == BLACK:
            self.board[move[0]][move[1]] = WHITE
        elif self.board[move[0]][move[1]] == WHITE:
            self.board[move[0]][move[1]] = BLACK
            
                
    def _flip_all_tiles(self, move: (int, int)) -> None:
        can_flip_tuple = self._can_flip(move)
        if can_flip_tuple[0]:
            for i in can_flip_tuple[1]:
                self._flip_tile(i)


    
