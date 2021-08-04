#include <stdlib.h>
#include <string.h>
#include "include/assert.h"
#include "include/except.h"
#include "include/mem.h"

const Except_T Mem_Failed = { "Allocation Failed" };

static struct descriptor {
	struct descriptor* free;
	struct descriptor* link;
	const void* ptr;
	long size;
	const char* file;
	int line;
} *htab[2048];

static struct descriptor freelist = {&freelist};

union align {
	int i;
	long l;
	long long ll;
	long *lp;
	long long *llp;
	void *p;
	void (*fp)(void);
	float f;
	double d;
	long double ld;
};

#define hash(p, t) (((unsigned long)(p)>>3) &\
	(sizeof(t)/sizeof((t)[0])-1))

#define NDESCRIPTORS 512

#define NALLOC ((4096 + sizeof(union align) - 1) / \
	(sizeof(union align)))*(sizeof(union align))

static struct descriptor* find(const void* ptr) {
	struct descriptor *bp = htab[hash(ptr,htab)];
	
	while(bp && bp->ptr != ptr)
		bp = bp->link;
	return bp;
}

void Mem_free(void* ptr, const char* file, int line) {
	if(ptr) {
		struct descriptor* bp;
		if (((unsigned long)ptr)%(sizeof(union align)) != 0
		|| (bp = find(ptr)) == NULL || bp->free)
			Except_raise(&Assert_Failed,file,"Mem_free()",line);

		bp->free = freelist.free;
		freelist.free = bp;
	}
}

void* Mem_resize(void* ptr, long nbytes, const char* file, int line) {
	struct descriptor* bp;
	void* newptr;
	
	assert(ptr);
	assert(nbytes > 0);
	
	if (((unsigned long)ptr)%(sizeof(union align)) != 0
	|| (bp = find(ptr)) == NULL || bp->free)
		Except_raise(&Assert_Failed,file,"Mem_resize()",line);
	newptr = Mem_alloc(nbytes, file, line);
	memcpy(newptr, ptr, nbytes < bp->size? nbytes : bp->size);
	Mem_free(ptr,file,line);
	return newptr;
}

void* Mem_calloc(long count, long nbytes, const char* file, int line) {
	void* ptr;
	
	assert(count >0);
	assert( nbytes > 0);
	
	ptr = Mem_alloc(count*nbytes, file, line);
	memset(ptr, '\0', count*nbytes);
	return ptr;
}

static struct descriptor* dalloc(void* ptr, long size, const char* file, int line) {
	static struct descriptor* avail;
	static int nleft;
	
	if(nleft <= 0) {
		avail = malloc(NDESCRIPTORS*sizeof(*avail));
		if(avail == NULL)
			return NULL;
		nleft = NDESCRIPTORS;
	}
	avail->ptr = ptr;
	avail->size = size;
	avail->file = file;
	avail->line = line;
	avail->free = avail->link = NULL;
	nleft--;
	return avail++;
}

void* Mem_alloc(long nbytes, const char* file, int line) {
	struct descriptor* bp, *prev;
	void* ptr;
	
	assert(nbytes > 0);
	nbytes = ((nbytes + sizeof(union align) - 1)/
		(sizeof(union align))) * (sizeof(union align));
		prev = freelist.free;
	for(bp = freelist.free; bp; bp = bp->free){
		if(bp->size > nbytes){
			bp->size -= nbytes;
			ptr = (char*) bp->ptr + bp->size;
			if(bp->size == sizeof(union align)){
				freelist.free = freelist.free->free;
			}
			if( (bp = dalloc(ptr, nbytes, file, line)) != NULL) {
				unsigned h = hash(ptr, htab);
				bp->link = htab[h];
				htab[h] = bp;
				memset(ptr,'\x5',nbytes);
				return ptr;
			}
			else{
				if(file == NULL)
					THROW(Mem_Failed,"Mem_alloc()");
				else
					Except_raise(&Mem_Failed,file,"Mem_alloc()",line);
			}
			
		}
		if(bp == &freelist){
			struct descriptor* newptr;
			if((ptr = malloc(nbytes + NALLOC)) == NULL
			|| (newptr = dalloc(ptr, nbytes + NALLOC, __FILE__, __LINE__)) == NULL) {
				if(file == NULL)
					THROW(Mem_Failed,"Mem_alloc()");
				else
					Except_raise(&Mem_Failed,file,"Mem_alloc()",line);
			}
			newptr->free = freelist.free;
			freelist.free = newptr;
		}
	}
	assert(0);
	return NULL;
}