#include <HAPI_lib.h>
#include "Visualisation.h"
#include "Rectangle.h"
#include "World.h"
using namespace HAPISPACE;

void HAPI_Main()
{
	//Creates a world instance
	World WorldInstance;


	//Loads the level and runs the game loop
	WorldInstance.LoadLevel();
	WorldInstance.Run();

}