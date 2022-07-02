#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define S_POINT 1 // �J�n�s�s��
#define Kosuu 1 // ���s��
#define MAX 9999 // �ő�l
#define M_ARGC 1 // ����
//#define randomize() srand(time(NULL)) // ���������l�ݒ�
#define getrandom(MAX, MIN) (rand() % (int)(MAX - MIN + 1) + MIN)
// ���w��͈̗͂����쐬
#define Max 25 // �����̍ő�l
#define Min 5 // �����̍ŏ��l
int Node; // �s�s�̐�
int** dis; // �����s��
int level; // �ċA�̐[��
int slide; // �J�n�s�s�����炷
int success; // ���̐��i�_�~�[�j
unsigned long check; // �T����
FILE* fp; // �t�@�C���|�C���^
int* array; // �����i�[

int arrayInit() {
    int i;
    //ex = (int*)malloc(sizeof(int) * (Node + 1));    //  memory�m��
    //r_p = (int*)malloc(sizeof(int) * (Node + 1));
    //r_min = (int*)malloc(sizeof(int) * (Node + 1));
    dis = (int**)malloc(sizeof(int*) * (Node + 1));
    for (i = 0; i <= Node; i++)
        dis[i] = (int*)malloc(sizeof(int) * (Node + 1));
    if (/* == NULL || r_p == NULL || r_min == NULL || */ dis == NULL) {
        printf("Error memory can't allocate!\n");  //�m�ۂł��Ȃ������ꍇ
        exit(1);
    }
    return 0;
}

void arrayFree() {
    /*free(ex);
    free(r_p);
    free(r_min);*/
    free(dis);
}

void makeRandom() {
    int i, count = 0;
    int indata1, indata2, bufsize;
    indata1 = Node;
    indata2 = Kosuu;
    bufsize = indata1 * (indata1 - 1) / 2 * indata2;
    // printf("bufsize=%d\n", bufsize);
    array = (int*)malloc(sizeof(int) * (bufsize + 1));
    //randomize();
    for (i = 0; i < bufsize; i++)
        array[i] = getrandom(Max, Min), ++count;
}

void makeMap() {       //�s�s�Ԃ̋����쐬
    int i, j, h, k, w;
    int count = 1;
    for (h = 0; h < Kosuu; h++) {
        k = 0, w = 1;
        for (j = 1; j <= Node; j++) {
            for (i = w; i <= Node; i++) {
                if (j == i)
                    dis[j][i] = 99;     //�ړ����Ȃ�������
                else {
                    dis[j][i] = array[k];
                    dis[i][j] = array[k];
                    k++;
                }
            }
            w++;
        }
        for (j = 1; j <= Node; j++) {
            for (i = 1; i <= Node; i++) {
                printf("%2d ", dis[j][i]);
            }
            puts("");
        }
        puts("");
    }
    free(array);

}

int main(int argc, char* argv[]) {
    int num;
    char names[1000];
    char filepath[256];
    for (num = 100; num < 110; num++) {
        names[num] = num;
        srand(num);
        printf("������,%d\n", num);
        int i, j, n, m;
        Node = 20;
        printf("�s�s��:%d\n", Node);
        //scanf("%d", &Node);
        arrayInit();
        makeRandom();
        makeMap();

        sprintf(filepath, "slvtsp20_%d.lp", names[num]);
        //--------------------------------------------------------------------------------------
        fp = fopen(filepath, "w"); // File���J��

        if (fp == NULL) {
            printf("�t�@�C���I�[�v�����s\n");
            return -1;
        }
        fputs("minimize\n", fp);   //�œK��
        for (n = 1; n <= Node; n++) {
            if (n == Node) {
                j = 1;
                for (i = 2; i <= Node; i++) {
                    if (i == Node && n == Node) {
                        fprintf(fp, "%d x(%d)(%d)(%d)\n", dis[i][j], i, j, n);
                    }
                    else {
                        fprintf(fp, "%d x(%d)(%d)(%d) + ", dis[i][j], i, j, n);
                    }
                }
            }
            else if (n != 1) {
                for (i = 2; i <= Node; i++) {
                    for (j = 2; j <= Node; j++) {
                        if (i == j) {

                        }

                        else if (j == Node - 1 && i == Node) {
                            fprintf(fp, "%d x(%d)(%d)(%d) + \n", dis[i][j], i, j, n);
                        }
                        else {
                            fprintf(fp, "%d x(%d)(%d)(%d) + ", dis[i][j], i, j, n);
                        }
                    }
                }
            }
            else if (n == 1) {
                i = 1;
                for (j = 1; j <= Node; j++) {
                    if (i == j) {

                    }
                    else if (i == 1 && j == Node) {
                        fprintf(fp, "%d x(%d)(%d)(%d) + \n", dis[i][j], i, j, n);
                    }
                    else {
                        fprintf(fp, "%d x(%d)(%d)(%d) + ", dis[i][j], i, j, n);
                    }
                }

            }
        }
        fprintf(fp, "\n");
        //-------------------------------------------------------------------------------------
        fputs("\nsubject to\n", fp); //�������
        for (n = 2; n <= Node; n++) {//�����ꏊ�ɂ����Ȃ� 0�Ԗ�
            j = 1;
            i = 1;
            if (n == Node) {
                fprintf(fp, "x(%d)(%d)(%d) ", j, n, i);
            }

            else {
                fprintf(fp, "x(%d)(%d)(%d) + ", j, n, i);
            }
        }
        fprintf(fp, "= 1\n");
        for (n = 2; n <= Node; n++) {//�����ꏊ�ɂ����Ȃ� 1~Node-1
            for (i = 1; i < Node; i++) {
                for (j = 1; j <= Node; j++) {
                    if (j == n) {

                    }
                    else if (i == 1 && j == 1) {
                        fprintf(fp, "x(%d)(%d)(%d) + ", j, n, i);
                    }
                    else if (j == Node && i == Node - 1 && (i != 1 && j != 1)) {
                        fprintf(fp, "x(%d)(%d)(%d) ", j, n, i);
                    }
                    else if (j == Node - 1 && n == Node && i == Node - 1 && (i != 1 && j != 1)) {
                        fprintf(fp, "x(%d)(%d)(%d) ", j, n, i);
                    }
                    else if (i != 1 && j != 1) {
                        fprintf(fp, "x(%d)(%d)(%d) + ", j, n, i);
                    }

                }
            }
            fprintf(fp, "= 1\n");
        }
        for (j = 2; j <= Node; j++) {//�����ꏊ�ɂ����Ȃ� �Ō�
            n = 1;
            i = Node;
            if (j == Node) {
                fprintf(fp, "x(%d)(%d)(%d) ", j, n, i);
            }
            else {
                fprintf(fp, "x(%d)(%d)(%d) + ", j, n, i);
            }
        }
        fprintf(fp, "= 1\n");

        //-------------------------------------------------------------------------------------
        //�������2�@�@���ɍs�����[�g�̐���
        fputs("\n", fp);
        i = 1;
        n = 1;
        for (j = 2; j <= Node; j++) {  //1�Ԗ�
            fprintf(fp, "x(%d)(%d)(%d) - ", i, j, n);
            for (m = 2; m <= Node; m++) {
                if (m == j) {

                }
                else if (m == Node) {
                    fprintf(fp, "x(%d)(%d)(%d) ", j, m, n + 1);
                }
                else if (m == Node - 1 && j == Node) {
                    fprintf(fp, "x(%d)(%d)(%d) ", j, m, n + 1);
                }
                else {
                    fprintf(fp, "x(%d)(%d)(%d) - ", j, m, n + 1);
                }
            }
            fprintf(fp, "= 0\n");
        }
        for (n = 2; n < Node - 1; n++) {//2~Node-1�Ԗ�
            for (i = 2; i <= Node; i++) {
                for (j = 2; j <= Node; j++) {
                    if (i == j) {

                    }
                    else if (j == Node) {
                        fprintf(fp, "x(%d)(%d)(%d) - ", j, i, n);
                    }
                    else if (j == Node - 1 && i == Node) {
                        fprintf(fp, "x(%d)(%d)(%d) - ", j, i, n);
                    }
                    else {
                        fprintf(fp, "x(%d)(%d)(%d) + ", j, i, n);
                    }
                }
                for (m = 2; m <= Node; m++) {
                    if (i == m) {

                    }
                    else if (m == Node) {
                        fprintf(fp, "x(%d)(%d)(%d)", i, m, n + 1);
                    }
                    else if (m == Node - 1 && i == Node) {
                        fprintf(fp, "x(%d)(%d)(%d)", i, m, n + 1);
                    }
                    else {
                        fprintf(fp, "x(%d)(%d)(%d) - ", i, m, n + 1);
                    }
                }
                fprintf(fp, "= 0\n");
            }
        }

        n = Node - 1; //�Ō�
        for (i = 2; i <= Node; i++) {
            for (j = 2; j <= Node; j++) {
                if (i == j) {

                }
                else if (j == Node) {
                    fprintf(fp, "x(%d)(%d)(%d) ", j, i, n);
                }
                else if (j == Node - 1 && i == Node) {
                    fprintf(fp, "x(%d)(%d)(%d) ", j, i, n);
                }
                else {
                    fprintf(fp, "x(%d)(%d)(%d) + ", j, i, n);

                }
            }
            fprintf(fp, "- x(%d)(%d)(%d) ", i, 1, n + 1);
            fprintf(fp, "= 0\n");
        }
        /*for (n = 0; n <= Node; n++) { //()�̈�ڂɊւ��Ăǂꂩ��1�ɂȂ�
            if (n == Node) {
                j = 1;
                for (i = 2; i <= Node; i++) {
                    if (i == Node && n == Node) {
                        fprintf(fp, "(%d)(%d)(%d)", i, j, n);
                    }
                    else {
                        fprintf(fp, "x(%d)(%d)(%d) + ", i, j, n);
                    }
                }
                fprintf(fp, " = 1\n");
            }
            else if (n != 0) {
                for (i = 2; i <= Node; i++) {
                    for (j = 2; j <= Node; j++) {
                        if (i == j) {

                        }
                        else if (i != j && j == Node) {
                            fprintf(fp, "x(%d)(%d)(%d)", i, j, n);
                        }
                        else if (i == Node && j == Node - 1) {
                            fprintf(fp, "x(%d)(%d)(%d)", i, j, n);
                        }
                        else {
                            fprintf(fp, "x(%d)(%d)(%d) + ", i, j, n);
                        }
                    }
                    fprintf(fp, " = 1\n");
                }
            }
            else {
                i = 1;
                for (j = 2; j <= Node; j++) {
                    if (i == j) {

                    }
                    else if (i != j && j == Node) {
                        fprintf(fp, "x(%d)(%d)(%d)", i, j, n);
                    }
                    else if (i == Node && j == Node - 1) {
                        fprintf(fp, "x(%d)(%d)(%d)", i, j, n);
                    }
                    else {
                        fprintf(fp, "x(%d)(%d)(%d) + ", i, j, n);
                    }
                }
                fprintf(fp, " = 1\n");
            }
        }
        for (n = 1; n <= Node-1; n++) {//()�̓�ڂɊւ��Ăǂꂩ��1�ɂȂ�
            for (i = 2; i <= Node; i++) {

                for (j = 2; j <= Node; j++) {
                        if (i == j) {

                        }
                        else if (i != j && j == Node) {
                            fprintf(fp, "x(%d)(%d)(%d)", j, i, n);
                        }
                        else if (i == Node && j == Node - 1) {
                            fprintf(fp, "x(%d)(%d)(%d)", j, i, n);
                        }
                        else {
                            fprintf(fp, "x(%d)(%d)(%d) + ", j, i, n);
                        }
                    }
                    fprintf(fp, " = 1\n");
                }
        }
        //for (i = 1; i <= Node; i++) { //()�̓�ڂɊւ��Ăǂꂩ��1�ɂȂ�
        //    for (j = i+1; j <= Node; j++) {
        //        fprintf(fp, "x(%d)(%d)(%d) + x(%d)(%d)(%d)<=1\n", i, j, j, i);
        //    }
        //}

        */
        //-------------------------------------------------------------------------------------
        fputs("\nbinary\n", fp);//�ϐ�
        for (n = 1; n <= Node; n++) {
            if (n == Node) {
                j = 1;
                for (i = 2; i <= Node; i++) {
                    if (i == Node) {
                        fprintf(fp, "x(%d)(%d)(%d)\n", i, j, n);
                    }
                    else {
                        fprintf(fp, "x(%d)(%d)(%d) ", i, j, n);
                    }
                }
            }
            else if (n != 1) {
                for (i = 2; i <= Node; i++) {
                    for (j = 2; j <= Node; j++) {
                        if (i == j) {

                        }

                        else if (j == Node - 1 && i == Node) {
                            fprintf(fp, "x(%d)(%d)(%d) \n", i, j, n);
                        }
                        else {
                            fprintf(fp, "x(%d)(%d)(%d) ", i, j, n);
                        }
                    }
                }
            }
            else if (n == 1) {
                i = 1;
                for (j = 1; j <= Node; j++) {
                    if (i == j) {

                    }
                    else if (i == 1 && j == Node) {
                        fprintf(fp, "x(%d)(%d)(%d) \n", i, j, n);
                    }
                    else {
                        fprintf(fp, "x(%d)(%d)(%d) ", i, j, n);
                    }
                }

            }

        }
        fputs("\nend\n", fp);
        fclose(fp);
        //-------------------------------------------------------------------------------------
        arrayFree();
        puts("");
    }
}
