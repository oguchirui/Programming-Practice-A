#include <stdio.h>

void print_array(int array[],int N); //必要な関数を宣言
int find_min(int array[],int N);
void swap(int array[],int x, int y);

int main(void){
    int N,minindex; //変数minindexは最小要素インデックスを格納するためのもの

    scanf("%d",&N);

    int data[N];

    for(int i=0;i<N;++i){ //配列の要素を読み込む
        scanf("%d",&data[i]);
    }

    print_array(data,N); //読み込んだ配列の要素を出力

    minindex=find_min(data,N); //最小要素を見つけ、そのインデックスを格納

    swap(data,0,minindex); //最小要素と先頭の要素を入れ替える

    print_array(data,N); //処理した配列の要素を出力

    return 0;
}

void print_array(int array[],int N){ //配列を出力する関数を定義
    for(int i=0;i<N;++i){ //配列のN個の要素を出力
        printf("%4d, ",array[i]);
    }

    printf("\n");
}

int find_min(int array[],int N){ //最小要素を見つける関数を定義
    int min,minindex=0;

    min=array[0]; //最初は先頭の要素が最小要素

    for(int i=1;i<N;++i){ //次の要素と比較して、次の要素の方が小さかったら、最小要素を更新
        if(array[i]<min){
            min=array[i];
            minindex=i; //最小要素インデックスを記録
        }
        
        printf("comp = %d, minValue = %d, minIndex = %d\n",i,min,minindex);
    }

    return minindex; //最小要素インデックスを返す
}

void swap(int array[],int x, int y){ //任意の二つの要素を入れ替える関数を定義
    int temp; //要素を一時保存する変数

    temp=array[x];
    array[x]=array[y];
    array[y]=temp; ///任意の二つの要素を入れ替える
}