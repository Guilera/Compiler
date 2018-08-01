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

_solve:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
addiu $sp $sp -4
addiu $sp $sp -4
# id = MX
la $a0 MX
lw $a0 0($a0)
sw $a0 0($sp)
addiu $sp $sp -4
# id = r
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
li $a0 0
sw $a0 0($sp)
addiu $sp $sp -4
# id = l
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
_while_0:
# id = l
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = r
lw $a0 -8($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
blt $t0 $a0 _start_while_0
j _end_while_0
_start_while_0:
addiu $sp $sp -4
# id = l
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = r
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
# id = mid
addiu $a0 $fp -12
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# id = mid
lw $a0 -12($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = mid
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
# id = x
lw $a0 4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
bge $t0 $a0 _true_branch_0
_false_branch_0:
# id = mid
lw $a0 -12($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
# id = l
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# saveCome = 0
j _end_if_0
_true_branch_0:
# id = mid
lw $a0 -12($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = r
addiu $a0 $fp -8
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
# saveCome = 0
_end_if_0:
# saveCome = 0
# mid removed
addiu $sp $sp 4
j _while_0
_end_while_0:
sw $fp 0($sp)
addiu $sp $sp -4
# id = l
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
# saveCome = 1
# r removed
# l removed
_end_function_solve:
addiu $sp $sp 8
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
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
# id = i
addiu $a0 $fp -4
lw $t0 4($sp)
addiu $sp $sp 4
sw $t0 0($a0)
addiu $a0 $t0 0
_while_1:
# id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = i
lw $a0 -4($fp) 
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1000000000
lw $t0 4($sp)
addiu $sp $sp 4
blt $t0 $a0 _start_while_1
j _end_while_1
_start_while_1:
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
j _while_1
_end_while_1:
# id = i
lw $a0 -4($fp) 
sw $a0 0($sp)
addiu $sp $sp -4
# id = MX
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
# saveCome = 1
# i removed
_end_function_main:
addiu $sp $sp 4
lw $ra 4($sp)
addiu $sp $sp 8
li $v0 10
syscall

# MX removed

.data
MX:    .space 4
