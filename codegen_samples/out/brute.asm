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

_brute:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
addiu $sp $sp -4
# id = len
lw $a0 8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = n
la $a0 n
lw $a0 0($a0)
lw $t0 4($sp)
addiu $sp $sp 4
beq $t0 $a0 _true_branch_0
_false_branch_0:
j _end_if_0
_true_branch_0:
li $a0 1
j _end_function_brute
# saveCome = 0
_end_if_0:
# id = last
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = K
la $a0 K
lw $a0 0($a0)
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
# id = i
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
_while_0:
# id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = last
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = K
la $a0 K
lw $a0 0($a0)
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
ble $t0 $a0 _start_while_0
j _end_while_0
_start_while_0:
# id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = lo
la $a0 lo
lw $a0 0($a0)
lw $t0 4($sp)
addiu $sp $sp 4
bge $t0 $a0 _true_branch_1
_false_branch_1:
j _end_if_1
_true_branch_1:
# id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = hi
la $a0 hi
lw $a0 0($a0)
lw $t0 4($sp)
addiu $sp $sp 4
ble $t0 $a0 _true_branch_2
_false_branch_2:
j _end_if_2
_true_branch_2:
# id = res
lw $a0 -8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
# id = len
lw $a0 8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
# id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _brute
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
# id = res
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# saveCome = 0
_end_if_2:
# saveCome = 0
_end_if_1:
# id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
# id = i
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# saveCome = 0
j _while_0
_end_while_0:
# id = res
lw $a0 -8($fp) 
j _end_function_brute
# saveCome = 1
# res removed
# i removed
_end_function_brute:
addiu $sp $sp 8
lw $ra 4($sp)
addiu $sp $sp 8
# len removed
addiu $sp $sp 4
# last removed
addiu $sp $sp 4
lw  $fp  0($sp)
jr $ra

_solve:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
addiu $sp $sp -4
# id = a
lw $a0 4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = n
la $a0 n
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# id = b
lw $a0 8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = K
la $a0 K
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# id = c
lw $a0 12($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = lo
la $a0 lo
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# id = d
lw $a0 16($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = hi
la $a0 hi
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# id = lo
la $a0 lo
lw $a0 0($a0)
sw $a0 0($sp)
addiu $sp $sp -4
# id = i
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
_while_1:
# id = i
lw $a0 -8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = hi
la $a0 hi
lw $a0 0($a0)
lw $t0 4($sp)
addiu $sp $sp 4
ble $t0 $a0 _start_while_1
j _end_while_1
_start_while_1:
# id = res
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
# id = i
lw $a0 -8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _brute
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
# id = res
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# id = i
lw $a0 -8($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
# id = i
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# saveCome = 0
j _while_1
_end_while_1:
sw $fp 0($sp)
addiu $sp $sp -4
# id = res
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
# saveCome = 1
# i removed
# res removed
_end_function_solve:
addiu $sp $sp 8
lw $ra 4($sp)
addiu $sp $sp 8
# d removed
addiu $sp $sp 4
# c removed
addiu $sp $sp 4
# b removed
addiu $sp $sp 4
# a removed
addiu $sp $sp 4
lw  $fp  0($sp)
jr $ra

_main:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 22
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 17
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 2
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 5
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 56
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 42
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 8
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 8
sw $a0 0($sp)
addiu $sp $sp -4
jal _solve
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 119
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 99
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 10
sw $a0 0($sp)
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

# hi removed
# lo removed
# n removed
# K removed

.data
K:    .space 4
n:    .space 4
lo:    .space 4
hi:    .space 4
