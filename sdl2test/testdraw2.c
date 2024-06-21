/*
  Copyright (C) 1997-2019 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/

/* Simple program:  draw as many random objects on the screen as possible */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

//#include "SDL_test_common.h"
//gcc -o testdraw2 testdraw2.c -lSDL2
#include <SDL2/SDL.h>
#define SHAPED_WINDOW_W 480 //640 //150
#define SHAPED_WINDOW_H 480 //150
#define SHAPED_WINDOW_X 0
#define SHAPED_WINDOW_Y 0

#define NUM_OBJECTS 100

//static SDLTest_CommonState *state;
static int num_objects;
static SDL_bool cycle_color;
static SDL_bool cycle_alpha;
static int cycle_direction = 1;
static int current_alpha = 255;
static int current_color = 255;
static SDL_BlendMode blendMode = SDL_BLENDMODE_NONE;

int done;

void
DrawPoints(SDL_Renderer * renderer)
{
    int i;
    int x, y;
    SDL_Rect viewport;

    /* Query the sizes */
    SDL_RenderGetViewport(renderer, &viewport);

    for (i = 0; i < num_objects * 4; ++i) {
        /* Cycle the color and alpha, if desired */
        if (cycle_color) {
            current_color += cycle_direction;
            if (current_color < 0) {
                current_color = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_color > 255) {
                current_color = 255;
                cycle_direction = -cycle_direction;
            }
        }
        if (cycle_alpha) {
            current_alpha += cycle_direction;
            if (current_alpha < 0) {
                current_alpha = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_alpha > 255) {
                current_alpha = 255;
                cycle_direction = -cycle_direction;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, (Uint8) current_color,
                               (Uint8) current_color, (Uint8) current_alpha);

        x = rand() % viewport.w;
        y = rand() % viewport.h;
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void
DrawLines(SDL_Renderer * renderer)
{
    int i;
    int x1, y1, x2, y2;
    SDL_Rect viewport;

    /* Query the sizes */
    SDL_RenderGetViewport(renderer, &viewport);

    for (i = 0; i < num_objects; ++i) {
        /* Cycle the color and alpha, if desired */
        if (cycle_color) {
            current_color += cycle_direction;
            if (current_color < 0) {
                current_color = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_color > 255) {
                current_color = 255;
                cycle_direction = -cycle_direction;
            }
        }
        if (cycle_alpha) {
            current_alpha += cycle_direction;
            if (current_alpha < 0) {
                current_alpha = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_alpha > 255) {
                current_alpha = 255;
                cycle_direction = -cycle_direction;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, (Uint8) current_color,
                               (Uint8) current_color, (Uint8) current_alpha);

        if (i == 0) {
            SDL_RenderDrawLine(renderer, 0, 0, viewport.w - 1, viewport.h - 1);
            SDL_RenderDrawLine(renderer, 0, viewport.h - 1, viewport.w - 1, 0);
            SDL_RenderDrawLine(renderer, 0, viewport.h / 2, viewport.w - 1, viewport.h / 2);
            SDL_RenderDrawLine(renderer, viewport.w / 2, 0, viewport.w / 2, viewport.h - 1);
        } else {
            x1 = (rand() % (viewport.w*2)) - viewport.w;
            x2 = (rand() % (viewport.w*2)) - viewport.w;
            y1 = (rand() % (viewport.h*2)) - viewport.h;
            y2 = (rand() % (viewport.h*2)) - viewport.h;
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
    }
}

void
DrawRects(SDL_Renderer * renderer)
{
    int i;
    SDL_Rect rect;
    SDL_Rect viewport;

    /* Query the sizes */
    SDL_RenderGetViewport(renderer, &viewport);

    for (i = 0; i < num_objects / 4; ++i) {
        /* Cycle the color and alpha, if desired */
        if (cycle_color) {
            current_color += cycle_direction;
            if (current_color < 0) {
                current_color = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_color > 255) {
                current_color = 255;
                cycle_direction = -cycle_direction;
            }
        }
        if (cycle_alpha) {
            current_alpha += cycle_direction;
            if (current_alpha < 0) {
                current_alpha = 0;
                cycle_direction = -cycle_direction;
            }
            if (current_alpha > 255) {
                current_alpha = 255;
                cycle_direction = -cycle_direction;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, (Uint8) current_color,
                               (Uint8) current_color, (Uint8) current_alpha);

        rect.w = rand() % (viewport.h / 2);
        rect.h = rand() % (viewport.h / 2);
        rect.x = (rand() % (viewport.w*2) - viewport.w) - (rect.w / 2);
        rect.y = (rand() % (viewport.h*2) - viewport.h) - (rect.h / 2);
        SDL_RenderFillRect(renderer, &rect);
    }
//SDL_Delay(1000);
}

void
DrawRects2(SDL_Renderer * renderer)
{
    int i;
    SDL_Rect rect;
    SDL_Rect viewport;

    /* Query the sizes */
    SDL_RenderGetViewport(renderer, &viewport);

        SDL_SetRenderDrawColor(renderer, 0xff, (Uint8) 0x00, (Uint8) 0x00, (Uint8) 0x00);

        rect.w = 320;
        rect.h = 240;
        rect.x = 50;
        rect.y = 100;
        SDL_RenderFillRect(renderer, &rect);
//SDL_Delay(1000);
}

void
loop(SDL_Renderer *renderer, SDL_Window *window)
{
    int i;
    SDL_Event event;

    /* Check for events */
    while (SDL_PollEvent(&event)) {
    //    SDLTest_CommonEvent(state, &event, &done);
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    done = 1;
                    break;
                }
            }
            if (event.type == SDL_QUIT) {
                done = 1;
                break;
            }
    }
    for (i = 0; i < 1/*state->num_windows*/; ++i) {
        //SDL_Renderer *renderer = state->renderers[i];
        if (window/*state->windows[i]*/ == NULL)
            continue;
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer);

#if 0
        DrawRects(renderer);
        DrawLines(renderer);
        DrawPoints(renderer);
#else
        DrawRects2(renderer);
#endif
        SDL_RenderPresent(renderer);
    }
#ifdef __EMSCRIPTEN__
    if (done) {
        emscripten_cancel_main_loop();
    }
#endif
}

int
main(int argc, char *argv[])
{
    int i;
    Uint32 then, now, frames;
    SDL_Window *window;
    SDL_Renderer *renderer;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    /* Initialize parameters */
    num_objects = NUM_OBJECTS;

    /* Initialize test framework */
    //state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);
    //if (!state) {
    //    return 1;
    //}
    for (i = 1; i < argc;) {
        int consumed;

        consumed = 0; //consumed = SDLTest_CommonArg(state, i);
        if (consumed == 0) {
            consumed = -1;
            if (SDL_strcasecmp(argv[i], "--blend") == 0) {
                if (argv[i + 1]) {
                    if (SDL_strcasecmp(argv[i + 1], "none") == 0) {
                        blendMode = SDL_BLENDMODE_NONE;
                        consumed = 2;
                    } else if (SDL_strcasecmp(argv[i + 1], "blend") == 0) {
                        blendMode = SDL_BLENDMODE_BLEND;
                        consumed = 2;
                    } else if (SDL_strcasecmp(argv[i + 1], "add") == 0) {
                        blendMode = SDL_BLENDMODE_ADD;
                        consumed = 2;
                    } else if (SDL_strcasecmp(argv[i + 1], "mod") == 0) {
                        blendMode = SDL_BLENDMODE_MOD;
                        consumed = 2;
                    }
                }
            } else if (SDL_strcasecmp(argv[i], "--cyclecolor") == 0) {
                cycle_color = SDL_TRUE;
                consumed = 1;
            } else if (SDL_strcasecmp(argv[i], "--cyclealpha") == 0) {
                cycle_alpha = SDL_TRUE;
                consumed = 1;
            } else if (SDL_isdigit(*argv[i])) {
                num_objects = SDL_atoi(argv[i]);
                consumed = 1;
            }
        }
        if (consumed < 0) {
            static const char *options[] = { "[--blend none|blend|add|mod]", "[--cyclecolor]", "[--cyclealpha]", NULL };
            //SDLTest_CommonLogUsage(state, argv[0], options);
	    int i = 0; 
            for (i=0; options[i];++i)
	       printf("%s\n", options[i]);
            return 1;
        }
        i += consumed;
    }
    //if (!SDLTest_CommonInit(state)) {
    //    return 2;
    //}
    if(SDL_VideoInit(NULL) == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL video.");
        exit(-2);
    }
cycle_color = SDL_TRUE;
#if 0
    window = SDL_CreateShapedWindow("testdraw2",
        SHAPED_WINDOW_X, SHAPED_WINDOW_Y,
        SHAPED_WINDOW_W, SHAPED_WINDOW_H,
        0);
#else
    window = SDL_CreateWindow("testdraw2",
        SHAPED_WINDOW_X, SHAPED_WINDOW_Y,
        SHAPED_WINDOW_W, SHAPED_WINDOW_H,
        0);
#endif
    SDL_SetWindowPosition(window, SHAPED_WINDOW_X, SHAPED_WINDOW_Y);
    if(window == NULL) {
        SDL_VideoQuit();
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create shaped window for SDL_Shape.");
        exit(-4);
    }
    renderer = SDL_CreateRenderer(window,-1,0);


    /* Create the windows and initialize the renderers */
    for (i = 0; i < 1/*state->num_windows*/; ++i) {
        //SDL_Renderer *renderer = state->renderers[i];
        SDL_SetRenderDrawBlendMode(renderer, blendMode);
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer);
    }

    srand((unsigned int)time(NULL));

    /* Main render loop */
    frames = 0;
    then = SDL_GetTicks();
    done = 0;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (!done) {
        ++frames;
        loop(renderer,window);
        }
#endif


    //SDLTest_CommonQuit(state);

    /* Print out some timing information */
    now = SDL_GetTicks();
    if (now > then) {
        double fps = ((double) frames * 1000) / (now - then);
        SDL_Log("%2.2f frames per second\n", fps);
    }
    return 0;
}

/* vi: set ts=4 sw=4 expandtab: */
