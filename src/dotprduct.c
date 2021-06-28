// Copyright 2021 Scott Lorberbaum
// Actual Code in this book has been reproduced from the C Interfaces and
// Implemntations book by David R. Hanson, published in 1997 by
// Addison-Wesley

// I have made a few changes and revisions to make the code more modern as of
// the std gnu2x

int dotProduct(const int x[], const int y[], const int n)  {
	int sum = 0;
	for(int i = 0; i < n; i++)
		sum += x[i]*y[i];
	return sum;
}
