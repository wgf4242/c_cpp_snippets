/*  base64.c - encode and decode routines */

/*
 * Copyright (c)2001, 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,21jul09,flu   Change copyright notice and module layout.
1.0 07Aug2001
*/

/*
 *  Utility functions base64Encode and base64Decode,
 * these functions encode/decode binary data into base 64 mime format
 */

/* includes */

#include <stdio.h>
#include <string.h>
#include <rtilib/makeheader.h>

Private char refTable[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};
Private char invRefTable[]={62,0,0,0,63,52,53,54,55,56,57,58,59,60,61,0,0,0,0,0,
 0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
 0,0,0,0,0,0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,
 46,47,48,49,50,51};


Public
/**
 * Return base64Encoded result for a stream of bytes,
 * Parameters :input input string to be encoded
 *             len   length of the input string
 *             retlen length of the encoded string
 * Returns    :bas64encoded equivalent of input string
 * side effects allocates the buffer it returns, Calling
 * function should take care to free it.
 */
void base64Encode(const unsigned char* const input, unsigned char* output,
                  const int len, int* const retlen)
{
    int i=0;
    int numBytes=0;
    unsigned char* retString;
    unsigned char* encodedString;
    numBytes=((len+2)/3)*4;
    *retlen = numBytes += 1;
    memset(output,0,1000);
    retString=encodedString = output;
    /*for the first 3N bytes in the input stream*/
    for (i=0; i<len; i += 3) {
        *encodedString++ = refTable[((input[i]&0xff)>>2) &0x3f];
        /*if this is a 3n+1 byte string it needs padding for last 2 bytes*/
        if (i+1==len){
            *encodedString++ = refTable[((input[i]&0xff)<<4)&0x3f];
            *encodedString++='=';
            *encodedString++='=';
            break;
        }
        else{
            *encodedString++ =
                refTable[((input[i]&0xff)<<4 | (input[i+1]&0xff)>>4)&0x3f];
        }
        /*if this is a 3n+2 byte string it needs padding for last byte*/
        if (i+2==len){
            *encodedString++=refTable[((input[i+1]&0xff)<<2) &0x3f];
            *encodedString++='=';
            break;
        }
        else {
            *encodedString++=refTable[( ((input[i+1]&0xff) <<2) | ((input[i+2]&0xff)>>6)) &0x3f];
            *encodedString++=refTable[(input[i+2]&0x3f)];
        }
    }
    *encodedString++='\0';
    if ((int)(encodedString-retString)!=numBytes){
        fprintf(stderr,"Error in encoding length numBytes:%d len:%d\n",numBytes,((int)(encodedString-retString)));
        /*exit(-1);*/
    }
    encodedString=retString;
}


Public
/**
 * Return base64Decoded result for a stream of bytes,
 * Parameters :
 *             input input string to be encoded
 *             len   length of the input string
 *             retlen length of the encoded string
 * Returns     pointer to bas64decoded equivalent of input string
 * side effects allocates the buffer it returns, Calling
 * function should take care to free it.
 */
void base64Decode(const unsigned char * const input,
                  unsigned char* const output,
                  const int len, int* const retLen)
{
    int numBytes=0;
    int i=0;
    unsigned char* retString;
    unsigned char* decodedString = 0;
    numBytes=(len/4)*3;
    memset(output,0,1000);
    retString=decodedString=output;
    for(i=0;i<len;i+=4){
        *decodedString++ =
            invRefTable[input[i]-43]<<2|invRefTable[input[i+1]-43]>>4;
        *decodedString++ =
            invRefTable[input[i+1]-43]<<4|invRefTable[input[i+2]-43]>>2;
        *decodedString++ =
            invRefTable[input[i+2]-43]<<6|invRefTable[input[i+3]-43];
    }
    if (input[len-1]=='='){
        retString[numBytes-1]='\0';
        *retLen=numBytes-1;
    }
    if (input[len-2]=='='){
        retString[numBytes-2]='\0';
        *retLen=numBytes-2;
    }
    decodedString = retString;
}

/*
int main(int argc,char** argv){
  char inputString[256];
  int i,j,retLen;
  int numRead;
unsigned char decodedData[1000], encodedData[1000];
struct EventsDataBufferHeaderStorage abc={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19.0,20.0,21.0,22.0,25.0};
memset(encodedData,0,100);
memset(decodedData,0,100);
outputFile=fopen(argv[1],"wb");
base64Encode((unsigned char*)(&abc),encodedData,sizeof(struct EventsDataBufferHeaderStorage),&retLen);
fclose(outputFile);
printf ("Encoded data length%d:%d data:\n%s\n",sizeof(struct EventsDataBufferHeaderStorage),retLen,encodedData);
base64Decode(encodedData,decodedData,retLen-1,&numRead);
 printf("Numread:%d\n",numRead);
showData((struct EventsDataBufferHeaderStorage*)decodedData);
}

*/
/*
  int main(int argc,char** argv){
    char inputString[62];
    int i,j,retLen;
    int numRead,numWrite=0;
    char* outputString;
    FILE* inputFile,* outputFile;
    printf("Argv[1]:%s Argv[2]:%s\n",argv[1],argv[2]);
    inputFile=fopen(argv[1],"rb");
    outputFile=fopen(argv[2],"wb");
    while (!feof(inputFile)){
      bzero(inputString,60);
      numRead=fread(inputString,sizeof(char),61,inputFile);
      if (inputString[strlen(inputString)-1]=='\n'){
        inputString[strlen(inputString)-1]='\0';
      }
      outputString=base64Decode(inputString,numRead,&numWrite);
      fwrite(outputString,sizeof(char),numWrite,outputFile);
    }
  }

*/
