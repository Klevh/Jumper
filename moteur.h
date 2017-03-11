#ifndef _GESTION_EVENT_JUMPR_KLEVH_
#define _GESTION_EVENT_JUMPR_KLEVH_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "SANDAL2/SANDAL2.h"

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

/* action en continue du personnage : deplacement vertical */
void gravite(ElementSDL2 *this);
/* action au clique d'une touche du personnage : deplacement horizontal */
void deplacement(ElementSDL2 *this, SDL_Keycode c);
void stop( ElementSDL2 *this, SDL_Keycode c);
/* initialise les premiers obstacles */
void initObstacle(ElementSDL2 *personnage, int couleur[4]);
/* genere un nouvel obstacle */
void genereObstacle(ElementSDL2 *personnage, int couleur[4],int brick);
/* actualise l'affichage du score */
void actualiseScore(ElementSDL2 * this);
/* message quand on clique sur le personnage */
void touch(ElementSDL2 * this);
#endif
