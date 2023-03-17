.data
prompt: .asciiz "Enter a float value: "
 
.text
main:
    # Print prompt message
    li $v0, 4
    la $a0, prompt
    syscall
 
    # Read float value from console
    # syscall 5 for reading an integer value
    li $v0, 6    # system call number for reading a float value
    syscall
    mov.s $f12, $f0    # move float value from $f0 to $f12 for display
 
    # Display input value
    li $v0, 2
    syscall
 
    # Exit program
    li $v0, 10
    syscall
