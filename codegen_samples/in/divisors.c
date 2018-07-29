int mod(int x, int MOD){
  int q;
  q = x/MOD;
  return x-q*MOD;
}

void solve(int x){
  int i;
  i = 1;
  while(i*i <= x){
    if(mod(x, i) == 0){
      println(i);
      if(i*i != x){
        println(x/i);
      }
    }

    i = i+1;
  }

  println(0-1);
}

void main(void){
  solve(8);
  solve(81);
  solve(47);
  solve(42);
  solve(56);
}
