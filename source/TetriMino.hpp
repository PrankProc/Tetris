#ifndef _TETRI_MINO_
#define _TETRI_MINO_

#pragma once

#include "Board.hpp"
#include "Block.hpp"


#include <list>

using namespace std;

class TetriMino{
public:
	TetriMino( int type, Board *board, int start_pos_x, int start_pos_y );
	void Draw();
	bool MoveDown();
	void TargetMoveDown( int x, int y );
	void MoveLeft();
	void MoveRight();
	void RotateLeft();
	void RotateRight();
	void DeleteBlock( int x, int y );
	int GetHadBlock();
	void Lock();
private:
	int had_block;
	bool move;
	int type;
	_BLOCK_POS block_pos_temp[ 4 ];
	list< Block* > block;
	list< Block * >::iterator itr;
	Board *board;
};

TetriMino::TetriMino( int type, Board *board, int start_pos_x, int start_pos_y ) : type( type ), board( board ){
	had_block = 4;
	for( int i = 0; i < 4; i++ ){
		block.push_back( new Block( this->type, board ) );
	}
	itr = block.begin();
	( *itr )->x = start_pos_x; ( *itr )->y = start_pos_y; itr++;
	switch( this->type ){
	case TETRIS_TYPE_I:
		( *itr )->x = start_pos_x + 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x - 2; ( *itr )->y = start_pos_y; itr++;
		break;
	case TETRIS_TYPE_O:
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x; ( *itr )->y = start_pos_y - 1; itr++;
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y - 1; itr++;
		break;
	case TETRIS_TYPE_S:
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x; ( *itr )->y = start_pos_y - 1; itr++;
		( *itr )->x = start_pos_x + 1; ( *itr )->y = start_pos_y - 1; itr++;
		break;
	case TETRIS_TYPE_Z:
		( *itr )->x = start_pos_x + 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x; ( *itr )->y = start_pos_y - 1; itr++;
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y - 1; itr++;
		break;
	case TETRIS_TYPE_L:
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x + 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x + 1; ( *itr )->y = start_pos_y - 1; itr++;
		break;
	case TETRIS_TYPE_J:
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x + 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y - 1; itr++;
		break;
	case TETRIS_TYPE_T:
		( *itr )->x = start_pos_x - 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x + 1; ( *itr )->y = start_pos_y; itr++;
		( *itr )->x = start_pos_x; ( *itr )->y = start_pos_y - 1; itr++;
	default:
		break;
	};
}

void TetriMino::Draw(){
	for( itr = block.begin(); itr != block.end(); itr++ ){
		( *itr )->Draw();
	}
}


bool TetriMino::MoveDown(){
	for( itr = block.begin(); itr != block.end(); itr++ ){
		if( board->GetData( ( *itr )->x, ( *itr )->y + 1 ) != 0 ){
			return false;
		}
	}
	for( itr = block.begin(); itr != block.end(); itr++ ){
		( *itr )->y++;
	}
	return true;
}


void TetriMino::MoveLeft(){
	for( itr = block.begin(); itr != block.end(); itr++ ){
		if( board->GetData( ( *itr )->x - 1, ( *itr )->y ) != 0 ){
			return;
		}
	}
	for( itr = block.begin(); itr != block.end(); itr++ ){
		( *itr )->x--;
	}
}

void TetriMino::MoveRight(){
	for( itr = block.begin(); itr != block.end(); itr++ ){
		if( board->GetData( ( *itr )->x + 1, ( *itr )->y ) != 0 ){
			return;
		}
	}
	for( itr = block.begin(); itr != block.end(); itr++ ){
		( *itr )->x++;
	}
}

void TetriMino::RotateRight(){
	int temp;
	itr = block.begin();
	int restore_x = ( *itr )->x + ( *itr )->y;
	int restore_y = ( *itr )->y - ( *itr )->x;
	if( type == 1 ){
		return;
	}

	for( itr = block.begin(); itr != block.end(); itr++ ){
		int x = ( *itr )->x;
		int y = ( *itr )->y;
		temp = x;
		x = -y;
		y = temp;
		x += restore_x;
		y += restore_y;
		if( board->GetData( x, y ) != 0 ){
			return;
		}
	}

	for( itr = block.begin(); itr != block.end(); itr++ ){
		temp = ( *itr )->x;
		( *itr )->x = -( *itr )->y;
		( *itr )->y = temp;
		( *itr )->x += restore_x;
		( *itr )->y += restore_y;
	}
}

void TetriMino::RotateLeft(){
	int temp;
	itr = block.begin();
	int restore_x = ( *itr )->x - ( *itr )->y;
	int restore_y = ( *itr )->y + ( *itr )->x;
	if( type == 1 ){
		return;
	}

	for( itr = block.begin(); itr != block.end(); itr++ ){
		int x = ( *itr )->x;
		int y = ( *itr )->y;
		temp = x;
		x = y;
		y = -temp;
		x += restore_x;
		y += restore_y;
		if( board->GetData( x, y ) != 0 ){
			return;
		}
	}

	for( itr = block.begin(); itr != block.end(); itr++ ){
		temp = ( *itr )->x;
		( *itr )->x = ( *itr )->y;
		( *itr )->y = -temp;
		( *itr )->x += restore_x;
		( *itr )->y += restore_y;
	}

}

void TetriMino::Lock(){
	for( itr = block.begin(); itr != block.end(); itr++ ){
		board->SetData( ( *itr )->x, ( *itr )->y, 1 );
	}
}

void TetriMino::TargetMoveDown( int x, int y ){
	for( itr = block.begin(); itr != block.end(); itr++ ){
		if( ( *itr )->x == x && ( *itr )->y == y ){
			( *itr )->y++;
		}
	}
}

int TetriMino::GetHadBlock(){
	return had_block;
}

void TetriMino::DeleteBlock( int x, int y ){
	list< Block * >::iterator del_itr;
	for( del_itr = block.begin(); del_itr != block.end(); del_itr++ ){
		if( ( *del_itr )->x == x && ( *del_itr )->y == y ){
			if( del_itr == itr ){	// if itr is live
				itr++;
			}
			board->SetData( ( *del_itr )->x, ( *del_itr )->y, 0 );
			delete ( *del_itr );
			block.erase( del_itr );
			had_block--;
			return;
		}
	}
}

#endif
