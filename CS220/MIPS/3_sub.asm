.text
.globl main
main:
  li $t1, 10
  li $t2, 20
  sub $t3, $t1, $t2
  li $v0, 10
  syscall