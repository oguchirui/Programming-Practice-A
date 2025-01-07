#include <stdio.h>

void print_array_range(int array[], int N, int p, int r); //必要な関数を宣言
int mrg_sort(int array[], int N, int from, int to);

int main(void) {
    int n; //配列の要素数

    scanf("%d", &n); //配列の要素数を読み込む

    int array[n];  //可変長配列による配列の確保

    for (int i = 0; i < n; i++) { //配列の要素を読み込む
        scanf("%d", &array[i]);
    }

    printf("INIT. ARRAY : ");
    print_array_range(array, n, 0, n - 1); //配列全体を出力
    
    mrg_sort(array, n, 0, n - 1); //mrg_sort関数を実行

    return 0;
}

void print_array_range(int array[], int N, int p, int r) { //print_array_range関数を定義
    int ri = 0;
    
    for (; ri < N - 1; ++ri) {
        if (ri < p || r < ri) { //範囲外の要素は"**"で表す
            printf("  **, ");
        }
    
        else {
            printf("%4d, ", array[ri]); //範囲内の要素を出力
        }
    }
    
    if (r < N - 1) {
        printf("  **\n");
    }
    
    else {
        printf("%4d\n", array[N-1]);
    }
}

int mrg_sort(int array[], int N, int from, int to) { //mrg_sort関数を定義
    printf("SORT(%2d,%2d)\n", from, to); //mrg_sort関数の範囲を出力

    int array_length = to - from + 1;

    if (array_length == 1) { //配列の長さが1の場合、その要素を返す
        return array[from];
    }

    if (array_length % 2 == 0) { //配列の長さが偶数の場合、配列を二つに分け、再帰処理
        mrg_sort(array, N, from, from + (array_length / 2 - 1));
        
        mrg_sort(array, N, to - (array_length / 2 - 1), to);
    }

    else { //配列の長さが奇数の場合、配列を二つに分け、再帰処理
        
        mrg_sort(array, N, from, from + array_length / 2);

        mrg_sort(array, N, to - (array_length / 2 - 1), to);
    }
}