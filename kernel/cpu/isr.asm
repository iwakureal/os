[bits 32]

%macro isr_e 1
isr_%1:
	nop
	nop
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
	pop ebx
	iret

global stub_table
stub_table:

%assign i 0
%rep 10
	isr i
	%assign i i+1
%endrep

; TODO: isr 10-255
