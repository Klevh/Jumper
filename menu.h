#ifndef _MENU_JUMPER_KLEVH_
#define _MENU_JUMPER_KLEVH_

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SANDAL2/SANDAL2.h"

#include "jeu.h"

/* interaction du bouton jouer */
void play(ElementSDL2 * this);

/* interaction du bouton quitter */
void quit(ElementSDL2 * this);

/* interaction du bouton config */
void config(ElementSDL2 * this);

/* interaction du bouton score */
void score(ElementSDL2 * this);

#endif
