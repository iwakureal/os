ENTRY(kentry)

SECTIONS {
	. = 0x8000;

	.text.kentry : {
		*(.text.kentry)
	}		

	.text : {
		*(.text*)
	}

	.rodata : {
		*(.rodata*)
	}

	.data : {
		*(.data*)
	}

	.bss : {
		*(.bss*)
		*(COMMON)
	}

	/DISCARD/ : {
		*(.eh_frame)
		*(.comment)
	}
}