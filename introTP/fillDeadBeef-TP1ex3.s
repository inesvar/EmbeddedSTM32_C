.syntax unified
.arch armv7-m
.cpu cortex-m4

.global _start


    /* PROCEDURE PRINCIPALE */

_start:

    // initialisalisation des parametres

    ldr r0, =0xdeadbeef // motif
    ldr r1, =0x10000000 //adresse de la zone memoire a remplir
    ldr r2, =0x00000100 //taille de la zone memoire a remplir

    ldr r3, =0x10000300 //adresse de la 2eme zone memoire ou on recopie
    
    // appel a la fonction de remplissage
    bl fill 


    // initialisalisation des parametres

    ldr r0, =0xc01dcafe // motif
    ldr r1, =0x10000700 // adresse de la zone memoire a remplir
    ldr r2, =0x00001000 //taille de la zone memoire a remplir

    ldr r3, =0x10002500 //adresse de la 2eme zone memoire ou on recopie
    
    // appel a la fonction de remplissage
    bl fill 


end : 
    b end 


    /* LA FONCTION DE REMPLISSAGE */

fill :
    add r2, r2, r1
    mov r4, r1

loop :
    // remplir une zone memoire avec un motif 
    str r0, [r1]
    add r1, r1, #4
    cmp r1, r2
    bne loop


loop2 :
    //copier coller la zone a une adresse differente
    ldr r0, [r4]
    str r0, [r3]
    add r4, r4, #4
    add r3, r3, #4
    cmp r4, r2
    bne loop2

    //fin d execution de la fonction
    bx lr
