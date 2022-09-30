.syntax unified
.arch armv7-m
.cpu cortex-m4
<<<<<<< HEAD
.thumb
=======

>>>>>>> c754556fee4266780145dd7b94c065a2a829927d
.global _start

_start :
    ldr sp, =0x10008000
<<<<<<< HEAD
    bl main

_end :
    b _end
    
=======
    b main
    
>>>>>>> c754556fee4266780145dd7b94c065a2a829927d
