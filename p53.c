#include <stdio.h>
#include "ppa_extra_h/mrg_sort.h"

struct Count {
    int comparison_count; //比較回数のカウントをする変数
    int element_count; //範囲内の要素数を保持する変数
};

struct Count count_less_unsorted(int array[], int N, int x); //必要な関数を宣言
struct Count count_less_sorted(int array[], int N, int x);
struct Count binary_search(int array[], int from, int to, int x, struct Count c);

int main(void) {
    int n; //配列の要素数

    scanf("%d", &n); //配列の要素数を読み込む

    int array[2 * n]; //可変長配列による配列の確保

    for (int i = 0; i < n; i++) { //配列の要素を読み込む
        scanf("%d", &array[i]);
    }

    int m; //xの個数

    scanf("%d", &m); //xの個数を読み込む

    int x[m]; //可変長配列によるxの配列の確保

    for (int i = 0; i < m; i++) { //xの配列の要素を読み込む
        scanf("%d", &x[i]);
    }

    printf("count_less_unsorted:\n");

    for (int i = 0; i < m; ++i) { //配列をソートしない場合の探索結果の出力
        printf("%d %d\n", count_less_unsorted(array, n, x[i]).element_count, count_less_unsorted(array, n, x[i]).comparison_count);
    }

    printf("count_less_sorted:\n");

    for (int i = 0; i < m; ++i) { //配列をソートした場合の探索結果の出力
        printf("%d %d\n", count_less_sorted(array, n, x[i]).element_count, count_less_sorted(array, n, x[i]).comparison_count);
    }

    return 0;
}

struct Count count_less_unsorted(int array[], int N, int x) { //count_less_unsorted関数を定義
    struct Count c = {0, 0}; 

    for (int i = 0; i < N; i++) { //配列の先頭から順にxより小さいか判定
        if (++c.comparison_count, array[i] < x) { //xより小さい場合、要素数カウンターを+1
            ++c.element_count;
        }
    }

    return c; //カウンターの構造体を返す
}

struct Count count_less_sorted(int array[], int N, int x) { //count_less_sorted関数を定義
    struct Count c = {0, 0};

    mrg_sort_(array, N, 0, N - 1); //配列をマージソート

    if (++c.comparison_count, x < array[0]) { //xが全ての配列の要素より小さい場合、要素数カウンターは0のまま
        return c; //カウンターの構造体を返す
    }

    else if (++c.comparison_count, array[N - 1] < x) { //xが全ての配列の要素より大きい場合、要素数カウンターを全ての要素数にする
        c.element_count = N;

        return c; //カウンターの構造体を返す
    }

    else { //以上に当てはまらない場合、二分探索を実行する
        return binary_search(array, 0, N - 1, x, c);
    }
}

struct Count binary_search(int array[], int from, int to, int x, struct Count c) { //二分探索を行う関数を定義
    int array_length = to - from + 1; //分割する配列の長さ
    int mid = (from + to) / 2 + 1; //後方の配列の先頭のインデックス

    if (array_length == 1) { //配列の長さが1の場合
        ++c.element_count; //要素数カウンターを調整

        return c; //カウンターの構造体を返す
    }

    else if (++c.comparison_count, x < array[mid]) { //xが後方の配列の先頭の要素より小さい場合
        return binary_search(array, from, mid - 1, x, c); //前方の配列を選ぶ
    }

    else { //xが後方の配列の先頭の要素より大きい場合
        c.element_count = mid; //要素数カウンターを後方の配列の先頭のインデックスにする

        return binary_search(array, mid, to, x, c); //後方の配列を選ぶ
    }
}