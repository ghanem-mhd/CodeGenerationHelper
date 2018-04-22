.text
.globl main
main:

#-----------Use comments while you are generation assembly
li $t1,10
li $t2,5
add $t3, $t1, $t2
move $a0,$t3
li $v0,1
syscall
li $v0,10
syscall





