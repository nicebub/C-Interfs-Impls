int dotProduct(const int x[], const int y[], const int n)  {
	int sum = 0;
	for(int i=0;i<n;i++)
		sum += x[i]*y[i];
	return sum;
}