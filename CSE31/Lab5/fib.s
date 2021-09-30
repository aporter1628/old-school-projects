
fib: 	beq     $t3, $0, finish	#while t3 != 0
	add     $t2,$t1,$t0
	move    $t0, $t1
	move    $t1, $t2
	subi    $t3, $t3, 1
	j       fib			

