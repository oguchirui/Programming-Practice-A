#include <stdio.h>

void print_array_range(int array[], int N, int p, int r); //必要な関数を宣言
int mrg_sort(int array[], int N, int from, int to);
int merge(int array[], int N, int from, int to, int mid);
int comp(int array[], int pos_a, int pos_b);
int* copy(int array[],int pos_a, int pos_b);

int main(void) {
    int n; //配列の要素数

    scanf("%d", &n); //配列の要素数を読み込む

    int array[2*n];  //可変長配列による配列の確保

    for (int i = 0; i < n; i++) { //配列の要素を読み込む
        scanf("%d", &array[i]);
    }

    printf("INIT. ARRAY : ");
    print_array_range(array, n, 0, n - 1); //ソート前の配列全体を出力

    printf("comp = %d\n", mrg_sort(array, n, 0, n - 1)); //mrg_sort関数を実行したのち、comp関数の呼び出し回数を出力

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
int array_length = to - from + 1; //分割する配列の長さ
int mid = from + (to - from) / 2 + 1; //二つ目の配列の始まりの位置
int count_comp = 0; //comp関数の呼び出し回数

    if (array_length == 1) { //配列の長さが1の場合、0を返す
        return 0;
    }

    else {
        count_comp += mrg_sort(array, N, from, mid - 1); //配列の長さが1より大きい場合、配列を二つに分け、再帰処理
        count_comp += mrg_sort(array, N, mid, to);

        count_comp += merge(array, N, from, mid, to); //二つに分けた配列をマージ

        return count_comp; //comp関数の呼び出し回数を返す
    }
}

int merge(int array[], int N, int from, int mid, int to) { //merge関数を定義
    int from_copy = from; //fromのコピーを作成。これは変動しない
    int mid_copy = mid; //midのコピーを作成。これは変動しない
    int point_merge = from; //マージ用記憶領域の場所を示す変数
    int count_comp = 0; //comp関数の呼び出し回数
    
    do {
        if (mid == to + 1) { //後方の配列の要素をすべてマージ用記憶領域に入れた場合
            for (; from <= mid - 1; from++, point_merge++) { //残りの前方の配列の要素をマージ用記憶領域に入れる
                copy(array, from, N + point_merge);
            }
        }
        
        else if (from == mid_copy) { //前方の配列の要素をすべてマージ用記憶領域に入れた場合
            for (; mid <= to; mid++, point_merge++){ //残りの後方の配列の要素をマージ用記憶領域に入れる
                copy(array, mid, N + point_merge);
            }
        }
        
        else if (comp(array, from, mid)) { //前方後方の配列の先頭の要素のうち、小さい方をマージ用記憶領域に入れる
            copy(array, from, N + point_merge);

            from++;
            point_merge++;
            count_comp++;
        }

        else {
            copy(array, mid, N + point_merge);

            mid++;
            point_merge++;
            count_comp++;
        }
    } while (point_merge <= to); //マージ用記憶領域が埋まらない限り、ループを続ける

    for (int i = from_copy; i <= to; i++) { //マージ用記憶領域の配列を元の領域にコピーする
        copy(array, N + i, i);
    }

    printf("MERG(%2d,%2d) : ", from_copy, to); //マージした範囲とその要素を出力
    print_array_range(array, N, from_copy, to);

    return count_comp; //comp関数の呼び出し回数を返す
}

int comp(int array[], int pos_a, int pos_b) { //comp関数を定義
    if (array[pos_a] < array[pos_b]) return 1; //位置aの要素が位置bの要素より小さい場合、1を返す 
    
    return 0; //そうでない場合、0を返す                                   
}

int* copy(int array[],int pos_a, int pos_b) { //copy関数を定義
    array[pos_b] = array[pos_a]; //位置aの要素を位置bの要素にコピーする
    
    return array; //配列を返す
}