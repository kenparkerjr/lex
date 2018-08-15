#include <string>

#define cmp      0x0001
#define jmp_eq   0x0002
#define jmp_neq  0x0003
#define jmp_lt   0x0004
#define jmp_gt   0x0005
#define jmp_lte  0x0006
#define jmp_gte  0x0007
#define addi     0x0101  
#define subi     0x0102
#define divi     0x0103
#define inci     0x0104
#define deci     0x0105
#define ori      0x0106
#define xori     0x0107
#define modi     0x0108
   
  
#define pushi    0x0109

#define puti     0x0501
#define geti     0x0502
  
#define stp     0x0999
 

int CommandFromName(string s)
{
  if(s == "cmp")     return cmp;
  if(s == "jmp_eq")  return jmp_eq;
  if(s == "jmp_neq") return jmp_neq;
  if(s == "jmp_lt")  return jmp_lt;
  if(s == "jmp_gt")  return jmp_gt;
  if(s == "jmp_lte") return jmp_lte;
  if(s == "jmp_gte") return jmp_gte;
  if(s == "addi")    return addi;
  if(s == "subi")    return subi;
  if(s == "inci")    return inci;
  if(s == "deci")    return deci;
  if(s == "ori")     return ori;
  if(s == "xori")    return xori;
  if(s == "pushi")   return pushi;
  if(s == "puti")    return puti;
  if(s == "geti")    return geti;
  if(s == "stp")    return stp;
   
  return -1;  
}
