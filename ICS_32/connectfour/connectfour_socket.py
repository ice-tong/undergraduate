#
# Project 2
# Kian Farsany 55375951
# Darrel Belen 72866173
# connectfour_socket.py
#

from collections import namedtuple
import socket

DEBUG_TRACE = False

Connection = namedtuple(
    'Connection',
    ['socket', 'input', 'output'])



class ProtocolError(Exception):
    pass



def connect(host: str, port: int) -> Connection:
    '''Connect to the given host on the given port'''
    game_socket = socket.socket()

    game_socket.connect((host, port))

    game_input = game_socket.makefile('r')
    game_output = game_socket.makefile('w')

    return Connection(
        socket = game_socket,
        input = game_input,
        output = game_output)

def hello(connection: Connection, username: str) -> None:
    '''Logs the user into the server using
       the proper protocol'''
    _write_line(connection, 'I32CFSP_HELLO ' + username)

    response = _read_line(connection)
    if response != 'WELCOME ' + username:
        raise ProtocolError()

def request_ai_game(connection: Connection) -> None:
    '''Initiate an AI game with the server'''
    _write_line(connection, 'AI_GAME')

    response = _read_line(connection)
    if response != 'READY':
        raise ProtocolError()

def send_move(connection: Connection, move: str) -> None:
    '''Send a move to the server, either drop or pop given
       that move is in the proper format'''   
    _write_line(connection, move)


def handle_responses(connection: Connection) -> (str, str):
    '''Return the proper response from the server as a tuple with a move and a winner'''
    response = _read_line(connection)
    response_move = ''
    response_after_move = ''
    
    if response == 'WINNER_RED':
        return ('WINNER_RED', '')
    elif response == 'WINNER_YELLOW':
        return ('WINNER_YELLOW', '')
    elif response == 'OKAY':
        response_move = _read_line(connection)
        response_after_move = _read_line(connection)
        if response_after_move == 'WINNER_RED':
            return ('WINNER_RED', response_move)
        elif response_after_move == 'WINNER_YELLOW':
            return ('WINNER_YELLOW', response_move)
        elif response_after_move == 'READY':
            return ('', response_move)
    
        
        
def close(connection: Connection) -> None:
    '''Close the connection to the server'''
    connection.input.close()
    connection.output.close()
    connection.socket.close()
    

def _read_line(connection: Connection) -> str:
    '''Read a line of text from the server without a newline'''
    line = connection.input.readline()[:-1]
    if DEBUG_TRACE:
        print('RCVD: ', line)

    return line

def _write_line(connection: Connection, line: str) -> None:
    '''Write a line of text to the server with a new line sequence'''
    connection.output.write(line + '\r\n')
    if DEBUG_TRACE:
        print('SENT: ', line)
    connection.output.flush()
