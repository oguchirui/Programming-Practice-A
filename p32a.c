#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/Vector.h"

struct Vector Vector_alloc(int n); //必要な関数を宣言
void Vector_free(struct Vector v);
int Vector_get_at(struct Vector v,int i);
void Vector_set_at(struct Vector v,int i,int x);
void Vector_print(struct Vector v);
struct Vector Vector_insert_at(struct Vector v,int i,int x);
struct Vector Vector_delete_at(struct Vector v,int i);
struct Vector Vector_deep_copy(struct Vector v);

int main(void){
    test_Vector(); //テスト関数を呼び出す

    return 0;
}

struct Vector Vector_alloc(int n){ //動的メモリを確保する関数を定義
    struct Vector v;

    v._array=(int*)malloc(sizeof(int)*n); //メモリを動的確保

    v._len=n; //配列の長さを記録

    if(v._array==(int*)NULL){ //確保失敗時のエラー処理
        fprintf(stderr,"Vector_alloc(): Cannot allocate memory\n");
        exit(1);
    }

    return v; //構造体を返す
}

void Vector_free(struct Vector v){ //動的メモリを開放する関数を定義
    free(v._array);
}

int Vector_get_at(struct Vector v,int i){ //配列要素を取得する関数を定義
    if(i<0||i>=v._len){
        fprintf(stderr,"Vector_get_at(): Index out of range\n"); //インデックスが有効な範囲の外にある場合、エラー
        exit(1);
    }

    return v._array[i]; //配列の要素を返す
}

void Vector_set_at(struct Vector v,int i,int x){ //配列要素を代入する関数を定義
    if(i<0||i>=v._len){
        fprintf(stderr,"Vector_set_at(): Index out of range\n"); //インデックスが有効な範囲の外にある場合、エラー
        exit(1);
    }

    v._array[i]=x; //配列の要素に値を代入
}

void Vector_print(struct Vector v){ //配列要素を出力する関数を定義
    if(v._len==0){
        printf("\n"); //配列の長さが0の場合、改行文字のみ出力
        return;
    }

    for(int i=0;i<v._len-1;++i){
        printf("%d ",v._array[i]); //配列要素を出力
    }

    printf("%d\n",v._array[v._len-1]);
}

struct Vector Vector_insert_at(struct Vector v,int i,int x){ //配列要素を挿入する関数を定義
    if(i<0||i>v._len){
        fprintf(stderr,"Vector_insert_at(): Index out of range\n"); //インデックスが有効な範囲の外にある場合、エラー
        exit(1);
    }

    struct Vector v_insert; //新たに構造体を作る

    v_insert=Vector_alloc(v._len+1); //新たに作った構造体に、引数の構造体より長さを1増やしてメモリを動的確保

    for(int j=0;j<i;++j){
        v_insert._array[j]=Vector_deep_copy(v)._array[j]; //新たに作った構造体の配列に要素を入れる
    }

    v_insert._array[i]=x;

    for(int j=i+1;j<v_insert._len;++j){
        v_insert._array[j]=Vector_deep_copy(v)._array[j-1];
    }

    Vector_free(v); //引数の構造体の動的メモリを開放

    return v_insert; //新たに作った構造体を返す
}

struct Vector Vector_delete_at(struct Vector v,int i){ //配列要素を削除する関数を定義
    if(i<0||i>=v._len||v._len==0){
        fprintf(stderr,"Vector_delete_at(): Index out of range\n"); //インデックスが有効な範囲の外にある場合、エラー
        exit(1);
    }

    struct Vector v_delete; //新たに構造体を作る

    v_delete=Vector_alloc(v._len-1); //新たに作った構造体に、引数の構造体より長さを1減らしてメモリを動的確保

    for(int j=0;j<i;++j){
        v_delete._array[j]=Vector_deep_copy(v)._array[j]; //新たに作った構造体の配列に要素を入れる
    }

    for(int j=i;j<v_delete._len;++j){
        v_delete._array[j]=Vector_deep_copy(v)._array[j+1];
    }

    Vector_free(v); //引数の構造体の動的メモリを開放

    return v_delete; //新たに作った構造体を返す
}

struct Vector Vector_deep_copy(struct Vector v){ //深いコピーを実行する関数を定義
    struct Vector v_copy; //コピー先の構造体を作る
    
    v_copy=Vector_alloc(v._len); //コピー先の構造体に、引数の構造体の長さ分メモリを動的確保

    for(int i=0;i<v._len;++i){
        Vector_set_at(v_copy,i,Vector_get_at(v,i)); //コピー先の構造体の配列要素に引数の構造体の配列要素を入れる
    }
    
    return v_copy; //コピー先の構造体を返す
}