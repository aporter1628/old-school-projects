	.data
promptPrice: .asciiz"Enter the price of a bar:\n"
promptWrappers: .asciiz"Enter the number of wrappers to exchange for a new bar:\n"
promptMoney: .asciiz"Enter the amount of money you have:\n"
firstBuy: .asciiz"You first buy "
bars: .asciiz " bars.\n"
nextBuys: .asciiz"Then you can get another "
final: .asciiz"With $"
final2: .asciiz" you will receive a maximum of "

	.text
main:
	#Put the price in s0
	li $v0, 4
	la $a0, promptPrice
	syscall
	li $v0, 5
	syscall
	move $s0, $v0
	
	#Put n in s1
	li $v0, 4
	la $a0, promptWrappers
	syscall
	li $v0, 5
	syscall
	move $s1, $v0
	
	#Put the amount of money in s2
	li $v0, 4
	la $a0, promptMoney
	syscall
	li $v0, 5
	syscall
	move $s2, $v0
	
	#Call the function
	move $a0, $s0
	move $a1, $s1
	move $a2, $s2
	jal maxBars
	
	#End of program
	move $s0, $v0 #Put the return value in s0
	li $v0, 4
	la $a0, final
	syscall
	li $v0, 1
	la $a0, ($s2) #The original amount of money is still in s2
	syscall
	
	li $v0, 4
	la $a0, final2
	syscall
	li $v0, 1
	la $a0, ($s0)
	syscall
	
	li $v0, 4
	la $a0, bars
	syscall
	
	li $v0, 10 #Stop the program
	syscall
	
	
maxBars: # a0 = price, a1 = n, a2 = money
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	div $t0, $a2, $a0 #numBars = money/price
	#Print the bars you buy first
	li $v0, 4
	la $a0, firstBuy
	syscall
	li $v0, 1
	la $a0, ($t0)
	syscall
	li $v0, 4
	la $a0, bars
	syscall
	
	#Prepare to call newBars
	move $a0, $t0 #Move numBars into a0. a1 already holds n
	addi $sp, $sp, -8
	sw $a0, 4($sp) #Store the original numBars on the stack
	#sw $a0, 8($sp) #Store it again
	sw $ra, 8($sp) 
	jal newBars
	
	lw $t0, 4($sp) #Get the original numBars
	add $t0, $t0, $v0 #numBars = numBars + return value of newBars
	move $v0, $t0 #Put numBars into the return value
	
	lw $ra, 0($sp)
	addi $sp, $sp, 8
	jr $ra
	
newBars: #a0 = numBars, $a1 = n
	#Base case
	add $v0, $zero, $zero #put 0 in the return value
	blt $a0, $a1, endNewBars
	
	
	#Recursive part
	div $a0, $a0, $a1 #numBars = numBars/n
	move $t0, $a0 #Put numBars into $t0
	li $v0, 4
	la $a0, nextBuys
	syscall
	li $v0, 1
	la $a0, ($t0)
	syscall
	li $v0, 4
	la $a0, bars
	syscall
	move $a0, $t0 #Put numBars back into $a0
	add $v0, $v0, $a0 #Accumulate numBars 
	sw $v0, 8($sp) #Put the return value on the stack
	
	#lw $t0, 8($sp)
	#add $t0, $t0, $a0 #Accumulate the numBars 
	#sw $t0, 8($sp) #Put it back on the stack
	jal newBars
	
	endNewBars:
	lw $v0, 8($sp) #Put the accumulated numBars in the return value
	lw $ra, 12($sp)
	addi $sp, $sp, 8
	jr $ra
	
