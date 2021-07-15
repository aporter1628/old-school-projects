#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include<string.h>
#include "computer.h"
#undef mips			/* gcc already has a def for mips */

unsigned int endianSwap(unsigned int);

void PrintInfo (int changedReg, int changedMem);
unsigned int Fetch (int);
void Decode (unsigned int, DecodedInstr*, RegVals*);
int Execute (DecodedInstr*, RegVals*);
int Mem(DecodedInstr*, int, int *);
void RegWrite(DecodedInstr*, int, int *);
void UpdatePC(DecodedInstr*, int);
void PrintInstruction (DecodedInstr*);

/*Globally accessible Computer variable*/
Computer mips;
RegVals rVals;

/*
 *  Return an initialized computer with the stack pointer set to the
 *  address of the end of data memory, the remaining registers initialized
 *  to zero, and the instructions read from the given file.
 *  The other arguments govern how the program interacts with the user.
 */
void InitComputer (FILE* filein, int printingRegisters, int printingMemory,
  int debugging, int interactive) {
    int k;
    unsigned int instr;

    /* Initialize registers and memory */

    for (k=0; k<32; k++) {
        mips.registers[k] = 0;
    }
    
    /* stack pointer - Initialize to highest address of data segment */
    mips.registers[29] = 0x00400000 + (MAXNUMINSTRS+MAXNUMDATA)*4;

    for (k=0; k<MAXNUMINSTRS+MAXNUMDATA; k++) {
        mips.memory[k] = 0;
    }

    k = 0;
    while (fread(&instr, 4, 1, filein)) {
	/*swap to big endian, convert to host byte order. Ignore this.*/
        mips.memory[k] = ntohl(endianSwap(instr));
        k++;
        if (k>MAXNUMINSTRS) {
            fprintf (stderr, "Program too big.\n");
            exit (1);
        }
    }

    mips.printingRegisters = printingRegisters;
    mips.printingMemory = printingMemory;
    mips.interactive = interactive;
    mips.debugging = debugging;
}

unsigned int endianSwap(unsigned int i) {
    return (i>>24)|(i>>8&0x0000ff00)|(i<<8&0x00ff0000)|(i<<24);
}

/*
 *  Run the simulation.
 */
void Simulate () {
    char s[40];  /* used for handling interactive input */
    unsigned int instr;
    int changedReg=-1, changedMem=-1, val;
    DecodedInstr d;
    
    /* Initialize the PC to the start of the code section */
    mips.pc = 0x00400000;
    while (1) {
        if (mips.interactive) {
            printf ("> ");
            fgets (s,sizeof(s),stdin);
            if (s[0] == 'q') {
                return;
            }
        }

        /* Fetch instr at mips.pc, returning it in instr */
        instr = Fetch (mips.pc);

        printf ("Executing instruction at %8.8x: %8.8x\n", mips.pc, instr);

        /* 
	 * Decode instr, putting decoded instr in d
	 * Note that we reuse the d struct for each instruction.
	 */
        Decode (instr, &d, &rVals);

        /*Print decoded instruction*/
        PrintInstruction(&d);

        /* 
	 * Perform computation needed to execute d, returning computed value 
	 * in val 
	 */
        val = Execute(&d, &rVals);

	UpdatePC(&d,val);

        /* 
	 * Perform memory load or store. Place the
	 * address of any updated memory in *changedMem, 
	 * otherwise put -1 in *changedMem. 
	 * Return any memory value that is read, otherwise return -1.
         */
        val = Mem(&d, val, &changedMem);

        /* 
	 * Write back to register. If the instruction modified a register--
	 * (including jal, which modifies $ra) --
         * put the index of the modified register in *changedReg,
         * otherwise put -1 in *changedReg.
         */
        RegWrite(&d, val, &changedReg);

        PrintInfo (changedReg, changedMem);
    }
}

/*
 *  Print relevant information about the state of the computer.
 *  changedReg is the index of the register changed by the instruction
 *  being simulated, otherwise -1.
 *  changedMem is the address of the memory location changed by the
 *  simulated instruction, otherwise -1.
 *  Previously initialized flags indicate whether to print all the
 *  registers or just the one that changed, and whether to print
 *  all the nonzero memory or just the memory location that changed.
 */
void PrintInfo ( int changedReg, int changedMem) {
    int k, addr;
    printf ("New pc = %8.8x\n", mips.pc);
    if (!mips.printingRegisters && changedReg == -1) {
        printf ("No register was updated.\n");
    } else if (!mips.printingRegisters) {
        printf ("Updated r%2.2d to %8.8x\n",
        changedReg, mips.registers[changedReg]);
    } else {
        for (k=0; k<32; k++) {
            printf ("r%2.2d: %8.8x  ", k, mips.registers[k]);
            if ((k+1)%4 == 0) {
                printf ("\n");
            }
        }
    }
    if (!mips.printingMemory && changedMem == -1) {
        printf ("No memory location was updated.\n");
    } else if (!mips.printingMemory) {
        printf ("Updated memory at address %8.8x to %8.8x\n",
        changedMem, Fetch (changedMem));
    } else {
        printf ("Nonzero memory\n");
        printf ("ADDR	  CONTENTS\n");
        for (addr = 0x00400000+4*MAXNUMINSTRS;
             addr < 0x00400000+4*(MAXNUMINSTRS+MAXNUMDATA);
             addr = addr+4) {
            if (Fetch (addr) != 0) {
                printf ("%8.8x  %8.8x\n", addr, Fetch (addr));
            }
        }
    }
}

/*
 *  Return the contents of memory at the given address. Simulates
 *  instruction fetch. 
 */
unsigned int Fetch ( int addr) {
    return mips.memory[(addr-0x00400000)/4];
}

/* Decode instr, returning decoded instruction. */
void Decode ( unsigned int instr, DecodedInstr* d, RegVals* rVals) {
    //Fill in the values of DecodedInstr* d based on the instruction type
    //Steps: 
        //1)Distinguish between R format, I format, and J format based on the opcode. For R format the opcode is always 0, for I and J you'll need to check from a   list of possible opcodes
        //2) Use shift instructions to find the rest of the values and put them into d

    //Find out the opcode, which is the first six digits, so shift the instruction right by 26
    d->op = instr >> 26;
    unsigned int temp;

    //First figure out if the instruction is unsupported
    if(d->op == 0) {
        temp = instr << 26;
        temp = temp >> 26;
        if(temp != 33 && temp != 36 && temp != 8 && temp != 37 && temp != 42 && temp != 0 && temp != 2 && temp != 35) {
            exit(0); //The instruction is unsupported so exit
        }
    }
    else {
        if(d->op != 9 && d->op != 12 && d->op != 13 && d->op != 15 && d->op != 2 && d->op != 3 && d->op != 4 && d->op != 5 && d->op != 35 && d->op != 43) {
            exit(0);
        }
    }

    if(d->op == 0) { //If the opcode is 0, the type is r-format
        d->type = R;

        //Figure out the function code for the instruction, which is the last six digits, so shift the instruction left by 26
        temp = instr << 26;
        d->regs.r.funct = temp >> 26;
        //printf("%d\n", d->regs.r.funct);

        //Find rs, which is the second five digits
        //Shift the instruction left by 6 and then right by 27
        temp = instr << 6;
        d->regs.r.rs = temp >> 27;
        
        //rt is the 11 bits from the left and 16 bits from the right
        //Shift left by 11 first and then right by 27
        temp = instr << 11;
        d->regs.r.rt = temp >> 27;

        //rd is 16 bits from the left and 11 bits from the right
        //Shift left by 16 first and then right by 27
        temp = instr << 16;
        d->regs.r.rd = temp >> 27;

        //shamt is 21 digits from the left and 6 digits from the right
        //Shift left by 21 and then right by 27
        temp = instr << 21;
        d->regs.r.shamt = temp >> 27;
    }
    else if(d->op == 2 || d->op == 3) { //The only J-format instructions are j and jal
        d->type = J;

        //The only information we need for J-format is the target
        //The address is the last 26 bits, so shift left by 6 and right by 6
        temp = instr << 6;
        d->regs.j.target = temp >> 6;
        //printf("0x%x\n", d->regs.j.target);
    }
    else{ //The rest are I-format
        d->type = I;
        //Find rs, which is the second five digits
        //Shift the instruction left by 6 and then right by 27
        temp = instr << 6;
        d->regs.i.rs = temp >> 27;

        //rt is the 11 bits from the left and 16 bits from the right
        //Shift left by 11 first and then right by 27
        temp = instr << 11;
        d->regs.i.rt = temp >> 27;

        //Note: andi and ori both do unsigned extension, so for these cases we would make the variable unsigned
        if(d->op == 12 || d->op == 13) {
            unsigned int unsignedTemp; //Declare signedTemp as an unsigned variable
            //The immediate is the last 16 bits so shift left by 16 and right by 16
            unsignedTemp = instr << 16;
            d->regs.i.addr_or_immed = unsignedTemp >> 16;
        }
        else {
            int signedTemp; //Otherwise the immediate is signed
            signedTemp = instr << 16;
            d->regs.i.addr_or_immed = signedTemp >> 16;
        }
    }
    /*else { //Otherwise it is an unsupported instruction
        exit(0);
    }*/
}

/*
 *  Print the disassembled version of the given instruction
 *  followed by a newline.
 */
void PrintInstruction ( DecodedInstr* d) {
    //Use the values in d to print the instruction
    //Distinguish between R-format, I-format, and J-format, and print out the values of each
    //Note: Print the whole 32-bit extended immediate
    char* insType;
    unsigned int temp;

    if(d->type == R) { //R-format instructions
        //The R-format instructions are addu, and, jr, or, slt, sll, srl, subu
        temp = d->regs.r.funct;
        if(temp == 33 || temp == 36 || temp == 37 || temp == 42 || temp == 35) { //addu, subu, and, or, slt all print out just three registers
            switch(temp) {
                case 33: insType = "addu"; break;
                case 35: insType = "subu"; break;
                case 36: insType = "and"; break;
                case 37: insType = "or"; break;
                case 42: insType = "slt"; break;
            }
            
            //The format is insType, rd, rs, rt
            printf("%s\t $%d, $%d, $%d\n", insType, d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
        }
        else if(temp == 0 || temp == 2) {//sll and srl both print out the shamt
            switch(temp) {            
                case 0: insType = "sll"; break;
                case 2: insType = "srl"; break;
            }
            printf("%s\t $%d, $%d, $%d\n", insType, d->regs.r.rd, d->regs.r.rt, d->regs.r.shamt);
        }
        else { //jr is the odd one out
            //Print jr and the value stored in rs in hex
            insType = "jr";
            printf("%s\t $31\n", insType);
        }
    }
    else if(d->type == I) { //I-format instructions
        temp = d->op;
        if(temp == 15) { //lui prints a register and then a hex value
            insType = "lui";
            printf("%s\t 0x%x\n", insType, d->regs.i.addr_or_immed);
        }
        else if(temp == 12 || temp == 13) { //ori and andi print two registers and then a hex value
            switch(temp) {
                case 12: insType = "andi"; break;
                case 13: insType = "ori"; break;
            }
            printf("%s\t $%d, $%d, 0x%x\n", insType, d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed); 
        }
        else if(temp == 4 || temp == 5) { //bne and beq print out two registers and a hex value
            switch(temp) {
                case 4: insType = "beq"; break;
                case 5: insType = "bne"; break;
            }
            printf("%s\t $%d, $%d, 0x%8.8x\n", insType, d->regs.i.rs, d->regs.i.rt, mips.pc + (d->regs.i.addr_or_immed << 2) + 4); 
        }
        else if(temp == 9) { //addiu prints two registers and an immediate (not in hex)
            insType = "addiu";
            printf("%s\t $%d, $%d, %d\n", insType, d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
        }
        else { //Lastly there is lw and sw
            switch(temp) {
                case 35: insType = "lw"; break;
                case 43: insType = "sw"; break;
            }
            printf("%s\t $%d, %d($%d)\n", insType, d->regs.i.rt, d->regs.i.addr_or_immed, d->regs.i.rs);

        }
    } 
    else{ //J-format instructions, both just print out an address
        temp = d->op;
        switch(temp) {            
            case 2: insType = "j"; break;
            case 3: insType = "jal"; break;
        }
        
        printf("%s\t 0x%8.8x\n", insType, (mips.pc & 0xf0000000) | (d->regs.j.target << 2));
    }
        
}

/* Perform computation needed to execute d, returning computed value */
int Execute ( DecodedInstr* d, RegVals* rVals) {
    /* Your code goes here */
    //The ALU portion. The four functionalities are:
        //1) Add or subtract two numbers (subu, addu, addiu)
        //2) Load word and store word
        //3) Branch instructions (bne and beq)
        //4) Shift instructions (sll and srl)
        //5) Comparison instructions (and, andi, or, ori, slt)
        //6) Implementing lui

    int val; //Used to store the changed value
    unsigned int temp;
    //The R-format instructions
    if(d->type == R) {
        temp = d->regs.r.funct;
        int rt = mips.registers[d->regs.r.rt];
        int rs = mips.registers[d->regs.r.rs];
        switch(temp) {
            //These are the add/subtract functions
            case 33: //addu
                rVals->R_rd = rt + rs;
                val = rVals->R_rd; //Store the value of rd in val
                break;
            case 35: //subu
                rVals->R_rd = rs - rt;
                val = rVals->R_rd;
                break;
            
            //These are the comparisons
            case 36: //and
                rVals->R_rd = rs & rt;
                val = rVals->R_rd;
                break;
            case 37: //or
                rVals->R_rd = rs | rt;
                val = rVals->R_rd;
                break;
            case 42: //slt
                if(rs < rt) 
                    rVals->R_rd = 1;
                else
                    rVals->R_rd = 0;
                val = rVals->R_rd;
                break;

            //These are the shifts, just shift rt by the amount of the shamt
            case 0: //sll
                rVals->R_rd = rt << d->regs.r.shamt;
                val = rVals->R_rd;
                break;
            case 2: //srl
                rVals->R_rd = rt >> d->regs.r.shamt;
                val = rVals->R_rd;
                break;
            case 8: //jr
                break; //jr doesn't do anything here
        }
    }
    //The J-format instructions 
    else if(d->type == J) {
        //We don't want J-format to do anything at this stage
        ;
    }
    //The I-format instructions
    else {
        int rs = mips.registers[d->regs.i.rs];
        int rt = mips.registers[d->regs.i.rt];
        temp = d->op;
        switch(temp) {
            case 9: //addiu, add the immediate to rs
                rVals->R_rt = rs + d->regs.i.addr_or_immed;
                val = rVals->R_rt;
                //printf("%d\n", val);
                break;
            case 12: //andi
                rVals->R_rt = rs & d->regs.i.addr_or_immed;
                val = rVals->R_rt;
                break;
            case 13: //ori
                 rVals->R_rt = rs | d->regs.i.addr_or_immed;
                 val = rVals->R_rt;
                 break;
            case 15: //lui, shifts the immediate left by 16 and stores in rt
                rVals->R_rt = d->regs.i.addr_or_immed << 16;
                val = rVals->R_rt;
                break;

            //For bne and beq, if the branch is not being taken, put 0 in val
            case 4: //beq
                if(rs == rt) 
                    val = d->regs.i.addr_or_immed; //The branch is being taken, so put the value of the immediate in val
                else
                    val = 0; //The branch isn't being taken
                break;
            case 5: //bne
                if(rs != rt) 
                    val = d->regs.i.addr_or_immed;
                else
                    val = 0;
                break;
            case 35: //lw, compute rs + immediate and put it in val. IF the immediate is not a multiple of 4, put -1 in val
                if(d->regs.i.addr_or_immed % 4 != 0) {
                    val = -1;
                }
                else {
                    val = rs + d->regs.i.addr_or_immed;
                    
                }
                break;
            case 43: //sw, does basically the same thing as lw
                if(d->regs.i.addr_or_immed % 4 != 0) {
                    val = -1;
                }
                else {
                    rVals->R_rt = rs + d->regs.i.addr_or_immed;
                    val = rVals->R_rt;
                }
                break;
        }
    }

  return val;
}

/* 
 * Update the program counter based on the current instruction. For
 * instructions other than branches and jumps, for example, the PC
 * increments by 4 (which we have provided).
 */
void UpdatePC ( DecodedInstr* d, int val) {
    //Check if the instruction is bne, beq, j, jr, or jal
    unsigned int temp = d->op;
    unsigned int rFunct = d->regs.r.funct;

    //bne and beq
    if(temp == 4 || temp == 5) { 
        //printf("%d\n", val);
        if(val == 0) { //If 0 is in val, the branch is not being taken, so just update pc normally
            mips.pc += 4;
        }
        else { //Otherwise add the immediate multiplied by 4 to mips.pc
            mips.pc = mips.pc + (d->regs.i.addr_or_immed << 2) + 4;
        }
    }

    //j, jr, and jal
    //jal stores its return (current) address into r31
    else if(temp == 2 || temp == 3 || rFunct == 8) {
        if(temp == 2) { //j makes PC equal to the target
            mips.pc = (mips.pc & 0xf0000000) | (d->regs.j.target << 2); //j makes the first four bits of the target equal to the first four bits of PC and multiplies the address by 4
        }
        else if(temp == 3) { //jal does the same thing as j
            //First store the original mips.pc in r31
            mips.registers[31] = mips.pc;
            //Now calculate the new mips.pc
            mips.pc = (mips.pc & 0xf0000000) | (d->regs.j.target << 2);
        }
        else { //jr jumps to the address stored in r31
            mips.pc = mips.registers[31];
        }
    } 
    //Otherwise just increment PC by 4
    else { 
        mips.pc+=4;
    }
}

/*
 * Perform memory load or store. Place the address of any updated memory 
 * in *changedMem, otherwise put -1 in *changedMem. Return any memory value 
 * that is read, otherwise return -1. 
 *
 * Remember that we're mapping MIPS addresses to indices in the mips.memory 
 * array. mips.memory[0] corresponds with address 0x00400000, mips.memory[1] 
 * with address 0x00400004, and so forth.
 *
 */
int Mem( DecodedInstr* d, int val, int *changedMem) {
    if(d->op == 35 || d->op== 43) { //So the program doesn't go here when it's not supposed to
        int retValue = -1;
        *changedMem = -1;
        //Only lw and sw are used here, because they're the only ones that update the memory
        if(val == -1 || (val + 0x00400000) > 0x00403fff || (val + 0x00400000) < 0x00401000) { //This means the memory location is not word-aligned or it is out of bounds
            printf("Memory Access Exception at %8.8x: address %8.8x\n", mips.pc, (val + 0x00400000));
            exit(0);
        }
        if(d->op == 35) { //For sw
            int location = val + 0x00400000;
            *changedMem = location;
            mips.memory[location] = mips.registers[d->regs.r.rt]; //Store the value of rt into memory
        } 
        else { //For lw
            int location = val + 0x00400000;
            retValue = location;
            mips.registers[d->regs.r.rt] = mips.memory[location]; //Load the memory value into rt
        }
        return retValue;
    }
    return val;
}

/* 
 * Write back to register. If the instruction modified a register--
 * (including jal, which modifies $ra) --
 * put the index of the modified register in *changedReg,
 * otherwise put -1 in *changedReg.
 */
void RegWrite( DecodedInstr* d, int val, int *changedReg) {
    //jal stores its return address into r31
    //I should be able to just do mips.memory[reg] 
    unsigned int temp = d->op;
    unsigned int rFunct = d->regs.r.funct;
    *changedReg = -1;

    //R-format
    if(temp == 0 && rFunct != 8) {
     //addu, and, or, srl, sll, slt, and subu all store its changed value in rd
        *changedReg = d->regs.r.rd;
        mips.registers[*changedReg] = val;
    }
    else if(temp == 9 || temp == 12 || temp == 13 || temp == 15) { //For addiu, andi, ori, and lui
        //All of these instructions store their result in rt
        *changedReg = d->regs.i.rt;
        mips.registers[*changedReg] = val;
    }
    else if (temp == 3){
        //For jal, which stores its return value in r31
        //I already stored mips.pc in r31, but it needs to be increased by 4
        mips.registers[31] += 4;
        *changedReg = 31;
    }
}










