.data
  myMessage: .asciiz "Hello World\n"

.text
  li $v0, 4 # print string
  la $a0, myMessage # load address of string
  syscall
  li $v0, 10 # exit
  syscall

