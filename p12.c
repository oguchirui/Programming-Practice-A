#include <stdio.h>

int main(){
    int x;
    scanf("%d",&x);
    if(2>x||x>100000){
        printf("Error\n");
        return 0;
    }
    for(int i=0;i<100;i++){
        printf("%d\n",x);
        if(x==1){
            printf("OK\n");
            break;
        }
        else if(x%2==0){
            x=x/2;
        }
        else{
            x=3*x+1;
        }
    }
    return 0;
}