BITS 32

global Syscall0
global Syscall1
global Syscall2
global Syscall3
global Syscall4
global Syscall5
global Syscall6

Syscall0:
	mov EAX,[ESP+4]
	INT 0X80
	RET

Syscall1:
	mov EAX,[ESP+4]
	mov EBX,[ESP+8]	
	INT 0X80
	RET

Syscall2:

	mov EAX,[ESP+4]
	mov EBX,[ESP+8]	
	mov ECX,[ESP+12]
	INT 0X80
	RET

Syscall3:
	mov EAX,[ESP+4]
	mov EBX,[ESP+8]	
	mov ECX,[ESP+12]
	MOV EDX,[ESP+16]
	INT 0X80
	RET

Syscall4:
	mov EAX,[ESP+4]
	mov EBX,[ESP+8]	
	mov ECX,[ESP+12]
	MOV EDX,[ESP+16]
	MOV ESI,[ESP+20]
	INT 0X80
	RET

Syscall5:
	mov EAX,[ESP+4]
	mov EBX,[ESP+8]	
	mov ECX,[ESP+12]
	MOV EDX,[ESP+16]
	MOV ESI,[ESP+20]
	MOV EDI,[ESP+24]
	INT 0X80
	RET

Syscall6:
	MOV EAX,[ESP+4]
	MOV EBX,[ESP+8]
	MOV ECX,[ESP+12]
	MOV EDX,[ESP+16]
	MOV ESI,[ESP+20]
	MOV EDI,[ESP+24]
	PUSH EBP
	MOV EBP, [ESP+32]
	INT 0X80	
	POP EBP
	RET
