void quickSort(int arr[], int left, int right) {
    int i;
	int j;
	int pivo;
	int aux;
	i = left; 
	j = right;
	pivo = arr[(i+j)/2];
	
	while(i <= j) {
		while(arr[i] < pivo)
			i = i + 1;
		while(arr[j] > pivo)
			j = j - 1;
		
		if(i <= j) {
			aux = arr[i];
			arr[i] = arr[j];
			arr[j] = aux;
			i = i + 1;
			j = j -1;
		}
	}
	
	if(left < j)
		quickSort(arr,left,j); 
	if(i < right)
		quickSort(arr,i,right);
}

void main(void)
{
	int n;
	int arr[100];
	int i;

	n = input();

	i = 0;
	while(i < n) {
		arr[i] = input();
		i = i + 1;
	}
	
	quickSort(arr,0,n-1);
	
	i = 0;
	while(i < n) {
		println(arr[i]);
		i = i + 1;
	}
}