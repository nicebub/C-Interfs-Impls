// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// the code in this main file is mostly ,if not all mine and not from the book

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "include/assert.h"
#include "include/except.h"
#include "include/atom.h"
#include "include/atom2.h"
#include "include/atom3.h"
#include "include/atom4.h"
#include "include/atom5.h"
#include "include/defines.h"
#include "include/mem.h"
// #include "mem.h"
extern int getword(FILE* fp, char *, const int);
#define MAX_DIST 10


#define VariableAtomLengthFnDecl int(*Atom_lng)(const char* str)
#define VariableAtomLengthFn Atom_lng

#define VariableAtomStringFnDecl const char*(*Atom_str)(const char*)
#define VariableAtomStringFn Atom_str

#define VariableAtomFillRandomFnDecl void (*Atom_fRndm)(void)
#define VariableAtomFillRandomFn Atom_fRndm

#define VariableAtomInitFnDecl void (*Atm_init)(const long hint)
#define VariableAtomInitFn Atm_init
#define closureFn1Decl void(*func1)(const long bucketNum, long* cl, long** cl2)
#define closureFn1 func1
#define closureFn2Decl void(*func2)(const char* cur, long* cl,\
long** cl2, VariableAtomLengthFnDecl)
#define closureFn2 func2
#define closureFn3Decl void(*func3)(const long bucketNum, long* cl, long** cl2)
#define closureFn3 func3
#define VariableAtomClosureFnDecl void (*Atom_clsr)(closureFn1Decl,\
	closureFn2Decl, closureFn3Decl, long* cl, long** cl2)
#define VariableAtomClosureFn Atom_clsr

#define VariableAtomvloadFnDecl void (*Atm_vload)(const char *str, ...)
#define VariableAtomvloadFn Atm_vload

#define VariableAtomaloadFnDecl void (*Atm_aload)(const char * strs[])
#define VariableAtomaloadFn Atm_aload
#ifdef NDEBUG
const Except_T Assert_Failed = { "Assertion Failed" };
//#define Assert_Failed 0
#endif
#define TBLOCK TRY("main()")\
		assert(result >=0);\
	CATCH(Assert_Failed){\
		fprintf(stderr, "%s\n", strerror(errno)); \
		exit(EXIT_FAILURE); \
		}\
	END_TRY

#define TIMERHEADER struct timeval time1, time2; \
	int result = gettimeofday(&time1, NULL); \
	TBLOCK
	/*
	if( ( (result =  ) == -1 ) ) { \
		fprintf(stderr, "%s\n", strerror(errno)); \
		exit(EXIT_FAILURE); \
	}
	*/

#define TIMERFOOTER	\
	result = gettimeofday(&time2, NULL); \
	TBLOCK\
	time2.tv_sec -= time1.tv_sec; \
	time2.tv_usec -= time1.tv_usec;

#define TIMER time2

void run_timer(FILE* fp, struct timeval seed, VariableAtomFillRandomFnDecl,
			VariableAtomStringFnDecl, VariableAtomClosureFnDecl, VariableAtomvloadFnDecl,
			VariableAtomaloadFnDecl);
void run_timer_new(FILE* fp, struct timeval seed, long *hint,
			VariableAtomFillRandomFnDecl, VariableAtomStringFnDecl,
			VariableAtomClosureFnDecl, VariableAtomInitFnDecl,
			VariableAtomvloadFnDecl, VariableAtomaloadFnDecl);


int main(int argc, const char* argv[]) {
	FILE* fp;
	struct timeval seed= {0};
	int result;
	if(argc > 1) {
		long given=0, *hint = NULL;

		fp = fopen(argv[1], "r");
		TRY("main()")
			 assert(!isBadPtr(fp));
			if(isBadPtr(fp)) THROW(Assert_Failed,"main()");
		CATCH(Assert_Failed){
			fprintf(stderr, "%s\n", strerror(errno) );
			return EXIT_FAILURE;
		}
		END_TRY

		argv += 2;

//		assert(!isBadPtr(*argv));
		if(*argv){
			char * str = ALLOC(sizeof (*str)* (strlen(*argv)+1));
			assert(!isBadPtr(str));
			strcpy(str, *argv);
			given = strtol(str, NULL, 10);
			FREE(str);
			hint = &given;
		}
		result =  gettimeofday(&seed, NULL);

		TBLOCK // check result from gettimeofday
		
// 		run_timer(fp,seed,Atom_fillRandom,Atom_string,Atom_closure);
// 		run_timer(fp,seed,Atom2_fillRandom,Atom2_string,Atom2_closure);
// 		run_timer(fp,seed,Atom3_fillRandom,Atom3_string,Atom3_closure);
// 		run_timer(fp,seed,Atom4_fillRandom,Atom4_string,Atom4_closure);
		run_timer_new(fp, seed, hint, Atom5_fillRandom, Atom5_string, Atom5_closure,
			Atom5_init, Atom_vload, Atom_aload);

		Atom_add("tester bug", strlen("tester bug"));

		const char* test1 = Atom5_string("your mama");
		assert(!isBadPtr(test1));

		const char* test2 = Atom_add("your mama is still here",
			strlen("your mama is still here"));
		assert(!isBadPtr(test2));

		Atom_add("fools gold is real gold", strlen("fools gold is real gold"));

		Atom_free(test1);
		Atom_free(test2);

		Atom_free(Atom5_string("mad"));
		Atom_free(Atom5_string("about"));
		Atom_free(Atom5_string("you"));
		Atom_free(Atom5_string("is"));

		Atom_free(Atom_add("is", strlen("is")));
		Atom_reset();
		fclose(fp);
	}
	return EXIT_SUCCESS;
}

void beginSum(const long b, long* cl, long** cl2) {
	assert(!isBadPtr(cl));
	cl[0] = 0;
}
void atomSum(const char* cur, long* cl, long** cl2, VariableAtomLengthFnDecl) {
	assert(!isBadPtr(cl));
	cl[0]++;
	cl[1]++;
}

void finishSum(const long b, long* cl, long** cl2) {
	assert(!isBadPtr(cl));
	assert(!isBadPtr(cl2) && !isBadPtr(*cl2));
	while((*cl2)[0] < cl[0]) {
		(*cl2) = RESIZE((*cl2), sizeof((**cl2))*(*cl2)[0]*2);
	    strerror(errno);
	    if((*cl2) == NULL)
		   assert(0);
		assert(!isBadPtr(*cl2));
		for(long i = (*cl2)[0]; i<((*cl2)[0]*2);i++)
		(*cl2)[i] = 0;
		(*cl2)[0] *= 	2;
	}

	(*cl2)[cl[0]+1]++;
	if(cl[2] < cl[0])
		cl[2] = cl[0];
//		THROW(Assert_Failed);
}

void lengthfunc(const char* cur, long* cl, long** cl2, VariableAtomLengthFnDecl) {
	assert(!isBadPtr(VariableAtomLengthFn));
	VariableAtomLengthFn(cur);
}
struct timeval cltimerfunc(VariableAtomClosureFnDecl) {
	assert(!isBadPtr(VariableAtomClosureFn));
	TIMERHEADER;
	VariableAtomClosureFn(NULL, lengthfunc, NULL, NULL, NULL);
	TIMERFOOTER;
	return TIMER;
}

struct timeval timerfunc(FILE* fp, VariableAtomStringFnDecl) {
	char word[128];
	TIMERHEADER;
	assert(!isBadPtr(fp));
	assert(!isBadPtr(VariableAtomStringFn));
	while(getword(fp, word, sizeof word)) {
		VariableAtomStringFn(word);
	}
	TIMERFOOTER;
	return TIMER;
}

void run_timer_new(FILE* fp, struct timeval seed, long *hint,
	VariableAtomFillRandomFnDecl, VariableAtomStringFnDecl,
	VariableAtomClosureFnDecl, VariableAtomInitFnDecl, VariableAtomvloadFnDecl,
	VariableAtomaloadFnDecl) {
		assert(!isBadPtr(fp));
		assert(!isBadPtr(VariableAtomFillRandomFn));
		assert(!isBadPtr(VariableAtomStringFn));
		assert(!isBadPtr(VariableAtomClosureFn));
		assert(!isBadPtr(VariableAtomInitFn));
		assert(!isBadPtr(VariableAtomvloadFn));
		assert(!isBadPtr(VariableAtomaloadFn));
		if(hint)
			VariableAtomInitFn(*hint);
		run_timer(fp, seed, VariableAtomFillRandomFn, VariableAtomStringFn,
				VariableAtomClosureFn, VariableAtomvloadFn, VariableAtomaloadFn);
	}

void run_timer(FILE* fp, struct timeval seed, VariableAtomFillRandomFnDecl,
						VariableAtomStringFnDecl, VariableAtomClosureFnDecl,
	VariableAtomvloadFnDecl, VariableAtomaloadFnDecl) {
	struct timeval time1, time2;
	long  sumNwords[3], *dist;
	assert(!isBadPtr(fp));
	assert(!isBadPtr(VariableAtomFillRandomFn));
	assert(!isBadPtr(VariableAtomStringFn));
	assert(!isBadPtr(VariableAtomClosureFn));
	assert(!isBadPtr(VariableAtomvloadFn));
	assert(!isBadPtr(VariableAtomaloadFn));

	fseek(fp, 0UL, SEEK_SET);
	srand(seed.tv_sec);
	VariableAtomFillRandomFn();
	VariableAtomvloadFn("mad", "about", "you", "arrested development",
		"is", "cool", NULL);
	static const char* my_strings[] = {
		"from",
		"the",
		"array",
		"could be already",
		"in this",
		NULL
	};
	VariableAtomaloadFn(my_strings);

	time1 = timerfunc(fp, VariableAtomStringFn);
	time2 = cltimerfunc(VariableAtomClosureFn);
//	sumNwords = ALLOC(sizeof(*sumNwords) * 3);

	assert(!isBadPtr(sumNwords));
    sumNwords[0] = 0;
	sumNwords[1] = 0;
	sumNwords[2] = 0;
	dist = ALLOC(sizeof(*dist) * MAX_DIST);
	assert(!isBadPtr(dist));

	for(long i = 0; i < MAX_DIST; i++)
		dist[i] = 0;
		dist[0] = MAX_DIST;
	fseek(fp, 0UL, SEEK_SET);
	VariableAtomClosureFn(beginSum, atomSum, finishSum, sumNwords, &dist);

	printf("distribution of numbers:\n");
	printf("[List Size]	");
	for(long i = 1; i <= sumNwords[2]+1; i++)
    printf("[%ld]	", i);
	printf("\n");
	printf("Num of Lists	");
	for(long i = 1; i <= sumNwords[2]+1; i++)
    printf("%ld	", dist[i]);
	printf("\n");
// 	printf("Max List Size: %d\n", sumNwords[2]+1);
    printf("Words added: %ld\n", sumNwords[1]);
	printf("Atom_length on all atoms: %ld seconds, %d microseconds\n",
		time2.tv_sec, time2.tv_usec);
	printf("Atom_string/Atom_new:  time %ld seconds %d microseconds\n",
		time1.tv_sec , time1.tv_usec);
//	FREE(sumNwords);
	FREE(dist);
}
