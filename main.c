#include "pong.h"
#include "screen.h"
#include <time.h>
#include <math.h>

static uint8_t delay = 5;
static uint8_t rightScore = 0;
static uint8_t leftScore = 0;

void Delay ( const uint8_t seconds ) {
    const clock_t start = clock();
    while ( clock() < start + seconds * 1000 )
        ;
}

int main ( void ) {
    paddle_t leftPaddle = { { 0, 0 }, { 0, 0 }, 16, 48 },
                rightPaddle = { { SCREEN_WIDTH - 16, 0 }, { 0, 0 }, 16, 48 };
    ball_t ball = { { SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1 }, { 1, 1 }, 16, 16 };
    bool quit = false;
    SDL_Event e;
    uint8_t volley = 0;

    if ( !InitScreen() ) {
        printf( "Failed to initalize!\n" );
        return -1;
    }

    Draw( ball, ballSurface );
    SDL_UpdateWindowSurface( gWindow );
    Draw( leftPaddle, leftPaddleSurface);
    SDL_UpdateWindowSurface( gWindow );
    Draw( rightPaddle, rightPaddleSurface );
    SDL_UpdateWindowSurface( gWindow );

    while ( quit == false ) {
        UpdatePosition( &ball.position, ball.velocity );
        if ( CheckGroundCollision( ball ) || CheckCeilingCollision( ball ) ) {
            ball.velocity.y *= -1;
        } else if ( CheckLeftWallCollision( ball ) ) {
            rightScore++;
            volley = 0;
            delay = 5;
            printf( "Left: %3d\tRight: %3d\n", leftScore, rightScore );
            Reset( &ball );
        } else if ( CheckRightWallCollision( ball ) ) {
            volley = 0;
            leftScore++;
            delay = 5;
            printf( "Left: %3d\tRight: %3d\n", leftScore, rightScore );
            Reset( &ball );
        }else if ( CheckMoveableCollision( leftPaddle, ball ) || CheckMoveableCollision( ball, rightPaddle ) ) {
            volley++;
            int xSign = ( ball.velocity.x < 0 ) ? -1 : 1;
            int ySign = ( ball.velocity.y < 0 ) ? -1 : 1;
            int increase = ( volley % 4 == 0 ) ? 1 : 0;
            ball.velocity.x = -1 * ( xSign * ( abs( ball.velocity.x ) + increase ) );
            delay += increase << 2;
            ball.velocity.y = ySign * ( abs( ball.velocity.x ) + increase );
        }
        while ( SDL_PollEvent( &e ) != 0 ) {
            if ( e.type == SDL_QUIT ) {
                quit = true;
            } else if ( e.type == SDL_KEYDOWN ) {
                switch ( e.key.keysym.sym ) {
                    case SDLK_UP:
                        if ( CheckCeilingCollision( rightPaddle ) ) {
                            rightPaddle.velocity.y = 0;
                            rightPaddle.position.y = 0;
                        } else {
                            rightPaddle.velocity.y = -10;
                            UpdatePosition( &rightPaddle.position, rightPaddle.velocity );
                        }
                    break;
                    case SDLK_DOWN:
                        if ( CheckGroundCollision( rightPaddle ) ) {
                            rightPaddle.velocity.y = 0;
                            rightPaddle.position.y = SCREEN_HEIGHT - rightPaddle.height;
                        } else {
                            rightPaddle.velocity.y = 10;
                            UpdatePosition( &rightPaddle.position, rightPaddle.velocity );
                        }
                    break;
                    case SDLK_w:
                        if ( CheckCeilingCollision( leftPaddle ) ) {
                            leftPaddle.velocity.y = 0;
                            leftPaddle.position.y = 0;
                        } else {
                            leftPaddle.velocity.y = -10;
                            UpdatePosition( &leftPaddle.position, leftPaddle.velocity );
                        }
                    break;
                    case SDLK_s:
                        if ( CheckGroundCollision( leftPaddle ) ) {
                            leftPaddle.velocity.y = 0;
                            leftPaddle.position.y = SCREEN_HEIGHT - leftPaddle.height;
                        } else {
                            leftPaddle.velocity.y = 10;
                            UpdatePosition( &leftPaddle.position, leftPaddle.velocity );
                        }
                    break;
                    default:
                        break;
                }
            } else if ( e.type == SDL_KEYUP ) {
                switch ( e.key.keysym.sym ) {
                    case SDLK_UP:
                    case SDLK_DOWN:
                        rightPaddle.velocity.y = 0;
                    break;
                    case SDLK_w:
                    case SDLK_s:
                        leftPaddle.velocity.y = 0;
                    break;
                    default:
                        break;
                }
            }
        }
        SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0x00, 0x00, 0x00 ) );
        Draw ( rightPaddle, rightPaddleSurface );
        Draw ( leftPaddle, leftPaddleSurface );
        Draw( ball, ballSurface );
        SDL_UpdateWindowSurface( gWindow );
        Delay( delay );
    }
    Close();
    return 0;
}
