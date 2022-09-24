/* TRADUCTION DU CODE :

uint32_t a;
...
for (uint8_t i=0; i<=a; i++) {
        g();
}
*/

.syntax unified
.arch armv7-m
.cpu cortex-m4

.global _start



    ldr r0, var //declaration de a
    mov r1, #0

loop :
    bl g
    add r1, r1, #1
    and r1, r1, #255 //masque pour imiter un uint8_t
    ldr r2, [r0] //on relit la valeur de a
    cmp r1, r2
    bls loop //si inferieur ou egal
    bx lr

var :
    .word a


/* 

Meme code MAIS i n'est plus un uint8_t mais un int

*/

//Les int sont generalement sur 4 octets
//la seule difference avec le code precedent est qu'on n'a plus besoin du masque


    ldr r0, var2 //declaration de a

    mov r1, #0
loop2 :
    bl g
    add r1, r1, #1
    ldr r2, [r0] //on relit la valeur de a
    cmp r1, r2
    bls loop //si inferieur ou egal
    bx lr

var2 :
    .word a


