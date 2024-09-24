#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct OPTAB
{
	char opcode[10];
	char hexacode[10];
}OT[30];
struct SYMTAB
{
	char label[10];
	int addr;
}ST[30];
FILE *fp1,*fp2,*fp3,*fp4,*fp5;
int oi=-1,si=-1,opd,start,locctr,flag,i,size=0,len;
char label[10],opcode[10],operand[10];
void read_OPTAB()
{
	while(1)
	{
		oi++;
		fscanf(fp2,"%s%s",OT[oi].opcode,OT[oi].hexacode);
		if(getc(fp2)==EOF)
		break;
	}
}
int main()
{
	fp1=fopen("input.txt","r");
	fp2=fopen("optab.txt","r");
	fp3=fopen("symtab.txt","w");
	fp4=fopen("intmed.txt","w");
	fp5=fopen("length.txt","w");
	read_OPTAB();
	fscanf(fp1,"%s%s%x",label,opcode,&opd);
	if(strcmp(opcode,"START")==0)
	{
		start=opd;
		locctr=start;
		fprintf(fp4,"\t%s\t%s\t%x\n",label,opcode,opd);
		fscanf(fp1,"%s%s%s",label,opcode,operand);
	}
	else
		locctr=0;
	while(strcmp(opcode,"END")!=0)
	{
		fprintf(fp4,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
		if(strcmp(label,"-")!=0)
		{
			for(i=0;i<=si;i++)
			{
				if(strcmp(ST[i].label,label)==0)
				{
					printf("DUPLICATE SYMBOL ERROR");
					exit(0);
				}
			}
			si++;
			strcpy(ST[si].label,label);
			ST[si].addr=locctr;	
		}
		flag=0;
		for(i=0;i<=oi;i++)
		{
			if(strcmp(opcode,OT[i].opcode)==0)
			{
				locctr=locctr+0x3;
				size=size+3;
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			if(strcmp(opcode,"WORD")==0)
			{
				locctr=locctr+0x3;
				size+=3;
			}
			else if(strcmp(opcode,"RESW")==0)
			{
				locctr=locctr+atoi(operand)*0x3;
			}
			else if(strcmp(opcode,"RESB")==0)
			{
				locctr=locctr+atoi(operand);
			}
			else if(strcmp(opcode,"BYTE")==0)
			{
				len=strlen(operand);
				len=len-3;
				if(operand[0]=='c')
				{
					locctr=locctr+len;
					size+=len;
				}
				else if(operand[0]=='x')
				{
					locctr=locctr+len/2;
					size+=len/2;
				}
			}
			else
			{
				printf("UNKNOWN OPCODE ERROR");
				exit(0);
			}
		}
		fscanf(fp1,"%s%s%s",label,opcode,operand);
	}
	fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);
	for(i=0;i<=si;i++)
	{
		fprintf(fp3,"%s\t%x",ST[i].label,ST[i].addr);
		if(i!=si)
		fprintf(fp3,"\n");
	}
	fprintf(fp5,"%x\n%x",locctr-start,size);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
}
