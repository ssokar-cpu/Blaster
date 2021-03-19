BITS 32

global __Syscall

__Syscall:

	mov eax, [ESP+4]
	mov EBX, [ESP+8]	
	mov ECX, [ESP+12]
	INT 0X80
	RET
