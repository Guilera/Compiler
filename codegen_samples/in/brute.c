int K;
int n;
int lo;
int hi;

int brute(int last, int len){
  int i;
  int res;
  if(len == n){
    return 1;
  }

  i = last-K;
  while(i <= last+K){
    if(i >= lo){
      if(i <= hi) {
        res = res + brute(i, len+1);
      }
    }
    i = i+1;
  }
  return res;
}

void solve(int a, int b, int c, int d){
  int res;
  int i;

  n = a;
  K = b;
  lo = c;
  hi = d;

  i = lo;
  while(i <= hi){
    res = res + brute(i, 1);
    i = i+1;
  }

  println(res);
}

void main(void){
  solve(5, 2, 17, 22);
  solve(3, 3, 42, 56);
  solve(8, 1, 3, 8);
  solve(2, 10, 99, 119);
}
