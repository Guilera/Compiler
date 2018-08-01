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

_fibonacci:
move $fp $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
addiu $sp $sp -4
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
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -16
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
lw $a0 4($fp)
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 2
lw $t0 4($sp)
addiu $sp $sp 4
slt $a0 $a0 $t0
xori $a0 $a0 1
bne $0 $a0 _begin_if_0
j _end_if_0
_begin_if_0:
lw $a0 -4($fp) 
j _end_function_fibonacci
_end_if_0:
_begin_while_0:
lw $a0 -16($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 4($fp)
lw $t0 4($sp)
addiu $sp $sp 4
slt $a0 $a0 $t0
xori $a0 $a0 1
beq $0 $a0 _end_while_0
lw $a0 -8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
lw $a0 -8($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
lw $a0 -16($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -16
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
j _begin_while_0
_end_while_0:
lw $a0 -8($fp) 
j _end_function_fibonacci
_end_function_fibonacci:
addiu $sp $sp 16
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
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 8
sw $a0 0($sp)
addiu $sp $sp -4
jal _fibonacci
sw $a0 0($sp)
addiu $sp $sp -4
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
sw $fp 0($sp)
addiu $sp $sp -4
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
_end_function_main:
addiu $sp $sp 4
lw $ra 4($sp)
addiu $sp $sp 4
lw $fp 4($sp)
addiu $sp $sp 4
jr $ra


.data
