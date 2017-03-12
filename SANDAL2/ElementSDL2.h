#ifndef _ELEMENTSDL2_SDL2TK_KLEVH_
#define _ELEMENTSDL2_SDL2TK_KLEVH_

#include "HitBox.h"
#include "FontSDL2.h"
#include "FenetreSDL2.h"
#include "DisplayCode.h"

/**
 * @file ElementSDL2.h
 * @brief Contains all structures related to Elements
 */

/**
 * @brief List of windows
 *   WARNING : Do not touch this list ... trust me
 */
extern ListFenetreSDL2 * _windows_SDL2TK;

/**
 * @struct EntrySDL2
 * @brief More informations about entry 
 */
typedef struct{
  int size_min;
  ///< minimum size of the text of the entry
  int size_max;
  ///< maximum size of the text of the entry
  int size;
  ///< actual size of the text of the entry
  /* vaut 1 si l'Entry est selectionnee, 0 sinon */
  int isSelect;
  ///< tells whether or not the Entry is selected (1 for yes, 0 for no)
  int isScripted;
  ///< tells whether or not the Entry is crypted (1 for yes, 0 for no)
}EntrySDL2;

struct ListPtrElementSDL2;

/**
 * @struct ElementSDL2
 * @brief All the informations of an element
 */
typedef struct ElementSDL2{
  float x;
  ///< abscissa coordinate of the top left of the element
  float y;
  ///< ordinate coordinate of the top left of the element
  float width;
  ///< width of the element
  float height;
  ///< height of the element
  float prX;
  ///< abscissa coordinate of the rotation point (if from 0 to 1, in the element)
  float prY;
  ///< ordinate coordinate of the rotation point (if from 0 to 1, in the element)
  float rotation;
  ///< rotation angle of the element
  float rotSpeed;
  ///< speed rotation (degree / update) of the element
  /* couleurs du texte et du block (la premiere case vaut -1 si la partie a colorie n'est pas dans l'element) */
  int coulBlock[4];
  ///< color of the block of the element (if first value -1, there is no block)
  float textSize;
  ///< text proportion in the block
  ListDisplayCode *codes;
  ///< list of display code of the element
  void (*action)(struct ElementSDL2*);
  ///< function called when update
  void (*onClick)(struct ElementSDL2*);
  ///< function called when the element is clicked
  void (*unClick)(struct ElementSDL2*);
  ///< function called when the element is unclicked
  void (*keyPress)(struct ElementSDL2*,SDL_Keycode c);
  ///< function called when a key is pressed
  void (*keyReleased)(struct ElementSDL2*,SDL_Keycode c);
  ///< function called when a key is released
  SDL_Texture *image;
  ///< texture of the image (NULL if no image)
  FontSDL2 *police;
  ///< informations about the text (NULL if no text)
  EntrySDL2 *entry;
  ///< informations about the entry (NULL if no entry)
  struct ListPtrElementSDL2 *interactions;
  ///< list of elements that this element can modifie
  ListHitBox * hitboxes;
  ///< list of clickable zones
  void * data;
  ///< data available for the user
  int delete;
  ///< tells whether or not the element should be deleted
}ElementSDL2;

/**
 * @struct PtrElementSDL2
 * @brief Structure used to store elements' pointers in a list of element
 */
typedef struct PtrElement{
  ElementSDL2 *element;
  ///< pointer of the element
  struct PtrElement *next;
  ///< next PtrElement in the list
}PtrElementSDL2;

/**
 * @struct ListPtrElementSDL2
 * @brief List of PtrElementSDL2
 */
typedef struct ListPtrElementSDL2{
  PtrElementSDL2 *first;
  ///< first PtrElementSDL2 of the list
  PtrElementSDL2 *last;
  ///< last PtrElementSDL2 of the list
  PtrElementSDL2 *current;
  ///< current PtrElementSDL2 of the list (used for iterator)
  struct ListPtrElementSDL2 * next;
  ///< next List of PtrElementSDL2
  int code;
  ///< plan of the list
}ListPtrElementSDL2;

/**
 * @struct ListDCElementSDL2
 * @brief List (display code) of list (plan) of element
 */
typedef struct ListDCElementSDL2{
  ListPtrElementSDL2 * first;
  ///< first list (plan) of element
  ListPtrElementSDL2 * current;
  ///< current list (plan) of element (used for iterator)
  struct ListDCElementSDL2 * next;
  ///< next list (display code) of list (plan) of element
  int code;
  ///< display code of this list
}ListDCElementSDL2;

/**
 * @struct ListElementSDL2
 * @brief List of list (display code) of list (plan) of elements
 */
typedef struct ListElementSDL2{
  ListDCElementSDL2 *first;
  ///< first list (display code) of list (plan) of elements
  ListDCElementSDL2 * currentDCIterator;
  ///< current list (display code) of list (plan) of elements (used for iterator)
  ListPtrElementSDL2 *currentPIterator;
  ///< current list (plan) of elements (used for iterator)
}ListElementSDL2;



/* -------------------------------------------------------
 * Liste d'elements SDL2 avec plan commun
 */
/**
 * @brief Initialise a list (plan) of elements
 * @param plan : plan of the list to be initialised
 * @return An empty list (plan) of elements
 */
ListPtrElementSDL2* initListPtrElementSDL2(int plan);
/**
 * @brief free the memory of a list (plan) of elements
 * @param l : list to be freed
 */
void freeListPtrElementSDL2(ListPtrElementSDL2* l);
/**
 * @brief add an element to a list (plan) of elements
 * @param l : list (plan) of elements which to add an element
 * @param e : element to add
 */
void addPtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e);
/**
 * @brief remove an element to a list (plan) of elements
 * @param l : list (plan) of elements which to remove an element
 * @param e : element to remove
 */
void removePtrElementSDL2(ListPtrElementSDL2* l,ElementSDL2* e);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (plan) d'element, contenant le code 
 * d'affichage
 */
/**
 * @brief Initialise a list (display code) of lists (plan) of elements
 * @param displayCode : display code of the list to be initialised
 * @return An empty list (display code) of lists (plan) of elements
 */
ListDCElementSDL2* initListDCElementSDL2(int displayCode);
/**
 * @brief free the memory of a list (display code) of lists (plan) of elements
 * @param l : list to be freed
 */
void freeListDCElementSDL2(ListDCElementSDL2* l);
/**
 * @brief add a list (plan) to a list (display code) of lists (plan) of elements
 * @param l : list (display code) of lists (plan) of elements which to add a list (plan)
 * @param lp : list (plan) to add
 */
void addListPtrElementSDL2(ListDCElementSDL2* l, ListPtrElementSDL2 *lp);
/**
 * @brief remove a list (plan) from a list (display code) of lists (plan) of elements
 * @param l : list (display code) of lists (plan) of elements which to remove an element
 * @param lp : list (plan) to remove
 */
void removeListPtrElementSDL2(ListDCElementSDL2* l,ListPtrElementSDL2 *lp);
/**
 * @brief remove an element all lists (display code) starting from a list (display code) of lists (plan) of elements 
 * @param l : list (display code) of lists (plan) of elements which to remove an element
 * @param e : element to be removed
 */
void removeDCElementSDL2(ListDCElementSDL2** l,ElementSDL2 *e);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Liste de liste (code d'affichage) de liste (plan) 
 * d'element
 */
/**
 * @brief Initialise a list of lists (display code) of lists (plan) of elements
 * @return An empty list  of lists (display code) of lists (plan) of elements
 */
ListElementSDL2* initListElementSDL2();
/**
 * @brief free the memory of a list of lists (display code) of lists (plan) of elements
 * @param l : list to be freed
 */
void freeListElementSDL2(ListElementSDL2* l);
/**
 * @brief add an element to a list of lists (display code) of lists (plan) of elements
 * @param e : element to be add
 */
int addElementSDL2(ElementSDL2* e);
/**
 * @brief remove all elements that are marked as deletable (do not use it yourself, used in update)
 */
void cleanElementSDL2();
/**
 * @brief mark an element as removable
 * @param e : element to be removed
 */
void removeElementSDL2(ElementSDL2 *e);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Creation, liberation et information sur un Element SDL2
 */
/**
 * @brief Free the memory used by an element
 * @param e : element to be freed
 */
void freeElementSDL2(ElementSDL2 *e);
/**
 * @brief Generate a rectangle like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param couleur : color of the rectangle (RGBA)
 * @param displayCode : display code of the rectangle
 * @param plan : plan of the rectangle
 */
ElementSDL2* createBlock(float x,float y,float width,float height,int couleur[4],int displayCode,int plan);
/**
 * @brief Generate a text like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param displayCode : display code of the text
 * @param plan : plan of the text
 */
ElementSDL2* createTexte(float x,float y,float width,float height,char * font,char * text,int textColor[4],int displayCode,int plan);
/**
 * @brief Generate an image like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param image : path to load the image to be used by the element
 * @param displayCode : display code of the image
 * @param plan : plan of the image
 */
ElementSDL2* createImage(float x,float y,float width,float height,char *image,int displayCode,int plan);
/**
 * @brief Generate a button like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param texteSize : proportion of the text in the rectangle (it is centered)
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param colorBlock : color of the rectangle (RGBA)
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 */
ElementSDL2* createButton(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan);
/**
 * @brief Generate a button like element with an image
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param texteSize : proportion of the text in the rectangle (it is centered)
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param image : path to load the image to be used by the element
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 */
ElementSDL2* createButtonImage(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan);
/**
 * @brief Generate a prompt like element
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param texteSize : proportion of the text in the rectangle (it is centered)
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param colorBlock : color of the rectangle (RGBA)
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 * @param min : minimum number of character for the prompt to be validate
 * @param max : maximum number of character for the prompt to be validate
 * @param isScripted : flag which tells whether or not the prompt is cripted
 */
ElementSDL2* createEntry(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],int couleurBlock[4],int displayCode,int plan,int min,int max, int isScripted);
/**
 * @brief Generate a prompt like element with an image
 * @param x : abscissa coordinate of its top left corner
 * @param y : ordinate coordinate of its top left corner
 * @param width : width of the element
 * @param height : height of the element
 * @param texteSize : proportion of the text in the rectangle (it is centered)
 * @param font : path to load the font to be used by the element
 * @param text : text of the element
 * @param textColor : color of the text (RGBA)
 * @param image : path to load the image to be used by the element
 * @param displayCode : display code of the button
 * @param plan : plan of the button
 * @param min : minimum number of character for the prompt to be validate
 * @param max : maximum number of character for the prompt to be validate
 * @param isScripted : flag which tells whether or not the prompt is cripted
 */
ElementSDL2* createEntryImage(float x,float y,float width,float height,float texteSize,char * font,char * text,int textColor[4],char *image,int displayCode,int plan,int min,int max,int isScripted);
/**
 * @brief tell whether or not the element can be displaied
 * @param e : element
 * @return 1 if the element is displaied, 0 if not
 */
int isDisplaied(ElementSDL2* e);
/**
 * @brief getter for the Element's coordinates
 * @param e : element to get the coordinates
 * @param x : where the abscissa coordinate will be store
 * @param y : where the ordinate coordinate will be store
 * @return 1 if there was an error, 0 if not
 */
int getCoordElementSDL2(ElementSDL2* e,float* x,float* y);
/**
 * @brief getter for the Element's angle
 * @param e : element to get the angle
 * @param a : where the angle will be store
 * @return 1 if there was an error, 0 if not
 */
int getAngleElementSDL2(ElementSDL2* e,float* a);
/**
 * @brief getter for the Element's dimensions
 * @param e : element to get the dimensions
 * @param w : where the width will be store
 * @param h : where the height will be store
 * @return 1 if there was an error, 0 if not
 */
int getDimensionElementSDL2(ElementSDL2* e,int* w,int * h);
/**
 * @brief getter for the Element's rotation point
 * @param e : element to get the rotation point's coordinate
 * @param x : where the abscissa coordinate of the rotation point will be store 
 * @param y : where the ordinate coordinate of the rotation point will be store 
 * @return 1 if there was an error, 0 if not
 */
int getRotationPointElementSDL2(ElementSDL2* e,float *x,float *y);
/**
 * @brief getter for the element's rotation speed
 * @param e : element to get the rotation speed
 * @param s : where the rotation speed will be store
 * @return 1 if there was an error, 0 if not
 */
int getRotationSpeedElementSDL2(ElementSDL2* e,float* s);
/**
 * @brief getter for the element's data
 * @param e : element to get its data
 * @return the data of the element
 */
void * getDataElementSDL2(ElementSDL2* e);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * modification d'un Element SDL2
 */
/**
 * @brief set the element's font
 * @param e : element to be modified
 * @param font : path of the new font
 */
void setFontElementSDL2(ElementSDL2 *e,char * font);
/**
 * @brief set the element's text
 * @param e : element to be modified
 * @param text : the new text
 */
void setTextElementSDL2(ElementSDL2 *e,char * text);
/**
 * @brief set the element's block color
 * @param e : element to be modified
 * @param color : new block color
 */
void setColorElementSDL2(ElementSDL2 *e,int color[4]);
/**
 * @brief set the element's text color
 * @param e : element to be modified
 * @param color : new text color
 */
void setTextColorElementSDL2(ElementSDL2 *e, int color[4]);
/**
 * @brief set the element's image
 * @param e : element to be modified
 * @param image : path of the new image
 */
int setImageElementSDL2(ElementSDL2 *e,char *image);
/**
 * @brief set the element's coordinates
 * @param e : element to be modified
 * @param x : new abscissa coordinate
 * @param y : new ordinate coordinate
 */
void replaceElementSDL2(ElementSDL2 *e,float x,float y);
/**
 * @brief move an element
 * @param e : element to be modified
 * @param x : abscissa increment
 * @param y : ordinate increment
 */
void moveElementSDL2(ElementSDL2 *e,float x,float y);
/**
 * @brief resize an element
 * @param e : element to be modified
 * @param width : new width
 * @param height : new height
 */
void resizeElementSDL2(ElementSDL2 *e,float width,float height);
/**
 * @brief set the text size of the text of an element in this element
 * @param e : element to be modified
 * @param textSize : new size of the text (in percent)
 */
void setTextSize(ElementSDL2 *e,float textSize);
/**
 * @brief add a display code to an element (if it did not already had it)
 * @param e : element to be modified
 * @param displayCode : new display code
 * @param plan : plan linked to the new display code
 */
void addDisplayCodeElementSDL2(ElementSDL2 *e,int displayCode,int plan);
/**
 * @brief remove a display code to an element (if it has it)
 * @param e : element to be modified
 * @param displayCode : display code to be removed
 */
void removeDisplayCodeElementSDL2(ElementSDL2 *e,int displayCode);
/**
 * @brief set the isDisplaied option of a display code (if the element has it)
 * @param e : element to be modified
 * @param displayCode : display code to be modified
 * @param isDisplaied : new isDisplaied option
 */
void setDisplayElementSDL2(ElementSDL2 *e,int displayCode,int isDisplaied);
/**
 * @brief set the plan of a display code (if the element has it)
 * @param e : element to be modified
 * @param displayCode : display code to be modified
 * @param plan : new plan linked to the display code
 */
void setPlanElementSDL2(ElementSDL2 *e,int DisplayCode,int plan);
/**
 * @brief set the continuous behaviour of an element
 * @param e : element to be modified
 * @param action : function to be called on each update call
 */
void setActionElementSDL2(ElementSDL2 *e,void (*action)(ElementSDL2*));
/**
 * @brief set the behaviour of an element when a key is pressed
 * @param e : element to be modified
 * @param keyPress : function to be called when a key is pressed
 */
void setKeyPressElementSDL2(ElementSDL2 *e,void (*keyPress)(ElementSDL2*,SDL_Keycode c));
/**
 * @brief set the behaviour of an element when a key is released
 * @param e : element to be modified
 * @param keyReleased : function to be called when a key is released
 */
void setKeyReleasedElementSDL2(ElementSDL2 *e,void (*keyReleased)(ElementSDL2*,SDL_Keycode c));
/**
 * @brief set the behaviour of an element when it is clicked
 * @param e : element to be modified
 * @param onCLick : function to be called when it is clicked
 */
void setOnClickElementSDL2(ElementSDL2 *e,void (*onCLick)(ElementSDL2*));
/**
 * @brief set the behaviour of an element when it is unclicked
 * @param e : element to be modified
 * @param unCLick : function to be called when it is unclicked
 */
void setUnClickElementSDL2(ElementSDL2 *e,void (*unCLick)(ElementSDL2*));
/**
 * @brief add an element to another so that this other can modifie the first one
 * @param e : element to be modified
 * @param add : element to be add
 */
void addElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *add);
/**
 * @brief remove an element to another so that this other can not modifie the first one
 * @param e : element to be modified
 * @param add : element to be removed
 */
void delElementToElementSDL2(ElementSDL2 *e,ElementSDL2 *del);
/**
 * @brief add a clickable zone to the element (or a blocking one)
 * @param e : element to be modified
 * @param hb : clickable zone to be add
 * @param blocking : tells whether or not the clickable zone is a blocking one
 */
void addHitBoxElementSDL2(ElementSDL2 *e,HitBox *hb,int blocking);
/**
 * @brief increase the rotation speed of an element
 * @param e : element to be modified
 * @param s : rotation speed increment
 */
void addRotationSpeedElementSDL2(ElementSDL2 *e,float s);
/**
 * @brief set the rotation speed of an element
 * @param e : element to be modified
 * @param s : new rotation speed of the element
 */
void setRotationSpeedElementSDL2(ElementSDL2 *e,float s);
/**
 * @brief increase the angle of an element
 * @param e : element to be modified
 * @param a : angle increment
 */
void addAngleElementSDL2(ElementSDL2 *e,float a);
/**
 * @brief set the angle of an element
 * @param e : element to be modified
 * @param a : new angle of the element
 */
void setAngleElementSDL2(ElementSDL2 *e,float a);
/**
 * @brief set the rotation point's coordinates of an element
 * @param e : element to be modified
 * @param x : new abscissa coordinate of the rotation point
 * @param y : new ordinate coordinate of the rotation point
 */
void setRotationPointElementSDL2(ElementSDL2 *e,float x,float y);
/**
 * @brief set the element's data
 * @param e : element to be modified
 * @param data : new data of the element
 */
void setDataElementSDL2(ElementSDL2 *e,void *data);
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * Iterateur de structure sur la liste d'ElementSDL2 lié a un autre ElementSL2
 */
/**
 * @brief initialise the element's iterator on all the elements it can modifie
 * @param e : element from which to initialise the iterator
 */
int initIterateurElementSDL2(ElementSDL2 *e);
/**
 * @brief gives the current element's iterator's value and go to the next one
 * @param e : element to be modified
 */
ElementSDL2* nextIterateurElementSDL2(ElementSDL2 *e);
/* ------------------------------------------------------- */



/* ------------------------------------------------------- 
 * Iterateur de structure sur la liste d'ElementSDL2
 */
/**
 * @brief initialise the iterator of all elements having a common display code
 * @param displayCode : common display code of the elements
 */
int initIterateur(int displayCode);
/**
 * @brief gives the current iterator's value and go to the next one
 */
ElementSDL2* nextElementSDL2();
/* ------------------------------------------------------- */



/* -------------------------------------------------------
 * modification d'un Element SDL2 spécifique aux Entry
 */
/**
 * @brief change the minimum and maximum size of a prompt (if a value is negative, it is not modified)
 * @param e : element to be modified
 * @param size_min : new minimum size of the prompt
 * @param size_max : new maximum size of the prompt
 */
void changeSizeEntrySDL2(ElementSDL2 *e,int size_min,int size_max);
/**
 * @brief set an element to crypted or uncrypted
 * @param e : element to be modified
 * @param isScripted : crypted option
 */
void setScriptedEntrySDL2(ElementSDL2 *e,int isScripted);
/**
 * @brief add a character to a prompt
 * @param e : element to be modified
 * @param c : character to be added
 */
void addCharEntrySDL2(ElementSDL2 *e,char c);
/**
 * @brief remove a character to a prompt
 * @param e : element to be modified
 */
void removeCharEntrySDL2(ElementSDL2 *e);
/* ------------------------------------------------------- */

#endif
