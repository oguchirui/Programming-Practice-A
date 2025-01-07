#include <stdio.h>

void pass_by_value(int x, int y);
void pass_by_address(int *ptr_x, int y);

int main(){
  int a, b;

  scanf("%d%d", &a, &b);

  // 値渡しをする関数の確認
  pass_by_value(a, b); // 変数aとbの値をpass_by_value関数に渡す
  printf("After pass_by_value: %d\n", a);
  printf("\n");

  // アドレス渡しをする関数の確認
  pass_by_address(&a, b); // 変数aのアドレスと変数bの値をpass_by_address関数に渡す
  printf("After pass_by_address: %d\n", a);

  return 0;
}

void pass_by_value(int x, int y){
  printf("In pass_by_value: before substitution: %d\n", x);
  x = y;
  printf("In pass_by_value: after substitution: %d\n", x);
}
void pass_by_address(int *ptr_x, int y){
  printf("In pass_by_address: before substitution: %d\n", *ptr_x);
  *ptr_x = y; // 渡されたアドレスにある変数にyを代入
  printf("In pass_by_address: after substitution: %d\n", *ptr_x);
}