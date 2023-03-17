.text
.globl main
  main:
  li $t1, 10
  li $t2, 20
  slt $t3, $t1, $t2 # $t3 = 1 if $t1 < $t2 else $t3 = 0
  slti $t4, $t1, 5 # $t4 = 1 if $t1 < 5 else $t4 = 0
  li $v0, 10
  syscall