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

_main:
move  $fp  $sp
sw $ra 0($sp)
addiu $sp $sp -4
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 5
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 5
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 12
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 5
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 3
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 10
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 4
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 100
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 3
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 20
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 6
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 2
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 2
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 1
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 59
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 1
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 2
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 49
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 37
lw $t0 4($sp)
addiu $sp $sp 4
sub $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 5
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
sw $fp 0($sp)
addiu $sp $sp -4
li $a0 201841
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 128
sw $a0 0($sp)
addiu $sp $sp -4
li $a0 120912
lw $t0 4($sp)
addiu $sp $sp 4
mul $a0  $t0  $a0
lw $t0 4($sp)
addiu $sp $sp 4
add $a0  $t0  $a0
sw $a0 0($sp)
addiu $sp $sp -4
jal _println
# saveCome = 1
_end_function_main:
addiu $sp $sp 0
lw $ra 4($sp)
addiu $sp $sp 8
li $v0 10
syscall


.data
