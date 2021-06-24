## RSA 加密系统  
函数  
``
struct rsa{  
  unsigned long long int public_key[2];  
  unsigned long long int private_key[2];  
  unsigned long long int value;  
};  
void createKey(struct rsa *);  
``
向createKey函数传递一个指向结构体rsa的指针，即可生成公钥和秘钥  
  
  
``
void encode_rsa(unsigned long long int * val,unsigned long long int * public_key);  
``
向函数encode_rsa传递下列参数用于加密  
1. 你要加密的值（无符号长长整数）    val  
2. 你的公钥（无符号长长整数数组指针）  public_key  
无返回值，会修改指针val的值  

``
void decode_rsa(unsigned long long int * val,unsigned long long int * private_key);  
``
同理，向函数decode_rsa传递下列参数用于解密  
第二个参数是你的密钥（无符号长长整数数组指针）private_key  
  
    
      
代码范例
``
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
``
