#include "letemps.h"
#include <math.h>
#include "draw.h"

static table_t * datas = NULL;



void droite_br65(int u, int v) {
    int x, y, delta, incD, incH;
    incH   = v << 1;
    delta  = incH - u;
    incD   = delta - u;
    for (x = 0, y = 0; x <= u; x++) 
    {
        if (delta > 0) {
            y++;
            delta += incD;
        }
        else {
            delta += incH;
        }
    }
}


void droite_AAS(int u, int v){
    int E = 0, incXA = 0, incXB = 0;
    int XB = (u - v) / v;
    int XA = XB + 1;    
    incXA   = XA * 2 * v;
    E  = incXA - u;
    incXB   = XB * 2 * (v - u);    
    int y = 0;                    
    for (int x = 0; x <= u;){     
        if (E < 0){
            x += XA;
            ++y;
            ++x;
            E += incXA;            
        }else{
            x += XB;
            ++y;
            ++x;
            E += incXB;
        }
    }
}

double lineLength(int u, int v){
    return sqrt(pow(u,2)+pow(v,2));
}

static int draw_style = 0;


static void quit(void) {
    freeDatas(datas);
    TTF_Quit();
    gl4duClean(GL4DU_ALL);
}


void dessin(void){
    char *str [] = {"AAS and DDA average time comparison",
                   "AAS and DDA best time comparison",
                   "AAS and DDA worst time comparison ",
                   "AAS and DDA storage comparason"
                   };
    static int saved[4] = {0};

    gl4dpClearScreenWith(RGB(255,255,255));
   
    if (draw_style != 0)    
        drawOnGridPage();
    else
        drawOnWhitePage();

    Uint32 colors[3];
    colors[AAS] = RGB(255,0,0);
    colors[DDA] = RGB(0,0,255);
    colors[2] = RGB(0,0,0);
    drawData(datas, 2, colors);
    drawText("AAS Boyer & Bourdin 2000", 700, 10, colors[AAS],20);
    drawText("Bresenham 1965 DDA", 670, 10, colors[DDA],20);
    drawText(str[0], 770, 350, colors[2],20);
    gl4dpUpdateScreen(NULL);
    if (!saved[0]){
        char toSave[100]="";
        sprintf(toSave,"./images/%s.bmp",str[0]);
        saveAsPicture(toSave);
        saved[0] = 1;
    }
}


int main(int argc, char ** argv) {
    
    if (argc > 1){
        if (strncmp("grid",argv[1],4) == 0)
            draw_style = 1;
    }else{
      fprintf(stdout,"---------------------------------------------------------\n");
        fprintf(stdout,"Pour dessiner les courbes dans une feuille millimétré\nTappez ./compareAAS_DDA grid\n\n");
    }
    fprintf(stdout,"Initialisation...\n");
    initDrawData(2);
    int u = 7,v = 3;
    fonction_t algorithms[]={
        {AAS,droite_AAS,"Bourdin & Boyer 2000 AAS"},
        {DDA,droite_br65,"Bresenham 1965 DDA"},
        {0,NULL, ""}
    };
    fprintf(stdout,"Génération des données...\n");
    int length = (int) lineLength(u,v);
    for (;length <= 5000 ;u+=100){
        for(v = 1; v < (int) u/2; v+=10){
            test_rapidite2(length, u, v, algorithms);
        }
        length = (int) lineLength(u,v);    
    }

    datas = getDatas();
    initDraw(300, 40, 700, 700);
    fprintf(stdout,"Affichage de la représentation des données...\n");
    if(!gl4duwCreateWindow(argc, argv, /* args du programme */
			 "Dessin de droite", /* titre */
			 10, 10, 1024, 800, /* x,y, largeur, heuteur */
			 GL4DW_SHOWN) /* état visible */) {
                return 1;
    }
    
    
    gl4dpInitScreen();
    atexit(quit);
    gl4duwDisplayFunc(dessin);
    gl4duwMainLoop();  
    return 0;
}
