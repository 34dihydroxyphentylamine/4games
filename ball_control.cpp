#include <SDL.h>
#include <iostream>
#include <cmath> 

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


const int POINT_DIAMETER = 60; 
const int POINT_RADIUS = POINT_DIAMETER / 2; 
const int MOVEMENT_SPEED = 5; 


void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for (int y = -radius; y <= radius; y++) {
         
        int x = static_cast<int>(sqrt(radius * radius - y * y));
        
        SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
    }
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    
    SDL_Window* window = SDL_CreateWindow(
        "Movable Point",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

   
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    
    SDL_Rect pointBoundingBox = {
        (WINDOW_WIDTH - POINT_DIAMETER) / 2,
        (WINDOW_HEIGHT - POINT_DIAMETER) / 2,
        POINT_DIAMETER,
        POINT_DIAMETER
    };

    bool quit = false;
    SDL_Event e;

   
    while (!quit) {
        
        while (SDL_PollEvent(&e) != 0) {
            
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    
                case SDLK_UP:
                case SDLK_w:
                    pointBoundingBox.y -= MOVEMENT_SPEED;
                    break;
                    
                case SDLK_DOWN:
                case SDLK_s:
                    pointBoundingBox.y += MOVEMENT_SPEED;
                    break;
                    
                case SDLK_LEFT:
                case SDLK_a:
                    pointBoundingBox.x -= MOVEMENT_SPEED;
                    break;
                    
                case SDLK_RIGHT:
                case SDLK_d:
                    pointBoundingBox.x += MOVEMENT_SPEED;
                    break;
                }
                
                if (pointBoundingBox.x < 0) pointBoundingBox.x = 0;
                if (pointBoundingBox.y < 0) pointBoundingBox.y = 0;
                if (pointBoundingBox.x + pointBoundingBox.w > WINDOW_WIDTH) pointBoundingBox.x = WINDOW_WIDTH - pointBoundingBox.w;
                if (pointBoundingBox.y + pointBoundingBox.h > WINDOW_HEIGHT) pointBoundingBox.y = WINDOW_HEIGHT - pointBoundingBox.h;
            }
        }

        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        
        int circleCenterX = pointBoundingBox.x + POINT_RADIUS;
        int circleCenterY = pointBoundingBox.y + POINT_RADIUS;

        
        drawFilledCircle(renderer, circleCenterX, circleCenterY, POINT_RADIUS, 0xFF, 0x00, 0x00, 0xFF); // Red color

        
        SDL_RenderPresent(renderer);

        
        SDL_Delay(10);
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
