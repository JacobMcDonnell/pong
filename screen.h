#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>
#include "pong.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *ballSurface;
extern SDL_Surface *leftPaddleSurface;
extern SDL_Surface *rightPaddleSurface;

bool InitScreen ( void );
void Close ( void );
void Draw ( const struct moveable_t m, SDL_Surface * const surface );

#endif //SCREEN_H
