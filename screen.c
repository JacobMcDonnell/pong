#include "screen.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *ballSurface = NULL;
SDL_Surface *leftPaddleSurface = NULL;
SDL_Surface *rightPaddleSurface = NULL;

static SDL_Surface *LoadSurface( const char * const path ) {
    SDL_Surface *optimizedSurface = NULL;
    SDL_Surface * loadedSurface = SDL_LoadBMP( path );
    if ( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() );
        return NULL;
    }
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
    if ( optimizedSurface == NULL ) {
        printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        return NULL;
    }
    SDL_FreeSurface( loadedSurface );
    return optimizedSurface;
}

bool InitScreen ( void ) {
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    gWindow = SDL_CreateWindow( "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if ( gWindow == NULL ) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    gScreenSurface = SDL_GetWindowSurface( gWindow );

    ClearScreen();

    ballSurface = LoadSurface( "ball.bmp" );
    leftPaddleSurface = LoadSurface( "paddle.bmp" );
    rightPaddleSurface = LoadSurface( "paddle.bmp" );

    return true;
}

void Close ( void ) {
    SDL_FreeSurface( rightPaddleSurface );
    rightPaddleSurface = NULL;
    SDL_FreeSurface( leftPaddleSurface );
    leftPaddleSurface = NULL;
    SDL_FreeSurface( ballSurface );
    ballSurface = NULL;
    SDL_FreeSurface( gScreenSurface );
    gScreenSurface = NULL;
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_Quit();
}

void Draw ( const struct moveable_t m, SDL_Surface * const surface ) {
    SDL_Rect drect = { m.position.x, m.position.y, m.width, m.height };
    const int status = SDL_BlitSurface( surface, NULL, gScreenSurface, &drect );
    if ( status < 0 ) {
        printf( "Error with draw! SDL Error: %s\n", SDL_GetError() );
    }
}

void ClearScreen( void ) {
    SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0x00, 0x00, 0x00 ) );
    SDL_UpdateWindowSurface( gWindow );
}
