#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_trecord(FILE *fobj,char *trecord,int *len)
{
    if(len >0)
    {
	fprintf(fobj,"T%s",trecord);
    }
}

void main()
{
    char label[10],opcode[10],operand[10],code[10],mnemonic[10];
    int start,locctr,len;
    char trecord[100]={0},hrecord[30]={0},erecord[10]={0},objinstr[10]={0};
    int tlen=0;
    FILE *fpin,*fpobj,*fpoptab,*fpsymtab;

    fpin=fopen("output.txt","r");
    fpobj=fopen("object_program.txt","w");
    fpoptab=fopen("optab.txt","r");
    fpsymtab=fopen("symtab.txt","r");

    fscanf(fpin,"\t%s\t%s\t%s\t",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
	sscanf(operand,"%X",&start);
	locctr=start;
	sprintf(hrecord,"H%-6s%06X%06X",label,start,0);
        fprintf(fpobj,"%s\n",hrecord);

	fscanf(fpin,"%X\t%s\t%s\t%s\t",&locctr,label,opcode,operand);
    }

    char saddress[50]={0};
    sprintf(saddress,"%06X",locctr);
    strcpy(trecord,saddress);
    while(strcmp(opcode,"END")!=0)
    {
	int opfound=0;
	rewind(fpoptab);
	while(fscanf(fpoptab,"%s\t%s",code,mnemonic)!=EOF)
	{
	    if(strcmp(code,opcode)==0)
	    {
		opfound=1;
		break;
	    }
	}
	if(opfound)
	{
	    strcat(trecord,mnemonic);
	    if(strcmp(opcode,"WORD")==0)
	    {
		sprintf(objinstr,"%06X",atoi(operand));
		strcat(trecord,objinstr);
		tlen+=3;
		if(tlen > 30)
		{
		    write_trecord(fpobj,trecord,&tlen);
		}
	    }
	    else if(strcmp(opcode,"BYTE")==0)
            {
		int i=0;
                if(operand[i]=='C')
		{
		    for(i=2;operand[i]!='\'';i++)
		    {
			char bytevalue[3];
			sprintf(bytevalue,"%02X",operand[i]);
			strcat(trecord,bytevalue);
			tlen++;
		    }
		}
                if(tlen > 30)
                {
                    write_trecord(fpobj,trecord,&tlen);
                }
            }
	    else if((strcmp(opcode,"RESW")==0)||(strcmp(opcode,"RESW")==0)||(strcmp(opcode,"BASE")==0))
	    {
		continue;
	    }
	    else
	    {
		tlen+=3;
		if(tlen > 30)
                {
                    write_trecord(fpobj,trecord,&tlen);
                }
	    }
	}

	fscanf(fpin,"%X\t%s\t%s\t%s",&locctr,label,opcode,operand);
	printf("%X\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand,objinstr);
    }

    fclose(fpin);
    fclose(fpobj);
    fclose(fpoptab);
    fclose(fpsymtab);
}
