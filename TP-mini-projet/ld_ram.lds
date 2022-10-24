MEMORY 
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
    SRAM2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}


SECTIONS
{
    .text : {
        *(.text)
    } > SRAM1

    .rodata : {
        *(.rodata)
    } > SRAM1

    .data : {
        _datastart = . ;
        *(.data)
        _dataend = . ;
    } > SRAM1

    .bss : {
        _bstart = . ;
        *(.bss) *(*COMMON*)
        _bend = . ;
    } > SRAM1
}

stack_start = ORIGIN(SRAM2) + LENGTH(SRAM2);
ENTRY(_start)

