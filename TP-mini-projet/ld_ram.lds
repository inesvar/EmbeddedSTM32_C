MEMORY 
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
    SRAM2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}


SECTIONS
{
    .vtor : {
        _vtor = . ;
        *(.vtor)
        _evtor = . ;
    } > SRAM1 AT> FLASH

    .textinit : {
        crt0.o(.text) init.o(.text)
    } > FLASH

    .text : {
        _text = . ;
        EXCLUDE_FILE (crt0.o init.o) *(.text)
        _etext = . ;
    } > SRAM1 AT> FLASH

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
_flashvtor = LOADADDR(.vtor);
_flashdata = LOADADDR(.data);
_flashtext = LOADADDR(.text);
ENTRY(_start)

