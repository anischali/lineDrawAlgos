#ifndef DRAW_H
#define DRAW_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL2/SDL_ttf.h>
#include "drawdata.h"
#include <assert.h>

void drawOnGridPage(void);
void drawOnWhitePage(void);
void drawText(char *string, int x, int y, Uint32 color, int text_size);
void initDraw(int x0, int y0, int h, int w);
void drawData(table_t *datas, int algos, Uint32 *colors);
void saveAsPicture(char *path);
#endif