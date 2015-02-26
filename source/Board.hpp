#ifndef _BOARD_
#define _BOARD_

#pragma once

#include "SDL_opengl.h"

struct _POS{
	float x;
	float y;
};

struct _BOARD_DATA{
	_POS pos_f[ 12 ][ 22 ];
	int pos_i[ 12 ][ 22 ];
};

class Board{
public:
	Board( float x, float y );
	void DrawBackBoard();
	void DrawFrame();
	void SetData( int x, int y, int data );
	int GetData( int x, int y);
	_POS GetPos( int x, int y );
private:
	void DrawEmptyCell( float x, float y );
	void DrawWallCell( float x, float y );
	_BOARD_DATA board_data;
};

Board::Board( float x, float y ){
	float sx = x;
	float sy = y;
	for( int i = 0; i < 12; i++ ){
		for( int j = 0; j < 22; j++ ){
			if( i == 0 || i == 11 || j == 21 ){
				board_data.pos_i[ i ][ j ] = 1;
			}else{
				board_data.pos_i[ i ][ j ] = 0;
			}
			board_data.pos_f[ i ][ j ].y = sy;
			board_data.pos_f[ i ][ j ].x = sx;
			sy -= 0.2f;
		}
		sy = y;
		sx += 0.2f;
	}
}

void Board::DrawBackBoard(){
	for( int i = 0; i < 12; i++ ){
		for( int j = 0; j < 22; j++ ){
			DrawEmptyCell( board_data.pos_f[ i ][ j ].x, board_data.pos_f[ i ][ j ].y );
		}
	}
}

void Board::DrawFrame(){
	for( int i =0; i < 12; i++ ){
		for( int j = 0; j < 22; j++ ){
			if( i == 0 || i == 11 || j == 0 || j == 21 ){
				DrawWallCell( board_data.pos_f[ i ][ j ].x, board_data.pos_f[ i ][ j ].y );
			}
		}
	}
};

_POS Board::GetPos( int x, int y ){
	_POS pos;
	pos.x = board_data.pos_f[ x ][ y ].x;
	pos.y = board_data.pos_f[ x ][ y ].y;
	return pos;
}

void Board::SetData( int x, int y, int data ){
	board_data.pos_i[ x ][ y ] = data;
}

int Board::GetData( int x, int y){
	return board_data.pos_i[ x ][ y ];
}

void Board::DrawEmptyCell( float x, float y ){
	glColor3f( 0, 0, 0 );
	glBegin( GL_LINE_STRIP );
	glVertex2f( x, y );
	glVertex2f( x + 0.2f, y );
	glVertex2f( x + 0.2f, y - 0.2f );
	glVertex2f( x, y - 0.2f );
	glVertex2f( x, y );
	glEnd();
}

void Board::DrawWallCell( float x, float y ){
	glColor3f( 0, 0, 0 );
	glRectf( x, y, x + 0.2f, y - 0.2f );
}

#endif