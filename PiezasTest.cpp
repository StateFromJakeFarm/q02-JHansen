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

TEST(PiezasTest, gameState) {
    Piezas myBoard;

    myBoard.dropPiece(0);
    myBoard.dropPiece(0);
    myBoard.dropPiece(1);
    myBoard.dropPiece(1);
    myBoard.dropPiece(2);
    myBoard.dropPiece(2);

    myBoard.print();

    EXPECT_EQ(Invalid, myBoard.gameState());
}
