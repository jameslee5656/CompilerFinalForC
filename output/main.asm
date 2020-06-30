;************** output/main.asm ****************
;
	global _main
_intstr	DB	'     ','$'
_buf	TIMES 256 DB ' '
	DB 13,10,'$'
_main:
	mov       rax, 0x02000004         ; system call for write
	mov       rdi, 1                  ; file handle 1 is stdout
	mov       rsi, message            ; address of string to output
	mov       rdx, 13                 ; number of bytes
	syscall                           ; invoke operating system to do the write
	mov       rax, 0x02000001         ; system call for exit
	xor       rdi, rdi                ; exit code 0
	syscall                           ; invoke operating system to exit
	section   .data
	message:  db	"Hello to NASM World", 30      ; note the newline at the end
