#include "jeu.h"

void gravite(ElementSDL2 *this){
  /* vitesse verticale du personnage */
  static float  dpy = -SPEED_MAX;
  /* score */
  static float score = 0.f;
  /* generateur */
  static float lastGenY = 0.f;
  /* difficulte */
  static int diff = 10;
  /* variables non static */
  ElementSDL2 * courant = NULL;
  ElementSDL2 * compteur = NULL;
  ElementSDL2 * tmp = NULL;
  int           noir[4] = {0,0,0,0};
  int           bleu[4] = {0,0,255,0};
  int           rouge[4] = {255,0,0,0};
  int           vert[4] = {0,255,0,0};
  int           blanc[4] = {255,255,255,0};
  int           collision = 0;
  int           height = 0;
  int         * tab;
  float         y = 0;
  
  initIterateurElementSDL2(this);
  compteur = nextIterateurElementSDL2(this);
  getDimensionWindowSDL2(NULL,&height);
  getCoordElementSDL2(this,NULL,&y);

  if(((Data*)(getDataElementSDL2(this)))->left==2){
    setActionElementSDL2(this,NULL);
    setKeyPressElementSDL2(this,NULL);
    setKeyReleasedElementSDL2(this,NULL);
    changeDisplayWindowSDL2(0);
    dpy = -SPEED_MAX;
    score = 0.f;
    lastGenY = 0.f;
    diff = 10;
  }else if(height<y){
    setActionElementSDL2(this,NULL);
    setKeyPressElementSDL2(this,NULL);
    setKeyReleasedElementSDL2(this,NULL);
    courant=createTexte(50.f,225.f,300.f,150.f,"arial.ttf","GAME OVER",blanc,1,0);
    addElementToElementSDL2(courant,this);
    setKeyPressElementSDL2(courant,endGame);
    dpy = -SPEED_MAX;
    score = 0.f;
    lastGenY = 0.f;
    diff = 10;
  }else{
    tab=(int*)getDataElementSDL2(compteur);
    courant=nextIterateurElementSDL2(this);
    while(courant){
      /* verifie qu'il y a collision avec l'element courant */
      if(dpy>0 && courant->x+courant->width>=this->x && courant->x<=this->x+this->width && courant->y<=this->y+this->height && courant->y+courant->height>=this->y+this->height){
	tmp=nextIterateurElementSDL2(this);
	if(tab){
	  tab[*((int *)(courant->data))]++;
	}
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
	courant = tmp;
      }else if(dpy<0 && this->y <= 100.f){
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
  
    if(!collision){
      dpy+=.3f;
    }else{
      dpy = -SPEED_MAX * collision;
    }
  
    score-=dpy;
    lastGenY-=dpy;
    if(score > ((Data *)(this->data))->score){
      ((Data *)(this->data))->score=(int)score;
      if(score>(diff+1)*1000){
	diff++;
      }
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
      if((!(rand()%(8+diff) && lastGenY >= HEIGHT_OBSTACLE * 2) || lastGenY>=((80+2*diff>DIST_MAX_BRICK?DIST_MAX_BRICK:80+2*diff))) && lastGenY>=(10+diff>DIST_MIN_BRICK?DIST_MIN_BRICK:10+2*diff)){
	if(!(rand()%50)){
	  genereObstacle(this,vert,3);
	}else{
	  genereObstacle(this,noir,0);
	}
	lastGenY=10;
      }else if(lastGenY >= DIST_MIN_BRICK/2 && !(rand()%30)){
	if(!(rand()%3)){
	  genereObstacle(this,rouge,2);
	  lastGenY=10;
	}else{
	  genereObstacle(this,bleu,1);
	}
      }
    }
  }
}

void deplacement(ElementSDL2 *this, SDL_Keycode c){
  if(c=='O'|| c=='^'){ /* fleche droite */
    ((Data *)(this->data))->right = 1;
  }else if(c=='P' || c=='\\'){ /* fleche gauche */
    ((Data *)(this->data))->left = 1;
  }else if(c==SDLK_ESCAPE){
    ((Data *)(this->data))->left = 2;
  }else{
    printf("%c\n",c);
  }
}
void stop(ElementSDL2 *this, SDL_Keycode c){
  if(c=='O'|| c=='^'){
    ((Data *)(this->data))->right=0;
  }else if(c=='P' || c=='\\'){
    ((Data *)(this->data))->left=0;
  }
}

void initGame(ElementSDL2 *personnage, int couleur[4]){
  ElementSDL2 * obstacle, *tmp;
  float i , *j;
  int w = 0;
  Data* d;

  actualiseScore(NULL);

  getDimensionWindowSDL2(&w,NULL);

  replaceElementSDL2(personnage,180.f,510.f);
  d=(Data*)(getDataElementSDL2(personnage));
  d->score = 0;
  d->right = 0;
  d->left = 0;
  
  setActionElementSDL2(personnage,gravite);
  setKeyPressElementSDL2(personnage,deplacement);
  setKeyReleasedElementSDL2(personnage,stop);

  initIterateurElementSDL2(personnage);
  nextIterateurElementSDL2(personnage);
  obstacle=nextIterateurElementSDL2(personnage);
  while(obstacle){
    tmp=nextIterateurElementSDL2(personnage);
    delElementToElementSDL2(personnage,obstacle);
    removeElementSDL2(obstacle);
    obstacle=tmp;
  }
  
  for(i=50.f;i<500.f;i+=60.f){
    j=malloc(sizeof(*j));
    *j=0;
    obstacle = createBlock((float)rand()/RAND_MAX*(w-WIDTH_OBSTACLE),i+(float)rand()/RAND_MAX*40-20.f,WIDTH_OBSTACLE,HEIGHT_OBSTACLE,couleur,1,2);
    setDataElementSDL2(obstacle,j);
    addElementToElementSDL2(personnage,obstacle);
  }

  j=malloc(sizeof(*j));
  *j=0;
  obstacle = createBlock(175.f,550.f,WIDTH_OBSTACLE,HEIGHT_OBSTACLE,couleur,1,2);
  setDataElementSDL2(obstacle,j);
  addElementToElementSDL2(personnage,obstacle);
}

void genereObstacle(ElementSDL2 *personnage,int couleur[4],int brick){
  ElementSDL2 * obstacle;
  int * i = malloc(sizeof(*i)), w = 0;

  getDimensionWindowSDL2(&w,NULL);
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

  if(!this){
    score = -1;
  }else{
    if(!e){
      if(initIterateurElementSDL2(this)){
	e=nextIterateurElementSDL2(this);
      }else{
	printf("Erreur dans actualiseScore\n");
      }
    }
    
    if(e && score < ((Data *)(e->data))->score){
      score = ((Data *)(e->data))->score;
      sprintf(s+8,"%d",score);
      i=8;
      while(s[i]){
	++i;
      }
      while(i<24){
	s[i]=' ';
	i++;
      }
      setTextElementSDL2(this,s);
    }
  }
}

void endGame(ElementSDL2 * this, SDL_Keycode c){
  int noir[4]={0,0,0,0};

  switch(c){
  case SDLK_ESCAPE:
    removeElementSDL2(this);
    changeDisplayWindowSDL2(0);
    break;
  case SDLK_SPACE:
    initIterateurElementSDL2(this);
    initGame(nextIterateurElementSDL2(this),noir);
    removeElementSDL2(this);
    break;
  }
}

void actualiseCompteur(ElementSDL2 *this){
  static int count[4]={0,0,0,0};
  char s[]="      ";
  int * vals;
  int * id;
  int i,j,v;
  ElementSDL2 * e;

  if(this){
    if(initIterateurElementSDL2(this)){
      e = nextIterateurElementSDL2(this);
      if(e){
	vals = (int*)getDataElementSDL2(e);
	id = (int *)getDataElementSDL2(this);
	if(vals && id){
	  if(vals[*id] > count[*id]){
	    v=count[*id];
	    j=0;
	    while(v!=0){
	      j++;
	      v/=10;
	    }
	    count[*id]=vals[*id];
	    sprintf(s,"%d",vals[*id]);
	    i=0;
	    while(s[i]){
	      ++i;
	    }
	    moveElementSDL2(this,-(i-j)*5.f,0.f);
	    while(i<6){
	      s[i]=' ';
	      i++;
	    }
	    setTextElementSDL2(this,s);
	  }
	}
      }
    }
  }
}
