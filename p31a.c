#include <stdio.h>

int main(){
  int a, b;
  int *p1, *p2;
  int **pp;

  // char, int, double型のバイト数の表示
  printf("sizeof(char)=%d, sizeof(int)=%d, sizeof(double)=%d\n", sizeof(char), sizeof(int), sizeof(double));


  // 10進数で変数a, bのアドレスを表示
  printf("\nAddresses:\n");
  printf("&a=%u, &b=%u\n", &a, &b);


  // aとbの初期値を入力
  scanf("%d %d", &a, &b);


  // NULLポインタで初期化
  p1 = (int *)NULL;
  p2 = (int *)NULL;
  pp = (int **)NULL;


  // 初期値を表示
  printf("\nInitial values:\n");
  printf("p1=%u, p2=%u\n", &*p1, &*p2); // ポインタ変数p1, p2の中身の表示
  printf("a=%d, b=%d\n", a, b);


  // 変数aのアドレスを取得して，ポインタ変数に格納する
  p1 = &a; 
  p2 = &b;
  
  printf("\nSubstitution of addresses into pointers:\n");
  printf("p1=%u, p2=%u\n", &*p1, &*p2); // ポインタ変数p1, p2の中身の表示
  printf("*p1=%d, *p2=%d\n", *p1, *p2); // p1, p2が指すアドレスにある変数の中身の表示
  printf("a=%d, b=%d\n", a, b);


  // ポインタを介してa, bに値を代入する
  *p1 = 10;
  *p2 = 20;

  printf("\nManipulation through pointers:\n");
  printf("p1=%u, p2=%u\n", &*p1, &*p2); // ポインタ変数p1, p2の中身の表示
  printf("*p1=%d, *p2=%d\n", *p1, *p2); // p1, p2が指すアドレスにある変数の中身の表示
  printf("a=%d, b=%d\n", a, b);


  // p2に格納されたアドレス（=b）をp1にコピーし、それを介してbの値を変える
  p1 = p2;
  *p1 = 30;

  printf("\nCopy of a pointer value to another pointer:\n");
  printf("p1=%u, p2=%u\n", &*p1, &*p2); // ポインタ変数p1, p2の中身の表示
  printf("*p1=%d, *p2=%d\n", *p1, *p2); // p1, p2が指すアドレスにある変数の中身の表示
  printf("a=%d, b=%d\n", a, b);


  // ポインタのポインタを介してa, bの値を変える
  p1 = &a;
  p2 = &b;

  printf("\nPointer-to-pointer:\n");

  pp = &p1; // p1のアドレスを代入
  **pp = 40; // ppが指すポインタが指すアドレスのある変数に40を代入
  printf("*pp=%u\n", &**pp);

  pp = &p2; // p2のアドレスを代入
  **pp = 50; // ppが指すポインタが指すアドレスのある変数に50を代入
  printf("*pp=%u\n", &**pp);

  printf("a=%d, b=%d\n", a, b);

  
  return 0;
}