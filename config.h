#ifndef CONFIG_H
#define CONFIG_H

/* All of the config values and constants used in the game, separated for clarity.
 * Many are taken from the chrome dino hop game, since that's the inspiration here. */

#define WIDTH 1280.0f
#define HEIGHT 720.0f

#define GRAVITY 0.6f
#define ACCELERATION 0.001f
#define INITIAL_JUMP_VELOCITY -6.0f
#define DROP_VELOCITY -5.0f
#define SPEED_DROP_COEFFICIENT 3.0f
#define MAX_JUMP_HEIGHT 70.0f
#define MIN_JUMP_HEIGHT 70.0f
#define SPEED 5.0f
#define MAX_SPEED 15.0f

#define OBSTACLE_HEIGHT 25.0f
#define OBSTACLE_WIDTH 15.0f

#define PLAYER_HEIGHT 47.0f
#define PLAYER_WIDTH 44.0f
#define PLAYER_HEIGHT_DUCK 25.0f
#define PLAYER_WIDTH_DUCK 44.0f

#define GROUND_Y_POS (HEIGHT/2.0f + PLAYER_HEIGHT)
#define PLAYER_X_POS 50.0f

#define MIN_JUMP_POS (GROUND_Y_POS - MIN_JUMP_HEIGHT)
#define MAX_JUMP_POS (GROUND_Y_POS - MAX_JUMP_HEIGHT)

#endif
