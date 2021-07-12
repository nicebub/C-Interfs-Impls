// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>  // for NULL
#include <limits.h>  // for LONG_MAX _MIN
#include <stdarg.h>
#include "include/atom5.h"
#include "include/defines.h"
// #include "include/mem.h" for later

// #include "include/assert.h" for later
// INCLUDES BEST VERSION OF ATOM_LENGTH

#define CHAR_LEN 43
#define BSIZE 2039
#define NELEMS(x) atomsize
#define ALLOC(x) malloc((x))
#define FREE(x) free(*(x)); *(x) = NULL
static int atomsize = 2039;
static struct atom5 {
	struct atom5* link;
	int len;
	char* str;
	} **buckets = NULL;

	static unsigned long scatter[256] = {};

void Atom5_fillRandom() {
	for(int i = 0; i < 256; i++)
		scatter[i] = rand();
}
void Atom5_init(const int hint) {
	assert(hint > 0);
	assert(!buckets && "buckets already allocated");
	buckets = ALLOC(sizeof(*buckets)*hint);
    if(!buckets) {
	   fprintf(stderr, "cannot allocate memory in Atom5_init\n");
	   exit(EXIT_FAILURE);
    }
	for(int i = 0; i < hint; i++) {
		buckets[i] = NULL;
	}
	atomsize = hint;
}

const char* Atom5_string(const char* str) {
	assert(!isBadPtr(str));
	return Atom5_new(str, (int)strlen(str));
}
const char* Atom5_int(const long n) {
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
	return Atom5_new(s, (str + sizeof str) - s);
}

const char* Atom5_new(const char* str, const int len) {
	unsigned long h;
	int i;
	struct atom5* p;
	assert(!isBadPtr(str));
	assert(len >= 0);
	if(!buckets)
	    Atom5_init(BSIZE);
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
		p->len = len;
		p->str = (char*)(p + 1);
		if(len > 0)
		    memcpy(p->str, str, len);
		p->str[len] = '\0';
		p->link = buckets[h];
		buckets[h] = p;
		return p->str;
}
int Atom5_oldlength(const char* str) {
	struct atom5* p;

	assert(!isBadPtr(str));
	assert(buckets  && "buckets not allocated");
	for(int i = 0; i < NELEMS(buckets); i++)
		for( p = buckets[i]; p; p = p->link)
			if(p->str == str)
				return p->len;

	assert(0 && "Not an Atom");
	return 0;
}

int Atom5_length(const char* str) {
	struct atom5* p;
	unsigned long h;

	assert(!isBadPtr(str));
	int i, len = (int)strlen(str);

	assert(buckets  && "buckets not allocated");
	for(h = 0 , i = 0; i < len; i++)
		h = (h << 1) + scatter[(unsigned char)str[i]];
	h %= NELEMS(buckets);
	for(p = buckets[h]; p; p = p->link) {
		if(p->str == str)
			return p->len;
	}

	assert(0 && "Not an Atom");
	return 0;
}

void Atom5_closure(void(*func1)(const int bucketNum, int* cl, int** cl2),
						void(*func2)(const char* cur, int* cl, int** cl2,
							int(*Atom_lng)(const char* str)),
						void(*func3)(const int bucketNum, int* cl, int** cl2),
							int* cl, int** cl2) {
	for(int i = 0; i < atomsize; i++) {
		assert(buckets && "buckets not allocated");
		struct atom5 *t = buckets[i];
		if(func1)func1(i, cl, cl2);
		for(; t; t = t->link) {
			if(func2)func2(t->str, cl, cl2, Atom5_length);
		}
		if(func3)func3(i, cl, cl2);
	}
}

void Atom_free(const char * str) {
	struct atom5* p, *l;
	unsigned long h;

	assert(!isBadPtr(str));
	int i, len = (int)strlen(str);

	assert(buckets && "buckets not allocated");
	for(h = 0 , i = 0; i < len; i++)
		h = (h << 1) + scatter[(unsigned char)str[i]];
	h %= NELEMS(buckets);
	if((p = buckets[h])->str == str) {
		buckets[h] = p->link;
		p->link = NULL;
		FREE(&p);
		return;
	}
	for(; p->link; p = p->link) {
		l = p->link->link;
		if(p->link->str == str) {
			FREE(&p->link);
			p->link = l;
			return;
		}
	}

	assert(0 && "Atom not found or not an Atom");
}


void Atom_reset(void) {
	struct atom5 *p, *q;
	assert(buckets && "buckets not allocated");
	for(int i = 0; i < NELEMS(buckets); i++)
		for(p = buckets[i]; p; p = q) {
			q = p->link;
			FREE(&p);
		}
}
void Atom_vload(const char *str, ...) {
	va_list ap;
	va_start(ap, str);
	assert(str && "NULL string");
	for(	; str; str = va_arg(ap, const char*)) {
		Atom5_string(str);
	}
	va_end(ap);
}
void Atom_aload(const char * strs[]) {
	assert(strs && "NULL array");
	while(*strs)
		Atom5_string(*strs++);
}
const char* Atom_add(const char* str, int len) {
	unsigned long h;
	int i;
	struct atom5* p;
	assert(!isBadPtr(str));
	assert(len >= 0);
	if(!buckets)
		Atom5_init(BSIZE);
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
		p = ALLOC(sizeof (*p));
		p->len = len;
		p->str = (char*)str;
		p->link = buckets[h];
		buckets[h] = p;
		return p->str;
}
