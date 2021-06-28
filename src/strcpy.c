char *strcpy_a(char dst[], const char src[]) {
	int i=0;
	for(;src[i] != '\0'; i++)
		dst[i] = src[i];
	dst[i] = '\0';
	return dst;
}

char* strcpy_b(char *dst, const char* src) {
	char * s = dst;
	while( (*dst++ = *src++) )
		;
	return s;
}