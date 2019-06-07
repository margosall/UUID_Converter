#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char uuid4[38+1] = "1e2ce83a-46e9-408b-a32d-0bf299d8c485"; //38 bytes + \0 terminator
    char uuid4Parsed[32+1] = "";
    long long unsigned int uuid4int[2]={0,0}; // 8 bytes * 2 = 16 bytez
    unsigned char uuid4bytes[16]={0}; // 16 bytes

    //remove dashes
    int parsedIndex=0;
    for(int i =0;(i<40) && (uuid4[i]!=0);i++)
    {
        if(uuid4[i] != '-')
        {
            uuid4Parsed[parsedIndex] = uuid4[i];
            parsedIndex++;
        }
    }
    //Split to two uint64 (8 Bytes) values
    for(int i=0;i<2;i++)
    {
        char *ptr;
        char uuid4Halve[20];
        int j;
        for(j = 0;j<16;j++)
        {
            uuid4Halve[j]=uuid4Parsed[j+i*16];
        }
        uuid4Halve[j]=0;
        // printf("UUID4 half: %s\n",uuid4Halve);
        uuid4int[i] = strtoull(uuid4Halve,&ptr,16);
    }
    //Split to single byte values
    for(int i = 0;i<2;i++)
    {
        for(int j = 0;j<8;j++)
        {
            uuid4bytes[i*8+j]=(unsigned char)((uuid4int[i] >>(8*(7-j)))&0xFF);
        }
    }
    
    printf("i %s \n",uuid4Parsed); //original without dashes (388 vytes)
    printf("o %8llx%8llx\n",uuid4int[0],uuid4int[1]);//Split to 2*8Bytes (38-6-16)=20 size reduced 20 bytes
    //Split to single byte values, same size in bytes as previous
    printf("B ");
    for(int i = 0;i<16;i++)
    {
        printf("%02x",uuid4bytes[i]);
    }
    printf("\n");
}
