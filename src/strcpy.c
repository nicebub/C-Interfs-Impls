// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include <sys/time.h>  // for gettimeofday(), timeval, timezone, etc
#include <stdlib.h>  // for EXIT_
#include <stdio.h>  // for fprintf
#include <errno.h>  // for errno
#include <string.h>  // for strerror()

extern int getword(FILE* fp, char *, const int);

struct timeval clock_function(FILE* fp, char*(strcpy_f)(char*, const char*),
											int* words);
char *strcpy_a(char dst[], const char src[]);
char* strcpy_b(char *dst, const char* src);

char *strcpy_a(char dst[], const char src[]) {
	int i = 0;
	for( ; src[i] != '\0'; i++)
		dst[i] = src[i];
	dst[i] = '\0';
	return dst;
}

char* strcpy_b(char *dst, const char* src) {
	char* s = dst;
	while((*dst++ = *src++) != '\0') {}
	return s;
}


struct timeval clock_function(FILE* fp, char*(strcpy_f)(char*, const char*),
												int* words) {
	char word[128], extra[128];
	struct timeval time1, time2;
	struct timezone zone;
	int result;
	*words = 0;
	if( ( (result =  gettimeofday(&time1, &zone)) == -1 ) ) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(getword(fp, word, sizeof word)) {
		strcpy_f(extra, word);
		(*words)++;
	}
	if( ( (result =  gettimeofday(&time2, &zone)) == -1 ) ) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	time2.tv_sec -= time1.tv_sec;
	time2.tv_usec -= time1.tv_usec;
	return time2;
}
/*
int main(int argc, const char* argv[]) {
	FILE* fp;
	if((fp = fopen(argv[1], "r") ) == NULL) {
		fprintf(stderr, "%s\n", strerror(errno) );
		return EXIT_FAILURE;
	}
	int words = 0;
	struct timeval time1;

	time1 = clock_function(fp, *strcpy_a, &words);
	printf("strcpy_a: num word: %d time %ld seconds %d microseconds\n", words,
				time1.tv_sec , time1.tv_usec);
	fseek(fp, 0UL, SEEK_SET);

	time1 = clock_function(fp, *strcpy_b, &words);
	printf("strcpy_b: num word: %d time %ld seconds %d microseconds\n", words,
				time1.tv_sec , time1.tv_usec);
	fseek(fp, 0UL, SEEK_SET);

	time1 = clock_function(fp, *strcpy_a, &words);
	printf("std strcpy: num word: %d time %ld seconds %d microseconds\n", words,
				time1.tv_sec , time1.tv_usec);
	fseek(fp, 0UL, SEEK_SET);

	fclose(fp);
	return EXIT_SUCCESS;
}
*/