// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x
// INCLUDES MORE BYTES IN EACH ATOM TO STORE THE HASH, and lookup use
// in Atom_new, negligible changes from this in time except sometimes
// on my cpu it seems to take twice as long
#include <unistd.h>
//#include <assert.h>
#include <string.h>
#include <stdlib.h>  // for NULL
#include <limits.h>  // for LONG_MAX _MIN
#include "include/atom3.h"
#include "include/defines.h"
#include "include/assert.h"
// #include "include/mem.h" for later

extern const Except_T Mem_Failed;// = { "Cannot Allocate Memory" };

#define BSIZE 2039
#define NELEMS(x) ((sizeof (x))/(sizeof ((x)[0])))
#define ALLOC(x) malloc((x))

static struct atom3 {
	struct atom3* link;
	unsigned long h;
	int len;
	char* str;
	} *buckets[BSIZE];

	static unsigned long scatter[256] = {};

void Atom3_fillRandom() {
	for(int i = 0; i < 256; i++)
		scatter[i] = rand();
}

const char* Atom3_string(const char* str) {
	assert(!isBadPtr(str));
	return Atom3_new(str, (int)strlen(str));
}
#define CHAR_LEN 43
const char* Atom3_int(const long n) {
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
		*--s = m%10 + '0';
	while((m /= 10) > 0);
	if(n < 0)
		*--s = '-';
	return Atom3_new(s, (int)((str + sizeof str) - s));
}
const char* Atom3_new(const char* str, const int len) {
	unsigned long h, oh;
	int i;
	struct atom3* p;

	assert(!isBadPtr(str));
	assert(len >= 0);
	for(h = 0 , i = 0; i < len; i++)
		h = (h << 1) + scatter[(unsigned char)str[i]];
	oh = h;
	h %= NELEMS(buckets);
	for(p = buckets[h]; p; p = p->link) {
		if(oh == p->h)
			return p->str;
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
		p->h = oh;
		return p->str;
}

int Atom3_length(const char* str) {
	struct atom3* p;
	assert(!isBadPtr(str));

	for(int i = 0; i < NELEMS(buckets); i++)
		for( p = buckets[i]; p; p = p->link)
			if(p->str == str)
				return p->len;

	assert(!"Not an Atom");
	return 0;
}

void Atom3_closure(void(*func1)(const int bucketNum, int* cl, int* cl2),
						void(*func2)(const char* cur, int* cl, int* cl2,
							int(*Atom_lng)(const char* str)),
						void(*func3)(const int bucketNum, int* cl, int* cl2),
							int* cl, int* cl2) {
	assert(!isBadPtr(buckets) || !"buckets not initialized");
	for(int i = 0; i < BSIZE; i++) {
		struct atom3 *t = buckets[i];
		if(func1)func1(i, cl, cl2);
		for(; t; t = t->link) {
			if(func2)func2(t->str, cl, cl2, Atom3_length);
		}
		if(func3)func3(i, cl, cl2);
	}
}
