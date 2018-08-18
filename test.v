@Data
int a 100
int b 150
int max 50
@Start
pushi $a
@Loop
inci
puti
cmp $a $max
jmp_lt @Loop
stp
