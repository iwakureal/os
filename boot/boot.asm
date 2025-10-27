	[bits 16]

	KERNEL_OFFSET equ 0x8000

_start:
	cli

	mov ax, cs
	mov ds, ax

	xor ax, ax
	mov ss, ax
	mov sp, 0x7c00
	mov bp, sp

	cld
	mov ah, 0x2
	mov al, 63
	mov ch, 0
	mov cl, 2
	mov dh, 0
	; mov dl, boot_drive has been done for us by bios
	xor bx, bx
	mov es, bx
	mov bx, KERNEL_OFFSET
	int 13h
	jc error

	; lets create mode info table
	mov ax, 0x4f00
	mov di, 0x7e00
	int 10h

	; load gdt
	lgdt [gdt_descriptor]

	; enable a20
	in al, 0x92
	or al, 2
	out 0x92, al

	; enable protected mode
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	; load segments
	mov ax, GDT_DATA
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	; jump to kernel
	jmp GDT_CODE:KERNEL_OFFSET

error:
	mov ah, 0x0e
	mov al, 'D'
	int 0x10
	jmp $

gdt_descriptor:
	dw gdt_end - gdt - 1	; gdt size - 1
	dd gdt			; gdt pointer

GDT_CODE equ gdt_code - gdt	; code offset
GDT_DATA equ gdt_data - gdt	; data offset

gdt:
gdt_null:
	dd 0x00000000
	dd 0x00000000
gdt_code:
	dw 0xffff	; limit 0-15
	dw 0x0000	; base 0-15
	db 0x00		; base 16-23
	db 10011010b	; access byte
	db 11001111b	; flags + limit 16-19
	db 0x00		; base 24-31
gdt_data:
	dw 0xffff	; limit 0-15
	dw 0x0000	; base 0-15
	db 0x00		; base 16-23
	db 10010010b	; access byte
	db 11001111b	; flags + limit 16-19
	db 0x00		; base 24-31
gdt_end:
