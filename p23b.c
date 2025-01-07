//////////////////////////////////////////////////////
//  東北大学　プログラミング演習A           
//  問題 p23b 用のエラーを含む初期コードです。         
//   この初期コードを修正し問題を解いてください。   
//////////////////////////////////////////////////////

#include <stdio.h>

int main() {
    int N, M;
    scanf("%d%d", &M, &N);                                    //年齢と番号の数を標準入力から受け取る

    int yourNumber[N];                                        //入力の当選番号用の可変長配列
    int winningNumber[5] = {10,23,44,45,21};                  //１等賞の番号を記憶するための配列
    int barcode[12];                                          //バーコード保存用の配列
    int minAge = 10;                                          //入力者の最小年齢

    if(M < minAge) {                                          //年齢チェック
        printf("You are not eligible\n");
    }
    else if(N != 5) {                                         //当選番号の数が異なる
        printf("Ticket not found\n");
    }
    else {                           
        int match = 1;

        for(int i=0; i<N; i++) {                                //当選番号を標準入力から受け取る
            scanf("%d", &yourNumber[i]);
        }

        for(int i=0; i<5; i++) {                                //当選番号と１等賞番号の比較
            if(yourNumber[i] != winningNumber[i]) {
                match = 0;
                break;
            }
        }

        for(int i=0; i<12; i++){
            scanf("%d", &barcode[i]);                           //バーコードを標準入力から受け取る
        }
        printf("=== Enshu Loto Jumbo 2023 ===\n");
        printf("Winning numbers : ");
        for(int i=0; i<5; i++){
            printf("%d ", winningNumber[i]);                   //１等賞番号の出力
        }
        printf("\n");
        printf("-----------------------------\n");

        printf("Your barcode : ");
        for(int i=0; i<11; i++){
            printf("%d-", barcode[i]);                         //バーコードの出力
        }
        printf("%d\n", barcode[11]);

        if(match == 1) {                                        //一致する場合の判定
            printf("You won 1,000,000,000\n");
        }
        else {                                                  //不一致の場合の判定
            printf("You lose\n");
        }
    }

    return 0;
}