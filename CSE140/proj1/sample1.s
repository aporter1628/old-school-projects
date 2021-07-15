# Short test case for your project.
#
# Note that this is by no means a comprehensive test!
#

		.text
	addi $t0, $t0, 1
	sw $t0, 0($t1)
	lw $t0, 0($t1)
	
