/*
 *      Ej [10] coloquio 11/07/2006
 * 		Escribir una rutina grafica que dibuje una linea discontinua
 * 		horizontal en la pantalla
 * 		Compilar con:
 * 		gcc -L/usr/lib -lSDL -lpthread -I/usr/include/SDL -D_REENTRANT 110706.10.c -o ej10
 */


#include <stdio.h>
#include <SDL/SDL.h>

int main(int argc, char** argv)
{
	int pixelX=0;
	int pixelY=240;
	Uint8* pixel;
	int bpp;
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen=SDL_SetVideoMode(640,480,16,SDL_DOUBLEBUF);
	if(!screen) {
		SDL_Quit();
		exit(1);	
	}
	
	/* paints pixels */
	Uint32 color;
	/* takes yellow color */
	color=SDL_MapRGB(screen->format,255,255,0);
	bpp=screen->format->BytesPerPixel;
	for (pixelX=0; pixelX<=screen->w; pixelX++) {
		pixel=(Uint8*)screen->pixels + pixelX*bpp + pixelY*screen->pitch;
		*(Uint16*)pixel=color;
		if (pixelX%160==0)
			pixelX=pixelX+6;
	}
	
	SDL_Flip(screen);
	/* waits 3 seconds showing window */
	SDL_Delay(3000);
	SDL_FreeSurface(screen);
	SDL_Quit();
	
	return 0;
}
