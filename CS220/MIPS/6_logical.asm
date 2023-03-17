.text
.globl main
main:
  li $t0, 1
  li $t1, 2
  and $t2, $t0, $t1
  or $t3, $t0, $t0
  andi $t4, $t0, 1
  ori $t5, $t0, 1

  sll $t6, $t0, 2 # shift left logical by 2 bits
  srl $t7, $t0, 2 # shift right logical by 2 bits 
  li $v0, 10
  syscall