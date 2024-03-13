#include "b4.asm"

; This'll be an entirely 4-Bit Mandelbrot Implementation.
; The numbers will be laid out as follows:
; SIID, range from -11.1 to +11.1 (binary), so -3 to 3.5
; 

; iterate over y
; iterate over x

; set coordinate to check
; no mapping of the range, we will give in range of -2 to 2
; memory locations
CX = 0
CY = 1
ZX = 2
ZY = 3
TEMP = 4
ITERATOR = 6
multiplyResult = 7
multiplyIterator = 8

; last 8 Byte for pixel output??

; constants
ITERATORLIMIT = 16
COMPAREVALUE = 4

; NOTES
; when mulitpling, we increment a value to keep track of
; how close we are to the desired value. we can use an equal check for this!
LDI 5,A
ST A,[CX]
ST A,[CY]

mandelbrot:
LD [CX],A
ST A,[ZX]
LD [CY],A
ST A,[ZY]

iteration:
; check if ITERATOR is greater than ITERATORLIMIT (can also be equal to)
; --- tmp = zx
; load zx into TMP
LD [ZX],A
ST A,[TEMP]
JPF multiplyZx

; --- zx = zx*zx - zy*zy + cx
; mulitply zx with itself
multiplyZx:
LD [ZX],A
LD [ZX],B
NAND 15
ADD 1
; get negative number
; if factor1 is 0, exit
; otherwise multiply
ST A,[multiplyIterator]
LD [multiplyResult],A
ADD B
ST A,[multiplyResult]
LD [multiplyIterator],A
ADD 1
JPCF multiplyZxFinish
JPN 4 ; to return to start of multipliation
multiplyZxFinish:
LD [multiplyResult],A
ST A,[ZX]
; zySquare = zy * zy
LD [ZY],A
LD [ZY],B
NAND 15
ADD 1
; get negative number
; multiply
ST A,[multiplyIterator]
LD [multiplyResult],A
ADD B
ST A,[multiplyResult]
LD [multiplyIterator],A
ADD 1
JPCF multiplyZyFinish
JPN 6 ; if triggers Carry, 0 has been reached
multiplyZyFinish:
; subtract zx² and zy²
; multiplyResult holds zySquare
LD [multiplyResult],A
NAND 15
ADD 1
; invert zySquare
ST A,[multiplyResult]
LD [multiplyResult],B
LD [ZX],A
ADD B
; add cx
LD [CX],B
ADD B
; store into zx
ST A,[ZX]

; --- zy = 2*tmp*zy + cy
; add tmp onto itself
; multiply with zy
; add cy

; --- if ((zx*zx + zy*zy) > 4):
; multiply zx with itself
; multiply zy with itself
; add zxM and zyM
; check if result is > 4 (software greater than check! yay!)
; if true, return 1 and break out

; if (iterator == iteratorLimit):
; if true, return 0


; if number of iterations reaches iterator limit, then return 0
; if zx*zx + zy*zy > 4, then return 1 