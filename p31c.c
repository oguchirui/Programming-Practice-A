#include <stdio.h>
#include <stdlib.h>

/*
 * 文字列処理関数群の前方宣言
 */

void read_string(char *str, int N);
void zeros(char *str, int N);
int delta(char *X, int a, char *Y, int b);
void reverse(char *str, int N);

int main(){
  // 文字配列をVLAで確保
  int n;
  scanf("%d", &n);
  char str[n+2]; // read_stringでは文字列長+2が必要

  // 文字配列strの初期化
  zeros(str, n+2);

  // read_string関数の動作確認
  read_string(str, n);
  printf("read_string: \"%s\"\n", str);

  // delta関数の動作確認
  char test_str[5] = "test";

  printf("\ndelta:\n");

  printf("  ");
  for(int i=0; i<4; i++){
    if( i != 0 ) printf(" ");
    printf("%c", test_str[i]);
  }
  printf("\n");

  for(int j=0; j<n; j++){  
    printf("%c", str[j]);

    for(int i=0; i<4; i++){
      printf(" %d", delta(str, j, test_str, i)); // 入力された文字列とtest_strを一文字ずつ比較
    }

    printf("\n");
  }


  // reverse関数の動作確認
  reverse(str, n); // 入力された文字列を逆順にする
  printf("\nreverse: \"%s\"\n", str);

  return 0;
}


/*
 * 文字列処理関数群の後方定義
 */

void read_string(char *str, int N){
  char tmpchar; // 文字列前の空白・改行を除外するために使う

  // 文字列の前に空白か改行があれば全て除外する
  do {
    tmpchar = getc(stdin);
    if( tmpchar == EOF ){ // 途中で読み込みが終了したらエラー終了
      printf("read_string(): Invalid string\n");
      exit(1);
    }
  }while( tmpchar==' ' || tmpchar=='\n' || tmpchar=='\r');

  ungetc(tmpchar, stdin); // 文字列を一文字stdinに戻す

  // N+1文字を標準入力から読み込む
  fgets(str, N+2, stdin); // p14のfgetsの使い方を参照
  ungetc(str[N], stdin); // 次の入力に影響しないよう，余計な空白・改行を１文字戻す

  // 文字列の長さがNよりも短い場合はエラー出力して強制終了
  for(int i=0; i<N; i++){
    if(str[i]=='\n' || str[i]=='\0' || str[i]=='\r'){ // 文字列中に改行・ヌル文字があれば長さが足りていない（※Windowsでは\r\nで改行を表す）
      fprintf(stderr, "read_string(): Invalid string\n");
      exit(1);
    }
  }
    
  // 文字列の長さがNよりも長い場合はエラー出力して強制終了
  if( !(str[N]=='\n' || str[N]=='\0' || str[N]=='\r') ){ // 長さがNの場合、N+1文字目は空白 or 改行 or ヌル文字であるはず
    fprintf(stderr, "read_string(): Invalid string\n");
    exit(1);
  }

  // fgetsで改行かスペースも読み込んでいる場合があるので，ヌル文字で上書き
  str[N] = '\0';
}

void zeros(char *str, int N){
  for(int i=0; i<N; i++){ //文字配列の要素N個全てをヌル文字で初期化
    str[i] = '\0';
  }
}

int delta(char *X, int a, char *Y, int b){
  if(X[a] == Y[b]){ //文字列Xのa番目と文字列Yのb番目が同じであれば1を返す
    return 1;
  }

  else{ //異なれば0を返す
    return 0;
  }
}

void reverse(char *str, int N){
  int length=0; 

  for(int i=0; str[i]!='\0' ;++i){ //文字列strの長さを記録
    ++length;
  }

  char copy[length]; //文字列strと同じ長さの配列を作成

  for(int i=0; i<length; ++i){ //文字列strを一旦別の配列に移す
    copy[i] = str[i]; 
  }

  for(int i=0; i<length; ++i){ //移した文字列を逆順にして配列strに戻す
    str[length-1-i] = copy[i];
  }
}