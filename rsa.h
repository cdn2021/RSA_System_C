#include <math.h>
#include <time.h>
struct rsa{
  unsigned long long int public_key[2];
  unsigned long long int private_key[2];
  unsigned long long int value;  
};
_Bool encode_rsa(unsigned long long int *,unsigned long long int *);
_Bool decode_rsa(unsigned long long int *,unsigned long long int *);
int createKey(struct rsa *);
int checkPrime(unsigned long long int);
int getGCD(unsigned long long int ,unsigned long long int );
void swap(unsigned long long int * ,unsigned long long int *);


_Bool encode_rsa(unsigned long long int * val,unsigned long long int * public_key) { 
    unsigned long long int x = 1;
    unsigned long long int i = 0;
    while (i < public_key[0]) {
      x *= (*val);
      x %= public_key[1];
      i++;
    };
  *val = x;
    return true;  
};
_Bool decode_rsa(unsigned long long int * val,unsigned long long int * private_key) { 
    unsigned long long int x = 1;
    unsigned long long int i = 0;
    while (i < private_key[0]) {
      x *= (*val);
      x %= private_key[1];
      i++;
    };
  *val = x;
    return true;  
};
int checkPrime(unsigned long long int n){
    if (n < 2)
      return 0;
    if (n == 2)
      return 1;
    unsigned long long int root = (unsigned long long int)sqrt(n);
  //得到n的平方根
    unsigned long long int i = 2;
  //从2开始遍历，到i为止
    while (i < root) {
     if (!(n % i))
       return 0;
    //n对i取余，如果值为0,（合数），那n就不是素数
    i++;
    };
  return 1;
  //n是素数
};

int getGCD(unsigned long long int a,unsigned long long int b) {
  if (a == b)
    return a;
  return getGCD(b,a % b);
};
void swap(unsigned long long int * v,unsigned long long int * w) {
  //交换v和w的值
  unsigned long long int tmp = *v;
  *v = *w;
  *w = tmp;
};
int createKey(struct rsa * res){
  unsigned long int p,q;
  p = (unsigned long int)time(NULL);
  while(!checkPrime(p))
    p = (unsigned long int)time(NULL);
  q = (unsigned long int)time(NULL);
  while(!checkPrime(q))
    q = (unsigned long int)time(NULL);
  //取得两个随机的大素数p,q
  unsigned long int n;
  n = p * q;
  //计算 n = p * q
  unsigned long long int uN;
  uN = (p - 1) * (q - 1);
  //计算uN = (p-1) * (q-1) 
  int e = 3;
  while (getGCD(uN,e) != 1)
    e += 2;
  //计算出与uN互素的小奇数e
  unsigned long long int k = 1;
  while ((k * uN + 1) % e)
    k++;
  unsigned long long int d = (k * uN + 1) / e;
  res->public_key[0] = e;
  res->public_key[1] = n;
  res->private_key[0] = d;
  res->private_key[1] = n;
  return 1;
};
