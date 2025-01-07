#include <stdio.h>

int mrg_sort(int array[], int N, int from, int to);
int merge(int array[], int N, int from, int to, int mid);

void print_array_range(int array[], int N, int p, int r) {
    int ri = 0;
    for (; ri < N - 1; ++ri) {
        if (ri < p || r < ri) {
            printf("  **, ");
        } else {
            printf("%4d, ", array[ri]);
        }
    }
    if (r < N - 1) {
        printf("  **\n");
    } else {
        printf("%4d\n", array[N-1]);
    }
}

int main() {
    int n;
    scanf("%d", &n);  // 配列の要素数を読み込む
    int array[2 * n];  // 2N個のメモリを確保する

    for(int i = 0; i < n; i++) {
        scanf("%d", &(array[i]));  // 配列の要素を読み込む
    }

    printf("INIT. ARRAY : ");
    print_array_range(array, n, 0, n - 1);

    int comp_count = mrg_sort(array, n, 0, n - 1);
    printf("comp = %d\n", comp_count);

    return 0;
}

int mrg_sort(int array[], int N, int from, int to) {
    if (from >= to) return 0;  // 長さが1の配列はソート済み

    int mid = from + (to - from) / 2;  // 真ん中の位置を計算
    int comp_count = 0;

    printf("SORT(%2d, %2d)\n", from, to);

    comp_count += mrg_sort(array, N, from, mid);       // 前半部分を再帰的にソート
    comp_count += mrg_sort(array, N, mid + 1, to);     // 後半部分を再帰的にソート
    comp_count += merge(array, N, from, to, mid);      // 前半と後半をマージ

    return comp_count;
}

int comp(int array[], int pos_a, int pos_b) {
    if (array[pos_a] < array[pos_b]) return 1;  
    return 0;                                   
}

int* copy(int array[], int pos_a, int pos_b) {
    array[pos_b] = array[pos_a];
    return array;
}

int merge(int array[], int N, int from, int to, int mid) {
    int comp_count = 0;
    int i = from, j = mid + 1, k = N;  // iは前半、jは後半、kはマージ用記憶領域の開始位置

    // マージ用記憶領域にマージ
    while (i <= mid && j <= to) {
        if (comp(array, i, j)) {
            copy(array, i++, k++);
        } else {
            copy(array, j++, k++);
        }
        comp_count++;
    }

    // 前半の残りをマージ用記憶領域にコピー
    while (i <= mid) {
        copy(array, i++, k++);
    }

    // 後半の残りをマージ用記憶領域にコピー
    while (j <= to) {
        copy(array, j++, k++);
    }

    // マージ用記憶領域から元の配列にコピー
    for (int l = from; l <= to; l++) {
        copy(array, N + l, l);
    }

    printf("MERG(%2d, %2d) : ", from, to);
    print_array_range(array, N, from, to);

    return comp_count;
}