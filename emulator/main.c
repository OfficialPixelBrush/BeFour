#include <stdio.h>
typedef unsigned char byte;



int main() {
	byte mem[256] = {0x30,0x58,0x01,0x30,0xf9,0x52,0xfa,0x04};
	byte A,B,PC = 0x00;
	byte oldA, oldB, oldPC = 0x00;
	byte inst, data = 0x0;
	byte carryFlag = 0;
	
	while(1) {
		inst = mem[PC] & 0x0F;
		data = (mem[PC] & 0xF0) >> 4;
		//printf("A:%X, B: %X | PC:%02X\n",A,B,PC);
		//printf("Inst: %X, Data: %X | A:%X, B: %X | PC:%02X\n", inst,data,A,B,PC);
		switch(inst) {
			// A mode
			case 0x0: // LDI
				A = data;
				printf("LDI %d,A", data);
				break;
			case 0x1: // PT
				A = B;
				printf("PT A");
				break;
			case 0x2: // ADD
				A = A + data;
				if (A > 0xF) {
					A = A & 0xF;
					carryFlag = 1;
				} else {
					carryFlag = 0;
				}
				printf("ADD %d,A", data);
				break;
			case 0x3: // NAND
				A = (~(A & data) & 0xF);
				printf("NAND %d,A", data);
				break;
			case 0x4: // LD
				A = mem[0xF0 | B];
				printf("LD [%d],A", B);
				break;
			case 0x5: // CMP
				if (A==B) {
					carryFlag = 1;
				} else {
					carryFlag = 0;
				}
				printf("CMP (A==B)");
				break;
			case 0x6: // JPC
				if (carryFlag) {
					PC = (PC & 0xF0) | data;
				}
				printf("JPC (near)");
				break;
			case 0x7: // JPZ
				if (A==0) {
					PC = (PC & 0xF0) | data;
				}
				printf("JPZ (near)");
				break;
			// B mode
			case 0x8: // LDI
				B = data;
				printf("LDI %d,B", data);
				break;
			case 0x9: // PT
				B = A;
				printf("PT B");
				break;
			case 0xA: // ADD
				A = A + B;
				if (A > 0xF) {
					A = A & 0xF;
					carryFlag = 1;
				} else {
					carryFlag = 0;
				}
				printf("ADD (%d),A", B);
				break;
			case 0xB: // NAND
				A = (~(A & B) & 0xF);
				printf("NAND (%d),A", B);
				break;
			case 0xC: // ST
				mem[0xF0 | B] = A;
				printf("ST A,[%d]", B);
				break;
			case 0xD: // CMP
				if (A!=B) {
					carryFlag = 1;
				} else {
					carryFlag = 0;
				}
				printf("CMP B");
				break;
			case 0xE: // JPC
				if (carryFlag) {
					PC = (data << 4) & 0xF0;
				}
				printf("JPC (far)");
				break;
			case 0xF: // JPZ
				if (A==0) {
					PC = (data << 4) & 0xF0;
				}
				printf("JPZ (far)");
				break;
		}
		printf("\n");
		// Print changes
		if (A != oldA) {
			printf("\t\tA: %d -> %d\n", oldA, A);
		}
		if (B != oldB) {
			printf("\t\tB: %d -> %d\n", oldB, B);
		}
		if (PC != oldPC) {
			printf("\t\tPC: 0x%02X -> 0x%02X\n", oldPC, PC);
		}
		PC++;
		A  = A  & 0x0F;
		B  = B  & 0x0F;
		PC = PC & 0xFF;
		oldA = A;
		oldB = B;
		oldPC = PC;
	}
	return 0;
}