main:
	lui	$a0,0x8000
	jal	first1pos
	jal	printv0
	lui	$a0,0x0001
	jal	first1pos
	jal	printv0
	li	$a0,1
	jal	first1pos
	jal	printv0
	add	$a0,$0,$0
	jal	first1pos
	jal	printv0
	li	$v0,10
	syscall

first1pos:	# shift $a0 to the left (slt), counting the shifts, until the first entry is 1. The pos is 31
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		addi $v0, $zero, 0 #set count equal to 0
		j loop
		
loop:		beq $a0, $zero, finish0 #if $a0 is 0 return -1
		slt $s0, $a0, $zero 
		beq $s0, 1, finish #If the leftmost bit is 1 return 31 - $v0
		sll $a0, $a0, 1
		addi $v0, $v0, 1
		j loop
finish:		
		addi $s0, $zero, 31
		sub $v0, $s0, $v0 #v0 = 31 - v0
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
finish0:
		addi $v0, $zero, -1
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
		

printv0:
	addi	$sp,$sp,-4
	sw	$ra,0($sp)
	add	$a0,$v0,$0
	li	$v0,1
	syscall
	li	$v0,11
	li	$a0,'\n'
	syscall
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	jr	$ra
