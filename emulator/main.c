#include <stdio.h>
#include <stdlib.h>

#define MEMSIZE 256
typedef unsigned char byte;
typedef unsigned short word;

#define printCurrentState 1 << 0
#define printExecInst     1 << 1
#define printChanges 	  1 << 2

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

// Internal Vars
byte mem[MEMSIZE];
int maxCycle = -1;
int currentCycle = 0;
int debugOutput = 0;

// Regs
byte A = 0;
byte B = 0;
word PC = 0;
byte conditionalFlag = 0;

// Old Regs
byte oldA = 0;
byte oldB = 0;
word oldPC = 0;
byte oldConditionalFlag = 0;

// Internal magics
byte inst, immediate = 0x0;
byte jumped = 0;

int printIndent() {
	if (debugOutput & ~printChanges) {
		printf("\t\t");
	}
}

int printExecutedInstruction() {
	printf("%02X: ", PC);
	switch(inst) {
		// A mode
		case 0x0: // LDI
			printf("LDI %01X,A", immediate);
			break;
		case 0x1: // LD
			printf("LD [%01X],A (%01X)", immediate, A);
			break;
		case 0x2: // ADD
			printf("ADD %01X,A (%d+%d+%d)", immediate, oldA, immediate, oldConditionalFlag);
			break;
		case 0x3: // NAND
			printf("NAND %01X,A (%d nand %d)", immediate, oldA, immediate);
			break;
		case 0x4: // CMP
			printf("CMP ");
			switch(immediate & 0b0111) {
				case 0: // Set
					printf("Set");
					break;
				case 1: // Zero
					printf("Zero");
					break;
				case 2: // Equal
					printf("Equal");
					break;
				case 3: // Sign
					printf("Sign");
					break;
				default:
					printf("Invalid condition!\n");
			}
			break;
		case 0x5: // ST
			printf("ST A,[%01X] (%01X%01X)", immediate, A&0xF, B);
			break;
		case 0x6: // STPC
			printf("SP PCL,[%03X]", PC);
			break;
		case 0x7: // JP
			printf("JP");
			break;
		// B mode
		case 0x8: // LDI
			printf("LDI %01X,B", immediate);
			break;
		case 0x9: // LD
			printf("LD [%01X],B (%01X)", immediate, B);
			break;
		case 0xA: // ADD
			printf("ADD B,A (%d+%d+%d)", oldA, oldB, oldConditionalFlag);
			break;
		case 0xB: // NAND
			printf("NAND B,A (%d nand %d)", oldA, oldB);
			break;
		case 0xC: // CMP
			printf("CMP ");
			switch(immediate & 0b0111) {
				case 0: // Reset
					printf("Reset");
					break;
				case 1: // Not Zero
					printf("Not Zero");
					break;
				case 2: // Not Equal
					printf("Not Equal");
					break;
				case 3: // Not Sign
					printf("Not Sign");
					break;
				default:
					printf("Invalid condition!\n");
			}
			break;
		case 0xD: // ST
			printf("ST B,[%01X] (%01X%01X)", immediate, B,B);
			break;
		case 0xE: // JP
			printf("JP (far)");
			break;
		case 0xF: // JPC
			printf("JPC (far)");
			break;
	}
	printf("\n");
	return 0;
}

int main(int argc, char *argv[]) {
	FILE *fptr;
	
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
			debugOutput = atoi(argv[2]);
		}

		if (argc > 3) {
			// Stop after # of cycles
			maxCycle = atoi(argv[3]);
		}
	} else {
		for (int i = 0; i < MEMSIZE; i++) {
			mem[i] = INTMEM[i];
		}
	}
	
	while((currentCycle < maxCycle) || (maxCycle == -1)) {
		inst = mem[PC] & 0x0F;
		immediate = (mem[PC] & 0xF0) >> 4;

		//printf("A:%X, B: %X | PC:%02X\n",A,B,PC);
		if (debugOutput & printCurrentState) {
			printf("Inst: %X, immediate: %X | A:%X, B: %X, Cond:%X | PC:%02X\n", inst,immediate,A,B,conditionalFlag,PC);
		}

		// For multi-byte instructions
		switch(inst & 0b0111) {
			case 0x1: // LD
			case 0x5: // ST
			case 0x6: // STPC
			case 0x7: // JP/JPC
				PC++;
				PC &= 0xFFF;
				immediate = immediate | (mem[PC] << 4);
				printf("Multi-byte:\t");
				break;
		}

		switch(inst) {
			// A mode
			case 0x0: // LDI
				A = immediate;
				break;
			case 0x1: // LD
				A = mem[0xF0 | immediate] >> 4;
				break;
			case 0x2: // ADD
				A = A + immediate + conditionalFlag;
				if (A > 0xF) {
					A = A & 0xF;
					conditionalFlag = 1;
				} else {
					conditionalFlag = 0;
				}
				break;
			case 0x3: // NAND
				A = (~(A & immediate) & 0xF);
				break;
			case 0x4: // CMP
				switch(immediate & 0b0111) {
					case 0: // Set
						conditionalFlag = 1;
						break;
					case 1: // Zero
						conditionalFlag = (A == 0);
						break;
					case 2: // Equal
						conditionalFlag = (A == B);
						break;
					case 3: // Sign
						conditionalFlag = ((A&0b1000) >> 3);
						break;
					default:
						break;
				}
				break;
			case 0x5: // ST
				mem[immediate] = (A << 4) | B;
				break;
			case 0x6: // STPC
				mem[immediate] = ((PC&0x00F) << 4) | B;
				break;
			case 0x7: // JP
				PC = immediate;
				jumped = 1;
				break;
			// B mode
			case 0x8: // LDI
				B = immediate;
				break;
			case 0x9: // LD
				B = mem[immediate] >> 4;
				break;
			case 0xA: // ADD
				A = A + B + conditionalFlag;
				if (A > 0xF) {
					A = A & 0xF;
					conditionalFlag = 1;
				} else {
					conditionalFlag = 0;
				}
				break;
			case 0xB: // NAND
				A = (~(A & B) & 0xF);
				break;
			case 0xC: // CMP
				switch(immediate & 0b0111) {
					case 0: // Reset
						conditionalFlag = 0;
						break;
					case 1: // Not Zero
						conditionalFlag = ~(A == 0);
						break;
					case 2: // Not Equal
						conditionalFlag = ~(A == B);
						break;
					case 3: // Not Sign
						conditionalFlag = ~((A&0b1000) >> 3);
						break;
					default:
						break;
				}
				break;
			case 0xD: // ST
				mem[immediate] = (B << 4) | B;
				break;
			case 0xE: // STPC
				mem[immediate] = ((PC&0xFF0) >> 4);
				break;
			case 0xF: // JPC
				if (conditionalFlag) {
					PC = immediate;
					jumped = 1;
				}
				break;
		}
		if (debugOutput & printExecInst) {
			printExecutedInstruction();
		}
		// Limit Registers to intended Range
		A         = A          &  0x0F;
		B         = B          &  0x0F;
		PC        = PC         & 0xFFF;
		conditionalFlag = conditionalFlag  & 0x01;
		// Print changes
		if (debugOutput & printChanges) {
			if (A != oldA) {
				printIndent();
				printf("A:\t%01X -> %01X\n", oldA, A);
			}
			if (B != oldB) {
				printIndent();
				printf("B:\t%01X -> %01X\n", oldB, B);
			}
			if (PC != oldPC) {
				printIndent();
				printf("PC:\t%02X -> %02X\n", oldPC, PC);
			}
			if (conditionalFlag != oldConditionalFlag) {
				printIndent();
				printf("Cond:\t%d -> %d\n", oldConditionalFlag, conditionalFlag);
			}
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