#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <3ds.h>
#define infoNum 9
#define strLen 30

char info[infoNum][strLen];
char colors[7][strLen];
int hours, minutes, pmin=-1;
int colorIndex=0;

void getInfo()
{
	FILE *fp;
	int i=1;

	fp = fopen("info.ini", "r");
	rewind(fp);

	while(fgets(info[i], strLen, fp))
	{
        i++;
    }

    for(i=1;i<infoNum;i++)
    {
        if(info[i][strlen(info[i])-1] == 10)
            info[i][strlen(info[i])-1] = 0;
    }

    for(i=1;i<infoNum;i++)
    {
        char *ptr = strchr(info[i], '\r');
        if (ptr)
        {
            *ptr  = '\0';
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
	iprintf("\x1b[2J");
	printf("\n\n");
	printf("                     - %02d:%02d -", hours, minutes); 
	printf("\n\n\n\n\n");

    setvbuf(stdout, NULL, _IONBF, 0); 
	printf("       ######       %s",info[0]);
    							printf("%s\033[0;m\n",info[1]);
                                printf("     ####  ####     \n");
    printf("    #####  #####    -----------\n");
    printf("   ## ##    ## ##   \n");
    printf("   ##          ##   %sOS",info[0]);
    							printf("\033[0;m: %s\n", info[2]);
                                printf("  ####        ####  \n");
	printf("  ####  ####  ####  %sFirmware",info[0]);
								printf("\033[0;m: %s\n", info[3]);
	printf("  #### ###### ####  \n");
	printf("  #### ###### ####  %sHost",info[0]);
								printf("\033[0;m: %s\n", info[4]);
	printf("  ###  ######  ###  \n");
	printf("  #     ####     #  %sResolution",info[0]);
								printf("\033[0;m: %s\n", info[5]);
	printf("  #  ##########  #  \n");
	printf("  ####  #  #  ####  %sCPU",info[0]);
								printf("\033[0;m: %s\n", info[6]);
	printf("   ##   #  #   ##   \n");
	printf("    #          #    %sGPU",info[0]);
								printf("\033[0;m: %s\n", info[7]);
	printf("    ##        ##    \n");
	printf("     ##########     %sMemory",info[0]);
								printf("\033[0;m: %s\n", info[8]);
}

void getColor()
{
	strcpy(info[0],colors[colorIndex]);
    fflush(NULL);
}

void initColors()
{
	strcpy(colors[0],"\033[1;31m");
	strcpy(colors[1],"\033[1;32m");
	strcpy(colors[2],"\033[1;33m");
	strcpy(colors[3],"\033[1;34m");
	strcpy(colors[4],"\033[1;35m");
	strcpy(colors[5],"\033[1;36m");
	strcpy(colors[6],"\033[1;37m");
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

void updateColorIndex()
{
	if(colorIndex++ > 6)
		colorIndex=0;
}

int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	getInfo();
	
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		initColors();
		getTime();
		
		if(timeCheck())
		{
			getColor();
			printLogo();
		}

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;
		else if(kDown & KEY_SELECT)
		{
			updateColorIndex();
			getColor();
			printLogo();
		}
	}

	gfxExit();
	return 0;
}
