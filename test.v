@Data
int  a 100
int  b 150
int  max 200 
@Start
pushi $a
pushi $b
addi
puti
cmp $a $max
jmp_gt @Start
stp
