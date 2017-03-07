/*


	CMPS 431 Program 1
	Simple Batch Simulator


	Ngu Hoang
	Date: 02/23/2017

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#define os 0
#define osMemSize 128
#define userPartition 128
#define userPartitionSize 256

char memory[384];
//void memset(void *str, int c,  n)
//void readFile(char *jobFile);
void simpleBatch(char *jobFile);
void loadJob(char pId[], int memSize, int start);
void clearMemory(int memSize, int start, char* c);
//void showMemory(void);
int runJob(char jId[], char *jProfile, int nJobs);

int cpuSim(int nSlices);
int inputSim(int nSlices);
int outputSim(int nSlices);
int waitSigSim(int nSlices);
int userChoice;

int main(void)
{

	/*do
	{
		printf("Please select the following options:\n");
		printf("Enter 1 to execute batch os job\n");
		printf("Enter 0 to exit the program\n");
		scanf("%i",&userChoice);

		if(userChoice == 1)
		{
			
			
			break;
		}
		else if (userChoice == 0)
		{
			break;
		}
		else
		{
			printf("I don't understand\t \n\n");
		}			
	}while(userChoice!=0);*/
	printf("Hello TV Land! \n");
	simpleBatch("jobs.txt");
	return 0;

}


void simpleBatch(char *jobFile)
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
			memset (memory,0,strlen(memory));
			loadJob(jId,memSize,osMemSize+1);
			//showMemory();
			runJob(jId,runProfile, nJobs);
			memset (memory,0,strlen(memory));
			//printf("jId %s	owner %s	arrival %d	memSize %d	runProfile %s \n", jId, owner, arrival, memSize, runProfile);
		}

		fclose(in);
	}
}


 void loadJob(char pId[], int memSize, int start){
	printf("Job %s loaded into memory at %d and ends on %d\n", pId, start, start+memSize);
	
} 


int cpuSim(int nSlices)
{
	int usedSlices = 0;
	int j;
	//printf("%d", nSlices);
	char spinMe[] = "|/-\\";

	printf("\ncpu \n");
	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		printf("c ");
		sleep(0.5);
	}

	for(j=0;j<5;j++) {
		printf("%c", (char)8);
		printf(" ");
		printf("%c", (char)8);
	}
	
	usedSlices = nSlices;
	return usedSlices;
}

int inputSim(int nSlices){
	int usedSlices = 0;
	int j;

	char spinMe[] = "|/-\\";

	printf("\ninput \n");

	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		printf("i ");
		sleep(0.5);
	}

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

	printf("\noutput \n");

	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		printf("o ");
		sleep(0.1);
	}

	for(j=0;j<5;j++) {
		printf("%c", (char)8);
		printf(" ");
		printf("%c", (char)8);
	}

	usedSlices = nSlices;

	return usedSlices;
}


int waitSigSim(int nSlices){
	int usedSlices = 0;
	int j;

	char spinMe[] = "|/-\\";

	//printf("\nwaiting\n ");

	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		//printf("w ");
		sleep(0.1);
	}


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
	int cpuTime =0;
	int inputTime=0,outputTime=0,waitTime=0;
	int totalIdleTime=0;
	int sumIdleTime ;
	int sumCpuTime ;
	while (pChr) {
	
		myDelimChar = dup[pChr-myStr+strlen(pChr)];
		if(myDelimChar == 'c'){
			cpuTime = cpuTime + atoi(pChr);
			cpuSim(cpuTime);		
			
		}
		else if(myDelimChar == 'i'){
			inputTime = inputTime + atoi(pChr);
			inputSim(inputTime);
			
		}
		else if(myDelimChar == 'o'){
			outputTime = outputTime + atoi(pChr);
			outputSim(outputTime);
			
		}
		else if(myDelimChar == 'w'){
			waitTime = waitTime + atoi(pChr);
			waitSigSim(waitTime);
			
		}
		//printf("%c ", myDelimChar);
		pChr = strtok (NULL, delim);
		//char delimUsed = dup[pChr-myStr];
	}
	totalIdleTime = inputTime + outputTime + waitTime;
	sumIdleTime = sumIdleTime + totalIdleTime;
	sumCpuTime = sumCpuTime + cpuTime;

	printf("\n\nJob id: %s \n",jId);
	printf("The total idle time is %d \n",sumIdleTime );
	printf("The total cpu time is %d \n",sumCpuTime);
	//sumCpuTime =0;
	//sumIdleTime =0;
	return 0;
}
//	printf("%c \n", myStr);




// void simpleBatch(char *jobFile){
	
// }
/*
void clearMemory(int memSize, int start, char *c){
	memset(memSize,start,c);
}
 */