//CMPS 431 Program 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <stdint.h>
#define os 0
#define osMemSize 128
#define userPartition 128
#define userPartitionSize 256

char memory[384];
//void *memset(void *str, int c,  n)
void readFile(char *jobFile);
//int simpleBatch(char *jobFile);
void loadJob(char pId[], int memSize, int start);
//void clearMemory(int memSize, int start, char c);
void showMemory(void);
int runJob(char jId[], char *jProfile, int nJobs);

int cpuSim(int nSlices);
int inputSim(int nSlices);
int outputSim(int nSlices);
int waitSigSim(int nSlices);

int main(void)
{
	printf("Hello TV Land! \n");
	readFile("jobs.txt");
	return 0;
}

void readFile(char *jobFile)
{
	FILE *in;
	int nJobs, j;
	char line[80];
	int arrival, memSize;
	char jId[8], owner[8], runProfile[64];
	in = fopen(jobFile, "r");
	if (in == NULL) {
		printf("Error: Could not open jobfile: %s \n", jobFile);
	}
	else {
		printf("Reading File....\n");
		/* Get number of jobs in file. */
		fscanf(in, "%d \n", &nJobs);
		printf("nJobs = %d \n", nJobs);
		/* Get next line. */
		fgets(line, 80, in);
		/* NAME	OWNER	ARRIVAL	MEMORYneeded	cpuIOProfile */
		printf("line = %s \n", line);

		/* Read jobs. */
		for(j=0;j<nJobs;j++) {
			fscanf(in, "%s %s %d %d %s \n", jId, owner, &arrival, &memSize, runProfile);
			//printf("%s \n",jId);
			memset(memory,0,sizeof(memory));
			loadJob(jId,memSize,osMemSize+1);
			showMemory();
			runJob(jId,runProfile, nJobs);
			//printf("jId %s	owner %s	arrival %d	memSize %d	runProfile %s \n", jId, owner, arrival, memSize, runProfile);
		}

		fclose(in);
	}
}

/* void loadJob(char pId[], int memSize, int start){
	printf("Job %s loaded into memory at slot %d and ends on slot %d\n", pId, start, start+memSize);
	
} */


int cpuSim(int nSlices)
{
	int usedSlices = 0;
	int j;
	//printf("%d", nSlices);
	char spinMe[] = "|/-\\";

	printf("cpu ");
	//printf("test");
	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		sleep(0.3);
	}

	printf(" ");

	for(j=0;j<5;j++) {
		printf("%c", (char)8);
		printf(" ");
		printf("%c", (char)8);
	}
	printf("cpu ");
	usedSlices = nSlices;
	return usedSlices;
}

int inputSim(int nSlices){
	int usedSlices = 0;
	int j;

	char spinMe[] = "|/-\\";

	printf("input ");

	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		sleep(0.1);
	}

	printf(" ");

	for(j=0;j<5;j++) {
		printf("%c", (char)8);
		printf(" ");
		printf("%c", (char)8);
	}

	usedSlices = nSlices;

	return usedSlices;
}
int outputSim(int nSlices){
		int usedSlices = 0;
	int j;

	char spinMe[] = "|/-\\";

	printf("output ");

	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		sleep(0.1);
	}

	printf(" ");

	for(j=0;j<5;j++) {
		printf("%c", (char)8);
		printf(" ");
		printf("%c", (char)8);
	}

	usedSlices = nSlices;

	return usedSlices;
}

int simpleBatch(char *jobFile){
	
}
/*
void clearMemory(int memSize, int start, int c){
	memset(memSize,start,c);
}
*/
/* void showMemory(void){
	
} */

int waitSigSim(int nSlices){
	int usedSlices = 0;
	int j;

	char spinMe[] = "|/-\\";

	printf("output ");

	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		//sleep(100);
	}

	printf(" ");

	for(j=0;j<5;j++) {
		printf("%c", (char)8);
		printf(" ");
		printf("%c", (char)8);
	}

	usedSlices = nSlices;

	return usedSlices;
}

int runJob(char jId[], char *jProfile, int nJobs){
	//printf("%s \n", jProfile);
	int i =0;
	char *myStr = jProfile;
	char *dup = strdup(myStr);
	char *delim = "ciow";
	char *pChr = strtok (myStr, delim);
	char *myDelimChar;
	int CPUt;
	int iTime,oTime,wTime;
	int totalIT;
	while (pChr) {
		//printf ("%s ", pChr);
		
		myDelimChar = dup[pChr-myStr+strlen(pChr)];
		if(myDelimChar == 'c'){
			CPUt += atoi(pChr);
			cpuSim(CPUt);
			//printf("%d ", myInt);
			//printf("got c ");
			
		}
		else if(myDelimChar == 'i'){
			iTime += atoi(pChr);
			inputSim(iTime);
			//printf("got I ");
		}
		else if(myDelimChar == 'o'){
			oTime += atoi(pChr);
			outputSim(oTime);
			//printf("got O ");
		}
		else if(myDelimChar == 'w'){
			wTime += atoi(pChr);
			waitSigSim(wTime);
			//printf("got W ");
		}
		
		//printf("%c ", myDelimChar);
		pChr = strtok (NULL, delim);
		//char delimUsed = dup[pChr-myStr];
	}
	totalIT += iTime + oTime + wTime;
	
	putchar ('\n');

	return 0;
}
//	printf("%c \n", myStr);



