#ifndef _GESTION_EVENT_JUMPR_KLEVH_
#define _GESTION_EVENT_JUMPR_KLEVH_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "SANDAL2/SANDAL2.h"

#define DIST_MAX_BRICK 170
#define DIST_MIN_BRICK 150
#define min(a,b) (a>b?b:a)
#define max(a,b) (a<b?b:a)
#define SPEED_MAX 10.f
#define WIDTH_OBSTACLE 50.f
#define HEIGHT_OBSTACLE 15.f

typedef struct{
  int left;
  int right;
  int score;
}Data;

/* --- phase de jeu --- */
/* action en continue du personnage : deplacement vertical */
void gravite(ElementSDL2 *this);
/* action au clique d'une touche du personnage : deplacement horizontal */
void deplacement(ElementSDL2 *this, SDL_Keycode c);
void stop( ElementSDL2 *this, SDL_Keycode c);
/* initialise les premiers obstacles */
void initGame(ElementSDL2 *personnage, int couleur[4]);
/* genere un nouvel obstacle */
void genereObstacle(ElementSDL2 *personnage, int couleur[4],int brick);
/* actualise l'affichage du score */
void actualiseScore(ElementSDL2 * this);
/* permet au joueur de relancer le jeu ou de revenir au menu quand defaite */
void endGame(ElementSDL2 * this, SDL_Keycode c);
/* -------------------- */

/* --- menu --- */
/* message quand on clique sur le bouton jouer */
void play(ElementSDL2 * this);
/* ------------ */

#endif
