//
// Created by studio25 on 07.04.2021.
//
#include <iostream>
#include "SDL2/SDL.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600


int main(int argc, char *argv[]){

    std::cout<<"lol wtf";
// 44,1 kHz
// 44100 times per second
// 60 fps <- that's me
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 0);

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, i);

    SDL_RenderPresent(renderer);


    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;


}