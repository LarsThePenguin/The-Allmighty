#include <stdio.h>
#include <stdbool.h>
#include "SDL3/SDL.h"

int main(int argc, char *argv[]) {
	/* Initialises data */
	SDL_Window *window = NULL;
	
	/*
	* Initialises the SDL video subsystem (as well as the events subsystem).
	* Returns 0 on success or a negative error code on failure using SDL_GetError().
	*/
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
		return 1;
	}

	/* Creates a SDL window */
	window = SDL_CreateWindow("SDL Example", /* Title of the SDL window */
					800, /* Width of the window in pixels */
					600, /* Height of the window in pixels */
					0); /* Additional flag(s) */

	/* Checks if window has been created; if not, exits program */
	if (window == NULL) {
		fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
		return 1;
	}

	/* Pauses all SDL subsystems for a variable amount of milliseconds */
	SDL_Delay(5000);

	/* Frees memory */
	SDL_DestroyWindow(window);
	
	/* Shuts down all SDL subsystems */
	SDL_Quit();
	return 0;
}