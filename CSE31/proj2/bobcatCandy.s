.data 
str0: .asciiz "Welcome to BobCat Candy, home to the famous BobCat Bars!\n"
promptPrice: .asciiz"Please enter the price of a BobCat Bar:\n"
promptWrappers: .asciiz"Please enter the number of wrappers needed to exchange for a new bar:\n"
promptMoney: .asciiz"How, how much do you have?\n"
random: .asciiz"Good! Let me run the number...\n"
firstBuy: .asciiz"You first buy "
bars: .asciiz " bars.\n"
nextBuys: .asciiz"Then, you will get another "
final: .asciiz"With $"
final2: .asciiz", you will receive a maximum of "
final3: .asciiz" BobCat Bars!"

.text

main:
	#This is the main program.
	#It first asks user to enter the price of each BobCat Bar.
	#It then asks user to enter the number of bar wrappers needed to exchange for a new bar.
	#It then asks user to enter how much money he/she has.
	#It then calls maxBars function to perform calculation of the maximum BobCat Bars the user will receive based on the information entered. 
	#It then prints out a statement about the maximum BobCat Bars the user will receive.
	
	addi $sp, $sp -4
	sw $ra, 0($sp)
	
	#Beginning statement
	li $v0, 4
	la $a0, str0
	syscall
	
	#Put the price in s1
	li $v0, 4
	la $a0, promptPrice
	syscall
	li $v0, 5
	syscall
	move $s1, $v0
	
	#Put n in s0
	li $v0, 4
	la $a0, promptWrappers
	syscall
	li $v0, 5
	syscall
	move $s0, $v0
	
	#Put the amount of money in s2
	li $v0, 4
	la $a0, promptMoney
	syscall
	li $v0, 5
	syscall
	move $s2, $v0
	
	#Before calculation statement
	li $v0, 4
	la $a0, random
	syscall
	
	#Call the function
	move $a0, $s0 #Move the variables into the arguments
	move $a1, $s1
	move $a2, $s2
	jal maxBars  # Call maxBars to calculate the maximum number of BobCat Bars

	# Print out final statement here
	move $s0, $v0 #Put the return value in s0
	#Print the max amount of bars you can get
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
	la $a0, final3
	syscall

	j end	# Jump to end of program



maxBars:
	# This function calculates the maximum number of BobCat Bars.
	# It takes in 3 arguments ($a0, $a1, $a2) as n, price, and money. It returns the maximum number of bars	
	add $v0, $zero, $zero #Put 0 in the return value
	blt $a2, $a1, endMaxBars #If money < price skip this function
	
	div $t0, $a2, $a1 #numBars = money/price
	move $a1, $a0 #Move n into a1 to preserve it
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
	move $a0, $t0 #Move numBars into a0
	addi $sp, $sp, -12
	sw $a0, 4($sp) #Store the original numBars on the stack
	sw $a0, 8($sp) #Store it again
	sw $ra, 12($sp) 
	jal newBars 	# Call a helper function to keep track of the number of bars.
		
	# End of maxBars
	lw $t0, 4($sp) #Get the original numBars
	addi $sp, $sp, 4
	add $t0, $t0, $v0 #numBars = numBars + return value of newBars
	move $v0, $t0 #Put numBars into the return value
	
	endMaxBars:
	jr $ra

newBars:
	# This function calculates the number of BobCat Bars a user will receive based on n.
	# It takes in 2 arguments ($a0, $a1) as number of bars so far and n.
	#a0 = numBars, $a1 = n
	#Base case
	add $v0, $zero, $zero #put 0 in the return value
	blt $a0, $a1, endNewBars
	
	#Recursive part
	div $a0, $a0, $a1 #numBars = numBars/n
	move $t0, $a0 #Put numBars into $t0
	
	li $v0, 4 #Print the current numBars
	la $a0, nextBuys
	syscall
	li $v0, 1
	la $a0, ($t0)
	syscall
	li $v0, 4
	la $a0, bars
	syscall
	
	move $a0, $t0 #Put numBars back into $a0
	lw $t0, 8($sp)
	add $t0, $t0, $a0 #Accumulate the numBars 
	sw $t0, 8($sp) #Put it back on the stack
	jal newBars
	
	endNewBars:
	lw $v0, 8($sp) #Put the accumulated numBars in the return value
	lw $ra, 12($sp)
	addi $sp, $sp, 8
	jr $ra
	# End of newBars

end: 
	# Terminating the program
	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
