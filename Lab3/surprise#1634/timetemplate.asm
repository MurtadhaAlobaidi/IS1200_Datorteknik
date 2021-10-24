  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1 # longer time if gt 0. Less time if ls than and equal 0
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
hexasc:
	andi	$t0, $a0, 0x0F	# t0 = a0 AND 1111
	
	addi	$v0, $t0, 0x30	# v0 = t0 + 48
	
	slti	$t1, $v0, 0x3A	# t1 = v0 < 58
	bne	$t1, $zero, return	# v0 == 0 ? return : contiune
	
	addi	$v0, $v0, 0x07	# v0 = v0 + 7

return:
	jr	$ra
	nop	

delay:
	bgt	$a0, $zero, while
	nop
	
	jr	$ra
	nop
	
while:
	subi	$a0, $a0, 1
	nop
	add	$t0, $zero, $zero
forloop:
	bge	$t0, 0x7530, done	# 4711 = 0x1267, # 5000 = 0x1388
	addi	$t0, $t0, 1
	j	forloop 

done:
	j	delay
	nop
			
time2string:
	PUSH	($s0)
	PUSH	($s1)
	PUSH	($ra)	# So we can return to previous nested loop
	
	add	$s0, $zero, $a0 # Parameter 0, address to our output string
	add	$s1, $zero, $a1	# Parameter 1, time (0x5958)
	#addi	$t0, $zero, 0xF000	# t0 = 0xF000, local variable
	#addi	$t1, $zero, 0x0C	# t1 = 12, local variable
	
	
	# Extract s1 values and convert to ASCII and store it in saved register
	
	# 0x5958 >> 0x5 = 0x35
	andi	$t2, $s1, 0xF000
	srl	$a0, $t2, 0x0C
	jal	hexasc
	nop
	sb	$v0, 0x00($s0)
	srl	$t0, $t0, 4
	sub	$t1, $t1, 4
	
	
	# 0x5958 >> 0x9 = 0x39
	andi	$t0, $s1, 0xF00
	srl	$a0, $t0, 0x08
	jal	hexasc
	nop
	sb	$v0, 0x01($s0)
	srl	$t0, $t0, 4
	sub	$t1, $t1, 4
	
	# Add colon 
	li	$t3, 0x3A
	sb	$t3, 0x02($s0)
	
	# 0x5958 >> 0x5 = 0x35
	# Handels the 5 in 16:53
	andi	$t0, $s1, 0xF0
	srl	$a0, $t0, 0x04
	jal	hexasc
	nop
	sb	$v0, 0x03($s0)
	srl	$t0, $t0, 4
	sub	$t1, $t1, 4
	
	# Ox5958 >> 0x8 = 0x38
	andi	$t0, $s1, 0xF
	srl	$a0, $t0, 0x00
	jal	hexasc
	nop
	sb	$v0, 0x04($s0)
	srl	$t0, $t0, 4
	sub	$t1, $t1, 4
	
	# null
	li 	$t4, 0x00
	sb	$t4, 0x05($s0)
	
	
	
	POP	($ra)
	POP	($s0)
	POP	($s1)
	
	jr	$ra
	nop
