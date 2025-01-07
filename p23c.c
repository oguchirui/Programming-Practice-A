//////////////////////////////////////////////////////
//  東北大学　プログラミング演習A           
//  問題 p23c 用のエラーを含む初期コードです。         
//   この初期コードを修正し問題を解いてください。   
//////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

int main() {
    int nStudents;

    scanf("%d", &nStudents);                             //学生の数を標準入力から受け取る
    int* seseki = (int*)malloc(sizeof(int)*nStudents);   //成績を記憶する配列の動的確保
    int* bangou = (int*)malloc(sizeof(int)*nStudents);   //学籍番号を記憶する配列の動的確保

    for(int i=0; i<nStudents; i++) {                     //学生の成績を標準入力から受け取る
        scanf("%d", &seseki[i]);
    }

    int end = nStudents - 1;
    int begin = 0;
    for(int i=0; i<nStudents; i++) {                     
        if(seseki[i] >= 60) {                              //60点以上で合格
            bangou[end] = i+1;                               //配列bangouの最後から右へ学籍番号を詰める   
            end--;                                           //次に格納する配列bangouの要素のインデックスを更新
        }
        else {                                             //60点未満で不合格
            bangou[begin] = i+1;                               //配列bangouの最初から左へ学籍番号を詰める
            begin++;                                         //次に格納する配列bangouの要素のインデックスを更新
        }
    }

    printf("Failed students\n");
    for(int i=0; i<=end; i++) {                          //不合格の学生の成績を学籍番号が小さい順に表示
        printf("Gakuseki bangou = %d, Marks = %d\n", bangou[i], seseki[bangou[i]-1]);
    }

    printf("\nPassed students\n");
    for(int i=nStudents-1; i>end; i--) {                 //合格の学生の成績を学籍番号が小さい順に表示
        printf("Gakuseki bangou = %d, Marks = %d\n", bangou[i], seseki[bangou[i]-1]);
    }

    free(seseki);                                        //確保したメモリ領域を開放
    free(bangou);                                        //確保したメモリ領域を開放

    return 0;
}