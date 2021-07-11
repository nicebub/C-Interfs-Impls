#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "atom.h"
#include "atom2.h"
#include "atom3.h"
extern int getword(FILE* fp, char *, const int);
extern struct timeval clock_function(FILE* fp, char*(func)(char*, const char*), int*words);
//extern char* strcpy_a(char[], const char[]);
//extern char* strcpy_b(char*, const char*); 

void beginSum(const int b, int* cl, int* cl2){
	cl[0] = 0;
}
void atomSum(void* cur, int* cl, int* cl2) {
	cl[0]++;
	cl[1]++;
}

void finishSum(const int b, int* cl, int* cl2) {
//	if((*cl))
//		printf("bucket[%d]: %d\n",b, *cl);
	cl2[cl[0]]++;
	if(cl[2] < cl[0])
		cl[2] = cl[0];
}

struct timeval timerfunc(FILE* fp,const char*(*func)(const char*)) {
	char word[128];
	struct timeval time1, time2;
	int result;
	if( ( (result =  gettimeofday(&time1, NULL)) == -1 ) ) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(getword(fp, word, sizeof word)) {
		func(word);
	}
	if( ( (result =  gettimeofday(&time2, NULL)) == -1 ) ) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	time2.tv_sec -= time1.tv_sec;
	time2.tv_usec -= time1.tv_usec;
	return time2;
}
#define MAX_DIST 32
void run_timer(FILE* fp, void (*Atom_fRndm)(),const char* (*Atom_str)(const char* str),
	void (*Atom_clsr)(void(*func1)(const int bucketNum, int* cl, int* cl2),
						void(*func2)(void* cur, int* cl, int* cl2),
						void(*func3)(const int bucketNum,int* cl, int* cl2),int* cl, int* cl2)) {

	struct timeval time1;
	int result, *sumNwords, dist[MAX_DIST] = {0} ;

	if( ( (result =  gettimeofday(&time1,NULL)) == -1 ) ) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0UL, SEEK_SET);

	srand(time1.tv_sec);
	Atom_fRndm();

	time1 = timerfunc(fp, Atom_str);
	sumNwords = malloc(sizeof *sumNwords * 3);
	sumNwords[1] = 0;
	sumNwords[2] = 0;
	Atom_clsr(beginSum,atomSum,finishSum,sumNwords,(int*)&dist);

	printf("distribution of numbers:\n");

	for(int i=0;i<MAX_DIST;i++)
		printf("[%d]",i+1);
	printf("\n");

	for(int i=0;i<MAX_DIST;i++)
		printf("%d ",dist[i]);
	printf("\n");
	int nsum = 0;
	for(int i=0;i<MAX_DIST;i++)
		nsum += dist[i];
	printf("total accumulated: %d\n",nsum);
	printf("Max List Size: %d\n", sumNwords[2]+1);
	printf("Atom_string/Atom_new: num word: %d time %ld seconds %d microseconds\n", sumNwords[1],
				time1.tv_sec , time1.tv_usec);
	free(sumNwords);
}

int main(int argc, const char* argv[]) {
	FILE* fp;
	if((fp = fopen(argv[1], "r") ) == NULL) {
		fprintf(stderr, "%s\n", strerror(errno) );
		return EXIT_FAILURE;
	}

	run_timer(fp,Atom_fillRandom,Atom_string,Atom_closure);
	run_timer(fp,Atom2_fillRandom,Atom2_string,Atom2_closure);
	run_timer(fp,Atom3_fillRandom,Atom3_string,Atom3_closure);

	fclose(fp);
	return EXIT_SUCCESS;
}
