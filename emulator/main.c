#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MEMSIZE 256
typedef unsigned char byte;

byte INTMEM[MEMSIZE] = {
	0x30, 0x58, 0x01, 0x30, 0xf9, 0x72, 0xfa, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0xf1, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
};

int main(int argc, char *argv[]) {
	FILE *fptr;
	byte mem[MEMSIZE];
	int maxCycle = -1;
	int currentCycle = 0;
	
	// Argument Handling
	if (argc > 1) {
		// Get the file
		if ((fptr = fopen(argv[1],"rb")) == NULL){
			printf("Error! opening file");

			// Program exits if the file pointer returns NULL.
			return 1;
		}
		//while()
		fread(&mem, sizeof(byte), MEMSIZE, fptr); 
		fclose(fptr);
		if (argc > 2) {
			// Stop after # of cycles
			maxCycle = atoi(argv[2]);
		}
	} else {
		for (int i = 0; i < MEMSIZE; i++) {
			mem[i] = INTMEM[i];
		}
	}
	// Regs
	byte A = 0;
	byte B = 0;
	byte PC = 0;
	byte conditionalFlag = 0;
	
	// Old Regs
	byte oldA = 0;
	byte oldB = 0;
	byte oldPC = 0;
	byte oldConditionalFlag = 0;
	
	// Internal magics
	byte inst, immediate = 0x0;
	byte jumped = 0;
	
	while(currentCycle < maxCycle) {
		inst = mem[PC] & 0x0F;
		immediate = (mem[PC] & 0xF0) >> 4;
		printf("%02X: ", PC);
		//printf("A:%X, B: %X | PC:%02X\n",A,B,PC);
		//printf("Inst: %X, immediate: %X | A:%X, B: %X | PC:%02X\n", inst,immediate,A,B,PC);
		switch(inst) {
			// A mode
			case 0x0: // LDI
				A = immediate;
				printf("LDI %01X,A", immediate);
				break;
			case 0x1: // LD
				A = mem[0xF0 | immediate];
				printf("LD [%01X],A (%01X)", immediate, A);
				break;
			case 0x2: // ADD
				A = A + immediate + conditionalFlag;
				if (A > 0xF) {
					A = A & 0xF;
					conditionalFlag = 1;
				} else {
					conditionalFlag = 0;
				}
				printf("ADD %01X,A (%d+%d+%d)", immediate, oldA, immediate, oldConditionalFlag);
				break;
			case 0x3: // NAND
				A = (~(A & immediate) & 0xF);
				printf("NAND %01X,A (%d nand %d)", immediate, oldA, immediate);
				break;
			case 0x4: // CMP
				printf("CMP ");
				switch(immediate & 0b0111) {
					case 0: // Set
						conditionalFlag = 1;
						printf("I");
						break;
					case 1: // Zero
						conditionalFlag = (A == 0);
						printf("Z");
						break;
					case 2: // Equal
						conditionalFlag = (A == B);
						printf("E");
						break;
					case 3: // Sign
						conditionalFlag = ((A&0b1000) >> 3);
						printf("S");
						break;
					default:
						printf("Invalid condition!\n");
				}
				break;
			case 0x5: // ST
				mem[0xF0 | immediate] = A;
				printf("ST A,[%01X] (%01X)", immediate, A&0xF);
				break;
			case 0x6: // JP
				PC = (PC & 0xF0) | immediate;
				jumped = 1;
				printf("JP (near)");
				break;
			case 0x7: // JPC
				if (conditionalFlag) {
					PC = (PC & 0xF0) | immediate;
					jumped = 1;
				}
				printf("JPC (near)");
				break;
			// B mode
			case 0x8: // LDI
				B = immediate;
				printf("LDI %01X,B", immediate);
				break;
			case 0x9: // LD
				B = mem[0xF0 | immediate];
				printf("LD [%01X],B (%01X)", immediate, B);
				break;
			case 0xA: // ADD
				A = A + B + conditionalFlag;
				if (A > 0xF) {
					A = A & 0xF;
					conditionalFlag = 1;
				} else {
					conditionalFlag = 0;
				}
				printf("ADD B,A (%d+%d+%d)", oldA, oldB, oldConditionalFlag);
				break;
			case 0xB: // NAND
				A = (~(A & B) & 0xF);
				printf("NAND B,A (%d nand %d)", oldA, oldB);
				break;
			case 0xC: // CMP
				printf("CMP ");
				switch(immediate & 0b0111) {
					case 0: // Reset
						conditionalFlag = 0;
						printf("O");
						break;
					case 1: // Not Zero
						conditionalFlag = ~(A == 0);
						printf("NZ");
						break;
					case 2: // Not Equal
						conditionalFlag = ~(A == B);
						printf("NE");
						break;
					case 3: // Not Sign
						conditionalFlag = ~((A&0b1000) >> 3);
						printf("NS");
						break;
					default:
						printf("Invalid condition!\n");
				}
				break;
			case 0xD: // ST
				mem[0xF0 | immediate] = B;
				printf("ST B,[%01X] (%01X)", immediate, B);
				break;
			case 0xE: // JP
				PC = (immediate << 4) & 0xF0;
				jumped = 1;
				printf("JP (far)");
				break;
			case 0xF: // JPC
				if (conditionalFlag) {
					PC = (immediate << 4) & 0xF0;
					jumped = 1;
				}
				printf("JPC (far)");
				break;
		}
		printf("\n");
		// Limit Registers to intended Range
		A         = A          & 0x0F;
		B         = B          & 0x0F;
		PC        = PC         & 0xFF;
		conditionalFlag = conditionalFlag  & 0x01;
		// Print changes
		if (A != oldA) {
			printf("\t\tA: %01X -> %01X\n", oldA, A);
		}
		if (B != oldB) {
			printf("\t\tB: %01X -> %01X\n", oldB, B);
		}
		if (PC != oldPC) {
			printf("\t\tPC: 0x%02X -> 0x%02X\n", oldPC, PC);
		}
		if (conditionalFlag != oldConditionalFlag) {
			printf("\t\tCarry: %d -> %d\n", oldConditionalFlag, conditionalFlag);
		}
		if (!jumped) {
			PC++;
		} else {
			jumped = 0;
		}
		oldA = A;
		oldB = B;
		oldPC = PC;
		oldConditionalFlag = conditionalFlag;
		currentCycle++;
	}
	return 0;
}