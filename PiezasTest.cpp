/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
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
    for(int r=0; r<BOARD_ROWS; r++) {
        for(int c=0; c<BOARD_COLS; c++) {
            EXPECT_EQ(Blank, myBoard.pieceAt(r, c));
        }
    }
}

TEST(PiezasTest, dropPiece) {
    Piezas myBoard;

    EXPECT_EQ(Blank, myBoard.pieceAt(0, 0));

    myBoard.dropPiece(0);

    EXPECT_EQ(X, myBoard.pieceAt(0, 0));

    myBoard.dropPiece(0);

    EXPECT_EQ(O, myBoard.pieceAt(1, 0));
    EXPECT_EQ(X, myBoard.pieceAt(0, 0));
    EXPECT_EQ(Blank, myBoard.pieceAt(2, 0));
}

TEST(PiezasTest, reset) {
    Piezas myBoard;

    for(int c=0; c<BOARD_COLS; c++) {
        for(int r=0; r<BOARD_ROWS; r++)
            myBoard.dropPiece(c);
    }

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

    myBoard.reset();

    for(int c=0; c<BOARD_COLS; c++) {
        for(int r=0; r<BOARD_ROWS; r++)
            EXPECT_EQ(Blank, myBoard.pieceAt(r, c));
    }
}

TEST(PiezasTest, gameState) {
    Piezas myBoard;

    myBoard.dropPiece(0);
    myBoard.dropPiece(0);
    myBoard.dropPiece(1);
    myBoard.dropPiece(1);
    myBoard.dropPiece(2);

    EXPECT_EQ(X, myBoard.gameState());

    myBoard.reset();
    myBoard.dropPiece(1);
    myBoard.dropPiece(2);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);
    myBoard.dropPiece(1);
    myBoard.dropPiece(3);

    myBoard.print();
    EXPECT_EQ(O, myBoard.gameState());
}
