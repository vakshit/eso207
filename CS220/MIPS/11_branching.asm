.text
.globl main
main:
  li $t1, 20
  li $t2, 20
  beq $t1, $t2, equal
  bne $t1, $t2, not_equal 
  # bgt bge blt also provided by assembler
  # branch on greater than, greater than or equal to, less than, less than


not_equal:
  addi $t1, $t1, 1
# why is this executed?
# not executed not... essentially bas itne lines are skipped
equal:
  addi $t2, $t2, 1
  li $v0, 10
  syscall