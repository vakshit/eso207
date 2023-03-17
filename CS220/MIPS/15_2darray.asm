.data
# initialize the 2D array
ARRAY: .space 480 # allocate space for 12 x 10 integers

.text
# load the dimensions into registers
lw $t0, 12
lw $t1, 10

# loop over the rows
li $t2, 0 # row index
LOOP1:
  bge $t2, $t0, EXIT1 # if row index >= number of rows, exit loop

  # loop over the columns
  li $t3, 0 # column index
  LOOP2:
    bge $t3, $t1, EXIT2 # if column index >= number of columns, exit loop

    # calculate the index of the current element in the array
    mul $t4, $t2, $t1 # multiply row index by number of columns
    add $t4, $t4, $t3 # add column index to get the element index
    sll $t4, $t4, 2 # multiply by 4 to convert to byte offset

    # load the current element from the array
    lw $t5, ARRAY($t4)

    # do something with the element (e.g., print it)
    # ...

    # increment the column index
    addi $t3, $t3, 1
    j LOOP2

  EXIT2:
    # reset the column index
    li $t3, 0

    # increment the row index
    addi $t2, $t2, 1
    j LOOP1

EXIT1:
