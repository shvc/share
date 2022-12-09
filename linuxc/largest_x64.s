# neghen@intra.nsfocus.com
# xi'an Shannxi
# 2015.06.17 

  .section .data
item_data:
  .quad 1,3,5,7,9,1,10,11,13,14,21,12,18,19,0

  .section .text
  .globl _start
_start:
  movq $0, %rbx
  movq $0, %rdi

start_loop:
  movq item_data(,%rbx, 8), %rcx
  incq %rbx
  cmpq $0, %rcx
  je   exit_loop
  cmpq %rcx, %rdi
  jge  start_loop
  movq %rcx, %rdi
  jmp  start_loop

exit_loop:
  movq $0x3c, %rax
  syscall
