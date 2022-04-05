/*--------------------------------------------------------------------*/
/* XEX2Cold                                                           */
/* by GienekP                                                         */
/* (c) 2022                                                           */
/*--------------------------------------------------------------------*/
#include <stdio.h>
/*--------------------------------------------------------------------*/
#include "sxegscold.h"
/*--------------------------------------------------------------------*/
void recall(unsigned char *b, unsigned char *u, unsigned int s, unsigned int addr)
{
	unsigned int i;
	for (i=0; i<(s-5); i++)
	{
		if ((b[i]==0xE0) && (b[i+1]==0x02) && (b[i+2]==0xE1) && (b[i+3]==0x02))
		    {
				printf("RUN $%02X%02X <-> $%04X\n",b[i+5],b[i+4],addr);
				u[7]=b[i+4];
				u[8]=b[i+5];
				b[i+4]=(addr&0xFF);
				b[i+5]=((addr>>8)&0xFF);
				i=s;
			};
	};
}
/*--------------------------------------------------------------------*/
void xex2cold(const char *fin, const char *fon)
{
	unsigned char buf[512*1024];
	unsigned int size=0;
	FILE *fi, *fo;
	fi=fopen(fin,"rb");
	if (fi)
    {
		printf("Load %s\n",fin);
		size=fread(buf,sizeof(unsigned char),512*1024,fi);
		if (size>0)
		{
			recall(buf,sxegscold_bin,size,0x0600);
			fo=fopen(fon,"wb");
			if (fo)
			{
				printf("Save %s\n",fon);
				fwrite(buf,sizeof(unsigned char),size,fo);
				fwrite(&sxegscold_bin[0],sizeof(unsigned char),sxegscold_bin_len-0,fo);
				fclose(fo);
			};
		};
		fclose(fi);
	}
	else
	{
		printf("Unknown file %s\n",fin);
	};
}
/*--------------------------------------------------------------------*/
int main(int argc, char* argv[])
{	
	printf("XEX2Cold\n");
	if (argc==3)
	{
		xex2cold(argv[1],argv[2]);
	}
	else
	{
		printf("(c) GienekP\n");
		printf("use:\xex2cold old.xex new.xex\n");
	};
	printf("\n");
	return 0;
}
/*--------------------------------------------------------------------*/
