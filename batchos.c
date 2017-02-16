#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

#define os 0
#define osMemSize 128
#define userPartition 128
#define userPartitionSize 256



int memory[384];

void readFile(char *jobFile);
int simpleBatch(char *jobFile);
void loadJob(int pId, int memSize, int start);
void clearMemory(int memSize, int start, char c);
void showMemory(void);
int runJob(int jId, char *jProfile);

int cpuSim(int nSlices);
int inputSim(int nSlices);
int outputSim(int nSlices);
int waitSigSim(int nSlices);

void main()
{
	printf("Hello TV Land! \n");
	simpleBatch("jobs.txt");
}


void readFile(char *jobFile)
{
	FILE *in;
	int nJobs, j;
	char line[80];

	int arrival, memSize;
	char jId[8], owner[8], runProfile[64];

	in = fopen(jobFile, "r");
	if (in == NULL)
	{
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
		for(j=0;j<nJobs;j++) 
		{
			fscanf(in, "%s %s %d %d %s \n", jId, owner, &arrival, &memSize, runProfile);
			printf("jId %s	owner %s	arrival %d	memSize %d	runProfile %s \n", jId, owner, arrival, memSize, runProfile);
		}

		fclose(in);
	}
}


int cpuSim(int nSlices)
{
	int usedSlices = 0;
	int j;

	char spinMe[] = "|/-\\";

	printf("cpu ");

	for(j=0;j<nSlices;j++) {
		printf("%c", spinMe[j%4]);
		printf("%c", (char)8);
		Sleep(100);
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

