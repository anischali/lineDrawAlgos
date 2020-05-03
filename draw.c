/*!\file draw.c
 * \brief Ce fichier contient toutes les fonctions de rendu des courbes.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
#include "draw.h"
/*!\brief X Début de cadre de dessin des courbes*/
static int shift_x = 0;
/*!\brief Y Début de cadre de dessin des courbes*/
static int shift_y = 0;
/*!\brief La hauteur de cadre de dessin des courbes*/
static int draw_height = 0;
/*!\brief La Largeur de cadre de dessin des courbes*/
static int draw_width = 0;
/*!\brief L'échelle de dessin pour les coordonnées y*/
static float time_scales = 0.0;
/*!\brief L'échelle de dessin pour les coordonnées x*/
static float length_scales = 0.0;


/*!\brief Initialise le début de cadre \a x0,\a y0 et sa hauteur \a h et largeur \a w.  
 * \param x0 début en x.
 * \param y0 début en y.
 * \param h hauteur.
 * \param w largeur.
 * \return void
 */
void initDraw(int x0, int y0, int h, int w){
    shift_x = x0;
    shift_y = y0;
    draw_height = h;
    draw_width = w;
}

/*!\brief Déssine une droite verticale partant de \a y0 jusqu'a \y1 dans le meme \a x.  
 * \param y0 début de la droite.
 * \param y1 fin de la droite.
 * \param x la coordonné x de la droite.
 * \return void
 */
void gl4dpVLine(int y0, int y1, int x){
    while(y0 <= y1){
        gl4dpPutPixel(x, y0++);
    }
}

/*!\brief Fonction de dessin de flèches horizontals dans un axe.  
 * \param x coordonné de la poite en x.
 * \param y coordonné de la poite en y.
 * \param width la largeur de la flèche.
 * \param height la hauteur de la flèche.
 * \return void
 */
void drawHArrow(int x, int y, int width, int height){
    for (int i = -1; i < 2; ++i)
        gl4dpLine(x-(width / 2)+i, y-height, x, y);
    for (int i = -1; i < 2; ++i)
        gl4dpLine(x+(width/2)+i, y-height, x, y);  
}

/*fonction de dessin de flèche vertical */
/*!\brief Fonction de dessin de flèches verticales dans un axe.  
 * \param x coordonné de la poite en x.
 * \param y coordonné de la poite en y.
 * \param width la largeur de la flèche.
 * \param height la hauteur de la flèche.
 * \return void
 */
void drawVArrow(int x, int y, int width, int height){
    for (int i = -1; i < 2; ++i)
        gl4dpLine(x-height, y-(width/2)+i, x, y);
    for (int i = -1; i < 2; ++i)
        gl4dpLine(x-height, y+(width/2)+i, x, y);  
}

/*!\brief Fonction de dessin de slash verticale.  
 * \param x coordonné de point en x.
 * \param y coordonné de point y.
 * \return void
 */
void drawVSlash(int x, int y){
    gl4dpVLine(y-3,y+3, x);
    gl4dpVLine(y-3,y+3, x-1);
}

/*!\brief Fonction de dessin de slash horizontal.  
 * \param x coordonné de point en x.
 * \param y coordonné de point y.
 * \return void
 */
void drawHSlash(int x, int y){
    gl4dpHLine(x-3, x+3, y);
    gl4dpHLine(x-3, x+3, y-1);
}

/*!\brief Fonction de dessin de texte dans le screen et à partir d'une SDL_Surface.  
 * \param SDL_Surface *text pointeur vers la surface contenant le text.
 * \param s_x coordonné de dessin sur l'écran en x.
 * \param s_y coordonné de dessin sur l'écran en y.
 * \param color la couleur de plaquage de text sur le screen.
 * \return void
 */
void drawToScreen(SDL_Surface *text, int s_x, int s_y, Uint32 color){
    int h = text->h, w = text->w;
    Uint32 pixel = 0;
    Uint32 *pp = text->pixels;
    Uint8 r, g, b;
    for (int x = 0; x < h; ++x){
        for (int y = 0; y < w; ++y){
            r = pp[x * w + y] >> 16;
            g = pp[x * w + y] >> 8;
            b = pp[x * w + y];
            pixel = RGB(r,g,b);
            if (pixel != RGB(0,0,0)){
                gl4dpSetColor(color);
                gl4dpPutPixel(y+s_y, x+s_x-(2*x));
            }   
        }
    }
}

/*!\brief Fonction de dessin de text sur une SDL_Surface.  
 * \param *text pointeur vers la surface contenant le text.
 * \param s_x coordonné de dessin sur l'écran en x.
 * \param s_y coordonné de dessin sur l'écran en y.
 * \param color la couleur de plaquage de text sur le screen.
 * \return void
 */
void drawText(char *string, int s_x, int s_y, Uint32 color, int text_size){
    static int first_time = 1;
    TTF_Font *font = NULL;
    SDL_Color c = {255,0,180};
    SDL_Surface *text = NULL, *formated_text = NULL;
    if (first_time){
        if (TTF_Init() == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de sdl ttf: %s\n",TTF_GetError());
            exit(EXIT_FAILURE);
        }
        first_time = 0;
    }
    font = TTF_OpenFont("OpenSans-Light.ttf",text_size);
    text = TTF_RenderText_Blended(font,string,c);
    formated_text = SDL_CreateRGBSurface(0, text->w, text->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_BlitSurface(text, NULL, formated_text, NULL);
    drawToScreen(formated_text, s_x, s_y, color);
    SDL_FreeSurface(text);
    SDL_FreeSurface(formated_text);
    TTF_CloseFont(font);
    atexit(TTF_Quit);
}

/*!\brief Fonction de dessin de l'axe x, y.  
 * \param x0 coordonné de début sur l'écran en x.
 * \param y0 coordonné de début sur l'écran en y.
 * \param height la hauteur de l'axe.
 * \param width la largeur de l'axe.
 * \param color la couleur de dessin des axes sur le screen.
 * \return void
 */
void drawAxes(int x0, int y0, int height, int width, Uint32 color){
    gl4dpSetColor(color);
    int j = 0;
    char text[100] = "";
    for (int i = 0; i < 2; ++i){
        gl4dpHLine(x0, width + x0, y0+i);
        gl4dpVLine(y0, height + y0, x0+i);
    }
    for (int j = x0 + 40; j < width + x0; j+=40){
        drawVSlash(j, y0);
    }
    for (int j = y0 + 40; j < height + y0; j+=40){
        drawHSlash(x0, j);
    }
    drawHArrow(x0, height + y0, 10, 10);
    drawVArrow(width + x0, y0, 10, 10);
    int value = 0;
    for (j = x0-5; j < width + x0; j+=40){
        sprintf(text,"%d",value++);    
        drawText(text, y0 - 10, j, color, 20);
    }
    drawText("Length(px)",y0 + 30, j-120, color, 20);
    value = 1;
    for (j = y0+50; j < height + y0; j+=40){
        sprintf(text,"%d",value++);    
        drawText(text, j, x0 - 35, color, 20);
    }
    drawText("CPU Ticks", j - 40, x0 + 10, color, 20);
}

/*!\brief Fonction de dessin des grille d'une feuille millimétré.  
 * \param x0 coordonné de début de la grille sur l'écran en x.
 * \param y0 coordonné de début sur la grille l'écran en y.
 * \param height la hauteur de la grille.
 * \param width la largeur de la grille.
 * \param color1 la couleur des lignes interne.
 * \param color2 la couleur des lignes externe.
 * \return void
 */
void drawGrids(int x0, int y0, int width, int height, Uint32 color1, Uint32 color2){
    int y = 0, x = 0;
    gl4dpSetColor(color1);
    for (y = y0; y < height + y0; y+=4){
        gl4dpHLine(x0, width + x0, y);
    }
    for (x = x0; x < width + x0; x+=4){
        gl4dpVLine(y0, height + y0, x);
    }
    gl4dpSetColor(color2);
    for (y = y0; y < height + y0; y+=40){
        gl4dpHLine(x0, width + x0, y);
    }
    for (x = x0; x < width + x0; x+=40){
        gl4dpVLine(y0, height + y0, x);
    }
}

/*!\brief Fonction de dessin d'une grille simple.  
 * \param void
 * \return void
 */
void drawOnWhitePage(void){
    gl4dpClearScreenWith(RGB(255,255,255));
    Uint32 color = RGB(0,0,0);
    drawAxes(shift_x, shift_y, 700, 700, color);
    
}

/*!\brief Fonction de dessin d'une grille millimétré.  
 * \param void
 * \return void
 */
void drawOnGridPage(void){
    gl4dpClearScreenWith(RGB(255,255,255));
    Uint32 c1 = RGB(200,200,200);
    Uint32 c2 = RGB(100,0,0);
    Uint32 c3 = RGB(0,0,0);
    drawGrids(shift_x, shift_y,700,700,c1,c2);
    drawAxes(shift_x, shift_y,700,700,c3);
}

/*!\brief Fonction de sauvegarde d'un screen sous image.  
 * \param *path chaine de caractères pour le chemin de sauvegarde.
 * \return void
 */
void saveAsPicture(char *path){
    SDL_Surface *surface = NULL;
    int x, y, yp, h = gl4dpGetHeight(), w = gl4dpGetWidth();
    surface = SDL_CreateRGBSurface(0, w, h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    Uint32 *pp = surface->pixels;
    for (x = w-1; x >= 0; --x)
        for (y = h-1, yp = 0; y >= 0; --y, ++yp)
            pp[yp * w + x] = gl4dpGetPixel(x, y);
    SDL_SaveBMP(surface, path);
    SDL_FreeSurface(surface);
}

/*!\brief Fonction de calcule de l'échelle x et y de dessin.  
 * \param *data tableau contenant les données à représenter.
 * \param algo indice de l'algorithme pour lequel on calcule l'échelle.
 * \param field vaut le temps moyen, le pire des cas ou le meilleur des cas. 
 * \return void
 */
void set_scales(table_t *data ,int algo,int field){
    int max_length_value = max_length (data, algo);
    float max_time_value = max_time (data, algo, field);
    time_scales = (float)(draw_height - 20) / max_time_value;
    if (field == STORAGE){
        time_scales = (float)(draw_height  - 20) / 2.0 / max_time_value;
    }
    length_scales = (float)(draw_width- 20) / max_length_value;
}

/*!\brief Fonction de récupération d'un tableau de champs particulier (average_time, best_time...).  
 * \param table_t* datas tableau contenant les données à représenter.
 * \param int  algo l'algo pour lequel on récupère les valeurs.
 * \param Uint32* colors les déffirentes couleurs pour déffirentier les courbes.
 * \param int field vaut le temps moyen, le pire des cas ou le meilleur des cas. 
 * \return float* un pointeur vers le tableau des temps concerné.
 */
float * getAllTimeValues(table_t *datas, int algo, int field){
    data_t * data = datas[algo].datas;
    int n = datas[algo].index;
    float *times = malloc(n * sizeof *times); 
    switch(field){
        case AVERAGE:
            for (int i = 0; i < n; ++i){
                times[i] = (data[i].average_time * time_scales) + shift_y;
            }
        break;
        case WORST:
            for (int i = 0; i < n; ++i){
                times[i] = (data[i].worst_time * time_scales) + shift_y;
            }
        break;
        case BEST:
            for (int i = 0; i < n; ++i){
                times[i] = (data[i].best_time * time_scales) + shift_y;
            }
        break;
        case STORAGE:
            for (int i = 0; i < n; ++i){
                times[i] = (data[i].storage * time_scales) + shift_y;
            }
        break;
    }
    return times;
}


/*!\brief Fonction de récupération d'un tableau du champs length.  
 * \param table_t* datas tableau contenant les données à représenter.
 * \param int  algo l'algo pour lequel on récupère les valeurs. 
 * \return float* un pointeur vers le tableau des lengths concerné.
 */
float * getAllLengthValues(table_t *datas, int algo){
    data_t * data = datas[algo].datas;
    int n = datas[algo].index;
    float *lengths = malloc(n * sizeof *lengths); 
    for (int i = 0; i < n; ++i){
        lengths[i] = (data[i].length * length_scales) + shift_x;
    }
    return lengths;
}

/*!\brief Fonction de dessin des courbes d'evolution de complexité.  
 * \param table_t* datas tableau contenant les données à représenter.
 * \param int  algos les algos pour lesquels on dessine les valeurs.
 * \param Uint32* colors les déffirentes couleurs pour déffirentier les courbes.
 * \param int field vaut le temps moyen, le pire des cas ou le meilleur des cas. 
 * \return void
 */
void drawData(table_t *datas, int algos, Uint32 *colors, int field){
    int x = 0, y = 0, y0 = 0, x0 = 0;
    set_scales(datas, DDA, field);
    char scale_x[200] = "";
    char scale_y[200] = "";
    int d_index = 0;
    float *times = NULL;
    float *lengths = NULL;
    for (int i = 0; i < algos; ++i){
        gl4dpSetColor(colors[i]);
        d_index = datas[i].index;
        times = getAllTimeValues(datas, i, field);
        lengths = getAllLengthValues(datas, i);
        for (int j = 0; j < d_index-1; ++j){
            y0 = times[j];
            x0 = lengths[j];
            y = times[j+1];
            x = lengths[j+1];
            gl4dpLine(x0,y0,x,y);
        }
        free(times);
        free(lengths);
    }
    float reverse_scale_y = (max_time(datas, DDA, field) / (float)(draw_height - 20) * 40);
    float reverse_scale_x = (max_length(datas, DDA) / (float)(draw_width - 20) * 40);
    if (field == STORAGE){
        reverse_scale_y = (max_time(datas, DDA, field) * 2.0 / (float)(draw_height - 20) * 40);
    }
    sprintf(scale_y,"Scale y: %0.2f", reverse_scale_y);
    drawText(scale_y, 150, 100, colors[3],20);
    sprintf(scale_x,"Scale x: %0.2f", reverse_scale_x);
    drawText(scale_x, 100, 100, colors[3],20);   
}