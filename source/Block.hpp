#ifndef _BLOCK_
#define _BLOCK_

#pragma once

#include "Board.hpp"

enum{
	TETRIS_TYPE_I = 0,
	TETRIS_TYPE_O = 1,
	TETRIS_TYPE_S = 2,
	TETRIS_TYPE_Z = 3,
	TETRIS_TYPE_L = 4,
	TETRIS_TYPE_J = 5,
	TETRIS_TYPE_T = 6,
};

struct _BLOCK_POS{
	int x;
	int y;
};

struct _COLOR{
	float r;
	float g;
	float b;
};

class Block{
public:
	Block( int type, Board *board );
	void Draw();
	_BLOCK_POS GetPos();
	int x;
	int y;
private:
	int type;
	_COLOR color;
	Board *board;
};

Block::Block( int type, Board *board ) : type( type ), board( board ){
	switch( this->type ){
	case TETRIS_TYPE_I:
		color.r = 0.000f; color.g = 0.808f; color.b = 0.820f;
		break;
	case TETRIS_TYPE_O:
		color.r = 1.000f; color.g = 0.843f; color.b = 0.000f;
		break;
	case TETRIS_TYPE_S:
		color.r = 0.196f; color.g = 0.804f; color.b = 0.196f;
		break;
	case TETRIS_TYPE_Z:
		color.r = 1.000f; color.g = 0.271f; color.b = 0.000f;
		break;
	case TETRIS_TYPE_L:
		color.r = 1.000f; color.g = 0.549f; color.b = 0.000f;
		break;
	case TETRIS_TYPE_J:
		color.r = 0.514f; color.g = 0.435f; color.b = 1.000f;
		break;
	case TETRIS_TYPE_T:
		color.r = 1.000f; color.g = 0.412f; color.b = 0.706f;
	default:
		break;
	};
}

_BLOCK_POS Block::GetPos(){
	_BLOCK_POS pos;
	pos.x = this->x;
	pos.y = this->y;
	return pos;
}

void Block::Draw(){
	_POS pos = board->GetPos( x, y );
	glColor3f( color.r, color.g, color.b );
	glRectf( pos.x, pos.y, pos.x + 0.2f, pos.y - 0.2f );
	glColor3f( 0, 0, 0 );
	glBegin( GL_LINE_STRIP );
	glVertex2f( pos.x, pos.y );
	glVertex2f( pos.x + 0.2f, pos.y );
	glVertex2f( pos.x + 0.2f, pos.y - 0.2f );
	glVertex2f( pos.x, pos.y - 0.2f );
	glVertex2f( pos.x, pos.y );
	glEnd();
}

#endif