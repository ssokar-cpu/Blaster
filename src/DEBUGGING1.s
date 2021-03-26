BITS  32
global DEBUGGING1
global _GET_HEADER_DEBUGGING1:

;; sys/syscall.h
%define SYS_write	4
%define SYS_mmap2	192
%define SYS_clone	120
%define SYS_exit	1

;; unistd.h
%define STDIN		0
%define STDOUT		1
%define STDERR		2

;; sched.h
%define CLONE_VM	0x00000100
%define CLONE_FS	0x00000200
%define CLONE_FILES	0x00000400
%define CLONE_SIGHAND	0x00000800
%define CLONE_PARENT	0x00008000
%define CLONE_THREAD	0x00010000
%define CLONE_IO	0x80000000

;; sys/mman.h
%define MAP_GROWSDOWN	0x0100
%define MAP_ANONYMOUS	0x0020
%define MAP_PRIVATE	0x0002
%define PROT_READ	0x1
%define PROT_WRITE	0x2
%define PROT_EXEC	0x4

%define THREAD_FLAGS \
 CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_PARENT|CLONE_THREAD|CLONE_IO

%define STACK_SIZE	(4096 * 1024)

DEBUGGING1:
	; Spawn a few threads
	mov ebx, __DEBUGGING1_TH
	CALL DEBUGGING1_CREATE
	RET

;; void threadfn(void)
__DEBUGGING1_TH:
	JMP __DEBUGGING1_TH

;; long thread_create(void (*)(void))
DEBUGGING1_CREATE:
	push ebx
	call DEBUGGING1_STACK_CREATE
	lea ecx, [eax + STACK_SIZE - 8]
	pop dword [ecx]
	mov ebx, THREAD_FLAGS
	mov eax, SYS_clone
	int 0x80
	ret

;; void *stack_create(void)
DEBUGGING1_STACK_CREATE:
	mov ebx, 0
	mov ecx, STACK_SIZE
	mov edx, PROT_WRITE | PROT_READ
	mov esi, MAP_ANONYMOUS | MAP_PRIVATE | MAP_GROWSDOWN
	mov eax, SYS_mmap2
	int 0x80
	ret

_GET_HEADER_DEBUGGING1:
	LEA EAX, [REL DEBUGGING1_STRUCT]
	RET

DEBUGGING1_STRUCT:
	DB 0X00,	;; -- UINT8_T -- ;;											  
	DB 0X01,	;; -- ERROR -- ;;										  
	
