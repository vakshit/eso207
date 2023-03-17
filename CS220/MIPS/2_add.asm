.text
.globl main
main:
  li $t0, 4
  li $t1, 5
  add $t3, $t1, $t0
  li $v0 , 10
  syscall