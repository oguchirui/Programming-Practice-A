#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p3_header.h"

int delta(char *X, int a, char *Y, int b); //必要な関数を宣言
int ld_dp(char *X, int m, char *Y, int n, int **dpt);
void show_matrix(char *X, int m, char *Y, int n, int **dpt);
void show_path(char *X, int m, char *Y, int n, int **dpt);
void get_ops(char *X, int m, char *Y, int n, int **dpt, char *seq_x, char *seq_y, char *ops);
void reverse_str(char *str);

int main(void){
    int len_x, len_y; //文字列の長さ

    scanf("%d", &len_x); //文字列の長さを読み込む
    scanf("%d", &len_y);

    char* data_x = malloc_string_(len_x); //文字列を格納する配列を動的確保
    char* data_y = malloc_string_(len_y);
    int** dpt = malloc_2d_(len_x + 1, len_y + 1); //二次元配列dptを動的確保
    
    char* seq_x = malloc_string_(len_x + len_y); //編集操作列に対応する文字列を格納する配列を動的確保
    char* seq_y = malloc_string_(len_x + len_y);
    char* ops = malloc_string_(len_x + len_y); //編集操作列を記録する文字列を格納する配列を動的確保

    read_string_(data_x, len_x); //長さlen_x, len_yの文字列をそれぞれ配列に読み込む
    read_string_(data_y, len_y);

    ld_dp(data_x, len_x, data_y, len_y, dpt); //ld_dp関数を実行

    show_matrix(data_x, len_x, data_y, len_y, dpt); //配列dptを出力

    /*show_path(data_x, len_x, data_y, len_y, dpt); //編集距離の道を出力*/

    get_ops(data_x, len_x, data_y, len_y, dpt, seq_x, seq_y, ops); //get_ops関数を実行

    printf("%s\n", seq_x); //配列seq_x, seq_y, opsを出力
    printf("%s\n", seq_y);
    printf("%s\n", ops);

    free_2d_(dpt, len_x + 1); //動的メモリを開放
    free(data_x);
    free(data_y);
    free(seq_x);
    free(seq_y);
    free(ops);

    return 0;
}

void show_matrix(char *X, int m, char *Y, int n, int **dpt){ //show_matrix関数を定義
    //1行目の出力
    printf("    ");
    
    for(int j = 0; j < n; ++j){
        printf("  %c",Y[j]);
    }
    
    printf("\n");

    //2行目の出力
    printf(" ");
    
    for(int j = 0; j < n + 1; ++j){
        printf(" %2d", dpt[0][j]);
    }
    
    printf("\n");

    //3行目以降の出力
    for(int i = 1; i < m + 1; ++i){
        printf("%c", X[i - 1]);

        for(int j = 0; j < n + 1; ++j){
            printf(" %2d", dpt[i][j]);
        }

        printf("\n");
    }
}

void show_path(char *X, int m, char *Y, int n, int **dpt){ //show_path関数の定義
    for(;;){
        if(m == 0 && n == 0){ //テーブルの左上の要素の時、要素を出力してループを抜ける
            printf("(%d,%d)\n", m, n);

            break;
        }

        if(m == 0){ //テーブルの上端の要素の時、要素を出力して左隣の要素に移動し、次のループへ
            printf("(%d,%d) > ", m, n);
            --n;

            continue;
        }

        if(n == 0){ //テーブルの左端の要素の時、要素を出力して上隣の要素に移動し、次のループへ
            printf("(%d,%d) > ", m, n);
            --m;

            continue;
        }
        
        printf("(%d,%d) > ", m, n); //要素を出力する

        int copy_replace = dpt[m - 1][n - 1]; //左上の経路
        int insert = dpt[m][n - 1]; //左隣の経路
        int delete = dpt[m - 1][n]; //上隣の経路

        int smallest_path = vmin3_(copy_replace, insert, delete); //最小の経路

        if(copy_replace == smallest_path){ //左上の経路が最小の経路の場合、左上の要素に移動し、次のループへ
            --m;
            --n;

            continue;
        }

        else if(insert == smallest_path){ //左隣の経路が最小の経路の場合、左隣の要素に移動し、次のループへ
            --n;

            continue;
        }

        else{ //上隣の経路が最小の経路の場合、上隣の要素に移動し、次のループへ
            --m;

            continue;
        }
    }
}

void get_ops(char *X, int m, char *Y, int n, int **dpt, char *seq_x, char *seq_y, char *ops){ //get_ops関数を定義
    int i = 0; //配列配列seq_x, seq_y, opsのインデックス
    
    for(;;){
        if(m == 0 && n == 0){ //テーブルの左上の要素の時、ループを抜ける
            break;
        }

        if(m == 0){ //テーブルの上端の要素の時
            seq_x[i] = ' '; //配列seq_xに空白, seq_yに文字を格納
            seq_y[i] = Y[n - 1];

            ops[i] = 'I'; //配列opsにIを格納
            
            --n; //左隣の要素に移動
            ++i; //インデックスを増やす

            continue; //次のループへ
        }

        if(n == 0){ //テーブルの左端の要素の時
            seq_x[i] = X[m - 1]; //配列seq_xに文字, seq_yに空白を格納
            seq_y[i] = ' ';

            ops[i] = 'D'; //配列opsにDを格納

            --m; //上隣の要素に移動
            ++i; //インデックスを増やす

            continue; //次のループへ
        }
        
        int copy_replace = dpt[m - 1][n - 1]; //左上の経路
        int insert = dpt[m][n - 1]; //左隣の経路
        int delete = dpt[m - 1][n]; //上隣の経路

        int smallest_path = vmin3_(copy_replace, insert, delete); //最小の経路

        if(copy_replace == smallest_path){ //左上の経路が最小の経路の場合
            seq_x[i] = X[m - 1]; //配列seq_x, seq_yに文字を格納
            seq_y[i] = Y[n - 1];
            
            if(delta(X, m ,Y, n) == 0){ //編集操作がコピーの場合、配列opsに=を格納
                ops[i] = '=';
            }

            else{ //編集操作が置換の場合、配列opsにRを格納
                ops[i] = 'R';
            }
            
            --m; //左上の要素に移動
            --n;
            ++i; //インデックスを増やす

            continue; //次のループへ
        }

        else if(insert == smallest_path){ //左隣の経路が最小の経路の場合
            seq_x[i] = ' '; //配列seq_xに空白, seq_yに文字を格納
            seq_y[i] = Y[n - 1];

            ops[i] = 'I'; //配列opsにIを格納
            
            --n; //左隣の要素に移動
            ++i; //インデックスを増やす

            continue; //次のループへ
        }

        else{ //上隣の経路が最小の経路の場合
            seq_x[i] = X[m - 1]; //配列seq_xに文字, seq_yに空白を格納
            seq_y[i] = ' ';

            ops[i] = 'D'; //配列opsにDを格納

            --m; //上隣の要素に移動
            ++i; //インデックスを増やす

            continue; //次のループへ
        }
    }

    reverse_str(seq_x); //文字列を逆順にする
    reverse_str(seq_y);
    reverse_str(ops);
}

void reverse_str(char *str){ //文字列を逆順にする関数を定義
    int str_length = 0;
    
    for(int i = 0; str[i] != '\0'; ++i){ //文字列の長さをカウント
        ++str_length;
    }

    for(int i = 0, j = str_length - 1; i < j; ++i, --j){ //文字列の両端から文字を交換
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int delta(char *X, int a, char *Y, int b){ //delta関数を定義
    if(X[a - 1] == Y[b - 1]){
        return 0; //文字列Xの位置aの文字と文字列Yの位置bの文字が等しい場合、0を返す
    }

    else{
        return 1; //異なる場合、1を返す
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