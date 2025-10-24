SECTIONS {
	. = 0x7c00;
	.text : {
		*(.text);
	}
	.data : {
		*(.data);
	}

	. = 0x7c00 + 510;
	.boot_sig : {
		SHORT(0xaa55)
	}
}
