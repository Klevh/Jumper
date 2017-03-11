#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "moteur.h"

int main(){
  /* variables lies a l'affichage graphique */
  ElementSDL2     * personnage;
  ElementSDL2     * score;
  ElementSDL2     * obstacle;
  SDL_Event         event;
  /* autres variables */
  int               blanc[4] = {255,255,255,0};
  int               gris[4] = {127,127,127,0};
  int               vert[4] = {0,150,0,0};
  int               noir[4] = {0,0,0,0};
  int               run = 1;
  int               tps = 0, ticks = 0;
  int             * i;
  Data            * pdata;
  int               height = 0;

  /* initialisation de la SDL2 */
  if(initAllSDL2(IMG_INIT_PNG)){
    fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
    exit(-1);
  }

  /* initialisation de la fenetre */
  initFenetreSDL2(400,600,"Jumper",SDL_WINDOW_RESIZABLE,gris,1);
  if(initIteratorFenetreSDL2()){
    closeAllSDL2();
    fprintf(stderr,"Erreur d'ouverture de la fenetre.\n");
    exit(-1);
  }

  /* initialisation de la seed aleatoire */
  srand(time(0));
  
  /* cadre supperieur du jeu */
  createBlock(0.f,0.f,400.f,40.f,noir,1,0);
  /* texte du score */
  score = createTexte(5.f,5.f,160.f,30.f,"arial.ttf","Score : 0",blanc,1,0);
  setActionElementSDL2(score,actualiseScore);
  /* personnage */
  pdata=malloc(sizeof(*pdata));
  pdata->score=0;
  pdata->left=0;
  pdata->right=0;
  personnage = createImage(180.f,510.f,40.f,40.f,"pixel.png",1,1);
  setActionElementSDL2(personnage,gravite);
  setKeyPressElementSDL2(personnage,deplacement);
  setKeyReleasedElementSDL2(personnage,stop);
  addHitBoxElementSDL2(personnage,rectangleHitBox(0.f,0.f,1.f,1.f),0);
  setOnClickElementSDL2(personnage,touch);
  setDataElementSDL2(personnage,pdata);
  addElementToElementSDL2(score,personnage);

  /* generation des premiers obstacles */
  i=malloc(sizeof(*i));
  *i=0;
  obstacle = createBlock(175.f,550.f,WIDTH_OBSTACLE,HEIGHT_OBSTACLE,noir,1,2);
  setDataElementSDL2(obstacle,i);
  addElementToElementSDL2(personnage,obstacle);
  initObstacle(personnage,noir);
  
  /* display de la fenetre */
  while(run){
    tps = SDL_GetTicks();
    /* gestion d'evenement */
    while(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_WINDOWEVENT:
	if(event.window.event == SDL_WINDOWEVENT_CLOSE)  {
	  run = 0;
	}
	break;
      case SDL_QUIT :   
	run = 0;
      case SDL_KEYUP:
	keyReleasedFenetreSDL2(event.key.keysym.sym);
	break;
      case SDL_KEYDOWN:
	keyPressedFenetreSDL2(event.key.keysym.sym);
	break;
      case SDL_MOUSEBUTTONDOWN:
	clickFenetreSDL2(event.button.x,event.button.y);
	break;
      }
    }

    /* update de la fenetre */
    updateFenetreSDL2();
    /* affichage de la fenetre */
    displayFenetreSDL2();
    /* delai pour 60 frames/secondes */
    ticks = 16 - SDL_GetTicks() + tps;
    if(ticks>0){
      SDL_Delay(ticks);
    }

    getDimensionFenetreSDL2(NULL,&height);
    if(personnage->y > height){
      run = 0;
    }
  }

  printf("Vous avez perdu. Votre score est de %d.\n",((Data *)(personnage->data))->score);
  closeAllFenetreSDL2();
  closeAllSDL2();

  return 0;
}
