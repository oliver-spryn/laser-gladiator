// Programming 2D Games
// Copyright (c) 2011 by:
// Charles Kelly
// Space War winmain.cpp v1.0

#define _CRTDBG_MAP_ALLOC
#define WIN32_LEAN_AND_MEAN

#include <crtdbg.h>
#include <stdlib.h>
#include "TestGame.h"
#include "Window.h"
#include <Windows.h>

// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 

// Game pointer
TestGame *game = NULL;
HWND hwnd = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//Check for memory leaks if debug build
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

//Create the objects used through out this program
	MSG msg;
	Window win(hwnd, hInstance, nCmdShow);
	game = new TestGame();

	try {
	//Create the game window
		win.setEventHandler(WinProc);
		win.setHeight(GAME_HEIGHT);
		win.setName(CLASS_NAME);
		win.setTitle(GAME_TITLE);
		win.setWidth(GAME_WIDTH);
		win.build();

	//Initialize the game
		game->initialize(hwnd);

	//Execute the game until completion
        int done = 0;

		do {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//Look for a quit message
                if (msg.message == WM_QUIT)
                    done = 1;
				
			//Decode and pass messages on to WinProc
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                game->run(hwnd);
			}
        } while(!done);

        SAFE_DELETE(game);
        return msg.wParam;
	} catch (const GameError &err) {
		game->deleteAll();
		win.destroy();
        MessageBox(NULL, err.getMessage(), "Error", MB_OK);
    } catch (...) {
		game->deleteAll();
        win.destroy();
        MessageBox(NULL, "Unknown error occured in game.", "Error", MB_OK);
    }

    SAFE_DELETE(game);
    return 0;
}

LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return game->messageHandler(hwnd, msg, wParam, lParam);
}