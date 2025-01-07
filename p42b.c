#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p3_header.h"

int delta(char *X, int a, char *Y, int b); //必要な関数を宣言
int ld(char *X, int m, char *Y, int n);
int ldmemo(char *X, int m, char *Y, int n, int **memo);
int ReadMemo(int **memo, int x, int y);
void WriteMemo(int **memo, int x, int y, int value);

int count = 0; //ld関数の呼び出し回数を数えるグローバル関数

int main(void){
    int len_x, len_y; //文字列の長さ

    scanf("%d", &len_x); //文字列の長さを読み込む
    scanf("%d", &len_y);

    char* data_x = malloc_string_(len_x); //文字列を格納する配列を動的確保
    char* data_y = malloc_string_(len_y);

    read_string_(data_x, len_x); //長さlen_x, len_yの文字列をそれぞれ配列に読み込む
    read_string_(data_y, len_y);

    int** memo = malloc_2d_(len_x + 1, len_y + 1); //二次元配列memoを動的確保

    for(int i = 0; i < len_x + 1; ++i){
        for(int j = 0; j < len_y + 1; ++j){
            if(i == 0){
                memo[i][j] = j; //i = 0の場合、配列memoを編集距離jで初期化
            }

            else if(j == 0){
                memo[i][j] = i; //j = 0の場合、配列memoを編集距離iで初期化
            }

            else{
                memo[i][j] = -1; //i ≠ 0かつj ≠ 0の場合、配列memoを-1で初期化
            }
        }
    }

    printf("%s %d\n", data_x, len_x); //文字列とその長さを出力
    printf("%s %d\n", data_y, len_y);

    int c_ldmemo = ldmemo(data_x, len_x, data_y, len_y, memo); //配列memoを出力する前に、関数ldmemoによる処理を行うことで、配列memoの要素を格納

    for(int i = 1; i < len_x + 1; ++i){ //配列memoの要素を出力
        for(int j = 1; j < len_y + 1; ++j){
            printf("%3d", memo[i][j]);
        }

        printf("\n");
    }

    printf("%d ", ld(data_x, len_x, data_y, len_y)); //ld関数で計算した編集距離を出力

    printf("%d\n", count); //ld関数の呼び出し回数を出力

    printf("%d\n", c_ldmemo); //ldmemo関数で計算した編集距離を出力

    free_2d_(memo, len_x + 1); //動的メモリを開放
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

int ld(char *X, int m, char *Y, int n){ //ld関数を定義
    /*printf("LD(%d,%d)\n", m, n); //LD(m,n)を出力*/

    ++count; //ld関数の呼び出し回数を増やす

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

int ldmemo(char *X, int m, char *Y, int n, int **memo){ //ldmemo関数を定義
    /*printf("LD(%d,%d)\n", m, n); //LD(m,n)を出力*/

    if(m == 0){
        return n; //m = 0の時、mを返し再帰を抜ける
    }

    else if(n == 0){
        return m; //n = 0の時、nを返し再帰を抜ける
    }

    else if(ReadMemo(memo, m, n) >= 0){
        return ReadMemo(memo, m, n); //配列memoに編集距離が格納されている場合、その値を返す
    }

    else{ //配列memoに編集距離が格納されていない場合、再帰処理    
        int copy_replace = ldmemo(X, m - 1, Y, n - 1, memo) + delta(X, m, Y, n); //コピー、置換の処理
        int delete = ldmemo(X, m - 1, Y, n, memo) + 1; //削除の処理
        int insert = ldmemo(X, m, Y, n - 1, memo) + 1; //挿入の処理

        WriteMemo(memo, m, n, vmin3_(copy_replace, delete, insert)); //配列memoに編集距離を格納

        return ReadMemo(memo, m, n); //格納した編集距離を返す
    }
}

int ReadMemo(int **memo, int x, int y){
    return memo[x][y]; //memoのx, yにおける値を返す
}

void WriteMemo(int **memo, int x, int y, int value){
    memo[x][y] = value; //memoのx, yにおける値にvalueを代入する
}