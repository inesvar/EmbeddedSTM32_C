.syntax unified
.arch armv7-m
.cpu cortex-m4

.global _start

_start :
    ldr sp, =0x10008000
    b main
    
