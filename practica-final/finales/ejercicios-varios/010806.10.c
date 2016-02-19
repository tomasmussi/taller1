/*
 *      Ejercicio [10] coloquio 01/08/06
 * 		Escribir una rutina grafica que pinte la pantalla de azul
 * 		Compilar con:
 * 		gcc -L/usr/lib -lSDL -lpthread -I/usr/include/SDL -D_REENTRANT 010806.10.c -o ej10
 */


#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen=SDL_SetVideoMode(640,480,16,SDL_DOUBLEBUF);
	if(!screen) {
		SDL_Quit();
		exit(1);	
	}
	
	Uint32 color;
	color=SDL_MapRGB(screen->format,0,0,255);
	SDL_FillRect(screen, NULL, color);
	SDL_Flip(screen);
	SDL_FreeSurface(screen);
	SDL_Delay(5000);
	SDL_Quit();
	return 0;
}
