#include "b4.asm"
variable1 = 5
variable2 = 7

; this program was written with BasicText!
LDI variable1,A
LDI variable2,B
ADD B
ST A,[15]
JPN 4