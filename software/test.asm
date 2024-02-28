#include "b4.asm"
firstTerm = 0
secondTerm = 1
nextTerm = 2

returnCode = 15;

; This tests:
; LDI A/B
; LD A/B
; ST A/B
; ADD B
; JP A/B
; JPC B (with carry)

; reset returnCode
LDI 0,A
ST A,[returnCode]

; init
LDI 0,B
ST B,[firstTerm]
LDI 1,B
ST B,[secondTerm]
ST B,[nextTerm]
ST B,[returnCode]
; init success
LDI 1,A
ST A,[returnCode]
JPF loop

; fibo loop
loop:
LD [secondTerm],A
ST A,[firstTerm]
LD [nextTerm],B
ST B,[secondTerm]
ADD B
ST A,[nextTerm]
JPCF finishedFibo
JPN 0

; A should have 5, B should have d
finishedFibo:
CMP dis
ADD 10 ; 5+10 = 15
NAND 15 ; 15 NAND 15 = 0
CMP NZ
JPCF fail
; fibo success
LDI 2,A
ST A,[returnCode]
; CMP with Zero Flag
JPF results

results:
LDI 0,B
LD [returnCode],A
JPN 2

fail:
LD [returnCode],B
LDI 0,A
JPN 2