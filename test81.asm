;************** test81.asm ****************
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
test81_msg1	DB	' x=','$'
test81_msg2	DB	' y=','$'
test81_x	DW	0
test81_y	DW	0
_start1:
	PUSH	3
	POP	AX
	MOV	[test81_x], AX
_go2:
	PUSH	WORD [test81_x]
	PUSH	0
	POP	BX
	POP	AX
	CMP	AX, BX
	JG	_go3
	JMP	_go4
_go3:
	PUSH	WORD [test81_x]
	PUSH	3
	POP	BX
	POP	AX
	MUL	BX
	PUSH	AX
	PUSH	6
	POP	BX
	POP	AX
	ADD	AX, BX
	PUSH	AX
	POP	AX
	MOV	[test81_y], AX
	dispstr	test81_msg1
	itostr	test81_x, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	newline
	dispstr	test81_msg2
	itostr	test81_y, _intstr, '$'
	MOV	DX, _intstr
	MOV	AH, 09H
	INT	21H
	newline
	PUSH	WORD [test81_x]
	PUSH	1
	POP	BX
	POP	AX
	SUB	AX, BX
	PUSH	AX
	POP	AX
	MOV	[test81_x], AX
	JMP	_go2
_go4:
	MOV	AX, 4C00H
	INT	21H
