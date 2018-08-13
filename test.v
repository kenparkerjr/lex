@Data
string  MyString  "Hello World"
string  tmp       "0"
int     start     100
int     end       150

@Start
print MyString
load a $start
load b $end
compare a b
inc a
jump_lt @Start
