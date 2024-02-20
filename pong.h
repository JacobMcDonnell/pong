#ifndef PONG_H
#define PONG_H

#include <stdint.h>

constexpr int PADDLE_WIDTH = 16;
constexpr int PADDLE_HEIGHT = 128;
constexpr int BALL_WIDTH = 16;
constexpr int BALL_HEIGHT = 16;

typedef struct vector_t {
    int32_t x;
    int32_t y;
} vector_t;

/* paddles have a fixed x position and velocity */
struct moveable_t {
    vector_t position;
    vector_t velocity;
    uint8_t width;
    uint8_t height;
};

typedef struct moveable_t ball_t;
typedef struct moveable_t paddle_t;

void UpdatePosition ( vector_t * const position, const vector_t velocity );
bool CheckMoveableCollision ( const struct moveable_t m1, const struct moveable_t m2 );
bool CheckLeftWallCollision ( const struct moveable_t m );
bool CheckRightWallCollision ( const struct moveable_t m );
bool CheckGroundCollision ( const struct moveable_t m );
bool CheckCeilingCollision ( const struct moveable_t m );
void Reset ( ball_t * const ball );

#endif //PONG_H
