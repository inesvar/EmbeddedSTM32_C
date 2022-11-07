.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start

.thumb_func
_start :
    ldr sp, =stack_start
    bl init_data
    bl init_bss
    bl init_text
    bl main

_exit :
    b _exit
