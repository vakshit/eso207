.text
.globl main
main:
  li $t2, 10
  # lw $t0, 100($t2) # load the value of the first element of the array
  # lw $t1, 104($t2) # load the value of the second element of the array
  lw $t3, value # load the value of the variable
  add $t4, $t2, $t3 # add the two values
  sub $t5, $t2, $t3 # subtract the two values

  li $v0, 10
  syscall

  # all memory initialisation at last
  value: .word 20