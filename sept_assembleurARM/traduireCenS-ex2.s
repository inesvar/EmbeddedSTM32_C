.syntax unified
.arch armv7-m
.cpu cortex-m4

.global _start


/* TRADUCTION DU CODE

uint32_t * a;
uint32_t * b;
uint32_t * c;
...
*a += *c;
*b += *c;

 */


ldr r0, var_a
ldr r1, var_c
ldr r0, [r0] 
ldr r1, [r1]
ldr r2, [r0] //dereferencement
ldr r3, [r1] //dereferencement
add r2, r2, r3
str r2, [r0]


ldr r0, var_a
ldr r1, var_b
ldr r0, [r0]
ldr r1, [r1]
ldr r2, [r0] //dereferencement
ldr r3, [r1] //dereferencement
add r2, r2, r3
str r2, [r0]


var_a :
    .word a

var_b :
    .word b

var_c : 
    .word c




