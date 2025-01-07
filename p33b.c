#include <stdio.h>
#include <math.h>

double f1(double x); //必要な関数を宣言
double f2(double x);
double f3(double x);
double f4(double x);
double F1(double x);
double F2(double x);
double F3(double x);
double F4(double x);
double integral_trapezoid(double (*f)(double x),double a,double b,int n);

int main(void){
    int i; //数学関数を指定する番号
    double a,b; //積分範囲[a,b]
    int n; //積分範囲の分割数
    double (*fp)(double),(*F)(double); //数学関数の先頭アドレスを格納する関数ポインタ
    
    scanf("%d%lf%lf%d",&i,&a,&b,&n); //i,a,b,nを読み込む

    if(i==1){ //入力された番号に従って、関数ポインタfpにf1,f2,f3,f4いずれかのアドレス、関数ポインタFにF1,F2,F3,F4いずれかのアドレスを代入
        fp=f1;
        F=F1;
    }

    if(i==2){
        fp=f2;
        F=F2;
    }

    if(i==3){
        fp=f3;
        F=F3;
    }

    if(i==4){
        fp=f4;
        F=F4;
    }

    printf("%.3f %.3f\n",F(b)-F(a),integral_trapezoid(fp,a,b,n)); //不定積分関数から求めた定積分、台形則の関数から求めた定積分の結果を出力

    /*double h=(b-a)/n; //範囲[a,b]をn等分する

    for(double x=a;x<b+0.01*h;x+=h){ //各区分の端の点における関数の値を出力
        printf("%.3f %.3f\n",x,fp(x));
    }*/

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

double F1(double x){ //F1を定義
    return x;
}

double F2(double x){ //F2を定義
    return x+x*x-((double)1/(double)3)*x*x*x;
}

double F3(double x){ //F3を定義
    return -cos(x);
}

double F4(double x){ //F4を定義
    return -((double)1/(double)4)*exp(-2*x*x);
}

double integral_trapezoid(double (*f)(double x),double a,double b,int n){ //台形則の関数を定義
    double h=(b-a)/n; //範囲[a,b]をn等分する
    double S=0; //台形を足し合わせた面積

    S+=h*((double)1/(double)2)*f(a); //第1項の計算
    
    for(double x=a+h;x<b-h+0.01*h;x+=h){ //第2~n-1項の計算
        S+=h*f(x);
    }

    S+=h*((double)1/(double)2)*f(b); //第n項の計算

    return S;
}