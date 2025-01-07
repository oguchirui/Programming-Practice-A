#include <stdio.h>

void showbanmen(char masu[]); //必要な関数を宣言
int errorcheck(int n,char masu[]);
int wincheck(int counter,char masu[]);
int evencheck(char masu[]);

int main(void){
    int n; //入力値を格納する変数
    char masu[9]={'1','2','3','4','5','6','7','8','9'}; //マス内の文字を格納する配列
    int counter=0; //現在、先手のターンなのか後手のターンなのか判断する変数
    
    showbanmen(masu); //初期状態の盤面を表示

    for(;;){
        scanf("%d",&n);

        if(counter%2==0){ //先手の入力値を出力
            printf("o> %d\n",n);
        }

        else{ //後手の入力値を出力
            printf("x> %d\n",n);
        }

        if(errorcheck(n,masu)==0){ //入力値がエラーの場合、次のループへ
            continue;
        }

        counter+=1;

        if(counter%2==1){ //先手の入力値のマスにoを配置
            masu[n-1]='o';
        }

        else{ //後手の入力値のマスにxを配置
            masu[n-1]='x';
        }
        
        showbanmen(masu); //マスにo,xを置いた後の盤面を表示

        if(wincheck(counter,masu)==0){ //勝敗がついた場合、ループを抜ける
            break;
        }

        if(evencheck(masu)==0){ //引き分けとなった場合、ループを抜ける
            break;
        }
    }

    return 0;
}

void showbanmen(char masu[]){ //盤面を表示する関数を定義
    printf("%c|%c|%c\n",masu[6],masu[7],masu[8]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n",masu[3],masu[4],masu[5]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n",masu[0],masu[1],masu[2]);
}

int errorcheck(int n,char masu[]){ //入力値のエラーを見つける関数を定義
    if(n<1||9<n){ //1から9以外の整数が入力された場合、エラー
        printf("ERROR\n");

        return 0;
    }

    if(masu[n-1]=='o'||masu[n-1]=='x'){ //すでにo,xが置かれているマスが指定された場合、エラー
        printf("ERROR\n");

        return 0;
    }

    return 1; //以上に当てはまらなかった場合、1を返す
}

int wincheck(int counter,char masu[]){ //勝敗を判断する関数を定義
    char a; //o,xのどちらかを格納する変数
    
    if(counter%2==1){
        a='o';
    }

    else{
        a='x';
    }

    if(masu[0]==a&&masu[1]==a&&masu[2]==a){ //以下の3つは横一列で揃った場合、勝利
        printf("%c win!\n",a);

        return 0;
    }
    
    if(masu[3]==a&&masu[4]==a&&masu[5]==a){
        printf("%c win!\n",a);

        return 0;
    }

    if(masu[6]==a&&masu[7]==a&&masu[8]==a){
        printf("%c win!\n",a);

        return 0;
    }

    if(masu[0]==a&&masu[3]==a&&masu[6]==a){ //以下の3つは縦一列で揃った場合、勝利
        printf("%c win!\n",a);

        return 0;
    }

    if(masu[1]==a&&masu[4]==a&&masu[7]==a){
        printf("%c win!\n",a);

        return 0;
    }

    if(masu[2]==a&&masu[5]==a&&masu[8]==a){
        printf("%c win!\n",a);

        return 0;
    }

    if(masu[0]==a&&masu[4]==a&&masu[8]==a){ //以下の2つは斜め一列で揃った場合、勝利
        printf("%c win!\n",a);

        return 0;
    }

    if(masu[2]==a&&masu[4]==a&&masu[6]==a){
        printf("%c win!\n",a);

        return 0;
    }

    return 1; //以上に当てはまらなかった場合、1を返す
}

int evencheck(char masu[]){ //引き分けを判断する関数を定義
    for(int i=0;i<9;++i){
        if(masu[i]!='o'&&masu[i]!='x'){ //盤面にo,x以外の文字のマスが存在する場合、1を返す
            return 1;
        }
    }

    printf("even.\n"); //盤面がo,xのマスで埋め尽くされた場合、引き分け

    return 0;
}