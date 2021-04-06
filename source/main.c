#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <3ds.h>
#define infoNum 8
#define strLen 30

char info[infoNum][strLen];
int hours, minutes, pmin=-1;

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

void getTime()
{
	time_t now;
 
    time(&now);
    struct tm *local = localtime(&now);
 
    hours = local->tm_hour;         
    minutes = local->tm_min;   
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

int timeCheck()
{
	if(pmin!=minutes)
	{
		pmin=minutes;
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		getTime();
		if(timeCheck())
		{
			iprintf("\x1b[2J");
			printf("\n\n");
			printf("                     - %02d:%02d -", hours, minutes); 
			printf("\n\n\n\n\n");
			getInfo();
			printLogo();
		}

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; 
	}

	gfxExit();
	return 0;
}
