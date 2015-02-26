#ifndef _TETRIS_
#define _TETRIS_

#pragma once

#include "Board.hpp"
#include "TetriMino.hpp"
#include "SGL.hpp"

#define START_POS_X 6
#define START_POS_Y 1

#include < random >

class Tetris{
public:
	Tetris( float x, float y );
	~Tetris();
	void Run();
private:
	void SpawnTetriMino();
	void DrawTetriMinos();
	bool MoveTetriMino();
	void LockTetriMino();
	void DeleteLines();
	void DownLines();
	bool GameOver();
	void DeleteAllTetriMinos();
	void ClearTetriMino();
	//void Console();
private:
	unsigned int ctrl_timer;
	bool key_flag;
	bool spawn;
	Board *board;
	list< TetriMino* > minos;
	list< TetriMino * >::iterator itr;
};

Tetris::Tetris( float x, float y ){
	board = new Board( x , y );
	spawn = true;
	ctrl_timer = 0;
	key_flag = false;
}

void Tetris::SpawnTetriMino(){
	random_device rnd;
	mt19937 mt( rnd() );
	uniform_int_distribution<> rand( 0, 6 );
	minos.push_back( new TetriMino( rand( mt ), board, START_POS_X, START_POS_Y ) );
	spawn = false;
}

void Tetris::DrawTetriMinos(){
	for( itr = minos.begin(); itr != minos.end(); itr++ ){
		( *itr )->Draw();
	}
}

bool Tetris::MoveTetriMino(){
	itr = minos.end();
	itr--;
	if( ctrl_timer == 30 ){
		if( ( *itr )->MoveDown() == false ){
			return true;
		}
		ctrl_timer = 0;
	}

	if( Keyboard::GetLeaveKey( SDL_SCANCODE_DOWN ) ){
		key_flag = false; 
	}
	if( Keyboard::GetPushedKey( SDL_SCANCODE_DOWN ) && key_flag == false ){
		key_flag = true;
		if( ( *itr )->MoveDown() == false ){
			return true;
		}
		ctrl_timer = 0;
	}

	if( Keyboard::GetLeaveKey( SDL_SCANCODE_RIGHT ) ){
		key_flag = false; 
	}
	if( Keyboard::GetPushedKey( SDL_SCANCODE_RIGHT ) && key_flag == false ){
		key_flag = true;
		( *itr )->MoveRight();
	}

	if( Keyboard::GetLeaveKey( SDL_SCANCODE_LEFT ) ){
		key_flag = false; 
	}
	if( Keyboard::GetPushedKey( SDL_SCANCODE_LEFT ) && key_flag == false ){
		key_flag = true;
		( *itr )->MoveLeft();
	}

	if( Keyboard::GetLeaveKey( SDL_SCANCODE_X ) ){
		key_flag = false; 
	}
	if( Keyboard::GetPushedKey( SDL_SCANCODE_X ) && key_flag == false ){
		key_flag = true;
		( *itr )->RotateRight();
	}

	if( Keyboard::GetLeaveKey( SDL_SCANCODE_Z ) ){
		key_flag = false; 
	}
	if( Keyboard::GetPushedKey( SDL_SCANCODE_Z ) && key_flag == false ){
		key_flag = true;
		( *itr )->RotateLeft();
	}
	//TODO
	if( Keyboard::GetLeaveKey( SDL_SCANCODE_SPACE ) ){
		key_flag = false; 
	}
	if( Keyboard::GetPushedKey( SDL_SCANCODE_SPACE ) && key_flag == false ){
		key_flag = true;
		while( ( *itr )->MoveDown() );
		return true;
	}
	ctrl_timer++;
	return false;
}

void Tetris::LockTetriMino(){
	itr = minos.end();
	itr--;
	( *itr )->Lock();
	spawn = true;
}

void Tetris::DeleteLines(){
	int count_block = 0;
	for( int y = 20; y > 0; y-- ){
		for( int x = 1; x < 11; x++ ){
			if( board->GetData( x, y ) )count_block++;
			if( count_block == 10 ){
				for( int del_x = 1; del_x < 11; del_x++ ){
					for( itr = minos.begin(); itr != minos.end(); itr++ ){
						( *itr )->DeleteBlock( del_x, y );
					}
				}
			}
		}
		count_block = 0;
	}
}

void Tetris::DownLines(){
	int count_empty = 0;
	bool isblock = false;
	for( int y = 1; y < 21; y++ ){
		for( int x = 1; x < 11; x++ ){
			if( board->GetData( x, y ) )isblock = true;
			if( isblock == true && board->GetData( x, y ) == 0 )count_empty++;
			if( count_empty == 10 ){
				for( int down_y = y; down_y > 0; down_y-- ){
					for( int down_x = 1; down_x < 11; down_x++ ){
						if( board->GetData( down_x, down_y - 1) ){
							board->SetData( down_x, down_y - 1, 0 );
							board->SetData( down_x, down_y, 1 );
							for( itr = minos.begin(); itr != minos.end(); itr++ ){
								( *itr )->TargetMoveDown( down_x, down_y - 1 );
							}
						}
					}
				}
			}
		}
		count_empty = 0;
	}
}

bool Tetris::GameOver(){
	for( int x = 1; x < 11; x++ ){
		if( board->GetData( x, 0 ) ){
			return true;
		}
	}
	return false;
}
/*
void Tetris::Console(){
	system( "cls" );
	for( int y = 1; y < 21; y++ ){
		for( int x = 1; x < 11; x++ ){
			if( board->GetData( x, y ) ){
				cout<< "¡";
			}else{
				cout<< " ";
			}
			
		}
		cout<<endl;
	}
}
*/
void Tetris::DeleteAllTetriMinos(){
	for( int x = 1; x < 11; x++ ){
		for( int y = 0; y < 21; y++ ){
			for( itr = minos.begin(); itr != minos.end(); itr++ ){
				( *itr )->DeleteBlock( x, y );
			}
		}
	}
}

void Tetris::ClearTetriMino(){
	list< TetriMino* >::iterator del_itr;
	for( del_itr = minos.begin(); del_itr != minos.end(); del_itr++ ){
		if( ( *del_itr )->GetHadBlock() == 0 ){
			if( del_itr == itr ){
				itr++;
			}
			delete ( *del_itr );
			minos.erase( del_itr );
			return;
		}
	}
}

void Tetris::Run(){
	board->DrawBackBoard();
	if( spawn ){
		//Spawn tetri mino;
		if( GameOver() ){
			// gameover
			DeleteAllTetriMinos();

		}else{
			SpawnTetriMino();
		}
	}else{
		if( MoveTetriMino() ){
			// lock Mino
			LockTetriMino();
			DeleteLines();
			DownLines();
			//Console();
		}
		//Move tetri mino;
	}
	ClearTetriMino();
	DrawTetriMinos();
	board->DrawFrame();
}

Tetris::~Tetris(){
	DeleteAllTetriMinos();
	ClearTetriMino();
	delete board;
}

#endif

