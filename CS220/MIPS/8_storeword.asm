.text
.globl main
  main:
  li $t2 , 0x04
  li $t8, 0x10010000
  lw $t3, value
  add $t4, $t2, $t3
  sub $t5, $t2, $t3
  sw $t5, 0($t8) # storeword directive
  li $v0, 10
  syscall

  value: .word 0x05