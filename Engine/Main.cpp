#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/lib/SDL2.lib" )
#pragma comment( lib, "SDL/lib/SDL2main.lib" )
#include "leak.h"

void DumpLeaks(void)
{
	_CrtDumpMemoryLeaks(); // show leaks with file and line where allocation was made
}

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;

int main(int argc, char ** argv)
{
	atexit(DumpLeaks);
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			App = new Application();
			state = MAIN_START;
			LOG("Application Creation --------------\n");
			break;

		case MAIN_START:

			LOG("Application Init --------------\n");
			if (App->Init() == false)
			{
				LOG("Application Init exits with error -----\n");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("Application Update --------------\n");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with error -----\n");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("Application CleanUp --------------\n");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with error -----\n");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}

	}

	delete App;
	return main_return;
}
