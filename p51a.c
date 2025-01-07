#include <stdio.h>

int main(void) {
    int n; //配列の要素数

    scanf("%d", &n); //配列の要素数を入力

    int data[n]; //可変超配列を宣言

    for (int i = 0; i < n; i++) { //配列の要素を入力
        scanf("%d", &data[i]);
    }

    for (int i = 0; i < n - 1; i++) { //配列を出力
        printf("%4d, ", data[i]);
    }
    printf("%4d\n", data[n - 1]);

    int comp = 0; //比較回数
    int min = data[0]; //最初は先頭の要素が最小要素
    int minindex = 0; //最小要素インデックス

    for (int i = 1; i < n; i++) {
        comp++; //比較回数を+1

        if (data[i] < min) { //他の要素と比較して、他の要素の方が小さかったら、最小要素を更新
            min = data[i];
            minindex = i; //最小要素インデックスを記録
        }

        printf("comp = %d, min = %d\n", comp, min); //その時点での比較回数、最小要素を出力
    }

    int temp; //要素を一時保持する変数

    temp = data[0]; //最小要素と先頭の要素を入れ替える
    data[0] = data[minindex];
    data[minindex] = temp;

    for (int i = 0; i < n - 1; i++) { //配列を出力
        printf("%4d, ", data[i]);
    }
    printf("%4d\n", data[n - 1]);

    return 0;
}