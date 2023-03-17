.text
.globl main
main:
  li $t1, 10
  li $t2, 20
  div $t1, $t2 # $hi, $low=$t1/$t2 Remainder in hi quotient in lo
  li $v0, 10
  syscall