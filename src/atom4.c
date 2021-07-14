// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include <unistd.h>
//#include <assert.h>
#include <string.h>
#include <stdlib.h>  // for NULL
#include <limits.h>  // for LONG_MAX _MIN
#include "include/atom4.h"
#include "include/defines.h"
#include "include/assert.h"
// #include "include/mem.h" for later

// INCLUDES BEST VERSION OF ATOM_LENGTH

extern const Except_T Mem_Failed;// = { "Cannot Allocate Memory" };

#define BSIZE 2039
#define NELEMS(x) ((sizeof (x))/(sizeof ((x)[0])))
#define ALLOC(x) malloc((x))

static struct atom4 {
	struct atom4* link;
	int len;
	char* str;
	} *buckets[BSIZE];

	static unsigned long scatter[256] = {};

void Atom4_fillRandom() {
	for(int i = 0; i < 256; i++)
		scatter[i] = rand();
}

const char* Atom4_string(const char* str) {
	assert(!isBadPtr(str));
	return Atom4_new(str, (int)strlen(str));
}
#define CHAR_LEN 43
const char* Atom4_int(const long n) {
	char str[CHAR_LEN];
	char* s = str + sizeof str;
	unsigned long m;

	if(n == LONG_MIN)
		m = LONG_MAX + 1UL;
	else if ( n < 0)
		m = -n;
	else
		m = n;
	do
		*--s = m % 10 + '0';
	while((m /= 10) > 0);
	if(n < 0)
		*--s = '-';
	return Atom4_new(s, (str + sizeof str) - s);
}

const char* Atom4_new(const char* str, const int len) {
	unsigned long h;
	int i;
	struct atom4* p;

	assert(!isBadPtr(str));
	assert(len >= 0);
	for(h = 0 , i = 0; i < len; i++)
		h = (h << 1) + scatter[(unsigned char)str[i]];
	h %= NELEMS(buckets);
	for(p = buckets[h]; p; p = p->link) {
		if(len == p->len) {
			for(i = 0; i< len && p->str[i] == str[i]; i++) {}
			if(i == len)
				return p->str;
		}
	}
		p = ALLOC(sizeof (*p) + len + 1);
		if(p == NULL) THROW(Mem_Failed);
		p->len = len;
		p->str = (char*)(p + 1);
		if(len > 0)
			memcpy(p->str, str, len);
		p->str[len] = '\0';
		p->link = buckets[h];
		buckets[h] = p;
		return p->str;
}
int Atom4_oldlength(const char* str) {
	struct atom4* p;

	assert(!isBadPtr(str));

	for(int i = 0; i < NELEMS(buckets); i++)
		for( p = buckets[i]; p; p = p->link)
			if(p->str == str)
				return p->len;

	assert(!"Not an Atom");
	return 0;
}

int Atom4_length(const char* str) {
	struct atom4* p;


	assert(!isBadPtr(str));
	unsigned long h;
	int i, len = (int)strlen(str);
	for(h = 0 , i = 0; i < len; i++)
		h = (h << 1) + scatter[(unsigned char)str[i]];
	h %= NELEMS(buckets);
	for(p = buckets[h]; p; p = p->link) {
		if(p->str == str)
			return p->len;
	}

	assert(!"Not an Atom");
	return 0;
}

void Atom4_closure(void(*func1)(const int bucketNum, int* cl, int* cl2),
						void(*func2)(const char* cur, int* cl, int* cl2,
							int(*Atom_lng)(const char* str)),
						void(*func3)(const int bucketNum, int* cl, int* cl2),
							int* cl, int* cl2) {
	assert(!isBadPtr(buckets) || !"buckets not initialized");
	for(int i = 0; i < BSIZE; i++) {
		struct atom4 *t = buckets[i];
		if(func1)func1(i, cl, cl2);
		for(; t; t = t->link) {
			if(func2)func2(t->str, cl, cl2, Atom4_length);
		}
		if(func3)func3(i, cl, cl2);
	}
}
