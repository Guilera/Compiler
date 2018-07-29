.text

main: 
j _main

_input:
move $fp $sp
sw $ra 0($sp)
addiu $sp $sp -4
li $v0 5
syscall 
move $a0 $v0
lw $ra 4($sp)
addiu $sp $sp 8
lw $fp 0($sp)
jr $ra

_println:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
li $v0 1
lw $a0 4($fp)
syscall
addi $a0, $0, 0xA
addi $v0, $0, 0xB
syscall
lw $ra 4($sp)
addiu $sp $sp 12
lw $fp 0($sp)
jr $ra

_main:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 4
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 5
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
lw $ra 4($sp)
addiu $sp $sp 8
li $v0 10
syscall


.data
