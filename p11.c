#include <stdio.h>

int main(){
    int a,b;
    int wa,sa;
    int A,B;
    scanf("%d %d",&a,&b);
    wa=a+b;
    sa=a-b;
    A=(a+b)/2;
    B=(b-a)/2;
    if(-100>=a||a>=b||b>=100){
        printf("ERROR\n");
        return 0;
    }
    else if(wa%2!=0||sa%2!=0){
        printf("ERROR\n");
        return 0;
    }
    else{
        printf("%d %d\n",A,B);
    }
    return 0;
}