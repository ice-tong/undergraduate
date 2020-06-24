#include "StudentAI.h"
#include <random>

const int BLACK = 1;
//The following part should be completed by students.
//The students can modify anything except the class name and exisiting functions and varibles.
StudentAI::StudentAI(int col,int row,int p)
    :AI(col, row, p)
{
    board = Board(col,row,p);
    board.initializeGame();
    player = 2;
}

Move StudentAI::GetMove(Move move) {
    if (move.seq.empty()) {
        player = 1;
    }
    else {
        board.makeMove(move,player == 1?2:1);
    }

    // This is so it just doesn't decide to do the first move and picks a random move as the best move
    vector<vector<Move>> moves = board.getAllPossibleMoves(player);
    int randI = rand() % (moves.size());
    vector<Move> checker_moves = moves[randI];
    int randJ = rand() % (checker_moves.size());
    Move bestMove = checker_moves[randJ];


    // Recursive minimax implementation
    int max = std::numeric_limits<int>::min();
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    for (int i = 0; i < moves.size(); i++) {
        for (int j = 0; j < moves[i].size(); j++) {
            Move tempMove = moves[i][j];
            board.makeMove(tempMove, player);

            // Return the move if we get a win
            if (board.isWin(player) == player)
                return tempMove;

            // Return the move if we get a tie
            if (board.isWin(player) == -1)
                return tempMove;

            // Pass in false since we just made a move.
            int temp = minimax(5, alpha, beta, false);
            if (temp > max) {
                bestMove = tempMove;
                max = temp;
            }
            board.Undo();
        }
    }

    board.makeMove(bestMove, player);
    return bestMove;
}

int StudentAI::minimax(int depth, int alpha, int beta, bool  maximizingPlayer) {
    if (depth == 0)
        return eval();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        vector<vector<Move>> moves = board.getAllPossibleMoves(player);
        for (int i = 0; i < moves.size(); i++) {
            for (int j = 0; j < moves[i].size(); j++) {
                board.makeMove(moves[i][j], player);
                int eval = minimax(depth - 1, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, maxEval);
                if(beta <= alpha) {
                    board.Undo();
                    break;
                }
                board.Undo();
            }
        }
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();
        /* Passes in (abs(player-2)+1) */
        vector<vector<Move>> moves = board.getAllPossibleMoves((abs(player-2)+1));
        for (int i = 0; i < moves.size(); i++) {
            for (int j = 0; j < moves[i].size(); j++) {
                board.makeMove(moves[i][j], (abs(player-2)+1));
                int eval = minimax(depth - 1, alpha, beta, true);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, minEval);
                if(beta <= alpha) {
                    board.Undo();
                    break;
                }
                board.Undo();
            }
        }
        return minEval;
    }
}

/* Very basic evaluation function */
int StudentAI::eval() {
    int newBlackCount = board.blackCount;
    int newWhiteCount = board.whiteCount;
    int halfOfBoard = board.row/2;


    for(int i = 0; i < board.row; i++) {
        for(int j = 0; j < board.col; j++) {
            if(board.board[i][j].toString() == "b" && i < halfOfBoard)
            {
                newBlackCount = newBlackCount + 4;
            }
            if(board.board[i][j].toString() == "w" && i >= halfOfBoard)
            {
                newWhiteCount = newWhiteCount + 4;
            }
            if(board.board[i][j].toString() == "b" && i >= halfOfBoard)
            {
                newBlackCount = newBlackCount + 6;
            }
            if(board.board[i][j].toString() == "w" && i < halfOfBoard)
            {
                newWhiteCount = newWhiteCount + 6;
            }
            if(board.board[i][j].isKing && board.board[i][j].toString() == "B")
            {
                newBlackCount = newBlackCount + 9;
            }
            if(board.board[i][j].isKing && board.board[i][j].toString() == "W")
            {
                newWhiteCount = newWhiteCount + 9;
            }
        }
    }
    return(player==BLACK)?newBlackCount-newWhiteCount:newWhiteCount-newBlackCount;
}
/*
    for(int i = 0; i < board.row; i++)
    {
        for(int j = 0; j < board.col; j++)
        {
            cout << setw(3) << board.board[i][j].isKing << board.board[i][j].toString();
        }
        cout << endl;
    }
*/
