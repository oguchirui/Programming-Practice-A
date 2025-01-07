#include <stdio.h>
#include <math.h>

double f1(double x); //必要な関数を宣言
double f2(double x);
double f3(double x);
double f4(double x);

int main(void){
    int i; //数学関数を指定する番号
    double a,b; //積分範囲[a,b]
    int n; //積分範囲の分割数
    double (*fp)(double); //数学関数の先頭アドレスを格納する関数ポインタ
    
    scanf("%d%lf%lf%d",&i,&a,&b,&n); //i,a,b,nを読み込む

    if(i==1){ //入力された番号に従って、関数ポインタfpにf1,f2,f3,f4いずれかのアドレスを代入
        fp=f1;
    }

    if(i==2){
        fp=f2;
    }

    if(i==3){
        fp=f3;
    }

    if(i==4){
        fp=f4;
    }

    double h=(b-a)/n; //範囲[a,b]をn等分する

    for(double x=a;x<b+0.01*h;x+=h){ //各区分の端の点における関数の値を出力
        printf("%.3f %.3f\n",x,fp(x));
    }

    return 0;
}

double f1(double x){ //f1を定義
    return 1;
}

double f2(double x){ //f2を定義
    return 1+2*x-x*x;
}

double f3(double x){ //f3を定義
    return sin(x);
}

double f4(double x){ //f4を定義
    return x*exp(-2*x*x);
}