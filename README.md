## RSA 加密系统  
函数  
```c
struct rsa{  
  unsigned long long int public_key[2];  
  unsigned long long int private_key[2];  
  unsigned long long int value;  
};  
void createKey(struct rsa *);  
```
向createKey函数传递一个指向结构体rsa的指针，即可生成公钥和秘钥  
  
  
```c
void encode_rsa(unsigned long long int * val,unsigned long long int * public_key);  
```
向函数encode_rsa传递下列参数用于加密  
1. 你要加密的值（无符号长长整数）    val  
2. 你的公钥（无符号长长整数数组指针）  public_key  
无返回值，会修改指针val的值  

```c
void decode_rsa(unsigned long long int * val,unsigned long long int * private_key);  
```
同理，向函数decode_rsa传递下列参数用于解密  
第二个参数是你的密钥（无符号长长整数数组指针）private_key  
  
    
      
代码范例  
```c
#include "rsa.h"  
#include <stdlib.h> // malloc,free函数原型  
int main(void){  
  struct rsa * val;  
  val = (struct rsa * val)malloc(sizeof(struct rsa));//申请结构体rsa空间  
  createKey(val);  
  //生成公钥和私钥  
  //作为例子，我们选用较小的数字来演示RSA公钥加密系统的工作原理  
  /*  
        1. 选取素数p=17和q=29  
        2. 计算n = pq = 493  
        3. 计算uN = (p-1)(q-1) = 448  
        4. 选取e=5，它和uN=448互素  
        5. 计算得出d=269  
        6. 得出，我的RSA公钥为P=public_key={5,493};  
                我的RSA私钥为S=private_key={269,493};  
   */  
   unsigned long long int * n;  
   *n = 327;  
   encode_rsa(n,val->public_key);//传入n=327,public_key={5,493}  
   //此时n=327^5 mod 493 = 3738856210407 mod 493 = 259  
   //n = 259  
   decode_rsa(n,val->private_key); //传入n=259,private_key={269,493}  
   //此时n=259^269 mod 493 = 327  
   return *n;  
     
};  
```
  
LeetCode 项目地址 [Click me](https://leetcode-cn.com/playground/eehdAAXi/shared)  
GitHub 项目地址 [Click me](https://github.com/cdn2021/RSA_System_C)  
  
    
  
  
源代码  
```c   
  
#include <math.h>
#include <time.h>
struct rsa{
  unsigned long long int public_key[2];
  unsigned long long int private_key[2];
  unsigned long long int value;  
};
void encode_rsa(unsigned long long int *,unsigned long long int *);
void decode_rsa(unsigned long long int *,unsigned long long int *);
void createKey(struct rsa *);
_Bool checkPrime(unsigned long long int);
int getGCD(unsigned long long int ,unsigned long long int );

void encode_rsa(unsigned long long int * val,unsigned long long int * public_key) { 
    unsigned long long int x = 1;
    unsigned long long int i = 0;
    while (i < public_key[0]) {
      x *= (*val);
      x %= public_key[1];
      i++;
    };
  *val = x;
    return;
};
void decode_rsa(unsigned long long int * val,unsigned long long int * private_key) { 
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
_Bool checkPrime(unsigned long long int n){
    if (n < 2)
      return false;
    if (n == 2)
      return true;
    unsigned long long int root = (unsigned long long int)sqrt(n);
  //得到n的平方根
    unsigned long long int i = 2;
  //从2开始遍历，到i为止
    while (i < root) {
     if (!(n % i))
       return false;
    //n对i取余，如果值为0,（合数），那n就不是素数
    i++;
    };
  return true;
  //n是素数
};

int getGCD(unsigned long long int a,unsigned long long int b) {
  if (a == b)
    return a;
  return getGCD(b,a % b);
};
void createKey(struct rsa * res){
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
  return;
};
```
