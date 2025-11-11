	[bits 16]

	KERNEL_OFFSET equ 0x8000

_start:
	jmp real_start
times 62 db 0
real_start:
	cli

	xor ax, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov sp, 0x7c00
	mov bp, sp

	mov si, boot_msg
	call puts16

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

	mov si, disk_msg
	call puts16

	; lets create mode info table
	;mov ax, 0x4f00
	;mov di, 0x7e00
	;int 10h

	; load gdt
	lgdt [gdt_descriptor]

	; enable a20
	in al, 0x92
	or al, 2
	out 0x92, al

	mov si, leave_msg
	call puts16

	; enable protected mode
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	; jump to kernel
	jmp GDT_CODE:KERNEL_OFFSET

error:
	mov si, disk_err_msg
	call puts16
	jmp $

boot_msg: db "Booting kernel...", 0x0a, 0x0d, 0
disk_msg: db "Read disk, setting up protected mode...", 0x0a, 0x0d, 0
leave_msg: db "Goodbye real mode!", 0x0a, 0x0d, 0

disk_err_msg: db "The disk could not be read.", 0

puts16:
	pusha
	mov ah, 0x0e
.loop:
	lodsb
	test al, al
	jz .done
	int 0x10
	jmp .loop
.done:
	popa
	ret

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
