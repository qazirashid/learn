global _start
section .data
	msg db "Hello World", 0x0a
	len equ $ - msg
section .text
_start:
mov eax, 4 ;sys_write system call
mov ebx, 1 ; file descriptor to write to
mov ecx, msg ; address of first byte in byte array to be written
mov edx, len ; number of bytes to be written
int 0x80  ; soft interupt to initiate system call
mov eax, 1; exit system call
mov ebx, 0 ; exit status
int 0x80 ; initiate exit system call
	
