#!/bin/makefile

SDL2TK = SANDAL2/ElementSDL2.o SANDAL2/FenetreSDL2.o SANDAL2/DisplayCode.o SANDAL2/FontSDL2.o SANDAL2/SANDAL2.o SANDAL2/HitBox.o

OFLAG= -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_ttf -g -lm
CFLAG=

OFILE=main.o jeu.o menu.o $(SDL2TK)
PROG=jumper

$(PROG): $(OFILE)
	gcc $(OFILE) -o $(PROG) $(OFLAG)

.o:.c
	gcc -c $< $(CFLAG)

clean:
	rm *.o *~
clear: clean
