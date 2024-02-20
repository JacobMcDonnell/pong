#include "pong.h"
#include "screen.h"

inline void UpdatePosition ( point_t * const position, const point_t velocity ) {
    position->x += velocity.x ;
    position->y += velocity.y ;
}

/* CheckMoveableCollision: Implementation of AABB collision for moveable objects */
bool CheckMoveableCollision ( const struct moveable_t m1, const struct moveable_t m2 ) {
    const point_t m1p = m1.position;
    const point_t m2p = m2.position;
    const bool checkX = m1p.x + m1.width > m2p.x,
                checkY = m1p.y + m1.height > m2p.y && m1p.y < m2p.y + m2.height;
    return checkX && checkY;
}

bool CheckLeftWallCollision ( const struct moveable_t m ) {
    return m.position.x < 0 ;
}

bool CheckRightWallCollision ( const struct moveable_t m ) {
    return m.position.x + m.width > SCREEN_WIDTH;
}

bool CheckGroundCollision ( const struct moveable_t m ) {
    return m.position.y + m.height > SCREEN_HEIGHT;
}

bool CheckCeilingCollision ( const struct moveable_t m ) {
    return m.position.y < 0;
}

void Reset ( ball_t * const ball ) {
    ball->position = ( point_t ) { SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1 };
    ball->velocity = ( point_t ){ 1, 1 };
}
