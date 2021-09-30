	addi $t3, $zero, 0xffffffff
	addi $t4, $zero, 0x00000001
	
	addu $t2, $t3, $t4
	sltu $t2, $t2, $t3
	
	#printing
	li $v0, 1
	move $a0, $t2
	syscall
	  
	
