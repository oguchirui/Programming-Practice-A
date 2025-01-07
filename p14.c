#include <stdio.h>

int main(){
    int i,count=0,sum=0;
    int num[60]={0};
    char str[61];
    fgets(str,62,stdin); 
    for(i=0;i<61;++i){
        if(str[i]=='\n'){ //文字列が途切れたら、ループを抜ける
            break;
        }
        ++count; //文字列の桁数をカウント
    }
    if(count==61){ //文字列の桁数が61を超えた場合、エラー
        printf("Too long!\n");
        return 1;
    }
    for(i=0;str[i]!='\n';++i){
        if(str[i]<'0'||'9'<str[i]){ //0〜9の整数以外があった場合、エラー
            printf("Not a number!\n");
            return 1;
        }
    }
    /*printf("%c",str[0]);  //最初の一文字を出力
    for(i=1;str[i]!='\n';++i){ //残りの文字を出力
        printf(" %c",str[i]);
    }
    printf("\n");*/
    for(i=0;str[i]!='\n';++i){
        num[i]=str[i]-'0'; //char型の配列をint型の配列に置き換える
    }
    for(;count>=0;count-=2){
        num[count-2]*=2; //文字列の右から数えて偶数番目の数字を2倍
        if(num[count-2]>9){ //2倍したものが10以上だった場合、9を引くことで10の位と1の位の和として計算
            num[count-2]-=9;
        }
    }
    for(i=0;i<60;++i){
        sum+=num[i]; //すべての桁の数字の総和を計算
    }
    if(sum%10==0){
        printf("true\n"); //総和が10で割り切れる場合、正しい
    }
    else{
        printf("false\n"); //総和が10で割り切れない場合、間違っている
    }
    return 0;
}