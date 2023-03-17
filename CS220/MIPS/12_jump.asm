.text
.globl main
main:
  li $t1, 10
  li $t2, 20
  j jump

jump:
  li $t3, 30
  li $t4, 40
  j end

end:
  li $v0, 10
  syscall