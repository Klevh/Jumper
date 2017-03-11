#include "moteur.h"

void gravite(ElementSDL2 *this){
  /* vitesse verticale du personnage */
  static float  dpy = -SPEED_MAX;
  /* score */
  static int score = 0;
  /* generateur */
  static int lastGenY = 10;
  /* difficulte */
  static int diff = 0;
  /* variables non static */
  ElementSDL2 * courant = NULL;
  ElementSDL2 * tmp = NULL;
  int           noir[4] = {0,0,0,0};
  int           bleu[4] = {0,0,255,0};
  int           rouge[4] = {255,0,0,0};
  int           vert[4] = {0,255,0,0};
  int           collision = 0;
  int           height = 0;
  
  initIterateurElementSDL2(this);
  courant = nextIterateurElementSDL2(this);
  
  while(courant){
  /* verifie qu'il y a collision avec l'element courant */
    if(dpy>0 && courant->x+courant->width>=this->x && courant->x<=this->x+this->width && courant->y<=this->y+this->height && courant->y+courant->height>=this->y+this->height){
      switch(*((int *)(courant->data))){
      case 3 :
	collision = 2;
	break;
      case 2:
	delElementToElementSDL2(this,courant);
	removeElementSDL2(courant);
	collision = (collision ? collision : 1);
	break;
      case 1:
	delElementToElementSDL2(this,courant);
	removeElementSDL2(courant);
	break;
      case 0:
	collision = (collision ? collision : 1);
	break;
      default:
	printf("Erreur, brique inconnue.\n");
      }
      courant = nextIterateurElementSDL2(this);
    }else if(dpy<0 && this->y <= 100.f){
      getDimensionFenetreSDL2(NULL,&height);
      moveElementSDL2(courant,0.f,-dpy);
      if(courant->y > height){
	tmp=nextIterateurElementSDL2(this);
	delElementToElementSDL2(this,courant);
	removeElementSDL2(courant);
	courant=tmp;
      }else{
	courant = nextIterateurElementSDL2(this);
      }
    }else{
      courant = nextIterateurElementSDL2(this);
    }
  }
  
  score-=dpy;
  lastGenY-=dpy;
  if(score > ((Data *)(this->data))->score){
    ((Data *)(this->data))->score=score;
    if(score>(diff+1)*1000){
      diff++;
    }
  }
  
  if(!collision){
    dpy+=.3f;
  }else{
    dpy = -SPEED_MAX * collision;
  }

  if(dpy>=0 || this->y>100){
    moveElementSDL2(this,3.f*((Data *)(this->data))->right-3.f*((Data *)(this->data))->left,dpy);
    if(this->x+this->width<=0){
      replaceElementSDL2(this,396.f,this->y);
    }else if(this->x>=400){
      replaceElementSDL2(this,4.f-this->width,this->y);
    }
  }else{
    moveElementSDL2(this,3.f*((Data *)(this->data))->right-3.f*((Data *)(this->data))->left,0);
    if(this->x+this->width<=0){
      replaceElementSDL2(this,396.f,this->y);
    }else if(this->x>=400){
      replaceElementSDL2(this,4.f-this->width,this->y);
    }
    if((!(rand()%(8+diff)) || lastGenY>=((80+2*diff>170?170:80+2*diff))) && lastGenY>=(10+diff>120?120:10+2*diff)){
      if(!(rand()%10)){
	genereObstacle(this,vert,3);
      }else{
	genereObstacle(this,noir,0);
      }
      lastGenY=10;
    }
    if(lastGenY >= 90 && !(rand()%30)){
      if(!(rand()%3)){
	genereObstacle(this,rouge,2);
      }else{
	genereObstacle(this,bleu,1);
      }
    }
  }
}

void deplacement(ElementSDL2 *this, SDL_Keycode c){
  if(c=='O'){ /* fleche droite */
    ((Data *)(this->data))->right = 1;
  }else if(c=='P'){ /* fleche gauche */
    ((Data *)(this->data))->left = 1;
  }
}
void stop(ElementSDL2 *this, SDL_Keycode c){
  if(c=='O'){
    ((Data *)(this->data))->right=0;
  }else if(c=='P'){
    ((Data *)(this->data))->left=0;
  }
}

void initObstacle(ElementSDL2 *personnage, int couleur[4]){
  ElementSDL2 * obstacle;
  float i = 50.f, *j;
  int w = 0;

  getDimensionFenetreSDL2(&w,NULL);
  for(;i<550.f;i+=80.f){
    j=malloc(sizeof(*j));
    *j=0;
    obstacle = createBlock((float)rand()/RAND_MAX*(w-WIDTH_OBSTACLE),i+(float)rand()/RAND_MAX*40-20.f,WIDTH_OBSTACLE,HEIGHT_OBSTACLE,couleur,1,2);
    setDataElementSDL2(obstacle,j);
    addElementToElementSDL2(personnage,obstacle);
  }
}

void genereObstacle(ElementSDL2 *personnage,int couleur[4],int brick){
  ElementSDL2 * obstacle;
  int * i = malloc(sizeof(*i)), w = 0;

  getDimensionFenetreSDL2(&w,NULL);
  *i=brick;
  obstacle = createBlock((float)rand()/RAND_MAX*(w-WIDTH_OBSTACLE),10,WIDTH_OBSTACLE,HEIGHT_OBSTACLE,couleur,1,2);
  setDataElementSDL2(obstacle,i);
  addElementToElementSDL2(personnage,obstacle);
}

void actualiseScore(ElementSDL2 * this){
  static int score = 0;
  static ElementSDL2 * e=NULL;
  static char s[100] = "Score :                 ";
  int i;

  if(!e){
    if(initIterateurElementSDL2(this)){
      e=nextIterateurElementSDL2(this);
    }else{
      printf("Erreur\n");
    }
  }

  if(e && score < ((Data *)(e->data))->score){
    score = ((Data *)(e->data))->score;
    sprintf(s+8,"%d",score);
    i=8;
    while(s[i]){
      ++i;
    }
    if(i<99){
      s[i]=' ';
    }
    setTextElementSDL2(this,s);
  }
}

void touch(ElementSDL2 * this){
  printf("Ca marche !\n");
}
