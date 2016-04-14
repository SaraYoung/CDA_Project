#include "spimcore.h"


/* ALU - Sara */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
  
  if(ALUcontrol == 000)
    *ALUresult = A + B;
    //Zero = A+B;
  else if(ALUcontrol == 001)
    Zero = A-B;
  else if(ALUcontrol == 010){
    if(A<B)
      Zero = 0000000000000001;
    else
      Zero = 0000000000000000;
}
  else if(ALUcontrol == 011){
     if(A<B)
      //Zero = 0000000000000001;
       *ALUresult = B << 16; //A idk 
    else
      Zero = 0000000000000000;
      
    else if(ALUcontrol == 110){
      B = B << 16;
    }
<<<<<<< HEAD
      
      
      *Zero = (*ALUresult) 1 ? 0;
=======
  }
    else if(ALUcontrol == 100){
      if(A==B)
        Zero = 0000000000000001;
      else
        Zero = 0000000000000000;
    }
    else if(ALUcontrol == 101){
      if
    }
>>>>>>> f406e1e6a9ec8c27d09eb35aef5513369066b19e
}

/* instruction fetch - Sara*/
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{

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

}

/* Read Register - Sara*/
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend - Alana */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations - Cal*/
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory - Cal */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register - Cal*/
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update - # Amigos */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

