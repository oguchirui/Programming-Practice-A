#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p3_header.h"

int delta(char *X, int a, char *Y, int b); //delta関数を宣言

int main(void){
    int len_x, len_y; //二つの文字列の長さ

    scanf("%d", &len_x); //二つの文字列の長さを読み込む
    scanf("%d", &len_y);

    char* data_x = malloc_string_(len_x); //文字列を格納する配列を動的確保
    char* data_y = malloc_string_(len_y);

    read_string_(data_x, len_x); //長さlen_x, len_yの文字列をそれぞれ配列に読み込む
    read_string_(data_y, len_y);

    int c = 0; //簡略化した編集距離

    for(int i = 1; i <= len_x; ++i){
        if(delta(data_x, i, data_y, i) == 1){ //delta関数の値が1の場合、簡略化した編集距離を1増やす
            ++c;
        }
    }

    for(int i = 0; i < len_x; ++i){
        printf("%c", data_x[i]); //文字列Xを出力
    }

    printf(" %d\n", len_x); //文字列Xの長さを出力

    for(int i = 0; i < len_y; ++i){
        printf("%c", data_y[i]); //文字列Yを出力
    }

    printf(" %d\n", len_x); //文字列Yの長さを出力

    printf("%d\n", c); //簡略化した編集距離を出力

    free(data_x); //動的メモリを開放
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