int fat(int n) {
    if (n <= 0) {
        return 1;
    }
    return n * fat(n - 1);
}

int main(void) {
  int x;
  x = fat(5);
  println(x);
}
