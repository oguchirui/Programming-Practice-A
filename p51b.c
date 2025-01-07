#include <stdio.h>

void print_array(int const array[], int size); //必要な関数を宣言
void swap(int array[], int x, int y);
void sel_sort(int array[], int size);

int main(void) {
    int n; //配列の要素数

    scanf("%d", &n); //配列の要素数を入力

    int data[n]; //可変超配列を宣言

    for (int i = 0; i < n; i++) { //配列の要素を入力
        scanf("%d", &data[i]);
    }

    printf("INIT. ARRAY : "); //入力された配列を出力
    print_array(data, n);

    sel_sort(data, n); //配列を選択ソートによって並び替える

    return 0;
}

void print_array(int const array[], int size) { //配列を出力する関数を定義
    for (int i = 0; i < size - 1; i++) {
        printf("%4d, ", array[i]);
    }
    printf("%4d\n", array[size - 1]);
}

void swap(int array[], int x, int y) { //任意の二つの要素を入れ替える関数を定義
    int temp; //要素を一時保持する変数

    temp = array[x]; //任意の二つの要素を入れ替える
    array[x] = array[y];
    array[y] = temp;
}

void sel_sort(int array[], int size) { //配列を選択ソートによって並び替える関数を定義
    int comp = 0; //比較回数

    for (int i = 0; i < size - 1; i++) { //配列の要素のうち、先頭からi番目を除く要素での比較
        int min = array[i]; //最初は先頭の要素が最小要素
        int minindex = i; //最小要素インデックス
        
        for (int j = 1 + i; j < size; j++) {
            comp++; //比較回数を+1

            if (array[j] < min) { //他の要素と比較して、他の要素の方が小さかったら、最小要素を更新
                min = array[j];
                minindex = j; //最小要素インデックスを記録
            }
        }

        swap(array, i, minindex); //先頭の要素と最小要素を入れ替える

        printf("SWAP(%2d,%2d) : ", i, minindex); //入れ替え後の配列を出力
        print_array(array, size);
    }

    printf("comp = %d\n", comp); //比較回数を出力
}