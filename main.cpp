//
// Created by studio25 on 07.04.2021.
//
#include <iostream>
#include <thread>
#include <cmath>
#include <conio.h>
#include "SDL2/SDL.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define PI 3.1415

struct wave_info {

    double *amplitude;
    double *interval;
    double *volume;

};
enum key_pressed {
    up,
    down,
    left,
    right,
    space,
    none


};

struct rgb_color {
    rgb_color(double r, double g, double b) : r(r), g(g), b(b) {}

    char r;
    char g;
    char b;
};

rgb_color gen_rainbow(unsigned height, unsigned max_height) {
    // sine wave algorythm
    // 3 parts
    // 1 :
    // r = cos(i) , g = sin(i), b =0
    // 2 :
    // r = 0 , g = cos(i), b = sin(x)
    // 3:
    // r = sin(i) , g = 0, b = cos(x)
    // every part is max_height / 3 translates into 0, PI/2

    // so for example in point 1/3 * max_height
    // r = cos(PI/2) = 0, g = sin(PI/2) = 1, b = 0


    char witch_third = height / (max_height / 3);
    //std::cout << (int) witch_third << " <t\n";
    //getch();
    double height_in_radians;
    switch (witch_third) {
        case 0:
            height_in_radians = height * PI / (max_height / 3) / 2;
            //   std::cout << height_in_radians << "<h\n";
            //      getch();

            return {cos(height_in_radians), sin(height_in_radians), 0};
        case 1:
            height -= max_height / 3;
            height_in_radians = height * PI / (max_height / 3) / 2;
            return {0, cos(height_in_radians), sin(height_in_radians)};

        case 2:
            height -= 2 * max_height / 3;
            height_in_radians = height * PI / (max_height / 3) / 2;
            return {sin(height_in_radians), 0, cos(height_in_radians)};

    }

}

struct cord {
    cord(int x, int y) : x(x), y(y) {}

    int x;
    int y;

};


int window_with_line(void *ptr_to_data) {

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;


    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, WINDOW_HEIGHT / 2);
    SDL_RenderPresent(renderer); // starting line

    auto time_start = std::chrono::steady_clock::now();


    double amplituda = 150;
    double okres = 0.5;
    int k = 0;
    int middle = WINDOW_HEIGHT / 2;

    key_pressed current_key = none;
    while (true) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (current_key != up) amplituda += 1.1;
                    current_key = up;
                    break;

                case SDLK_DOWN:
                    if (current_key != down) amplituda -= 1.1;
                    current_key = down;
                    break;

                case SDLK_LEFT:
                    if (current_key != left) okres -= 0.01;
                    current_key = left;
                    break;

                case SDLK_RIGHT:
                    if (current_key != right) okres += 0.01;
                    current_key = right;
                    break;
                case SDLK_SPACE:
                    if (current_key != space) {
                        std::cout << "amplituda: " << amplituda << "\t" << "okres: " << okres << "\n";
                    }
                    current_key = space;
                    break;
                default:
                    current_key = none;
                    break;
            }
        }
        {
            auto time_dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - time_start);
            // 1s = 1000 milliseconds
            // 60 frame per second = 1 frame per 16,66  milliseconds

            if (time_dif.count() > 16) {
                k++;
                time_start = std::chrono::steady_clock::now();
                current_key = none;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);


                //    rgb_color current_pixel_color = gen_rainbow(k, WINDOW_HEIGHT);
                //  SDL_SetRenderDrawColor(renderer, current_pixel_color.r, current_pixel_color.g,
                //                       current_pixel_color.b, 255);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

                for (int i = 0; i < WINDOW_WIDTH * (1 / okres); ++i) {
                    cord current_pixel_position = {
                            (int) (i * okres),
                            (int) (middle + cos(PI * i * 50 * 2) * amplituda)
                    };


                    SDL_RenderDrawPoint(renderer, current_pixel_position.x, current_pixel_position.y - 1);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x, current_pixel_position.y);
                    SDL_RenderDrawPoint(renderer, current_pixel_position.x, current_pixel_position.y + 1);

                }
                SDL_RenderPresent(renderer);
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 18;
}


int main(int argc, char *argv[]) {

    std::cout << "lol wtf";
// 44,1 kHz
// 44100 times per second
// 60 fps <- that's me

    rgb_color first= gen_rainbow(30,255*3);
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event * event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, first.r, first.g, first.b, 255);

    for (int i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, WINDOW_HEIGHT / 2);
    SDL_RenderPresent(renderer); // starting line
    SDL_WaitEvent(event);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    //SDL_Thread *mainthread;

    // mainthread = SDL_CreateThread(window_with_line, "idk", (void *) ptr_to_data);


    int *thread_status;
    //  SDL_WaitThread(mainthread, thread_status);

    printf("Thread returned value: %d\n", *thread_status);

    return 0;
}