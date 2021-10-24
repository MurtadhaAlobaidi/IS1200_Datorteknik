  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.
.data



.text
main:
	li	$a0,0x08		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc:
	andi	$t0, $a0, 0x0F	# t0 = a0 AND 1111
	
	addi	$v0, $t0, 0x30	# v0 = t0 + 48
	
	slti	$t1, $v0, 0x3A	# t1 = v0 < 58
	bne	$t1, $zero, return	# v0 == 0 ? return : contiune
	
	addi	$v0, $v0, 0x07	# v0 = v0 + 7
	
	
return: jr	$ra		# return value
