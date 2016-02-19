/*
 *     Ejercicio [10] final 19/02/08
 * 	   Escribir una rutina grafica que dibuje dos lineas horizontales
 *		dividiendo la pantalla en tres franjas iguales.
 * 		gcc -L/usr/lib -lSDL -lpthread -I/usr/include/SDL -D_REENTRANT 190208.10.c -o ej10_4
 */


#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char** argv)
{
	int pixelX;
	int pixelY;
	Uint8* pixel;
	int bpp;
	Uint32 color;
		
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen=SDL_SetVideoMode(640,480,16,SDL_DOUBLEBUF);
	if (!screen) {
		SDL_Quit();
		exit(1);
	}
	bpp = screen->format->BytesPerPixel;
	color = SDL_MapRGB(screen->format, 255, 150, 150);
	for (pixelY=160; pixelY<=screen->h; pixelY=pixelY+160) {
		for (pixelX=0; pixelX<=screen->w; pixelX++){
			pixel=(Uint8*)screen->pixels+screen->pitch*pixelY+bpp*pixelX;
			*(Uint16*)pixel=color;
		}
	}
	SDL_Flip(screen);
	SDL_Delay(3000);
	SDL_FreeSurface(screen);	
	SDL_Quit();
	return 0;
}
