/*!\file draw.h
 * \brief Ce fichier contient toutes les prototypes des fonctions de rendu des courbes.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
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
/**
 * \brief Dessine sur une feuille millimétré.
 */
void drawOnGridPage(void);
/**
 * \brief Dessine sur une feuille simple.
 */
void drawOnWhitePage(void);
/**
 * \brief Dessine de texte.
 */
void drawText(char *string, int x, int y, Uint32 color, int text_size);
/**
 * \brief Initialise les paramètre de dessin.
 */
void initDraw(int x0, int y0, int h, int w);
/**
 * \brief Dessine les courbes.
 */
void drawData(table_t *datas, int algos, Uint32 *colors, int field);
/**
 * \brief Sauvegarde comme image.
 */
void saveAsPicture(char *path);
#endif