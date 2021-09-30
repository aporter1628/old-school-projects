
	.text

main:
	li $a0, 0
	jal putDec
	li $a0, '\n'
	li $v0, 11
	syscall
	
	li $a0, 1
	jal putDec
	li $a0, '\n'
	li $v0, 11
	syscall
	
	li $a0, 196
	jal putDec
	li $a0, '\n'
	li $v0, 11
	syscall
	
	li $a0, -1
	jal putDec
	li $a0, '\n'
	li $v0, 11
	syscall
	
	li $a0, -452
	jal putDec
	li $a0, '\n'
	li $v0, 11
	syscall
	
	li $a0, 2
	jal mystery
	move $a0, $v0
	jal putDec
	li $a0, '\n'
	li $v0, 11
	syscall

	li $a0, 3
	jal mystery
	move $a0, $v0
	jal putDec
	li $a0, '\n'
	li $v0, 11
	syscall

	li 	$v0, 10		# terminate program
	syscall

putDec: 

	## FILL IN ## 
	bne $a0, $zero, loop
	addi $a0, $zero, 0
	li $a0, '0'
	li $v0, 11
	syscall
	jr $ra
	
	loop:
	blt $a0, $zero, negative
	addi $s2, $zero, 100
	addi $s3, $zero, 10
	bgt $a0, $s2, loop2 
	bgt $a0, $s3, loop3
	j loop4
		
	negative:	
	add $t8, $zero, $a0
	li $a0, '-'
	li $v0, 11
	syscall
	sub $a1, $zero, $t8  
	add $a0, $zero, $a1
	j loop
	
	loop2:
	addi $a0, $a0, -100
	addi $a2, $a2, 1 #count
	addi $s0, $zero, 100
	add $t1, $zero, $a0
	blt $a0, $s0, print1
	blt $a0, $s0, loop3
	j loop2
	
	loop3:
	addi $a0, $a0, -10
	addi $a3, $a3, 1 #count
	addi $s0, $zero, 10
	add $t2, $zero, $a0
	blt $a0, $s0, print2
	j loop3
	
	loop4:
	addi $a0, $a0, -1
	addi $s1, $s1, 1 #count
	beq $a0, $zero, print3
	j loop4
	
	print1:
	li $a0, '0'	
	add $a0, $a0, $a2
	li $v0, 11
	syscall
	add $a0, $zero, $t1
	addi $a2, $zero, 0
	j loop3
		
	print2:
	li $a0, '0'	
	add $a0, $a0, $a3
	li $v0, 11
	syscall
	add $a0, $zero, $t2
	addi $a3, $zero, 0
	j loop4
	
	print3:
	li $a0, '0'
	add $a0, $a0, $s1
	li $v0, 11
	syscall
	addi $s1, $zero, 0
		
	jr	$ra		# returnv

mystery: bne $0, $a0, recur 	# 
 	li $v0, 0 		#
 	jr $ra 			#
 recur: sub $sp, $sp, 8 	#
 	sw $ra, 4($sp) 	#
 	sub $a0, $a0, 1 	#
 	jal mystery 		#
 	sw $v0, 0($sp) 	#
 	jal mystery 		#
 	lw $t0, 0($sp) 	#
 	addu $v0, $v0, $t0 	#
 	addu $v0, $v0, 1 	#
 	add $a0, $a0, 1 	#
 	lw $ra, 4($sp) 	#
 	add $sp, $sp, 8 	#
 	jr $ra 			#
