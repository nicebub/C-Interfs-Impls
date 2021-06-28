// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

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
