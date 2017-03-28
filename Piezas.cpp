#include "Piezas.h"
#include<iostream>
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas() {
    turn = X;

    board.resize(BOARD_ROWS);
    for(int r=0; r<BOARD_ROWS; r++) {
        board[r].resize(BOARD_COLS);

        for(int c=0; c<BOARD_COLS; c++)
            board[r][c] = Blank;
    }
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset() {
    for(int r=0; r<BOARD_ROWS; r++) {
        for(int c=0; c<BOARD_COLS; c++)
            board[r][c] = Blank;
    }
}

void Piezas::print() {
    for(int r=0; r<BOARD_ROWS; r++) {
        for(int c=0; c<BOARD_COLS; c++) {
            std::cout << pieceAt(r, c) << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column) {
    if(column >= 0 && column < BOARD_COLS) {
        for(int r=0; r<BOARD_ROWS; r++) {
            if(pieceAt(r, column) == Blank) {
                board[r][column] = turn;

                Piece justPlaced = turn;
                if(turn == X)
                    turn = O;
                else
                    turn = X;

                return justPlaced;
            }
        }

        return Blank;
    } else {
        return Invalid;
    }
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column) {
    if(row >= 0 && row < BOARD_ROWS && column >= 0 && column < BOARD_COLS)
        return board[row][column];

    return Invalid;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState() {
    int xH = 0;
    int xV = 0;
    int oH = 0;
    int oV = 0;

    int maxX = 0;
    int maxO = 0;

    Piece lastH = Blank;
    Piece lastV = Blank;
    for(int r=0; r<BOARD_ROWS; r++) {
        for(int c=0; c<BOARD_COLS; c++) {
            Piece cur = pieceAt(r, c); 
            Piece prevH = pieceAt(r, c-1);
            Piece prevV = pieceAt(r-1, c);

            if(cur != Blank && cur == prevH) {
                if(cur == X) {
                    if(lastH != cur) {
                        if(maxO < oH) {
                            maxO = oH;
                            oH = 0;
                        }
                    }

                    ++xH;
                } else {
                    if(lastH != cur) {
                        if(maxX < xH) {
                            maxX = xH;
                            xH = 0;
                        }
                    }

                    ++oH;
                }
            } else {
                lastH = cur;
            }
        }
    }
std::cout << "maxX = " << maxX << std::endl;
std::cout << "maxO = " << maxO << std::endl;
    return Invalid;
}










