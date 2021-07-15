.text
addiu $t0, $t0, 1
addiu $t1, $t1, 2
addiu $t3, $t3, 3

subu $t4, $t1, $t0
subu $t4, $t0, $t1

sll $t5, $t5, 2
srl $t5, $t5, 2

and $t6, $t0, $t1
andi $t6, $t0, 2

or $t6, $t0, $t1
ori $t6, $t0, 2

lui $t6, 16

slt $t6, $t0, $t1
slt $t6, $t1, $t0
