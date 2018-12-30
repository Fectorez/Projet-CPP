// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

#ifndef PCH_H
#define PCH_H

#define TITLE "Donkey Kong"
#define WINDOW_WIDTH 448
#define WINDOW_HEIGHT 448
#define TIME_PER_FRAME (1.f / 60.f)
#define PLAYER_SPEED 1
#define TEXTURE_SIZE 32
#define TIME_PER_ANIM (1.f / 15.f)
#define MARIO_TEXTURE_FILE "mario_sprite6.png"
#define ENEMY_TEXTURE_FILE "goomba_sprite.png"
#define COIN_TEXTURE_FILE "coin_sprite.png"
#define PLATFORM_TEXTURE_FILE "platform.png"
#define LADDER_TEXTURE_FILE "ladder.png"
#define PLATFORM_SIZE_X 32
#define PLATFORM_SIZE_Y 16
#define MARIO_SIZE_X 16
#define MARIO_SIZE_Y 31

enum class Gravity { Up, Down, None };
enum class Direction { Left, Right, Up, Down };
enum class Position { Top, Bottom, None, Peach };

struct Anim
{
	int x;
	int y;
	int nb;
};
const Anim ANIM_LEFT{ 0,1,3 };
const Anim ANIM_RIGHT{ 0,2,3 };
const Anim ANIM_LADDER{ 0,3,2 };
const Anim ANIM_JUMP_LEFT{ 0,0,1 };
const Anim ANIM_JUMP_RIGHT{ 0,4,1 };

#define ANIM_LEFT_Y 1
#define ANIM_RIGHT_Y 2
#define ANIM_CLIMBING_LADDER_Y 3
#define ANIM_LEFT_NB 3
#define ANIM_RIGHT_NB 3
#define ANIM_CLIMBING_LADDER_NB 2

#include <SFML/Graphics.hpp>
#include <iostream>

#endif //PCH_H
