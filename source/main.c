#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#define infoNum 8
#define strLen 30

char info[infoNum][strLen];

void getInfo()
{
	FILE *fp;
	int i=0, k=0;

	fp = fopen("info.ini", "r");
	rewind(fp);

	while(fgets(info[i], strLen, fp))
	{
        i++;
    }

    for(i=0;i<infoNum;i++)
    {
        for(k=0;k<strLen;k++)
        {
            if(info[i][k]=='\n')
                info[i][k]='\0';
        }
    }

	fclose(fp);
}

void printLogo()
{
	printf("       ######       \033[1;31m%s\033[0;m\n",info[0]);
	printf("     ####  ####     \n");
	printf("    #####  #####    -----------\n");
	printf("   ## ##    ## ##   \n");
	printf("   ##          ##   \033[1;31mOS\033[0;m: %s\n", info[1]);
	printf("  ####        ####  \n");
	printf("  ####  ####  ####  \033[1;31mFirmware\033[0;m: %s\n", info[2]);
	printf("  #### ###### ####  \n");
	printf("  #### ###### ####  \033[1;31mHost\033[0;m: %s\n", info[3]);
	printf("  ###  ######  ###  \n");
	printf("  #     ####     #  \033[1;31mResolution\033[0;m: %s\n", info[4]);
	printf("  #  ##########  #  \n");
	printf("  ####  #  #  ####  \033[1;31mCPU\033[0;m: %s\n", info[5]);
	printf("   ##   #  #   ##   \n");
	printf("    #          #    \033[1;31mGPU\033[0;m: %s\n", info[6]);
	printf("    ##        ##    \n");
	printf("     ##########     \033[1;31mMemory\033[0;m: %s\n", info[7]);
}

int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	printf("\n\n\n\n\n\n");
	getInfo();
	printLogo();

	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; 
	}

	gfxExit();
	return 0;
}
