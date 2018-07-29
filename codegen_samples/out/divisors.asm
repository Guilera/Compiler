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

_mod:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
#id = x
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = MOD
lw $a0 8($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
div $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
#id = q
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
#id = x
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = q
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = MOD
lw $a0 8($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
# q removed
addiu $sp $sp 4
lw $ra 4($sp)
addiu $sp $sp 16
# MOD removed
addiu $sp $sp 4
# x removed
addiu $sp $sp 4
lw  $fp  0($sp)
jr $ra

_solve:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
#id = i
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
_while_0:
#id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = i
lw $a0 -4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
#id = x
lw $a0 4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
ble $t0 $a0 _start_while_0
j _end_while_0
_start_while_0:
sw $fp 0($sp)
addiu $sp $sp -4
#id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = x
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _mod
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
lw $t0 4($sp)
addiu $sp $sp 4
beq $t0 $a0 _true_branch_0
_false_branch_0:
j _end_if_0
_true_branch_0:
sw $fp 0($sp)
addiu $sp $sp -4
#id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
#id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = i
lw $a0 -4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
#id = x
lw $a0 4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
bne $t0 $a0 _true_branch_1
_false_branch_1:
j _end_if_1
_true_branch_1:
sw $fp 0($sp)
addiu $sp $sp -4
#id = x
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = i
lw $a0 -4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
div $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
_end_if_1:
_end_if_0:
#id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
#id = i
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
j _while_0
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
# i removed
addiu $sp $sp 4
lw $ra 4($sp)
addiu $sp $sp 12
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
lw $ra 4($sp)
addiu $sp $sp 8
li $v0 10
syscall


.data
