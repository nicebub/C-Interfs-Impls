#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "atom.h"
extern int getword(FILE* fp, char *, const int);
extern struct timeval clock_function(FILE* fp, char*(func)(char*, const char*), int*words);
extern char* strcpy_a(char[], const char[]);
extern char* strcpy_b(char*, const char*); 

void beginSum(const int b, int* cl, int* cl2){
	(*cl) = 0;
}
void atomSum(void* cur, int* cl, int* cl2) {
	(*cl)++;
}

void finishSum(const int b, int* cl, int* cl2) {
//	if((*cl))
//		printf("bucket[%d]: %d\n",b, *cl);
	cl2[*cl]++;
}

struct timeval timeAtomNew(FILE* fp,const char*(*func)(const char*)) {
	char word[128];
	struct timeval time1, time2;
	struct timezone zone;
	int result;
	if( ( (result =  gettimeofday(&time1, &zone)) == -1 ) ) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(getword(fp, word, sizeof word)) {
		func(word);
	}
	if( ( (result =  gettimeofday(&time2, &zone)) == -1 ) ) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	time2.tv_sec -= time1.tv_sec;
	time2.tv_usec -= time1.tv_usec;
	return time2;
}

#define MAX_DIST 15
int main(int argc, const char* argv[]) {
	FILE* fp;
	if((fp = fopen(argv[1], "r") ) == NULL) {
		fprintf(stderr, "%s\n", strerror(errno) );
		return EXIT_FAILURE;
	}
	int words = 0;
	struct timeval time1;
	sranddev();
	Atom_fillRandom();
	time1 = timeAtomNew(fp, Atom_string);
	int sum;
	int dist[MAX_DIST] = {0};
	Atom_closure(beginSum,atomSum,finishSum,&sum,(int*)&dist);
	printf("distribution of numbers:\n");
	for(int i=0;i<MAX_DIST;i++)
		printf("[%d]	",i+1);
	printf("\n");
	for(int i=0;i<MAX_DIST;i++)
		printf("%d	",dist[i]);
	printf("\n");
	printf("Atom_string/Atom_new: num word: %d time %ld seconds %d microseconds\n", words,
				time1.tv_sec , time1.tv_usec);
	fseek(fp, 0UL, SEEK_SET);
	fclose(fp);
	return EXIT_SUCCESS;
}
