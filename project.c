#include "spimcore.h"


/* ALU - Sara */
/* 10 Points */
void ALU(unsigned A,unsigned B,int ALUControl,unsigned *ALUresult,char *Zero)
{
  
  if(ALUControl == 0)
    *ALUresult = A + B;
    //Zero = A+B;
  else if(ALUControl == 1)
    *ALUresult = A-B;
    //Zero = A-B;
  else if(ALUControl == 2)
  {
    if((signed)A<(signed)B)
      *ALUresult = 1;
      //Zero = 0000000000000001;
    else
      *ALUresult = 0;
      //Zero = 0000000000000000;
  }
  else if(ALUControl == 3)
  {
     if((unsigned)A<(unsigned)B)
     *ALUresult = 1;
      //Zero = 0000000000000001;
       //*ALUresult = B << 16; //A idk 
    else
      *ALUresult = 0;
     // Zero = 0000000000000000;
  }
    else if(ALUControl == 4){
      *ALUresult = A&B;
      //B = B << 16;
    }
    else if(ALUControl == 5){
      *ALUresult = A|B;
    }
    else if(ALUControl == 6){
      *ALUresult = B<<16;
    }
    else if(ALUControl == 7){
      *ALUresult = ~A;
    }
      
      *Zero = (*ALUresult) ? 1 : 0;
  
}

/* instruction fetch - Sara*/
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
  unsigned mem_index;
  mem_index = PC>>2;
  
  if(PC%4 == 0){
    *instruction = Mem[mem_index];
    return 0;
  }
  else
    return 1;
}


/* instruction partition - Alana */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
*op = (instruction >> 26) & 0x0000003f;

    //bit-wise shift by 21
    //then AND with 0001 1111 to get r1
    *r1 = (instruction >> 21) & 0x0000001F;

    //bitwise shift by 16
    //AND with 0001 1111 to get r2
    *r2 = (instruction >> 16) & 0x0000001F;

    //shift by 11
    //AND with 0001 1111 to get r3
    *r3 = (instruction >> 11) & 0x0000001F;

    //Now funct is equal to instruction AND 0011 1111
    *funct = instruction & 0x0000003F;

    //when you AND instruction and a 16 bit of (1111 1111 1111 1111) you get the offset
    *offset = instruction & 0X0000FFFF;

    //jsec is equal to the instruction AND-ed to the 26 bit of (0011 1111 1111 1111 1111 1111 1111)
    *jsec = instruction & 0x03FFFFFF;
}



/* instruction decode - Alana */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
//Used for stopping on any unused opcode
    int h = 0;

    //Switch cases
    switch (op) {

        case 0x00:
            /*REGISTER TYPE*/
            //RegDst = 1 when there is a register destination in use (obvs because it stands for Register Destination)
            controls->RegDst = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            //ALUop is (0111) aka R-type instruction
            controls->ALUOp = 7;
            controls->MemWrite = 0;
            //the ALUSrc is zero because the second operand for the ALU is taken from a register
            controls->ALUSrc = 0;
            //RegWrite = 1 when a register is also being written (RegWrite = Register Write)
            controls->RegWrite = 1;
            break;

        case 0x0d:
            /*OR IMMEDIATE*/
            //RegDst = 1 because there is a register destination in use
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            //ALUop is (0101)
            controls->ALUOp = 5;
            controls->MemWrite = 0;
            //the ALUSrc = 0 because the second operand for the ALU is taken from a register
            controls->ALUSrc = 1;
            //RegWrite = 1 because a register is being written
            controls->RegWrite = 1;
            break;

        case 0x23:
            /*LOAD WORD*/
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            //MemRead = 1 because there is something being read from memory
            controls->MemRead = 1;
            //MemtoReg = 1 Memory goes (is written) to the register AFTER its loaded
            controls->MemtoReg = 1;
            //ALUop = 0
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            //ALUSrc = 1 since instruction = immediate type
            controls->ALUSrc = 1;
            //RegWrite is on because a register is being written
            controls->RegWrite = 1;
            break;

        case 0x2b:
            /*STORE WORD*/
            controls->RegDst = 2;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 2;
            //ALUop is 0
            controls->ALUOp = 0;
            //MemWrite = 1 because we are writing in to the memory
            controls->MemWrite = 1;
            //ALUSrc = 1 because the second operand for the ALU is taken from the instruction,
            controls->ALUSrc = 1;
            controls->RegWrite = 0;
            break;

        case 0x0a:
            /*SET LESS THAN IMMEDIATE*/
            controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            //the ALUop is (0010) means the ALU will do set less than
            controls->ALUOp = 2;
            controls->MemWrite = 0;
            //ALUSrc = 1 since instruction = immediate type
            controls->ALUSrc = 1;
            //RegWrite is on because (guess what) register is being written (shocking
            controls->RegWrite = 1;
            break;

        case 0x04:
            /*BRANCH EQ*/
            controls->RegDst = 2;
            controls->Jump = 0;
            //Branch = 1 when the instruction is a branch & the equal comparator is being used
            controls->Branch = 1;
            controls->MemRead = 0;
            controls->MemtoReg = 2;
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            //ALUSrc = 1 when the second operand for the ALU is in the instruction
            controls->ALUSrc = 1;
            controls->RegWrite = 0;
            break;

        case 0x01:
            /*BRANCH: IF EQUAL TO OR GREATER THAN 0*/
            controls->RegDst = 0;
            controls->Jump = 0;
            //Branch = 1 when the instruction is a branch & the equal comparator is used
            controls->Branch = 1;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 6;
            controls->MemWrite = 0;
            //ALUSrc = 1 when the second op for the ALU is in the instruction
            controls->ALUSrc = 1;
            controls->RegWrite = 0;
            break;

        case 0x02:
            /*JUMP*/
            controls->RegDst = 2;
            controls->Jump = 1;
            controls->Branch = 2;
            controls->MemRead = 2;
            controls->MemtoReg = 2;
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            controls->ALUSrc = 2;
            controls->RegWrite = 0;
            break;
        default:
            //Stuff we don't work with
            h = 1;
    }
    return h;
}

/* Read Register - Sara*/
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
  *data1 = Reg[r1];
  *data2 = Reg[r2];
}


/* Sign Extend - Alana */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
 //if offset AND 0x00008000 is true
    if (offset & 0x00008000) {
        *extended_value = offset | 0xffff0000;
    }
    else {
        *extended_value = offset;
    }
}



/* ALU operations - Cal*/
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    int temp = 0; 
    
    if(ALUSrc == 1)
        data2 = extended_value;

    
    if(ALUOp == 7)
    {
        //Implement :: add, sub, and, or, slt, slu
        switch(funct)
        {
             case 32:
                ALUOp = 0;
                ALU(data1, data2, ALUOp, ALUresult, Zero);
                break;
             case 34:
                ALUOp = 1;
                ALU(data1, data2, ALUOp, ALUresult, Zero);
                break;
             case 36:
                ALUOp = 4;
                ALU(data1, data2, ALUOp, ALUresult, Zero);
                break; 
             case 37:
                ALUOp = 5;
                ALU(data1, data2, ALUOp, ALUresult, Zero);
                break; 
             case 39:
                ALUOp = 7;
                ALU(data1, data2, ALUOp, ALUresult, Zero);
                break;
             case 42:
                ALUOp = 2;
                ALU(data1, data2, ALUOp, ALUresult, Zero);
                break; 
             case 43:
                ALUOp = 3;
                ALU(data1, data2, ALUOp, ALUresult, Zero);
                break; 
            default: 
                temp++;
                break;
        }   
        return temp;
    }
    ALU(data1, data2, ALUOp, ALUresult, Zero);
    return temp;
       
}

/* Read / Write Memory - Cal */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    if(MemRead == 1) {
        if(ALUresult % 4 != 0)
            return 1;
       *memdata = Mem[ALUresult >> 2];
    }
    
    if(MemWrite == 1)
    {
        if(ALUresult%4 != 0)
            return 1;    
        Mem[ALUresult>>2] = data2; //Write the value of data2 to the memory location addressed by ALURESULT
    }
    return 0;
}


/* Write Register - Cal*/
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    //Write the data (ALUresult or memdata )to a register (Reg) addreesed by r2 or r3, if asserted
    /*If RegWrite is deasserted do nothing */
    if(!RegWrite)
        return;
    
    if(RegWrite == 1)
    {
          //ALUresult or memdata 
          if(MemtoReg == 1)
          {
              if(RegDst == 0)
                Reg[r2] = memdata;
              else
                Reg[r3] = memdata;
          }
          if(MemtoReg == 0)
          {
            if(RegDst == 1)
              Reg[r3] = ALUresult;
            else
              Reg[r2] = ALUresult;
          }
    }
           
}

/* PC update - # Amigos */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
  *PC+=4;
  if(Branch ==1&& Zero == 1){
    *PC+=extended_value<<2;
  }
  else if(Jump==1){
    *PC = jsec<<2 | (*PC&0xf0000000);
  }
}

