#include "menu.h"

void play(ElementSDL2 * this){
  int noir[4]={0,0,0,0};
  ElementSDL2 *e;
  
  changeDisplayWindowSDL2(1);
  initIterateurElementSDL2(this);
  e=nextIterateurElementSDL2(this);
  if(e){
    initGame(e,noir);
  }else{
    printf("Erreur dans play\n");
  }
}

void quit(ElementSDL2 * this){
  *((int*)(getDataElementSDL2(this)))=0;
}

void config(ElementSDL2 * this){
}

void score(ElementSDL2 * this){
}
