ENTRY(_start)

SECTIONS
{
	/* Starts at LOADER_ADDR. */
	. = 0x8000;
	__start = .;
	__text_start = .;
	.text :
	{
		KEEP(*(.text.boot))
		*(.text)
	}
	/* align to page size */
	. = ALIGN(4096);
	__text_end = .;

	__rodata_start = .;
	.rodata :
	{
		*(.rodata)
	}
	/* align to page size */
	. = ALIGN(4096);
	__rodata_end = .;

	__data_start = .;
	.data :
	{
		*(.data)
	}
	/* align to page size */
	. = ALIGN(4096);
	__data_end = .;

	__bss_start = .;
	.bss :
	{
		bss = .;
		*(.bss)
	}
	/* align to page size */
	. = ALIGN(4096);
	__bss_end = .;
	__end = .;
}