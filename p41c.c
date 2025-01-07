#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p3_header.h"

int delta(char *X, int a, char *Y, int b); //必要な関数を宣言
int ld(char *X, int m, char *Y, int n);

int main(void){
    int len_x, len_y; //文字列の長さ

    scanf("%d", &len_x); //文字列の長さを読み込む
    scanf("%d", &len_y);

    char* data_x = malloc_string_(len_x); //文字列を格納する配列を動的確保
    char* data_y = malloc_string_(len_y);

    read_string_(data_x, len_x); //長さlen_x, len_yの文字列をそれぞれ配列に読み込む
    read_string_(data_y, len_y);

    printf("%s %d\n", data_x, len_x); //文字列とその長さを出力
    printf("%s %d\n", data_y, len_y);

    printf("%d\n", ld(data_x, len_x, data_y, len_y)); //編距離を出力

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

int ld(char *X, int m, char *Y, int n){ //ld関数を定義
    /*printf("LD(%d,%d)\n", m, n); //LD(m,n)を出力*/

    if(m == 0){
        return n; //m = 0の時、mを返し再帰を抜ける
    }

    if(n == 0){
        return m; //n = 0の時、nを返し再帰を抜ける
    }

    int copy_replace = ld(X, m - 1, Y, n - 1) + delta(X, m, Y, n); //コピー、置換の処理
    int delete = ld(X, m - 1, Y, n) + 1; //削除の処理
    int insert = ld(X, m, Y, n - 1) + 1; //挿入の処理

    return vmin3_(copy_replace, delete, insert); //処理の結果のうち、最小値を返す
}