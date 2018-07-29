int fibonacci(int n) {
  int a;
  int b;
  int x;
  int i;
  a = 1;
  b = 1;
  i = 3;
  if(n <= 2) {
    return a;
  }

  while(i <= n) {
    a = b;
    b = a + b;
    i = i + 1;
  }

  return b;
}

void main(void) {
  int x;
  x = fibonacci(8);
  println(x);
}