[bits 32]

%macro isr_e 1
isr_%1:
	push %1
	jmp isr_common_entry
%endmacro

%macro isr 1
isr_%1:
	push 0
	push %1
	jmp isr_common_entry
%endmacro

isr_common_entry:
	pusha

	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	[extern isr_common]
	cld
	call isr_common
this_is_a_problem:
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8 ; pop error code and int num without touching registers
	iret

global stub_table
stub_table:

	%assign i 0
	%rep 256
	dd isr_%+i
		%assign i i+1
	%endrep

isr_handler_stubs:
%assign i 0
%rep 8
	isr i
	%assign i i+1
%endrep
isr_e 8
isr 9
isr_e 10
isr_e 11
isr_e 12
isr_e 13
isr_e 14
isr 15	; reserved
isr 16
isr_e 17
isr 18
isr 19
isr 20
isr_e 21
; 22-27 reserved
%assign i 22
%rep 6
	isr i
	%assign i i+1
%endrep
isr 28
isr_e 29
isr_e 30
isr 31	; reserved
%assign i 32
%rep (256-i)
	isr i
	%assign i i+1
%endrep
