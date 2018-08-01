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

_mod:
move $fp $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
lw $a0 4($fp)
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 8($fp)
lw $t0 4($sp)
addiu $sp $sp 4
div $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
lw $a0 4($fp)
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 8($fp)
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
j _end_function_mod
_end_function_mod:
addiu $sp $sp 4
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
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
_begin_while_0:
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 4($fp)
lw $t0 4($sp)
addiu $sp $sp 4
slt $a0 $a0 $t0
xori $a0 $a0 1
beq $0 $a0 _end_while_0
sw $fp 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _mod
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
sw $fp 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 4($fp)
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0 $t0 $a0
sltu $a0 $0 $a0
bne $0 $a0 _begin_if_1
j _end_if_1
_begin_if_1:
sw $fp 0($sp)
addiu $sp $sp -4
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
div $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
_end_if_1:
_end_if_0:
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
j _begin_while_0
_end_while_0:
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
_end_function_solve:
addiu $sp $sp 4
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
li $a0 8
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 81
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 47
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 42
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 56
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
