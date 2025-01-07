#include <stdio.h>

double SMA(double x[],int t,int M); //必要な関数を宣言
double WMA(double x[],int t,int M);

int main(void){
    int N,Ms,Ml;

    scanf("%d%d%d",&N,&Ms,&Ml); //データ数、短期日数、長期日数を読み込む

    double data[N];

    for(int i=0;i<N;++i){
        scanf("%lf",&data[i]); //データを読み込む
    }

    /*for(int i=0;i<N;++i){
        printf("%d ",i+1); //日付を出力
        
        printf("%.2lf ",data[i]); //その日のデータを出力

        if(i+1<Ms){
            printf("NA "); //その日付に対応する移動平均が存在しない時、NAを出力
        }
        else{
            printf("%.2lf ",SMA(data,i,Ms)); //短期日数の単純移動平均を出力
        }
        
        if(i+1<Ml){
            printf("NA "); //その日付に対応する移動平均が存在しない時、NAを出力
        }
        else{
            printf("%.2lf ",SMA(data,i,Ml)); //長期日数の単純移動平均を出力
        }

        if(i+1<Ms){
            printf("NA "); //その日付に対応する移動平均が存在しない時、NAを出力
        }
        else{
            printf("%.2lf ",WMA(data,i,Ms)); //短期日数の加重移動平均を出力
        }

        if(i+1<Ml){
            printf("NA\n"); //その日付に対応する移動平均が存在しない時、NAを出力
        }
        else{
            printf("%.2lf\n",WMA(data,i,Ml)); //長期日数の加重移動平均を出力
        }
    }*/

    for(int i=Ml-1;i<N-1;++i){ //長期日数の移動平均が計算できる日付のデータから始める
        if(SMA(data,i,Ms)<SMA(data,i,Ml)&&SMA(data,i+1,Ms)>SMA(data,i+1,Ml)){ //単純移動平均でのゴールデンクロスを出力
            printf("Golden cross with SMA found:\n");
            
            printf("SMA^{(%d)}_(%d)=%.2lf < SMA^{(%d)}_(%d)=%.2lf\n",Ms,i+1,SMA(data,i,Ms),Ml,i+1,SMA(data,i,Ml));
            printf("SMA^{(%d)}_(%d)=%.2lf > SMA^{(%d)}_(%d)=%.2lf\n",Ms,i+2,SMA(data,i+1,Ms),Ml,i+2,SMA(data,i+1,Ml));
        }

        if(SMA(data,i,Ms)>SMA(data,i,Ml)&&SMA(data,i+1,Ms)<SMA(data,i+1,Ml)){ //単純移動平均でのデッドクロスを出力
            printf("Dead cross with SMA found:\n");

            printf("SMA^{(%d)}_(%d)=%.2lf > SMA^{(%d)}_(%d)=%.2lf\n",Ms,i+1,SMA(data,i,Ms),Ml,i+1,SMA(data,i,Ml));
            printf("SMA^{(%d)}_(%d)=%.2lf < SMA^{(%d)}_(%d)=%.2lf\n",Ms,i+2,SMA(data,i+1,Ms),Ml,i+2,SMA(data,i+1,Ml));
        }

        if(WMA(data,i,Ms)<WMA(data,i,Ml)&&WMA(data,i+1,Ms)>WMA(data,i+1,Ml)){ //多重移動平均でのゴールデンクロスを出力
            printf("Golden cross with WMA found:\n");

            printf("WMA^{(%d)}_(%d)=%.2lf < WMA^{(%d)}_(%d)=%.2lf\n",Ms,i+1,WMA(data,i,Ms),Ml,i+1,WMA(data,i,Ml));
            printf("WMA^{(%d)}_(%d)=%.2lf > WMA^{(%d)}_(%d)=%.2lf\n",Ms,i+2,WMA(data,i+1,Ms),Ml,i+2,WMA(data,i+1,Ml));
        }

        if(WMA(data,i,Ms)>WMA(data,i,Ml)&&WMA(data,i+1,Ms)<WMA(data,i+1,Ml)){ //多重移動平均でのデッドクロスを出力
            printf("Dead cross with WMA found:\n");

            printf("WMA^{(%d)}_(%d)=%.2lf > WMA^{(%d)}_(%d)=%.2lf\n",Ms,i+1,WMA(data,i,Ms),Ml,i+1,WMA(data,i,Ml));
            printf("WMA^{(%d)}_(%d)=%.2lf < WMA^{(%d)}_(%d)=%.2lf\n",Ms,i+2,WMA(data,i+1,Ms),Ml,i+2,WMA(data,i+1,Ml));
        }
    }

    return 0;
}

double SMA(double x[],int t,int M){ //単純移動平均を計算する関数を定義
    double sum=0.0;

    for(int i=0;i<M;++i){ //日付tからそのM-1日前までのデータを足し合わせる
        sum+=x[t];
        --t;
    }

    return sum/M; //単純移動平均を返す
}

double WMA(double x[],int t,int M){ //加重移動平均を計算する関数を定義
    double sum=0.0;
    int Mcopy=M; //McopyにMの値をコピーする

    for(int i=0;i<M;++i){ //日付tからそのM-1日前までのデータを足し合わせる（それぞれのデータにM,M-1,...をそれぞれ掛けている）
        sum+=Mcopy*x[t];
        --Mcopy;
        --t;
    }
    
    int bunbo=0;
    Mcopy=M; //再びMcopyにMの値をコピーする

    for(int i=0;i<M;++i){ //分母を計算する（M,M-1,...を足し合わせる）
        bunbo+=Mcopy;
        --Mcopy;
    }

    return sum/bunbo; //加重移動平均を返す
}