int MX;

void solve(int x){
  int l;
  int r;
  r = MX;
  l = 0;
  while(l < r){
    int mid;
    mid = (l+r)/2;
    if(mid*(mid+1)/2 >= x){
      r = mid;
    } else {
      l = mid+1;
    }
  }

  println(l);
}

void main(void){
  int i;
  i = 1;
  while(i*i < 1000000000){
    i = i+1;
  }

  MX = i;

  solve(42);
  solve(109092190);
  solve(999999999);
  solve(80475327);
  solve(424242424);
  solve(24242424);
  solve(199999289);
}
