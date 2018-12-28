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
#define PLAYER_SPEED 3
#define TEXTURE_SIZE 32
#define TIME_PER_ANIM (1.f / 15.f)
#define MARIO_TEXTURE_FILE "mario_sprite.png"
#define ENEMY_TEXTURE_FILE "goomba_sprite.png"
#define COIN_TEXTURE_FILE "coin_sprite.png"
#define PLATFORM_TEXTURE_FILE "platform.png"
#define PLATFORM_SIZE_X 32
#define PLATFORM_SIZE_Y 16

enum class Gravity { Up, Down, None };
enum class Direction { Left = -1, Right = 1 };
enum class Position { Top, Bottom, None };

#include <SFML/Graphics.hpp>
#include <iostream>

#endif //PCH_H
