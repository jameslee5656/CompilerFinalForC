;************** test82.asm ****************
;
	ORG	100H
	JMP	_start1
_intstr	DB	'     ','$'
_buf	TIMES 256 DB ' '
	DB 13,10,'$'
%include	"dispstr.mac"
%include	"itostr.mac"
%include	"readstr.mac"
%include	"strtoi.mac"
%include	"newline.mac"
test82_msg1	DB	' x=','$'
test82_msg2	DB	' y=','$'
test82_x	DW	0
test82_y	DW	0
_start1:
	PUSH	3
	POP	AX
	MOV	[test82_x], AX
_go2:
	PUSH	WORD [test82_x]
	JMP	_go3
_go2:
_go3:
	dispstr	test82_msg1
	itostr	test82_x, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	newline
	dispstr	test82_msg2
	itostr	test82_y, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	newline
	PUSH	WORD [test82_x]
	PUSH	1
	POP	BX
	POP	AX
	SUB	AX, BX
	PUSH	AX
	POP	AX
	MOV	[test82_x], AX
	MOV	AX, 4C00H
	INT	21H
