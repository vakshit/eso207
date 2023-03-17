.text
.globl main
  main:
  li $t0, 10
  li $t1, 20
  move $t3, $t1 # $t3 = $t1

  div $t1, $t0 # $t1 / $t0
  mflo $t2 # $t2 = $t1 / $t0
  mfhi $t4 # $t4 = $t1 % $t0
  li $v0, 10
  syscall