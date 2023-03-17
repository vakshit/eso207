.text
.globl main
main:
  li $t1, 10
  li $t2, 20
  mult $t1, $t2 # $high, $lo = $t1 * $t2
  li $v0, 10
  syscall