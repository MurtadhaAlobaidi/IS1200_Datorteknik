# n = $a0
# resultat = $v0
# product = $a1
# i = $a2
# j = $a3
# k = $v1

addi $a0, $0, 11		# $a0 = n = 0,3,8 (rad 5)
addi $v0, $0, 1		# return value = 1 to start with (!0 == 1) (rad 8)
addi $v1, $a0, 1	# k = n + 1 (rad 7)
addi $a2, $0, 1		# initialise outer loop var i to 1 (rad 6)

loop:
	beq $a2, $v1, done	# i != k, if i(a2) == k(v1) we're done (rad 10)
	addi $a2, $a2, 1	# i++, increment loop variable (rad 11)
	addi $a1, $0, 0		# initialise the product to 0 (rad 12)
	
	addi $a3,$0, 1		# initialise inner loop var j to 1 (rad 13)
	
	multi:
		beq $a3, $a2, out	# if j == i, if a3 == a2 done "multiadding"#om de lika(rad 15)
		addi $a3, $a3, 1	# j++, increment inner loop variable (rad 16)
		add $a1, $a1, $v0	# product == product + resultat (rad 17)
		beq $0, $0, multi	# jump back to multi
		
	out:
		addi $v0, $a1, 0		# set return variable to product of "multi"
		beq $0, $0, loop		# jump back to outer loop
	
done:
	beq $0, $0, done		# infinite unconditional branch loop
