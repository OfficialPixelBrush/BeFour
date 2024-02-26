#include "b4.asm"
firstTerm = 0
secondTerm = 1
nextTerm = 2

; init
LDI 0,B
ST B,[firstTerm]
LDI 1,B
ST B,[secondTerm]
ST B,[nextTerm]
JPF loop

; fibo loop
loop:
LD [secondTerm],A
ST A,[firstTerm]
LD [nextTerm],B
ST B,[secondTerm]
ADD B
ST A,[nextTerm]
JPCF finished 
JPN 0

; A should have 5, B should have d
finished:
JPN 0 ; infinite loop