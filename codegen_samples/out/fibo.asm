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

_fibonacci:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
addiu $sp $sp -4
addiu $sp $sp -4
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
#id = a
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
#id = b
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
#id = i
addiu $a0 $fp -16
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
#id = n
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 2
lw $t0 4($sp)
addiu $sp $sp 4
ble $t0 $a0 _true_branch_0
_false_branch_0:
j _end_if_0
_true_branch_0:
#id = a
lw $a0 -4($fp) 
_end_if_0:
_while_0:
#id = i
lw $a0 -16($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = n
lw $a0 4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
ble $t0 $a0 _start_while_0
j _end_while_0
_start_while_0:
#id = b
lw $a0 -8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = a
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
#id = a
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
#id = b
lw $a0 -8($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
#id = b
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
#id = i
lw $a0 -16($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
#id = i
addiu $a0 $fp -16
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
j _while_0
_end_while_0:
#id = b
lw $a0 -8($fp) 
# i removed
addiu $sp $sp 4
# x removed
addiu $sp $sp 4
# b removed
addiu $sp $sp 4
# a removed
addiu $sp $sp 4
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
li $a0 8
sw $a0 0($sp)
addiu $sp $sp -4
jal _fibonacci
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
