#include <b4.asm>

; This'll be an entirely 4-Bit Mandelbrot Implementation.
; The numbers will be laid out as follows:
; SIID, range from -11.1 to +11.1 (binary), so -3 to 3.5
; 

; iterate over y
; iterate over x

; set coordinate to check
; no mapping of the range, we will give in range of -2 to 2
; memory locations
ZX = 0
ZY = 1
TEMP = 2
MULTIPLYTEMP = 3
ITERATOR = 4

; last 8 Byte for pixel output??

; constants
ITERATORLIMIT = 16
COMPAREVALUE = 4

; NOTES
; when mulitpling, we increment a value to keep track of
; how close we are to the desired value. we can use an equal check for this!

; check if ITERATOR is greater than ITERATORLIMIT (can also be equal to)
; --- tmp = zx
; load zx into TMP

; --- zx = zx*zx - zy*zy + cx
; mulitply zx with itself
; multiply zx with zy*zy
; subtract zx² and (zx*zy)
; add cx
; store into zx

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