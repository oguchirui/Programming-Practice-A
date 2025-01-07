#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double v, double g, double a, double b); //必要な関数を宣言
void euler_method(double *v, double h, int n, double a, double b, double g);
void rk2_method(double *v, double h, int n, double a, double b, double g);
void rk4_method(double *v, double h, int n, double a, double b, double g);

int main(void){
    double a, b, te;
    int n;

    scanf("%lf %lf %lf %d", &a, &b, &te, &n); //α, β, te, nを入力

    double *v_euler = (double *)malloc((n + 1) * sizeof(double)); //それぞれの解法の値を格納する配列に動的メモリ確保
    double *v_rk2 = (double *)malloc((n + 1) * sizeof(double));
    double *v_rk4 = (double *)malloc((n + 1) * sizeof(double));

    v_euler[0] = 0.0; //速度の初期値を指定
    v_rk2[0] = 0.0;
    v_rk4[0] = 0.0;

    double g = 9.80665; //重力加速度、区間数を指定
    double h = te / n;

    euler_method(v_euler, h, n, a, b, g); //それぞれの開放で値を求める
    rk2_method(v_rk2, h, n, a, b, g);
    rk4_method(v_rk4, h, n, a, b, g);

    for(int i = 0; i < n + 1; ++i){ //値を出力する
        printf("%.2f %.2f %.2f %.2f\n", i * h, v_euler[i], v_rk2[i], v_rk4[i]);
    }

    free(v_euler); //動的メモリを開放
    free(v_rk2);
    free(v_rk4);

    return 0;
}

double func(double v, double g, double a, double b){ //微分方程式の右辺の関数を定義
    return -g - a * v - b * v * fabs(v);
}

void euler_method(double *v, double h, int n, double a, double b, double g){ //オイラー法の関数を定義
    
    for(int i = 1; i <= n; ++i){
        v[i] = v[i-1] + h * func(v[i-1], g, a, b);
    }
}

void rk2_method(double *v, double h, int n, double a, double b, double g){ //2次のルンゲ・クッタ法の関数を定義
    for(int i = 1; i <= n; ++i){
        double k1 = h * func(v[i-1], g, a, b);
        double k2 = h * func(v[i-1] + 0.5 * k1, g, a, b);
        
        v[i] = v[i-1] + k2;
    }
}

void rk4_method(double *v, double h, int n, double a, double b, double g){ //4次のルンゲ・クッタ法の関数を定義
    for(int i = 1; i <= n; ++i){
        double k1 = h * func(v[i-1], g, a, b);
        double k2 = h * func(v[i-1] + 0.5 * k1, g, a, b);
        double k3 = h * func(v[i-1] + 0.5 * k2, g, a, b);
        double k4 = h * func(v[i-1] + k3, g, a, b);
        
        v[i] = v[i-1] + (k1 + 2*k2 + 2*k3 + k4) / 6.0;
    }
}