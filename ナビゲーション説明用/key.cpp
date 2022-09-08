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
        printf("�������̈ړ��̌������]�B\n");
        deltaX = -1.0 * deltaX;
        break;
    case 'y':
        printf("�c�����̈ړ��̌������]�B\n");
        deltaY = -1.0 * deltaY;
        break;
    default:
        x[1] += deltaX;  // �ړ�
        x[2] += deltaX;
        x[3] += deltaX;
        x[4] += deltaX;
        y[1] += deltaY;
        y[2] += deltaY;
        y[3] += deltaY;
        y[4] += deltaY;
        break;
    }

    glutPostRedisplay();  // �R�[���o�b�N�֐�display()���Ăяo��
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

        x[1] += deltaX;  // �ړ�
        x[2] += deltaX;
        x[3] += deltaX;
        x[4] += deltaX;
        y[1] += deltaY;
        y[2] += deltaY;
        y[3] += deltaY;
        y[4] += deltaY;
        
        glutPostRedisplay();  // �R�[���o�b�N�֐�display()���Ăяo��
    }
}

int main( int argc, char *argv[] )
{
    x[1]=0.0;   y[1]=0.0;  // �������W
    x[2]=0.1;   y[2]=0.2;
    x[3]=0.2;   y[3]=0.1;
    x[4]=0.3;   y[4]=0.3;

    deltaX = -0.1;  // �ړ���
    deltaY = -0.1;

    printf("�f�t�H���g�ō����ɓ����܂��B\n");
    printf("'x'�L�[�ŉ������̈ړ��̌����𔽓]�B\n");
    printf("'y'�L�[�ŏc�����̈ړ��̌����𔽓]�B\n");
    printf("���̑��̃L�[�ňړ��B\n");
    printf("���̕��N���b�N�ňړ��������ցB\n");
    printf("�E�̕��N���b�N�ňړ������E�ցB\n");
    printf("���̕��N���b�N�ňړ��������ցB\n");
    printf("��̕��N���b�N�ňړ�������ցB\n");

    glutInit(&argc, argv);  // GLUT�̏�����
    glutInitWindowPosition(100, 100);  // �E�B���h�E�̕\���ʒu�̎w��
    glutInitWindowSize(800, 800);  // �E�B���h�E�T�C�Y�̎w��

    glutCreateWindow("simple");
    glutDisplayFunc(display);  // �`��C�x���g���̃R�[���o�b�N�֐��̐ݒ�
    glutKeyboardFunc(keyboard);  // �L�[�{�[�h�C�x���g���̃R�[���o�b�N�֐��̐ݒ�
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
