/*!\file compareAAS_DDA.c
 * \brief Ce fichier contient l'entrée de programme et ainsi que les algorithme B&B AAS 2000 et B DDA 65.
 * \author Anis CHALI anis.chali1@outlook.com 15612337
 * \date November 28, 2018
 *
*/
#include "letemps.h"
#include <math.h>
#include "draw.h"
#include "algorithmes.h"


static table_t * datas = NULL;
static int draw_style = 0;

/*!\brief la longueur d'une droite \a u et \a v en utilisant la distance euclidienne 
 * retourne la distance.
 * \param u représente (x2 - x1), en pixels.
 * \param v représente (y2 - y1), en pixels.
 * \return double la distance en double.
 */
double lineLength(int u, int v){
    return sqrt(pow(u,2)+pow(v,2));
}

/*!\brief La fonction sert à libéré la mémoire occuppé par les données et gl4Dummies. 
 * \param void
 * \return void
 */
static void quit(void) {
    fprintf(stdout,"\n\n\nLes résultats sont stocké dans images et logs\n\n\n");
    gl4duClean(GL4DU_ALL);
}

/*!\brief La fonction est utilisé pour dessiner toutes les courbes
 * des déffirentes complexités. 
 * \param void
 * \return void
 */
void dessin(void){
    char *str [COMPLEXITY] = {"AAS and DDA average time comparison",
                              "AAS and DDA worst time comparison",
                              "AAS and DDA best time comparison",
                              "AAS and DDA storage comparison" 
                            };
    static int saved[COMPLEXITY] = {0};
    Uint32 colors[4];
    colors[AAS] = RGB(255,0,0);
    colors[DDA] = RGB(0,0,255);
    colors[2] = RGB(0,255,0);
    colors[3] = RGB(0,0,0);
    
    for (int i = 0; i < COMPLEXITY; ++i){
        gl4dpClearScreenWith(RGB(255,255,255));
        if (draw_style != 0)    
            drawOnGridPage();
        else
            drawOnWhitePage();
        drawText("AAS Boyer & Bourdin 2000", 700, 10, colors[AAS],20);
        drawText("Bresenham 1965 DDA", 670, 10, colors[DDA],20);
        drawText("AASPLUS", 640, 10, colors[2],20);
        drawData(datas, 3, colors,i);
        drawText(str[i], 770, 350, colors[3],20);
        gl4dpUpdateScreen(NULL);
        if (!saved[i]){
            char toSave[512]= "0";
            sprintf(toSave,"./images/%s.bmp",str[i]);
            saveAsPicture(toSave);
            saved[i] = 1;
        }
    }
    saveAsFile("./logs/results", datas);
    fprintf(stdout,"Enregistrement des logs contenant les résultas...\n");
    exit(0);
}

/*!\brief La fonction main qui la rentré de programme.
 * \param argc le nombre d'argements passé au lancement de programme.
 * \param **argv les argements passé au lancement de programme.
 * \return int l'état de retour de programme.
 */
int main(int argc, char ** argv) {
    //si le paramètre grid est passé en ligne de commande on déssine sur une feuille milimètré.
    if (argc > 1){
        if (strncmp("grid",argv[1],4) == 0)
            draw_style = 1;
    }else{
      fprintf(stdout,"---------------------------------------------------------\n");
        fprintf(stdout,"Pour dessiner les courbes dans une feuille millimétré\nTappez ./compareAAS_DDA grid\n\n");
    }
    fprintf(stdout,"Initialisation...\n");
    initDrawData(3);
    int u = 7,v = 3;
    fonction_t algorithms[]={
        {AAS,droite_AAS,"Bourdin & Boyer 2000 AAS"},
        {DDA,droite_br65,"Bresenham 1965 DDA"},
	{2,droite_AASPLUS,"Bresenham 1965 AASPLUS"},
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
    fprintf(stdout,"Enregistrement des images des représentations des données...\n");
    
    if(!gl4duwCreateWindow(argc, argv, 
			 "Dessin de courbes", 
			 10, 10, 1024, 800, 
			 GL4DW_SHOWN)) {
                return 1;
    }
    
    gl4dpInitScreen();
    atexit(quit);
    gl4duwDisplayFunc(dessin);
    gl4duwMainLoop();
    freeDatas(datas);
    return 0;
}
