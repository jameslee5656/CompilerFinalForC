;************** output/main.asm ****************
;
	global _main
_intstr	DB	'     ','$'
_buf	TIMES 256 DB ' '
;%include	"ORGFile/dispstr.mac"
;%include	"ORGFile/itostr.mac"
;%include	"ORGFile/readstr.mac"
;%include	"ORGFile/strtoi.mac"ls
;%include	"ORGFile/newline.mac"
	DB 13,10,'$'
_main:
;	dispstr   message
;	mov       rax, 0x02000004         ; system call for write
	mov       rdi, 1                  ; file handle 1 is stdout
;	mov       rsi, vk_const            ; address of string to output
;	mov       rdx, 13                 ; number of bytes
;	syscall                           ; invoke operating system to do the write 
;*****************************************************
;   pop       rsi
;	mov       rax, 0x02000004         ; system call for write
;	mov       rdi, 1                  ; file handle 1 is stdout
;	mov       rsi, message            ; address of string to output
;	mov       rdx, 13                 ; number of bytes
;	syscall
;*****************************************************
;	mov       rax, 0x02000001         ; system call for exit
;	xor       rdi, rdi                ; exit code 0
;	syscall                           ; invoke operating system to exit
;*****************************************************
	section   .data
	message:  	db	"hello", 0xA, 0xD	; note the newline at the end
	vk_const:	DW	"10", 0xA, 0xD
;*****************************************************
