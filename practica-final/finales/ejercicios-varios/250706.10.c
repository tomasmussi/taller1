/*
 *      Ej [10] coloquio 11/07/2006
 * 		Escribir una rutina grafica que dibuje una cruz
 * 		del tamanio de la ventana
 * 		Compilar con:
 * 		gcc -L/usr/lib -lSDL -lpthread -I/usr/include/SDL -D_REENTRANT 110706.10.c -o ej10_3
 */


#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char** argv)
{
	int pixelX=0;
	int pixelY=0;
	Uint8* pixel;
	int bpp;
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen=SDL_SetVideoMode(640,480,16,SDL_DOUBLEBUF);
	if(!screen) {
		SDL_Quit();
		exit(1);	
	}
	
	Uint32 colorX, colorY;
	/* takes black and sky blue*/
	colorX=SDL_MapRGB(screen->format,255,255,255);
	colorY=SDL_MapRGB(screen->format,100,160,255);
	/* paints horizontal pixels */
	pixelY=240;
	bpp=screen->format->BytesPerPixel;
	for (pixelX=0; pixelX<=screen->w; pixelX++) {
		pixel=(Uint8*)screen->pixels + pixelX*bpp + pixelY*screen->pitch;
		*(Uint16*)pixel=colorX;
	}
	/* paints vertical pixels */
	pixelX=320;
	for (pixelY=0; pixelY<=screen->h; pixelY++) {
		pixel=(Uint8*)screen->pixels + pixelX*bpp + pixelY*screen->pitch;
		*(Uint16*)pixel=colorY;
	}
	
	SDL_Flip(screen);
	/* waits 3 seconds showing window */
	SDL_Delay(3000);
	SDL_FreeSurface(screen);
	SDL_Quit();
	
	return 0;
}
