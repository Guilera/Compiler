.text

main: 
jal _main

li $v0 10
syscall

_input:
move $fp $sp
sw $ra 0($sp)
addiu $sp $sp -4
li $v0 5
syscall 
move $a0 $v0
lw $ra 4($sp)
addiu $sp $sp 4
lw $fp 4($sp)
addiu $sp $sp 4
jr $ra

_println:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
lw $a0 4($fp)
li $v0 1
syscall
addi $a0, $0, 0xA
addi $v0, $0, 0xB
syscall
lw $ra 4($sp)
addiu $sp $sp 8
lw $fp 4($sp)
addiu $sp $sp 4
jr $ra

_alpha:
move $fp $sp
sw $ra 0($sp)
addiu $sp $sp -4
lw $a0 8($fp)
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0 $t0 $a0
sltu $a0 $0 $a0
xori $a0 $a0 1
bne $0 $a0 _begin_if_0
j _end_if_0
_begin_if_0:
lw $a0 4($fp)
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
j _end_function_alpha
_end_if_0:
lw $a0 4($fp)
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0 $t0 $a0
sltu $a0 $0 $a0
xori $a0 $a0 1
bne $0 $a0 _begin_if_1
j _end_if_1
_begin_if_1:
sw $fp 0($sp)
addiu $sp $sp -4
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
_end_if_1:
sw $fp 0($sp)
addiu $sp $sp -4
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
lw $a0 8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
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
_end_function_alpha:
addiu $sp $sp 0
lw $ra 4($sp)
addiu $sp $sp 4
addiu $sp $sp 4
addiu $sp $sp 4
lw $fp 4($sp)
addiu $sp $sp 4
jr $ra

_solve:
move $fp $sp
sw $ra 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _alpha
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
_end_function_solve:
addiu $sp $sp 0
lw $ra 4($sp)
addiu $sp $sp 4
addiu $sp $sp 4
lw $fp 4($sp)
addiu $sp $sp 4
jr $ra

_main:
move $fp $sp
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
_end_function_main:
addiu $sp $sp 0
lw $ra 4($sp)
addiu $sp $sp 4
lw $fp 4($sp)
addiu $sp $sp 4
jr $ra


.data
