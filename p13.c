#include <stdio.h>

int main(){
    int n,i;
    double max=-20,min=100;
    double sum=0;
    scanf("%d",&n);
    double a[n];
    for(i=0;i<n;i++){
        scanf("%lf",&a[i]);
        if(-20>=a[i]||a[i]>=100){
            printf("Out of Range\n");
            return 0;
        }
        if(a[i]>max){
            max=a[i];
        }
        if(a[i]<min){
            min=a[i];
        }
    }
    for(i=0;i<n;i++){
        sum+=a[i];
    }
    printf("%.2f\n",(sum-(max+min))/((double)n-2));
    return 0;
}