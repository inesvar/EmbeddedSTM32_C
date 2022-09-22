.syntax unified
.arch armv7-m
.cpu cortex-m4

.global _start


    /* PROCEDURE PRINCIPALE */

_start :

    //recuperer l adresse de la chaine
    adr r0, str_bonjour

    //adresse de destination
    ldr r1, =0x10001010

    //appel a la copie 
    bl copy

    //adresse de destination
    ldr r1, =0x10001050

    //appel a la copie 
    bl copy



end :
    b end



    /* PROCEDURE DE COPIE */

copy :
    mov r2, r0
loop :
    ldrb r3, [r2]
    strb r3, [r1]
    add r2, r2, #1
    add r1, r1, #1
    lsl r3, r3, #24
    cmp r3, #0
    bne loop

    bx lr


    /* CHAINE DE CARACTERES */

str_bonjour :
    .asciz "Bonjour le monde!"



