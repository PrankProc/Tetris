#include "SGL.hpp"
#include "Tetris.hpp"

int main( int argc, char **args ){
	
	SGL::SGL_INITDATA init_data;
		init_data.win_tile_name = _T( "Tetris by SGL" );
		init_data.win_size_width = 800;
		init_data.win_size_height = 600;
		init_data.win_start_pos_x = NULL;
		init_data.win_start_pos_y = NULL;
		init_data.win_flag = NULL;
		init_data.fps = 60;
	unique_ptr< SGL::Core > core( new Core( init_data ) );

	Tetris tetris( -1.2f, 2.2f );

	while( core->SGL_Update() ){
		glClear( GL_COLOR_BUFFER_BIT );
		glClearColor( 255,255,255,255 );

		tetris.Run();

		glFlush();
	}

	return 0;
}