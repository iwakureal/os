[section .text.kentry]
[bits 32]

[global kentry]
kentry:
	mov esp, 0x7e00
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	[extern kmain]
	call kmain

	hlt
	jmp $
