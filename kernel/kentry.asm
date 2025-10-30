[section .text.kentry]
[bits 32]

[global kentry]
kentry:
	mov esp, 0x7e00

	[extern kmain]
	call kmain

	hlt
	jmp $
