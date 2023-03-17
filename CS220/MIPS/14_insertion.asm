.data
	arr: .space 40
	string_input: .asciiz  "Enter a number: "

.text
	.globl	main

main:
	addi $t1,$zero,0
	addi $t7,$zero,40

while_input:
	beq $t1,$t7,exit_input
	li $v0,4
	la $a0,string_input
	syscall

	li $v0, 5
    syscall
	
	move $t0,$v0
	sw $t0,arr($t1)
	addi $t1,$t1,4
	
	j while_input

exit_input:
	addi $a1,$zero,10
	la $a0,arr
    jal sort

sort:	
	addi $sp,$sp,-16
	sw $s3,12($sp)
	sw $s2,8($sp)
	sw $s1,4($sp)
	sw $s0,0($sp)
	addi $s1,$a0,0
	addi $s2,$a1,0
	addi $s0,$zero,1	#i=1

loop1:	
	slt $t0,$s0,$s2		#i<n t0=1
	beq $t0,$zero,exit1	#t0=0 exit
	addi $s3,$s0,-1		#j=i-1
	sll $t0,$s0,2		#t0=i*4
	add $t0,$t0,$s1		#t0=arr+i*4
	lw $t1,0($t0)		#t1=arr[i]
	addi $s3,$s0,-1		#j=i-1

loop2:	slt $t0,$s3,$zero	#j>=0
	bne $t0,$zero,exit2
	sll $t0,$s3,2		#t0=j*4
	add $t0,$t0,$s1		#t0=arr+j*4
	lw $t2,0($t0)		#t2=arr[j]
	ble $t2,$t1,exit2	#arr[j]<=key
	addi $t0,$t0,4		#t0=t0+1
	sw $t2,0($t0)		#arr[j+1]=t2
	addi $s3,$s3,-1		#j=j-1
	j loop2

exit2:	addi $s0,$s0,1		#i=i+1
	sll $t0,$s3,2		#t0=j*4
	addi $t0,$t0,4
	la $t6,arr
	add $t0,$t0,$t6
	sw $t1,0($t0)		#arr[j+1]=hey
	j loop1

exit1:	lw $s0, 0($sp) # restore $s0 from stack
	lw $s1, 4($sp)
	lw $s2, 8($sp)
	lw $s3, 12($sp)
	addi $sp,$sp,16
	addi $t7,$zero,40
	addi $t4,$zero,0

while:
	beq $t4,$t7,e
	lw $t5,arr($t4)
	li $v0,1
	addi $a0,$t5,0
	syscall
	li $a0, 32
	li $v0, 11  
	syscall
	addi $t4,$t4,4
	j while

e:
	li   $v0, 10              # terminate program run and
    syscall