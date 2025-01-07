#include <stdio.h>

int GCD(int a,int b); //関数GCDを宣言

int main(void){
    int a,b,c; //cはa,bを入れ替える際にaの数値を一時保存する変数

    scanf("%d",&a);
    scanf("%d",&b); 

    printf("INIT::::::::::: %d, %d\n",a,b);

    if(a<=b){ //入力されたbがaより大きかった場合、a,bを入れ替える
        c=a;
        a=b;
        b=c;
    }

    printf("%d\n",GCD(a,b)); //関数GCDを出力

    return 0;
}

int GCD(int a,int b){ //関数GCDを定義
    int r; //あまり
    
    r=a%b;
    
    printf("GCD(%4d, %4d) r = %d\n",a,b,r);
    
    if(r==0){ //あまりが0の場合、bを返り値として関数の処理を終了
        printf("DONE:::::::::::\n");

        return b;
    }
    
    a=b;
    b=r; //あまりが0でない場合、aをb、bをrとして関数の処理を再び行う
    
    return GCD(a,b); 
}