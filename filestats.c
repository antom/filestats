/*********************************************************************
File:        filestats.c
Author:		 Andrew Thomas
Last edited: 3rd Apr 2003
Description: EL1113 assignment 2, 2002/3.  Text file analysis program.
**********************************************************************/


#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 1024
#define NCHARS 256

int getfile(char *fname, char *buffer, int buflen);
void countchars(char *buffer, int *count);
int Nlines(char *buffer);
int Nchars(char *buffer);
int Nwords(char *buffer);

void main(void)
{

   char fname[100];
   char buffer[BUFSIZE];
   int cdata[NCHARS];
   int i,N;
   char c;

   printf("EL1113 assignment 2, 2002/3.");
   printf("\nText file analysis program.");

   printf("\n\nEnter the file name: ");
   scanf("%s",fname);

   if (getfile(fname,buffer,BUFSIZE))
   {
      printf("\n%s contains ",fname);
      printf("%d characters and ",Nchars(buffer));
      printf("%d words in ",Nwords(buffer));
      printf("%d lines.\n",Nlines(buffer));

      countchars(buffer,cdata);
      printf("\nDistribution of letters in %s is:",fname);
      for (c='A';c<='Z';c++)
      {
         N=cdata[c]+cdata[tolower(c)];

         printf("\n'%c' %4d: ",c,N);
         for (i=0;i<N;i=i+10)
         {
            putchar(c);
         }
      }
      printf("\n");

   }

}

int getfile(char *fname, char *buffer, int buflen)
/*******************************************************************
Description:   Reads contents of file into buffer.
               Clears buffer.
               Opens file.
               Reads file contents
               Closes file.

Arguments:     fname: file name
               buffer: character buffer
               buflen: no characters in buffer

Return value:  1 if sucessful.
               0 if not sucessful (file not found).
*******************************************************************/
{
   int i;
   int ch;
   int nchars = 0;
   FILE *ipfile;

   /*clear buffer*/
   for (i=0;i<buflen;i++)
   {
      buffer[i]='\0';
   }

   /*read from file into buffer*/
   ipfile=fopen(fname,"r");
   if (ipfile==NULL)
   {
      fprintf(stderr,"\nFile %s not found.",fname);
      return 0;
   }
   else
   {
      do
      {
         ch=fgetc(ipfile);
         if (ch!=EOF)
         {
            buffer[nchars]=ch;
            nchars++;
            if (nchars==buflen)
            {
               fprintf(stderr,"\nFile %s ",fname);
               fprintf(stderr,"too large for buffer.");
               fprintf(stderr,"\nRead first %d ",buflen);
               fprintf(stderr,"characters from %s.",fname);
            }
         }
      }
      while ((ch!=EOF)&&(nchars<buflen));

      fclose(ipfile);

      return 1;
   }

}


/******************************************************************/

void countchars(char *buffer, int *count)
{
char chrC;
int bufC;

// go through each letter.
for (chrC='A'; chrC<='Z';chrC++)
{
	// set each upper-case letter count to zero.
	count[chrC] = 0;
	// do the same to the lower case letter counts.
	count[tolower(chrC)] = 0;
}

// only count the characters if the buffer contains something.
if (buffer[0]!='\0')
{
	// go through the buffer.
	// (starts at 1 to avoid counting an extra character)
	for (bufC=1; bufC<=BUFSIZE; bufC++)
	{

		for (chrC='A'; chrC<='Z'; chrC++)
    	{

			// if letter equals uppercase letter, add to the count.
			if (buffer[bufC]==chrC)
				{
					count[chrC]++;
				}

			// do the same to the lower case letter counts.
			if (buffer[bufC]==tolower(chrC))
				{
					count[tolower(chrC)]++;
				}

		}
	}

}

}

/******************************************************************/

int Nlines(char *buffer)
{
int bufC, lineC=1;

// is the file empty? return zero if true.
if (buffer[0]=='\0')
{
	lineC = 0;
	return lineC;
}

else
{
	// go through the buffer.
	for (bufC=0; bufC<=BUFSIZE; bufC++)
	{
	// adds to the countif current part of buffer = new line,
		if (buffer[bufC]=='\n')	lineC++;
	}
	return lineC;
}

}

/******************************************************************/

int Nchars(char *buffer)
{
int bufC, charC=0;

// is the file empty? return zero if true.
if (buffer[0]=='\0')
{
	charC = 0;
	return charC;
}

else
{
	// go through the buffer.
	// (start at 1 to avoid counting an extra char)
	for (bufC=1; bufC<=BUFSIZE; bufC++)
	{
	if (buffer[bufC]!='\0') charC++;
	}
	return charC;
}

}

/******************************************************************/

int Nwords(char *buffer)
{
int bufC, wordC=0, multispace=0;

// is the file empty? return zero if true.
if (buffer[0]=='\0')
{
	wordC = 0;
	return wordC;
}

else
{
	// count a word if characters > 0
	if (Nchars>0) wordC++;

	// go through the buffer.
	for (bufC=0; bufC<=BUFSIZE; bufC++)
	{
	// is there multiple spaces? don't increase the word count!
	if ((buffer[bufC]==' ') && (buffer[bufC-1]==' ')) multispace++;
	if (((multispace==0) && (buffer[bufC]==' ')) || (buffer[bufC]=='\n')) wordC++;
	multispace = 0;
	}
	return wordC;
}

}