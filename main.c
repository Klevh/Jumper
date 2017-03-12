#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SANDAL2/SANDAL2.h"

#include "menu.h"

int main(){
  /* variables lies a l'affichage graphique */
  ElementSDL2     * personnage;
  ElementSDL2     * scor;
  ElementSDL2     * button;
  SDL_Event         event;
  /* autres variables */
  int               blanc[4] = {255,255,255,0};
  int               gris[4] = {127,127,127,0};
  int               vert[4] = {0,150,0,0};
  int               noir[4] = {0,0,0,0};
  int             * run = malloc(sizeof(*run));
  int               tps = 0, ticks = 0;
  int               dp = 0;

  /* initialisation de la SDL2 */
  if(initAllSDL2(IMG_INIT_PNG)){
    fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
    exit(-1);
  }

  /* initialisation de la fenetre */
  initFenetreSDL2(400,600,"Jumper",SDL_WINDOW_RESIZABLE,gris,0);
  if(initIteratorFenetreSDL2()){
    closeAllSDL2();
    fprintf(stderr,"Erreur d'ouverture de la fenetre.\n");
    exit(-1);
  }

  /* initialisation de la seed aleatoire */
  srand(time(0));

  /* --- phase de jeu --- */
  /* cadre supperieur du jeu */
  createBlock(0.f,0.f,400.f,40.f,noir,1,0);
  /* texte du score */
  scor = createTexte(5.f,5.f,160.f,30.f,"arial.ttf","Score : 0",blanc,1,0);
  setActionElementSDL2(scor,actualiseScore);
  /* personnage */
  personnage = createImage(180.f,510.f,40.f,40.f,"pixel.png",1,1);
  addHitBoxElementSDL2(personnage,rectangleHitBox(0.f,0.f,1.f,1.f),0);
  setDataElementSDL2(personnage,malloc(sizeof(Data)));
  addElementToElementSDL2(scor,personnage);

  /* --- menu principal --- */
  /* titre */
  createTexte(100.f,30.f,200.f,50.f,"arial.ttf","JUMPER",noir,0,0);
  createImage(50.f,30.f,50.f,50.f,"pixel.png",0,0);
  createImage(300.f,30.f,50.f,50.f,"pixel.png",0,0);

  /* bouton jouer */
  button=createButton(125.f,150.f,150.f,80.f,80.f,"arial.ttf","Jouer",blanc,noir,0,0);
  addHitBoxElementSDL2(button,rectangleHitBox(0.f,0.f,1.f,1.f),0);
  addElementToElementSDL2(button,personnage);
  setOnClickElementSDL2(button,play);

  /* bouton scores */
  button=createButton(125.f,250.f,150.f,80.f,80.f,"arial.ttf","Scores",blanc,noir,0,0);
  addHitBoxElementSDL2(button,rectangleHitBox(0.f,0.f,1.f,1.f),0);
  setOnClickElementSDL2(button,score);
  
  /* bouton configuration */
  button=createButton(125.f,350.f,150.f,80.f,80.f,"arial.ttf","Reglage",blanc,noir,0,0);
  addHitBoxElementSDL2(button,rectangleHitBox(0.f,0.f,1.f,1.f),0);
  setOnClickElementSDL2(button,config);
  
  /* bouton quitter */
  button=createButton(250.f,500.f,100.f,50.f,80.f,"arial.ttf","Quitter",blanc,noir,0,0);
  addHitBoxElementSDL2(button,rectangleHitBox(0.f,0.f,1.f,1.f),0);
  setOnClickElementSDL2(button,quit);
  setDataElementSDL2(button,run);
  *run = 1;

  /* display de la fenetre */
  while(*run){
    tps = SDL_GetTicks();
    /* gestion d'evenement */
    while(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_WINDOWEVENT:
	if(event.window.event == SDL_WINDOWEVENT_CLOSE)  {
	  *run = 0;
	}
	break;
      case SDL_QUIT :   
	*run = 0;
      case SDL_KEYUP:
	keyReleasedFenetreSDL2(event.key.keysym.sym);
	break;
      case SDL_KEYDOWN:
	getDisplayCodeFenetreSDL2(&dp);
	if(!dp && event.key.keysym.sym==SDLK_ESCAPE){
	  *run=0;
	}else{
	  keyPressedFenetreSDL2(event.key.keysym.sym);
	}
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
  }

  closeAllFenetreSDL2();
  closeAllSDL2();

  return 0;
}
