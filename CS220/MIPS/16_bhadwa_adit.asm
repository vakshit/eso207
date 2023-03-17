.data
    arr:        .float  0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434, 0.1126, 0.554, 0.3349, 0.678, 0.3656, 0.9989
    p:          .word   12
    buckets:    .space  480
    n:          .word   5
    count:      .word   0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    new_line:   .asciiz "\n"

# s0 contains the starting address of the array
# s1 contains the length of the array
# s2 contains the starting address of the 2D buckets array
# s3 contains the bucket size
# s4 contains the count array

.text
.globl main
main:
    la $s0, arr
    lw $s1, p
    la $s2, buckets
    lw $s3, n
    lw $s4, count

assign_values:
    lw $t0, 0
    assign_loop:
        beq $t0, $s1, print_values

        move $a0, $t0
        li $v0, 1
        syscall

        add $t0, $t0, 1
        j assign_loop

# sort_buckets:

# merge_buckets:

print_values:
    print_loop:
        beq $t0, 48, exit
        l.s $f12, arr($t0)
        li $v0, 2
        syscall

        la $a0, new_line
        li $v0, 4
        syscall

        addi $t0, $t0, 4
        j print_loop

exit:
    li $v0, 10
    syscall