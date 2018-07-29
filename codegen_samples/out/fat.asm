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

_fat:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
#id = n
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
lw $t0 4($sp)
addiu $sp $sp 4
ble $t0 $a0 _true_branch_0
_false_branch_0:
j _end_if_0
_true_branch_0:
li $a0 1
_end_if_0:
#id = n
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
#id = n
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _fat
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
lw $ra 4($sp)
addiu $sp $sp 12
# n removed
addiu $sp $sp 4
lw  $fp  0($sp)
jr $ra

_main:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 5
sw $a0 0($sp)
addiu $sp $sp -4
jal _fat
sw $a0 0($sp)
addiu $sp $sp -4
#id = x
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
sw $fp 0($sp)
addiu $sp $sp -4
#id = x
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
# x removed
addiu $sp $sp 4
lw $ra 4($sp)
addiu $sp $sp 8
li $v0 10
syscall


.data
