//-------------- include section ---------------
#pragma region Includes
#include <iostream> 
#include "GameController.h"
#include "ErrorDialog.h"
#pragma endregion

//-------------- libs --------------------------
#pragma region Libs
// for SFML library
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#pragma comment ( lib, "sfml-network-d.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#else
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#pragma comment ( lib, "sfml-network.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#endif
#pragma endregion

//-------------- main --------------------------
int main() {
	// initialize random seed
	srand(unsigned(time(NULL)));

	try {
		// run game
		GameController gameController;
		gameController.run();
	}
	catch (std::exception& ex) {
		// Oh No! error...
		GUI::ErrorDialog::show(ex.what());
	}

	return EXIT_SUCCESS;
}