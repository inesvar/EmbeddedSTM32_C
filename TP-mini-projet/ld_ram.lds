MEMORY 
{
    BOOT (rx) : ORIGIN = 0x00000000, LENGTH = 1M
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
    SRAM2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}


SECTIONS
{
    .vtor : {
        *(.vtor)
    } > FLASH

    .text : {
        *(.text)
        _flashdata = . ;
    } > FLASH

    .rodata : {
        *(.rodata)
    } > FLASH

    .data : {
        _data = . ;
        *(.data)
        _edata = . ;
    } > SRAM1 AT> FLASH 

    .bss : {
        _bstart = . ;
        *(.bss) *(*COMMON*)
        _bend = . ;
    } > SRAM1 AT> FLASH
}

stack_start = ORIGIN(SRAM2) + LENGTH(SRAM2);
ENTRY(_start)

