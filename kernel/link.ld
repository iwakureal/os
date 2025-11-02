ENTRY(kentry)

SECTIONS {
	. = 0x8000;

	.text.kentry : {
		*(.text.kentry)
	}		

	.text : {
		*(.text)
	}

	.data : {
		*(.data)
	}

	.rodata : {
		*(.rodata)
	}

	.bss : {
		*(.bss)
	}
}
