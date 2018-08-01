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

_solve:
move $fp $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
addiu $sp $sp -4
la $a0 MX
lw $a0 0($a0)
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
li $a0 0
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
lw $a0 -8($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
slt $a0 $t0 $a0
beq $0 $a0 _end_while_0
addiu $sp $sp -4
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 -8($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 2
lw $t0 4($sp)
addiu $sp $sp 4
div $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -12
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
lw $a0 -12($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 -12($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 2
lw $t0 4($sp)
addiu $sp $sp 4
div $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 4($fp)
lw $t0 4($sp)
addiu $sp $sp 4
slt $a0 $t0 $a0
xori $a0 $a0 1
bne $0 $a0 _begin_if_0
lw $a0 -12($fp) 
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
j _end_if_0
_begin_if_0:
lw $a0 -12($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
_end_if_0:
addiu $sp $sp 4
j _begin_while_0
_end_while_0:
sw $fp 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
_end_function_solve:
addiu $sp $sp 8
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
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
_begin_while_1:
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1000000000
lw $t0 4($sp)
addiu $sp $sp 4
slt $a0 $t0 $a0
beq $0 $a0 _end_while_1
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
j _begin_while_1
_end_while_1:
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
la $a0 MX
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 42
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 109092190
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 999999999
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 80475327
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 424242424
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 24242424
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 199999289
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
_end_function_main:
addiu $sp $sp 4
lw $ra 4($sp)
addiu $sp $sp 4
lw $fp 4($sp)
addiu $sp $sp 4
jr $ra


.data
MX:    .space 4
