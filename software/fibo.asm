#include "b4.asm"
firstTerm = 0
secondTerm = 1
nextTerm = 2

; This tests:
; LDI A/B
; LD A/B
; ST A/B
; ADD B
; JP A/B
; JPC B (with carry)
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
; only use this once conditionals are in lol
JPCF finished 
JPN 0

; A should have 5, B should have d
finished:
