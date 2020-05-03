#include "draw.h"



static int shift_x = 0;
static int shift_y = 0;
static int draw_height = 0;
static int draw_width = 0;
static float time_scales = 0.0;
static float length_scales = 0.0;

/* Fonction dessinant une ligne vertical*/
/*remarque: la fonction n'existe pas dans gl4dummies*/

void initDraw(int x0, int y0, int h, int w){
    shift_x = x0;
    shift_y = y0;
    draw_height = h;
    draw_width = w;
}


void gl4dpVLine(int y0, int y1, int x){
    while(y0 <= y1){
        gl4dpPutPixel(x, y0++);
    }
}

/*fonction de dessin de flèches horizontal*/
void drawHArrow(int x, int y, int width, int height){
    for (int i = -1; i < 2; ++i)
        gl4dpLine(x-(width / 2)+i, y-height, x, y);
    for (int i = -1; i < 2; ++i)
        gl4dpLine(x+(width/2)+i, y-height, x, y);  
}


/*fonction de dessin de flèche vertical */
void drawVArrow(int x, int y, int width, int height){
    for (int i = -1; i < 2; ++i)
        gl4dpLine(x-height, y-(width/2)+i, x, y);
    for (int i = -1; i < 2; ++i)
        gl4dpLine(x-height, y+(width/2)+i, x, y);  
}

void drawVSlash(int x, int y){
    gl4dpVLine(y-3,y+3, x);
    gl4dpVLine(y-3,y+3, x-1);
}


void drawHSlash(int x, int y){
    gl4dpHLine(x-3, x+3, y);
    gl4dpHLine(x-3, x+3, y-1);
}

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




/* Fonction pour les numéro sur la feuille feuille millimétré*/
/*fonction non terminé*/

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
}

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

void drawOnWhitePage(void){
    gl4dpClearScreenWith(RGB(255,255,255));
    Uint32 color = RGB(0,0,0);
    drawAxes(shift_x, shift_y, 700, 700, color);
    
}



/*Fonction de dessin d'une feuille millimétré*/

void drawOnGridPage(void){
    
    gl4dpClearScreenWith(RGB(255,255,255));
    Uint32 c1 = RGB(200,200,200);
    Uint32 c2 = RGB(100,0,0);
    Uint32 c3 = RGB(0,0,0);

    drawGrids(shift_x, shift_y,700,700,c1,c2);
    drawAxes(shift_x, shift_y,700,700,c3);
    
    
}
/*pour sauvegarder dans un fichier*/
/*fonction non terminé*/

void saveAsPicture(char *path){
    SDL_Surface *surface = NULL;
    
    int x, y, yp, h = gl4dpGetHeight(), w = gl4dpGetWidth();
    surface = SDL_CreateRGBSurface(0, w, h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    Uint32 *pp = surface->pixels;
    for (x = w-1; x >= 0; --x)
        for (y = h-1, yp = 0; y >= 0; --y, ++yp)
            pp[yp * w + x] = gl4dpGetPixel(x, y);
        
    
    SDL_SaveBMP(surface, path);
    
}


void set_scales(table_t *data ,int algo){
    int max_length_value = max_length(data, algo);
    float max_time_value = max_time(data, algo);

    time_scales = (float)(draw_height - 20) / max_time_value;
    length_scales = (float)(draw_width- 20) / max_length_value;
}

void drawData(table_t *datas, int algos, Uint32 *colors){
    int x = 0, y = 0, y0 = 0, x0 = 0;
    set_scales(datas, DDA);
    char scale_x[200] = "";
    char scale_y[200] = "";
    for (int i = 0; i < algos; ++i){
        gl4dpSetColor(colors[i]);
        
        for (int j = 0; j < datas[i].index-1; ++j){
            y0 = (int) ((datas[i].datas[j].average_time * time_scales) + shift_y);
            x0 = (int) ((datas[i].datas[j].length * length_scales) + shift_x);
            y = (int) ((datas[i].datas[j+1].average_time * time_scales) + shift_y);
            x = (int) ((datas[i].datas[j+1].length * length_scales) + shift_x);

            gl4dpLine(x0,y0,x,y);
        }
    }
    
    sprintf(scale_y,"Scale y: %0.2f", (max_time(datas, DDA) / (float)(draw_height - 20) * 40));
    drawText(scale_y, 150, 100, colors[2],20);
    sprintf(scale_x,"Scale x: %0.2f",(max_length(datas, DDA) / (float)(draw_width - 20) * 40));
    drawText(scale_x, 100, 100, colors[2],20);
    
    
}