#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

double x[5], y[5];
double deltaX;
double deltaY;


void display( void ) {
    glColor3f(0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINE_LOOP);
    glVertex2d(x[1], y[1]);
    glVertex2d(x[2], y[2]);
    glVertex2d(x[3], y[3]);
    glVertex2d(x[4], y[4]);
    glEnd();
    
    glFlush();
}

void keyboard( unsigned char key, int X, int Y ) {
    switch( key ) {
    case 'x':
        printf("横方向の移動の向き反転。\n");
        deltaX = -1.0 * deltaX;
        break;
    case 'y':
        printf("縦方向の移動の向き反転。\n");
        deltaY = -1.0 * deltaY;
        break;
    default:
        x[1] += deltaX;  // 移動
        x[2] += deltaX;
        x[3] += deltaX;
        x[4] += deltaX;
        y[1] += deltaY;
        y[2] += deltaY;
        y[3] += deltaY;
        y[4] += deltaY;
        break;
    }

    glutPostRedisplay();  // コールバック関数display()を呼び出し
}

void mouse(int button, int state, int X, int Y) {
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        if( X<=400 ) {
            deltaX = -0.1;

            if( Y>=400 ) {
                deltaY = -0.1;
            }
            else {
                deltaY = 0.1;
            }
        }
        else {
            deltaX = 0.1;
 
            if( Y>=400 ) {
                deltaY = -0.1;
            }
            else {
                deltaY = 0.1;
            }
        }

        x[1] += deltaX;  // 移動
        x[2] += deltaX;
        x[3] += deltaX;
        x[4] += deltaX;
        y[1] += deltaY;
        y[2] += deltaY;
        y[3] += deltaY;
        y[4] += deltaY;
        
        glutPostRedisplay();  // コールバック関数display()を呼び出し
    }
}

int main( int argc, char *argv[] )
{
    x[1]=0.0;   y[1]=0.0;  // 初期座標
    x[2]=0.1;   y[2]=0.2;
    x[3]=0.2;   y[3]=0.1;
    x[4]=0.3;   y[4]=0.3;

    deltaX = -0.1;  // 移動幅
    deltaY = -0.1;

    printf("デフォルトで左下に動きます。\n");
    printf("'x'キーで横方向の移動の向きを反転。\n");
    printf("'y'キーで縦方向の移動の向きを反転。\n");
    printf("その他のキーで移動。\n");
    printf("左の方クリックで移動方向左へ。\n");
    printf("右の方クリックで移動方向右へ。\n");
    printf("下の方クリックで移動方向下へ。\n");
    printf("上の方クリックで移動方向上へ。\n");

    glutInit(&argc, argv);  // GLUTの初期化
    glutInitWindowPosition(100, 100);  // ウィンドウの表示位置の指定
    glutInitWindowSize(800, 800);  // ウィンドウサイズの指定

    glutCreateWindow("simple");
    glutDisplayFunc(display);  // 描画イベント時のコールバック関数の設定
    glutKeyboardFunc(keyboard);  // キーボードイベント時のコールバック関数の設定
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
