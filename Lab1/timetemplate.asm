  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro    PUSH (%reg)
    addi    $sp,$sp,-4
    sw    %reg,0($sp)
.end_macro

.macro    POP (%reg)
    lw    %reg,0($sp)
    addi    $sp,$sp,4
.end_macro

    .data
    .align 2
mytime:    .word 0x5957
timstr:    .ascii "text more text lots of text\0"
    .text
main:
    # print timstr
    la    $a0,timstr
    li    $v0,4
    syscall
    nop
    # wait a little
    li    $a0,1000
    jal    delay
    nop
    # call tick
    la    $a0,mytime
    jal    tick
    nop
    # call your function time2string
    la    $a0,timstr
    la    $t0,mytime
    lw    $a1,0($t0)
    jal    time2string
    nop
    # print a newline
    li    $a0,10
    li    $v0,11
    syscall
    nop
    # go back and do it all again
    j    main
    nop
# tick: update time pointed to by $a0
tick:    lw    $t0,0($a0)    # get time
    addiu    $t0,$t0,1    # increase
    andi    $t1,$t0,0xf    # check lowest digit
    sltiu    $t2,$t1,0xa    # if digit < a, okay
    bnez    $t2,tiend
    nop
    addiu    $t0,$t0,0x6    # adjust lowest digit
    andi    $t1,$t0,0xf0    # check next digit
    sltiu    $t2,$t1,0x60    # if digit < 6, okay
    bnez    $t2,tiend
    nop
    addiu    $t0,$t0,0xa0    # adjust digit
    andi    $t1,$t0,0xf00    # check minute digit
    sltiu    $t2,$t1,0xa00    # if digit < a, okay
    bnez    $t2,tiend
    nop
    addiu    $t0,$t0,0x600    # adjust digit
    andi    $t1,$t0,0xf000    # check last digit
    sltiu    $t2,$t1,0x6000    # if digit < 6, okay
    bnez    $t2,tiend
    nop
    addiu    $t0,$t0,0xa000    # adjust last digit
tiend:    sw    $t0,0($a0)    # save updated result
    jr    $ra        # return
    nop

  # you can write your code for subroutine "hexasc" below this line
  #########################################################################(Assignment 2)
hexasc:
    andi $a0,$a0,0xF    # Lägger till 0xF, Zero-extendar alla bitar utom sista 4 bitarna
    ble $a0,0x9,num        # Jämnför $a0 med 9, ifall det är mindre eller lika med 9 då hoppa till num (0-9)
    
    addi $v0,$a0,0x37    # Adderar hexa 37(55 uni cod = 7 decmal) till $a0 för att komma till ASCII bokstäverna och för över till $v0 för returvärde
    j end

num:
    addi $v0,$a0,0x30    # Adderar hexa 37 till $a0 för att komma till ASCII siffrorna och för över till $v0 för returvärde
    
end:
    jr $ra
     nop            # delay slot filler (just in case)
#################################################################################(Assignment 4)
# "delay" subroutine
delay:
 # frees up the variables $s0, $t0 and $s1
 PUSH($s0)
 PUSH($s1)
 
 li    $s1, 50        # sets $s1 to a constant, in this case 2 (hastighet)
 
delayloop1:
 # checks if $t7 is less than or equal to 0 and if so moves to delayend
 sle    $t0, $a0, $0    #($t7 <= $0 då sätt $t0 = 1)
 bne    $t0, 0, delayend
 nop            # delay slot filler (just in case)

 subi    $a0, $a0, 1    # subtracts 1 from $t7 ($t7=1000 ms)
 li    $s0, 0        # sets $s0 to 0

delayloop2:
 #checks if $s0 is less than to $s1 and if so moves to delayend
 slt    $t0, $s0, $s1    #($s0 < $s1 då sätt $t0 = 1)
 beq    $t0, 0, delayloop1 #equal
 nop            # delay slot filler (just in case)
 nop            # extra delay to make delayloop2 take 1 ms

 addi    $s0, $s0, 1    # adds 1 to $s0
 j    delayloop2    # begins the loop again
 nop            # delay slot filler (just in case)


delayend:
 # restores registers $s1, $t0 and $s0
 POP($s1)
 POP($s0)
 jr     $ra        # jumps using the return adress
 nop            # delay slot filler (just in case)
##################################################################################(Assignment 3)
 # "time2string" subroutine
 #
 # "time2string" subroutine
 #
time2string:
 PUSH($s0)        #free up $t0, $t1 and $ra
 PUSH($s1)        #PUSH för att kopera 16 bits inhåller till topp av staken
 PUSH($ra)

 move    $s0, $a0    #save $a0 to $t0
 move     $s1,$a1

 #save the first minute nibble to $a0, shift it to the right, activate hexasc and store the result ($v0)
 andi    $s1, $a1, 0xf000  #($a1 är mytime) (59:57 dicemal (0101 1001 0101 0111)) då andi 0xf000(1111 0000 0000 0000 0000) och spara den i $t1
 srl    $a0, $s1, 12      # Shift 12 >> right ($a0,timstr) (timstr: .ascii "text more text lots of text\0")
 jal    hexasc          # jump to hexasc
 nop
 sb    $v0, 0($s0)      # $v0 spars i $t0 + imm

 # save the second minute nibble to $a0, shift it to the right, activate hexasc and store the result ($v0)
 andi    $s1, $a1, 0x0f00
 srl    $a0, $s1, 8        #Shift 8 >> right
 jal    hexasc
 nop
 sb    $v0, 1($s0)

 # store the hexvalue for ':' in $v0 and store it
 li    $v0, 0x3A
 sb    $v0, 2($s0)

 # save the first second nibble to $a0, shift it to the right, activate hexasc and store the result ($v0)
 andi    $s1, $a1, 0x00f0
 srl    $a0, $s1, 4    #Shift 4 >> right
 jal    hexasc
 nop
 sb    $v0, 3($s0)

 # save the second minute nibble to $a0, activate hexasc and store the result ($v0)
 andi    $a0, $a1, 0x000f
 jal    hexasc
 nop
 sb    $v0, 4($s0)

 # store the hexvalue for a null byte in $v0 and store it
 li    $v0, 0x0
 sb    $v0, 5($s0)

 POP($ra)        # restore $t0, $t1 and $ra
 POP($s1)
 POP($s0)

 jr    $ra        # jumps using returnadress
 nop            # delay slot filler (just in case)

