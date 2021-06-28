// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
int linenum;

int getword(FILE* fp, char *, const int);
void doubleword(const char*, FILE *);

int main(int argc, const char* argv[]) {
	for(int i = 0; i < argc; i++) {
		FILE* fp = fopen(argv[i], "r");
		if(fp == NULL) {
			fprintf(stderr, "%s: can't open '%s'(%s)\n",
				argv[0], argv[i], strerror(errno));
				return EXIT_FAILURE;
		} else {
			doubleword(argv[i], fp);
			fclose(fp);
		}
	}
	if(argc == 1 ) doubleword(NULL, stdin);
	return EXIT_SUCCESS;
}

int getword(FILE* fp, char* buf, const int size) {
	int c;

	c = getc(fp);
	for( ; c != EOF && isspace(c); c=getc(fp))
		if( c == '\n' )
			linenum++;
	 {
		int i = 0;
		for(; c != EOF && !isspace(c); c=getc(fp))
			if( i < size - 1 )
				buf[i++] = tolower(c);
		if( i < size)
			buf[i] = '\0';
	}
	if( c != EOF)
		ungetc(c, fp);
	return buf[0] != '\0';
}

void doubleword(const char * name, FILE* fp) {
	char prev[128], word[128];

	linenum = 1;
	prev[0]= '\0';
	while(getword(fp, word, sizeof word)) {
		if(isalpha(word[0]) && strcmp(prev, word) == 0) {
			if(name)
				printf("%s:", name);
			printf("%d: %s\n", linenum, word);
			word[0] = '\0';
		}
		strncpy(prev, word, sizeof prev);
	}
}
