.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start

_start :
    ldr sp, =0x10008000
    bl main

_exit :
    b _exit
