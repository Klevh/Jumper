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
  int               noir[4] = {0,0,0,0};
  int               bleu[4] = {0,0,255,0};
  int               vert[4] = {0,255,0,0};
  int               rouge[4] = {255,0,0,0};
  int             * run = malloc(sizeof(*run));
  int               tps = 0, ticks = 0;
  int               dp = 0;
  int               x,y,w;
  int             * compteur = NULL;

  /* initialisation de la SDL2 */
  if(initAllSDL2(IMG_INIT_PNG)){
    fprintf(stderr,"Erreur d'initialisation de la bibliotheque graphique.\n");
    exit(-1);
  }

  /* initialisation des fenetres */
  initWindowSDL2(400,600,"Jumper",SDL_WINDOW_RESIZABLE,gris,0);
  initWindowSDL2(300,110,"Jumper - Count",0,gris,0);
  if(initIteratorWindowSDL2()){
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

  /* --- deuxieme fenetre --- */
  getDimensionWindowSDL2(&w,NULL);
  getCoordWindowSDL2(&x,&y);
  if(!nextWindowSDL2()){
    setCoordWindowSDL2(x+w+6,y);
    /* differents blocks */
    button=createBlock(20.f,20.f,50.f,15.f,noir,0,0);
    createBlock(90.f,20.f,50.f,15.f,bleu,0,0);
    createBlock(160.f,20.f,50.f,15.f,rouge,0,0);
    createBlock(230.f,20.f,50.f,15.f,vert,0,0);
    compteur=malloc(4*sizeof(*compteur));
    for(dp=0;dp<4;++dp){
      compteur[dp]=0;
    }
    dp=0;
    setDataElementSDL2(button,compteur);
    addElementToElementSDL2(personnage,button);

    /* textes associees */
    scor=createTexte(40.f,45.f,60.f,45.f,"arial.ttf","0     ",blanc,0,0);
    compteur=malloc(sizeof(*compteur));
    *compteur=0;
    setDataElementSDL2(scor,compteur);
    addElementToElementSDL2(scor,button);
    setActionElementSDL2(scor,actualiseCompteur);
    scor=createTexte(110.f,45.f,60.f,45.f,"arial.ttf","0     ",blanc,0,0);
    compteur=malloc(sizeof(*compteur));
    *compteur=1;
    setDataElementSDL2(scor,compteur);
    addElementToElementSDL2(scor,button);
    setActionElementSDL2(scor,actualiseCompteur);
    scor=createTexte(180.f,45.f,60.f,45.f,"arial.ttf","0     ",blanc,0,0);
    compteur=malloc(sizeof(*compteur));
    *compteur=2;
    setDataElementSDL2(scor,compteur);
    addElementToElementSDL2(scor,button);
    setActionElementSDL2(scor,actualiseCompteur);
    scor=createTexte(250.f,45.f,60.f,45.f,"arial.ttf","0     ",blanc,0,0);
    compteur=malloc(sizeof(*compteur));
    *compteur=3;
    setDataElementSDL2(scor,compteur);
    addElementToElementSDL2(scor,button);
    setActionElementSDL2(scor,actualiseCompteur);
  }

  /* display de la fenetre */
  initIteratorWindowSDL2();
  tps=0;
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
	break;
      case SDL_KEYUP:
	keyReleasedWindowSDL2(event.key.keysym.sym);
	break;
      case SDL_KEYDOWN:
	getDisplayCodeWindowSDL2(&dp);
	if(!dp && event.key.keysym.sym==SDLK_ESCAPE){
	  *run=0;
	}else{
	  keyPressedWindowSDL2(event.key.keysym.sym);
	}
	break;
      case SDL_MOUSEBUTTONDOWN:
	clickWindowSDL2(event.button.x,event.button.y);
	break;
      }
    }

    /* update de la fenetre */
    updateAllWindowSDL2();
    /* affichage de la fenetre */
    displayAllWindowSDL2();
    /* delai pour 60 frames/secondes */
    ticks = 16 - SDL_GetTicks() + tps;
    if(ticks>0){
      SDL_Delay(ticks);
    }
  }

  closeAllWindowSDL2();
  closeAllSDL2();

  return 0;
}
