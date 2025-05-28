#include <SDL.h>
#include <iostream>
#include <cmath>

const int WINDOW_WIDTH = 540;
conts int WINDOW_HEIGHT = 540;

int main(int argc, char* args[]){
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		std::cerr << "SDL could not initialize. SDL Error: " <<SDL_GetError()<<std::endl;
		return 1;
		
	SDL_Window* window = SDL_CreateWindow(
		"Crystal Math",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer*  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr){
		std::cerr << "Renderer could not be created. SDL Error: " <<SDL_GetError()<<std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	
	SDL_SetRendererDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RendererClear(renderer);
	
	SDL_RendererPresent(renderer);
	
	SDL_Delay(10);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;

}

