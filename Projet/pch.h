#ifndef PCH_H
#define PCH_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define TITLE "Donkey Kong"
#define WINDOW_WIDTH 448
#define WINDOW_HEIGHT 448
#define TIME_PER_FRAME (1.f / 60.f)
#define TIME_PER_ANIM (1.f / 12.f)
#define PLATFORM_SIZE_X 32
#define PLATFORM_SIZE_Y 16

// Vitesses
const sf::Vector2f PLAYER_SPEED{ 1.f, 2.f };
const float PLAYER_MAX_Y_SPEED = 2.0f;
const float PLAYER_Y_DELTA = 0.08f;
const sf::Vector2f BARREL_SPEED{ 3.f, 0.f };
const float BARREL_Y_DELTA = 0.08f;
const sf::Vector2f FIRE_MONSTER_SPEED{ 1.f, 0.3f };
const float FIRE_MONSTER_MAX_Y_SPEED = 1.0f;
const float FIRE_MONSTER_Y_DELTA = 0.08f;

// Textures files
#define MARIO_TEXTURE_FILE "mario_sprite8.png"
#define ENEMY_TEXTURE_FILE "goomba_sprite.png"
#define COIN_TEXTURE_FILE "coin_sprite.png"
#define PLATFORM_TEXTURE_FILE "platform.png"
#define LADDER_TEXTURE_FILE "ladder.png"
#define BARRELS_STACK_TEXTURE_FILE "barrels_stack3.png"
#define DK_TEXTURE_FILE "donkey_kong_sprite2.png"
#define BARREL_TEXTURE_FILE "barrel_sprite2.png"
#define PEACH_TEXTURE_FILE "peach_sprite.png"
#define BURNING_BARREL_TEXTURE_FILE "burningBarrel_sprite.png"
#define BLUE_BARREL_TEXTURE_FILE "blueBarrel_sprite2.png"
#define FIRE_MONSTER_TEXTURE_FILE "fireMonster_sprite.png"
#define WIN_TEXT_TEXTURE_FILE "win_text.png"
#define LOSE_TEXT_TEXTURE_FILE "lose_text.png"

typedef int TYPE;

enum class Gravity { Up, Down, None };
enum class Direction { Left, Right, Up, Down };
enum class Position { Top, Bottom, None, Peach };

struct Anim
{
	int x;
	int y;
	int nb;
};

// Barril
const Anim BARREL_ANIM{ 0, 0, 4 };
const sf::Vector2u BARREL_SIZE{ 24, 20 };
const TYPE WOODEN = 0;
const TYPE BLUE = 1;

// Barril de pétrole
const Anim BURNING_BARRIL_ANIM_OFF{ 0, 0, 1 };
const Anim BURNING_BARRIL_ANIM{ 0, 1 ,3 };
const sf::Vector2u BURNING_BARREL_SIZE{ 32, 64 };

// Donkey Kong
const Anim DK_ANIM{ 0, 0, 5 };
#define DK_ANIM_STOP 0
#define DK_ANIM_LEFT 1
#define DK_ANIM_STOP_BARREL 2
#define DK_ANIM_STOP_BLUE_BARREL 3
#define DK_ANIM_RIGHT 4
const sf::Vector2u DK_SIZE{ 86, 64 };
enum class DKState { Stop, Left, StopBarrel, StopBlueBarrel, Right, RightBlueBarrel };
const float PROBA_BLUE_BARREL = 1.f / 2.f;

// Fire monster
const sf::Vector2u FIRE_MONSTER_SIZE{ 30, 32 };
const Anim FIRE_MONSTER_ANIM_LEFT{ 0, 0, 2 };
const Anim FIRE_MONSTER_ANIM_RIGHT{ 0, 1, 2 };

// Mario
const Anim ANIM_LEFT{ 0,0,3 };
const Anim ANIM_RIGHT{ 0,1,3 };
const Anim ANIM_LADDER{ 0,2,2 };
const Anim ANIM_JUMP_LEFT{ 0,3,1 };
const Anim ANIM_JUMP_RIGHT{ 0,4,1 };
#define ANIM_LEFT_Y 1
#define ANIM_RIGHT_Y 2
#define ANIM_CLIMBING_LADDER_Y 3
#define ANIM_LEFT_NB 3
#define ANIM_RIGHT_NB 3
#define ANIM_CLIMBING_LADDER_NB 2
const sf::Vector2u MARIO_SIZE{ 32, 32 };

// Peach
const sf::Vector2u PEACH_SIZE{ 23, 32 };
const sf::IntRect PEACH_RECT{ 0, 0, 23, 32 };

#endif //PCH_H
