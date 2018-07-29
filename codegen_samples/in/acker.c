int alpha(int n, int m){
  if(m == 0){
    return n+1;
  }

  if(n == 0){
    return alpha(1, m-1);
  }

  return alpha(alpha(n-1, m), m-1);
}

void solve(int x){
  println(alpha(x, x));
}

void main(void){
  solve(3);
  solve(1);
  solve(2);
}
