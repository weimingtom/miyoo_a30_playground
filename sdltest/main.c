#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
#include <linux/fb.h>
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>

int main(int argc, char* args[])
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("%s, failed to SDL_Init\n", __func__);
    return -1;
  }
 
  SDL_Surface* screen;
//SDL_SWSURFACE
  screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //SDL_HWSURFACE | SDL_DOUBLEBUF
  if(screen == NULL){
    printf("%s, failed to SDL_SetVideMode\n", __func__);
    return -1;
  }
  SDL_ShowCursor(0);

  int index=30, cnt=30;
  while(cnt--){
    switch(index){
    case 0:
      SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));
printf(">red\n");
      break;
    case 1:
      SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0xff, 0x00));
printf(">green\n");
      break;
    case 2:
      SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0xff));
printf(">blue\n");
      break;
    default:
printf(">none default\n");
      break;
    }
    index+= 1;
    if(index >= 3){
      index = 0;
    }
    SDL_Flip(screen);
    SDL_Delay(5000);
  }
	SDL_Quit();
  return 0;
}

