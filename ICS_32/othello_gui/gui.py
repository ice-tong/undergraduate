#
# Kian Farsany 55375951
# Project 5
# gui.py
# 

import tkinter
import game_logic
import othello_input


FONT = ('Helvetica', 24)


class OthelloApplication:
    def __init__(self, game_state: game_logic.GameState):
        self._root_window = tkinter.Tk()

        self.game_state = game_state
        self.inputting_black = True
        self.inputting_white = False
        
        self._score_label = tkinter.Label(
            master = self._root_window,
            text = '', font = FONT)

        self._score_label.grid(
            row = 0, column = 0,
            sticky = tkinter.N + tkinter.S + tkinter.W + tkinter.E)
        
        self._canvas = tkinter.Canvas(
            master = self._root_window,
            width = self.game_state.cols * 100,
            height = self.game_state.rows * 100,
            background = '#2D7013')

        self._canvas.grid(
            row = 1, column = 0,
            sticky = tkinter.N + tkinter.S + tkinter.W + tkinter.E)

        self._turn_label = tkinter.Label(
            master = self._root_window,
            text = 'Place the starting black tiles then press ENTER', font = FONT)

        self._turn_label.grid(
            row = 2, column = 0,
            sticky = tkinter.N + tkinter.S + tkinter.W + tkinter.E)

        _full_label = tkinter.Label(
            master = self._root_window,
            text = 'FULL', font = FONT)

        _full_label.grid(
            row = 3, column = 0,
            sticky = tkinter.N + tkinter.S + tkinter.W + tkinter.E)

        self._canvas.bind('<Configure>', self._on_canvas_resized)
        self._canvas.bind('<Button-1>', self._on_click)
        self._root_window.bind('<KeyPress>', self._on_enter)

        self._root_window.rowconfigure(0,weight=0)
        self._root_window.rowconfigure(1,weight=1)
        self._root_window.rowconfigure(2,weight=0)
        self._root_window.rowconfigure(3,weight=0)
        self._root_window.columnconfigure(0,weight=1)
        

    def run(self) -> None:
        self._root_window.mainloop()

    def _on_canvas_resized(self, event: tkinter.Event) -> None:
        self._canvas.delete(tkinter.ALL)
        
        canvas_width = self._canvas.winfo_width()
        canvas_height = self._canvas.winfo_height()
        
        self._redraw_board(canvas_width, canvas_height)
        

    def _on_click(self, event: tkinter.Event) -> None:
        click_x = event.x
        click_y = event.y
        canvas_width = self._canvas.winfo_width()
        canvas_height = self._canvas.winfo_height()
        cell_width = canvas_width / self.game_state.cols
        cell_height = canvas_height / self.game_state.rows

        for r in range(self.game_state.rows):
            for c in range(self.game_state.cols):
                x0 = c * cell_width
                y0 = r * cell_height
                x1 = x0 + cell_width
                y1 = y0 + cell_height
                if click_x > x0 and click_x < x1 and \
                click_y > y0 and click_y < y1 \
                and self.game_state.board[r][c] == game_logic.EMPTY:
                    if self.inputting_black:
                        self.game_state.board[r][c] = game_logic.BLACK
                        self._redraw_board(canvas_width, canvas_height)
                    elif self.inputting_white:
                        self.game_state.board[r][c] = game_logic.WHITE
                        self._redraw_board(canvas_width, canvas_height)
                    else:
                        self._check_valid_move(canvas_width, canvas_height,
                                              (r+1,c+1))
                    

    def _on_enter(self, event: tkinter.Event) -> None:
        if event.keysym == 'Return':
            if self.inputting_black:
                self.inputting_black = False
                self.inputting_white = True
                self._turn_label['text'] = \
                'Place the starting white tiles then press ENTER'
            elif self.inputting_white:
                self._format_turn()
                self._format_winner()
                self.inputting_white = False
                

    def _redraw_board(self, width: int, height: int) -> None:
        rows = self.game_state.rows
        cols = self.game_state.cols
        
        cell_width = width / cols
        cell_height = height / rows
        
        for r in range(rows):
            for c in range(cols):
                x0 = c * cell_width
                y0 = r * cell_height
                x1 = x0 + cell_width
                y1 = y0 + cell_height
                self._canvas.create_rectangle(x0, y0, x1, y1, outline = 'white')
                self._draw_oval(x0, y0, x1, y1, r, c, cell_width, cell_height)
                
        self._format_score()
        if not self.game_state.game_over() and not self.inputting_white:
            self._format_turn()

    

    def _draw_oval(self, x0: int, y0: int, x1: int, y1: int, r: int, c: int,
                   cell_width: int, cell_height: int) -> None:
        x0 = x0 + (.1 * cell_width)
        y0 = y0 + (.1 * cell_height)
        x1 = x1 - (.1 * cell_width)
        y1 = y1 - (.1 * cell_height)
        if self.game_state.board[r][c] == game_logic.BLACK:
            self._canvas.create_oval(x0, y0, x1, y1, fill = 'black',
                                     outline = 'white')
        elif self.game_state.board[r][c] == game_logic.WHITE:
            self._canvas.create_oval(x0, y0, x1, y1, fill = 'white')

    def _check_valid_move(self, width: int, height: int,
                          move: (int, int)) -> None:
        try:
            self.game_state.move(move)
        except game_logic.InvalidMoveError:
            pass
        except game_logic.GameOverError:
            pass
        else:
            self._canvas.delete(tkinter.ALL)
            self._redraw_board(width, height)
            self._format_winner()
        

    def _format_turn(self) -> None:
        if self.game_state.turn == game_logic.BLACK:
            turn = 'Black'
        else:
            turn = 'White'
            
        self._turn_label['text'] = f'Turn: {turn}'

    def _format_score(self) -> None:
        black_total = self.game_state.count_black_tiles()
        white_total = self.game_state.count_white_tiles()
        
        self._score_label['text'] = 'Black: {}   White: {}'.format(black_total,
                                                                   white_total)

    def _format_winner(self) -> None:
        if self.game_state.game_over():
            if self.game_state.winner() == game_logic.BLACK:
                self._turn_label['text'] = 'Black Wins!'
            elif self.game_state.winner() == game_logic.WHITE:
                self._turn_label['text'] = 'White Wins!'
            else:
                self._turn_label['text'] = "It's a tie!"
            

    

if __name__ == '__main__':
    game_state = othello_input.OthelloInput().run()
    
    OthelloApplication(game_state).run()
