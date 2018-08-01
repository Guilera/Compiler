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

_alpha:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
# id = m
lw $a0 8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
lw $t0 4($sp)
addiu $sp $sp 4
beq $t0 $a0 _true_branch_0
_false_branch_0:
j _end_if_0
_true_branch_0:
# id = n
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
j _end_function_alpha
# saveCome = 0
_end_if_0:
# id = n
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
lw $t0 4($sp)
addiu $sp $sp 4
beq $t0 $a0 _true_branch_1
_false_branch_1:
j _end_if_1
_true_branch_1:
sw $fp 0($sp)
addiu $sp $sp -4
# id = m
lw $a0 8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
jal _alpha
j _end_function_alpha
# saveCome = 0
_end_if_1:
sw $fp 0($sp)
addiu $sp $sp -4
# id = m
lw $a0 8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
# id = m
lw $a0 8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = n
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _alpha
sw $a0 0($sp)
addiu $sp $sp -4
jal _alpha
j _end_function_alpha
# saveCome = 1
_end_function_alpha:
addiu $sp $sp 0
lw $ra 4($sp)
addiu $sp $sp 8
# m removed
addiu $sp $sp 4
# n removed
addiu $sp $sp 4
lw  $fp  0($sp)
jr $ra

_solve:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
# id = x
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = x
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _alpha
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
# saveCome = 1
_end_function_solve:
addiu $sp $sp 0
lw $ra 4($sp)
addiu $sp $sp 8
# x removed
addiu $sp $sp 4
lw  $fp  0($sp)
jr $ra

_main:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 2
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
# saveCome = 1
_end_function_main:
addiu $sp $sp 0
lw $ra 4($sp)
addiu $sp $sp 8
li $v0 10
syscall


.data
