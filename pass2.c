#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *f1,*f2,*f3,*f4,*f5,*f6;
int oi=0,si=0,len,i,j;
char length[10],size[10],label[10],opcode[10],operand[10],st_addr[10],address[10],ad[10];
struct optab
{
	char opcode[10],hexcode[10];
}ot[20];
struct symtab
{
	char label[10];
	char addr[10];
}st[30];
void readoptab()
{
	while(1)
	{
		
		fscanf(f2,"%s%s",ot[oi].opcode,ot[oi].hexcode);
		oi++;
		if(getc(f2)==EOF)
		{
			break;
		}
	}
}
void readsymtab()
{
	while(1)
	{
		
		fscanf(f3,"%s%s",st[si].label,st[si].addr);
		si++;
		if(getc(f3)==EOF)
		{
			break;
		}
	}
}
int main()
{
	
	f1=fopen("intmed.txt","r");
	f2=fopen("optab.txt","r");
	f3=fopen("symtab.txt","r");
	f4=fopen("length.txt","r");
	f5=fopen("assembly.txt","w");
	f6=fopen("objcode.txt","w");
	if(f1==NULL)
	{
		printf("NOT OPENED");
	}
	
	fscanf(f4,"%s%s",length,size);
	readoptab();
	readsymtab();
	fscanf(f1,"%s%s%s",label,opcode,operand);
	strcpy(st_addr,operand);
	if(strcmp(opcode,"START")==0)
	{
		fprintf(f5,"\t%s\t%s\t%s\n",label,opcode,operand);
		fprintf(f6,"H^%s  ^00%s^0000%s",label,operand,length);
		fprintf(f6,"\nT^00%s^%s",operand,size);
		fscanf(f1,"%s%s%s%s",address,label,opcode,operand);
	}
	while(strcmp(opcode,"END")!=0)
	{
		if(strcmp(opcode,"RESW")==0 || strcmp(opcode,"RESB")==0)
		{
			fprintf(f5,"%s\t%s\t%s\t%s\t\n",address,label,opcode,operand);
		}
		else if(strcmp(opcode,"WORD")==0)
		{
			fprintf(f5,"%s\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,operand);
			fprintf(f6,"^00000%s",operand);
		}
		else if(strcmp(opcode,"BYTE")==0)
		{
			fprintf(f5,"%s\t%s\t%s\t%s\t",address,label,operand,opcode);
			len=strlen(operand);
			if(operand[0]=='c')
			{
				for(i=2;i<len-1;i++)
				{
					sprintf(ad,"%x",operand[i]);
					fprintf(f5,"%s",ad);
					fprintf(f6,"^%s",ad);
				}
				fprintf(f5,"%s","\n");
			}
			else if(operand[0]=='x')
			{
				for(i=2;i<len-1;i++)
				{
					fprintf(f5,"%c",operand[i]);
					fprintf(f6,"^%c",operand[i]);
				}
				fprintf(f5,"%s","\n");
			}
		}
		else
		{
			i=0;
			while(strcmp(opcode,ot[i].opcode)!=0)
			{
				i++;
			}
			j=0;
			while(strcmp(operand,st[j].label)!=0)
			{
				j++;
			}
			fprintf(f5,"%s\t%s\t%s\t%s\t%s\t%s\t\n",address,label,opcode,operand,ot[i].hexcode,st[j].addr);
			fprintf(f6,"^%s%s",ot[i].hexcode,st[j].addr);
		}
		fscanf(f1,"%s%s%s%s",address,label,opcode,operand);
	}
	fprintf(f5,"%s\t%s\t%s\t%s",address,label,opcode,operand);
	fprintf(f6,"\nE^00%s",st_addr);
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
	fclose(f5);
	fclose(f6);	
}
