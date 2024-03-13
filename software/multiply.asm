#include "b4.asm"

result = 7
iterator = 8
; factor1: A
; factor2: B
NAND 15
ADD 1
; get negative number
; if factor1 is 0, exit
CMP Z
JPCN 11
; otherwise multiply
ST A,[iterator]
LD [result],A
ADD B
ST A,[result]
LD [iterator],A
ADD 1
JPN 2