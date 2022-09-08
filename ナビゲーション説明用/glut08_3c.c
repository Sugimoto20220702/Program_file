//---------------------------------------------------------------------
// Priklad cislo 16
// Autor: Pavel Tisnovsky
//
// Vykresleni vektorovych fontu
//---------------------------------------------------------------------

#include <GL/glut.h>                    // hlavickovy soubor funkci GLUTu



//---------------------------------------------------------------------
// Tato funkce vykresli retezec danym vektorovym fontem
//---------------------------------------------------------------------
void printStringUsingGlutVectorFont(char *string, void *font, int x, int y, float scale, float r, float g, float b)
{
    glColor3f(r, g, b);                 // nastaveni barvy vykreslovanych bitmap
    glMatrixMode(GL_MODELVIEW);         // zacatek modifikace modelview matice
    glPushMatrix();                     // ulozit soucasnou hodnotu projekcni matice na zasobnik
    glTranslatef(x, y, 0);              // posun na pocatek vykreslovani
    glScalef(scale, -scale, scale);     // zmena meritka pisma

    while (*string)                     // projit celym retezcem
        glutStrokeCharacter(font, *string++); // vykresleni jednoho znaku

    glPopMatrix();                      // obnovit predchozi hodnotu projekcni matice
}



//---------------------------------------------------------------------
// Nastaveni souradneho systemu v zavislosti na velikosti okna
//---------------------------------------------------------------------
void onResize(int w, int h)             // w a h reprezentuje novou velikost okna
{
    glViewport(0, 0, w, h);             // viditelna oblast pres cele okno
    glMatrixMode(GL_PROJECTION);        // zacatek modifikace projekcni matice
    glLoadIdentity();                   // vymazani projekcni matice (=identita)
    glOrtho(0, w, 0, h, -1, 1);         // mapovani abstraktnich souradnic do souradnic okna
    glScalef(1, -1, 1);                 // inverze y-ove osy, aby se y zvetsovalo smerem dolu
    glTranslatef(0, -h, 0);             // posun pocatku do leveho horniho rohu
}



//---------------------------------------------------------------------
// Tato funkce je volana pri kazdem prekresleni okna
//---------------------------------------------------------------------
void onDisplay(void)
{
    float f, top;
    glClear(GL_COLOR_BUFFER_BIT);       // vymazani bitovych rovin barvoveho bufferu
    top=20.0;                           // horni hranice vykreslovani proporcionlniho pisma
    for (f=0.1; f<0.7; f+=0.1) {        // vykresleni pisma v sesti velikostech
        printStringUsingGlutVectorFont("Roman Simplex proporcionalni", GLUT_STROKE_ROMAN, 10, top, f, 1.0-f*2.0, f*2.0, 1.0);
        top+=f*120.0+15.0;              // vypocet posunu dalsiho radku
    }
    top=300.0;                          // horni hranice vykreslovani neproporcionalniho pisma
    for (f=0.1; f<0.7; f+=0.1) {        // vykresleni pisma v sesti velikostech
        printStringUsingGlutVectorFont("Roman Simplex neproporcionalni", GLUT_STROKE_MONO_ROMAN, 10, top, f, 1.0, f*2.0, 1.0-f*2.0);
        top+=f*120.0+15.0;              // vypocet posunu dalsiho radku
    }
    glFlush();                          // provedeni a vykresleni zmen
}



//---------------------------------------------------------------------
// Tato funkce je volana pri stlaceni ASCII klavesy
//---------------------------------------------------------------------
void onKeyboard(unsigned char key, int x, int y)
{
    key=(key>'A' && key<='Z') ? key+'a'-'A':key; // prevod na mala pismena
    switch (key) {
        case 27:                        //  Escape
            exit(0);
            break;
        case 'f':
            glutFullScreen();           // prepnuti na celou obrazovku
            break;
        case 'w':
            glutReshapeWindow(600, 600);// prepnuti zpet do okna
            glutPositionWindow(50, 50);
            break;
        default:
            break;
    }
}



//---------------------------------------------------------------------
// Hlavni funkce konzolove aplikace
//---------------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);              // inicializace knihovny GLUT
    glutCreateWindow("Priklad cislo 16");// vytvoreni okna pro kresleni
    glutReshapeWindow(600, 600);        // nastaveni velikosti okna
    glutDisplayFunc(onDisplay);         // registrace funkce volane pri prekreslovani okna
    glutReshapeFunc(onResize);          // registrace funkce volane pri zmene velikosti okna
    glutKeyboardFunc(onKeyboard);       // registrace funkce volani pri stlaceni ASCII klavesy
    glutMainLoop();                     // nekonecna smycka, kde se volaji zaregistrovane fce
    return 0;                           // navratova hodnota vracena operacnimu systemu
}



//---------------------------------------------------------------------
// Konec zdrojoveho souboru
//---------------------------------------------------------------------

