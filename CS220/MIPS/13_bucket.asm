.data
arr: .float 0.6, 0.2, 0.8, 0.3, 0.9, 0.1, 0.7, 0.4, 0.5
size: .word 9
space: .asciiz " "

.text
.globl main

main:
  lw $s1, size

  li $t0, 1
  loop1:
    blt $t0, $s1, continue
    j exit1
  continue:
    mul $t5, $t0, 4
    lwc1 $f1, arr($t5) # key = arr[i]
    addi $t1, $t0, -1 # j = i - 1
    innerLoop:
      mul $t2, $t1, 4
      lwc1 $f2, arr($t2) # f2 = arr[j] 
      blt $t1, $zero, outerLoop # j < 0
      c.lt.s $f2, $f1 # arr[i] <= key
      bc1t outerLoop 
      addi $t3, $t2, 4
      swc1 $f2, arr($t3)
      addi $t1, $t1, -1
      j innerLoop
    outerLoop:
      mul $t2, $t1, 4
      addi $t3, $t2, 4
      swc1 $f1, arr($t3)
      addi $t0, $t0, 1
      j loop1

  exit1:
    li $t0, 0
    # Print sorted array
    loop:
      beq $t0, 36, exit
      l.s $f12, arr($t0)
      li $v0, 2
      syscall

      la $a0 space
      li $v0, 4
      syscall

      addi $t0, $t0, 4
      j loop

    exit:
      li $v0, 10
      syscall