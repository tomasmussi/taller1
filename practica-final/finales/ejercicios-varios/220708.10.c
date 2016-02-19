/*
 * Ejercicio [10] final 22/07/08    
 * Escriba una rutina (para ambiente gráfico Windows o Linux) que
 * pinte un rectángulo rojo de la 1/3 parte del alto y ancho de la
 * ventana.
 * gcc -L/usr/lib -lSDL -lpthread -I/usr/include/SDL -D_REENTRANT 220708.10.c -o ej10_5
 */


#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char** argv)
{
	int pixelX;
	int pixelY;
	Uint8* pixel;
	Uint32 color;
	int bpp;
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(640,480,16,SDL_DOUBLEBUF);
	if (!screen) {
		SDL_Quit();
		exit(1);
	}
	color=SDL_MapRGB(screen->format, 255,0,0);
	bpp = screen->format->BytesPerPixel;
	
	for (pixelY=160; pixelY<320; pixelY++) {
		for (pixelX=214; pixelX<=428; pixelX++) {
			pixel=(Uint8*)screen->pixels + pixelX*bpp + pixelY*screen->pitch;
			*(Uint16*)pixel=color;
		}
	}
	SDL_Flip(screen);
	SDL_Delay(4000);
	SDL_FreeSurface(screen);
	SDL_Quit();	
	return 0;
}
