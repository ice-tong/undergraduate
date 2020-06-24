#
# Kian Farsany 55375951
# Project 5
# othello_input.py
#

import tkinter
import game_logic


FONT = ('Helvetica', 20)



class InvalidInputError(Exception):
    pass



class OthelloInput:
    def __init__(self):
        self._root_window = tkinter.Tk()

        row_label = tkinter.Label(
            master = self._root_window,
            text = 'Enter an even number of rows from 4 to 16:',
            font = FONT)

        row_label.grid(row = 0, column = 0, padx = 15, pady = 15,
                        sticky = tkinter.W)

        self._row_entry = tkinter.Entry(
            master = self._root_window,
            font = FONT)

        self._row_entry.grid(
            row = 0, column = 1, columnspan = 2, padx = 15, pady = 15,
            sticky = tkinter.W + tkinter.E)

        col_label = tkinter.Label(
            master = self._root_window,
            text = 'Enter an even number of columns from 4 to 16:',
            font = FONT)

        col_label.grid(row = 1, column = 0, padx = 15, pady = 15,
                        sticky = tkinter.W)

        self._col_entry = tkinter.Entry(
            master = self._root_window, font = FONT)

        self._col_entry.grid(
            row = 1, column = 1, columnspan = 2, padx = 15, pady = 15,
            sticky = tkinter.W + tkinter.E)

        color_label = tkinter.Label(
            master = self._root_window, text = 'Who will go first?',
            font = FONT)

        color_label.grid(row = 2, column = 0, padx = 15, pady = 15,
                         sticky = tkinter.W)

        self._black_button = tkinter.Button(
            master = self._root_window, text = 'BLACK', font = FONT,
            command = self._on_black_button)

        self._black_button.grid(row = 2, column = 1, padx = 15, pady = 15,
                           sticky = tkinter.W + tkinter.E)

        self._white_button = tkinter.Button(
            master = self._root_window, text = 'WHITE', font = FONT,
            command = self._on_white_button)

        self._white_button.grid(row = 2, column = 2, padx = 15, pady = 15,
                           sticky = tkinter.W + tkinter.E)

        winner_label = tkinter.Label(
            master = self._root_window,
            text = 'Will the winner have more or less tiles than the loser?',
            font = FONT)

        winner_label.grid(
            row = 3, column = 0, padx = 15, pady = 15, sticky = tkinter.W)

        self._more_points = tkinter.Button(
            master = self._root_window, text = 'MORE', font = FONT,
            command = self._on_more_button)

        self._more_points.grid(
            row = 3, column = 1, padx = 15, pady = 15,
            sticky = tkinter.W + tkinter. E)

        self._less_points = tkinter.Button(
            master = self._root_window, text = 'LESS', font = FONT,
            command = self._on_less_button)

        self._less_points.grid(
            row = 3, column = 2, padx = 15, pady = 15,
            sticky = tkinter.W + tkinter. E)
           
        ok_button = tkinter.Button(
            master = self._root_window, text = 'OK', font = FONT,
            command = self._on_ok_button)

        ok_button.grid(
            row = 4, column = 0, columnspan = 3, padx = 15, pady = 15,
            sticky = tkinter.N + tkinter.S)

        self._root_window.rowconfigure(0, weight = 1)
        self._root_window.rowconfigure(1, weight = 1)
        self._root_window.rowconfigure(2, weight = 1)
        self._root_window.rowconfigure(3, weight = 1)
        self._root_window.rowconfigure(4, weight = 1)
        self._root_window.columnconfigure(1, weight = 1)
        self._root_window.columnconfigure(2, weight = 1)

        
        self.rows = 0
        self.cols = 0
        self.first_turn = 0
        self.winning_case = ''

        #
        # Important GameState to be sent to main application for initialization
        #
        self.game_state = None



    def run(self) -> game_logic.GameState:
        self._root_window.mainloop()

        return self.game_state
        



    def _on_black_button(self) -> None:
        
        self._black_button = tkinter.Button(
            master = self._root_window, text = 'BLACK', font = FONT,
            state = tkinter.DISABLED)

        self._black_button.grid(row = 2, column = 1, padx = 15, pady = 15,
                           sticky = tkinter.W + tkinter.E)


        self.first_turn = game_logic.BLACK
        

        self._white_button = tkinter.Button(
            master = self._root_window, text = 'WHITE', font = FONT,
            command = self._on_white_button)

        self._white_button.grid(row = 2, column = 2, padx = 15, pady = 15,
                           sticky = tkinter.W + tkinter.E)


    def _on_white_button(self) -> None:
        
        self._white_button = tkinter.Button(
            master = self._root_window, text = 'WHITE', font = FONT,
            state = tkinter.DISABLED)

        self._white_button.grid(row = 2, column = 2, padx = 15, pady = 15,
                           sticky = tkinter.W + tkinter.E)


        self.first_turn = game_logic.WHITE
        

        self._black_button = tkinter.Button(
            master = self._root_window, text = 'BLACK', font = FONT,
            command = self._on_black_button)

        self._black_button.grid(row = 2, column = 1, padx = 15, pady = 15,
                           sticky = tkinter.W + tkinter.E)

    def _on_more_button(self) -> None:

        self._more_button = tkinter.Button(
            master = self._root_window, text = 'MORE', font = FONT,
            state = tkinter.DISABLED)

        self._more_button.grid(row = 3, column = 1, padx = 15, pady = 15,
                           sticky = tkinter.W + tkinter.E)


        self.winning_case = '>'


        self._less_button = tkinter.Button(
            master = self._root_window, text = 'LESS', font = FONT,
            command = self._on_less_button)
        
        self._less_button.grid(row = 3, column = 2, padx = 15, pady = 15,
                               sticky = tkinter.W + tkinter. E)

    def _on_less_button(self) -> None:

        self._less_button = tkinter.Button(
            master = self._root_window, text = 'LESS', font = FONT,
            state = tkinter.DISABLED)

        self._less_button.grid(row = 3, column = 2, padx = 15, pady = 15,
                           sticky = tkinter.W + tkinter.E)


        self.winning_case = '<'


        self._more_button = tkinter.Button(
            master = self._root_window, text = 'MORE', font = FONT,
            command = self._on_more_button)
        
        self._more_button.grid(row = 3, column = 1, padx = 15, pady = 15,
                               sticky = tkinter.W + tkinter. E)

    def _on_ok_button(self) -> None:
        try:
            self.game_state = self._create_blank_game()
        except InvalidInputError:
            self._create_invalid_label()
        else:
            self._root_window.destroy()


    def _create_invalid_label(self) -> None:
        invalid_label = tkinter.Label(
            master = self._root_window, text = 'Invalid Input Given',
            font = FONT, fg = 'red')

        invalid_label.grid(row = 5, column = 0, columnspan = 3, padx = 15, pady = 15,
            sticky = tkinter.N + tkinter.S)
            


    def _create_blank_game(self) -> game_logic.GameState:
        self._check_dimensions()
        self._check_buttons_pressed()

        board = []
        row_contents = []
        for r in range(self.rows):
            for c in range(self.cols):
                row_contents.append(0)
            board.append(row_contents)
            row_contents = []

        return game_logic.GameState(self.rows, self.cols, self.first_turn,
                                    self.winning_case, board)
        

    def _check_dimensions(self) -> None:
        rows = self._row_entry.get()
        cols = self._col_entry.get()
        try:
            rows = int(rows)
            cols = int(cols)
        except:
            raise InvalidInputError()
        else:
            if rows >= 4 and rows <= 16 and rows%2 == 0 and \
               cols >= 4 and cols <= 16 and cols%2 == 0:
                self.rows = rows
                self.cols = cols
            else:
                raise InvalidInputError()

    def _check_buttons_pressed(self) -> None:
        if self.first_turn == 0 or self.winning_case == '':
            raise InvalidInputError()




