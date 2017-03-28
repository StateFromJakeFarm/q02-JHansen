/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
#include <iostream>
using namespace std;
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, constructor) {
    Piezas myBoard;

    // ensure myBoard initialized with all spaces set to 'Blank'
    for(int r=0; r<BOARD_ROWS; r++) {
        for(int c=0; c<BOARD_COLS; c++) {
            EXPECT_EQ(Blank, myBoard.pieceAt(r, c));
        }
    }
}

TEST(PiezasTest, dropPiece) {
    Piezas myBoard;

    // space should be blank to begin with
    EXPECT_EQ(Blank, myBoard.pieceAt(0, 0));

    // place piece
    myBoard.dropPiece(0);

    // ensure piece was placed
    EXPECT_EQ(X, myBoard.pieceAt(0, 0));

    // place another piece in column
    myBoard.dropPiece(0);

    // new piece should be above the old one
    EXPECT_EQ(O, myBoard.pieceAt(1, 0));
    // old piece should still be intact
    EXPECT_EQ(X, myBoard.pieceAt(0, 0));
    // space above new piece should still be Blank
    EXPECT_EQ(Blank, myBoard.pieceAt(2, 0));
}

TEST(PiezasTest, reset) {
    Piezas myBoard;

    // fill myBoard completely
    for(int c=0; c<BOARD_COLS; c++) {
        for(int r=0; r<BOARD_ROWS; r++)
            myBoard.dropPiece(c);
    }

    // ensure myBoard is currently filled
    Piece cur = X;
    for(int c=0; c<BOARD_COLS; c++) {
        for(int r=0; r<BOARD_ROWS; r++) {
            EXPECT_EQ(cur, myBoard.pieceAt(r, c));

            if(cur == X)
                cur = O;
            else
                cur = X;
        }
    }

    // clear myBoard
    myBoard.reset();

    // ensure myBoard was cleared
    for(int c=0; c<BOARD_COLS; c++) {
        for(int r=0; r<BOARD_ROWS; r++)
            EXPECT_EQ(Blank, myBoard.pieceAt(r, c));
    }
}

TEST(PiezasTest, gameState) {
    Piezas myBoard;

    // X win horizontal
    myBoard.dropPiece(0);
    myBoard.dropPiece(0);
    myBoard.dropPiece(1);
    myBoard.dropPiece(1);
    myBoard.dropPiece(2);
    EXPECT_EQ(X, myBoard.gameState());

    // O win vertical
    myBoard.reset();
    myBoard.dropPiece(1);
    myBoard.dropPiece(2);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
myBoard.print();
    EXPECT_EQ(O, myBoard.gameState());

    // tie horizontal
    myBoard.reset();
    myBoard.dropPiece(0);
    myBoard.dropPiece(2);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    EXPECT_EQ(Invalid, myBoard.gameState());

    // tie vertical
    myBoard.reset();
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    EXPECT_EQ(Invalid, myBoard.gameState());

    // full-board cat's game
    myBoard.reset();
    for(int c=0; c<BOARD_COLS; c++) {
        for(int r=0; r<BOARD_ROWS; r++)
            myBoard.dropPiece(c);
    }
    EXPECT_EQ(Blank, myBoard.gameState());

    // more permutations
    myBoard.reset();
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    myBoard.dropPiece(4);
    myBoard.dropPiece(2);
    EXPECT_EQ(Invalid, myBoard.gameState());
}



















