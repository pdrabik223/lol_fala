//
// Created by studio25 on 07.04.2021.
//
#include <iostream>
#include <thread>
#include "SDL2/SDL.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600

int window_with_line(void *ptr_to_data) {

    ptr_to_data = (int*)ptr_to_data;

    std::cout << ptr_to_data;


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

}


int main(int argc, char *argv[]) {

    std::cout << "lol wtf";
// 44,1 kHz
// 44100 times per second
// 60 fps <- that's me
    int *ptr_to_data = new int (5);

    std::cout<<*ptr_to_data;

    SDL_Thread *mainthread;

    mainthread = SDL_CreateThread(window_with_line, "idk", (void *) ptr_to_data);

    int *thread_status;
    SDL_WaitThread(mainthread, thread_status);

    printf("Thread returned value: %d\n", *thread_status);

    return 0;
}