#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p3_header.h"

int delta(char *X, int a, char *Y, int b); //必要な関数を宣言
void dpt_delta(char *X, int m, char *Y, int n, int **dpt);
int ld_dp(char *X, int m, char *Y, int n, int **dpt);

int main(void){
    int len_x, len_y; //文字列の長さ

    scanf("%d", &len_x); //文字列の長さを読み込む
    scanf("%d", &len_y);

    char* data_x = malloc_string_(len_x); //文字列を格納する配列を動的確保
    char* data_y = malloc_string_(len_y);

    read_string_(data_x, len_x); //長さlen_x, len_yの文字列をそれぞれ配列に読み込む
    read_string_(data_y, len_y);

    int** dpt = malloc_2d_(len_x + 1, len_y + 1); //二次元配列dptを動的確保

    printf("%s %d\n", data_x, len_x); //文字列とその長さを出力
    printf("%s %d\n", data_y, len_y);

    /*dpt_delta(data_x, len_x, data_y, len_y, dpt); //dpt_delta関数の処理

    for(int i = 0; i < len_x + 1; ++i){ //配列dptの要素を出力
        for(int j = 0; j < len_y; ++j){
            printf("%2d ", dpt[i][j]);
        }
        printf("%2d", dpt[i][len_y]);
        printf("\n");
    }*/

    printf("%d\n", ld_dp(data_x, len_x, data_y, len_y, dpt)); //ld_dp関数による編集距離を出力

    free_2d_(dpt, len_x + 1); //動的メモリを開放
    free(data_x);
    free(data_y);

    return 0;
}


int delta(char *X, int a, char *Y, int b){ //delta関数を定義
    if(X[a - 1] == Y[b - 1]){
        return 0; //文字列Xの位置aの文字と文字列Yの位置bの文字が等しい場合、0を返す
    }

    else{
        return 1; //異なる場合、1を返す
    }
}

void dpt_delta(char *X, int m, char *Y, int n, int **dpt){ //dpt_delta関数を定義
    for(int i = 0; i < m + 1; ++i){
        for(int j = 0; j < n + 1; ++j){
            if(i == 0 || j == 0){ //iまたはjが0の場合、配列dptに-1を格納
                dpt[i][j] = -1;
            }

            else{
                dpt[i][j] = delta(X, i, Y, j); //Xのi番目の文字とYのj番目の文字が等しい場合、配列dptに0を格納、そうでない場合は1を格納
            }
        }
    }
}

int ld_dp(char *X, int m, char *Y, int n, int **dpt){ //ld_dp関数を定義
    for(int i = 0; i < m + 1; ++i){ //jが0の場合、またはiが0の場合の配列dptの要素をあらかじめ格納しておく
        dpt[i][0] = i;
    }

    for(int j = 1; j < n + 1; ++j){
        dpt[0][j] = j;
    }
    
    for(int i = 1; i < m + 1; ++i){
        for(int j = 1; j < n + 1; ++j){
            //表の左上、左隣、真上の値を参照して配列dptの要素を格納していく
            dpt[i][j] = vmin3_(dpt[i - 1][j - 1] + delta(X, i, Y, j), dpt[i][j - 1] + 1, dpt[i - 1][j] + 1);
        }
    }

    return dpt[m][n]; //編集距離である、表の一番右下の値を返す
}