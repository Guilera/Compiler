int arr[100];

void read(int arr[], int n) {

	int i;
	i = 0;

	while(i < n) {
		arr[i] = input();
		i = i + 1;
	}
}

void print(int arr[], int n) {

	int i;
	i = 0;

	while(i < n) {
		println(arr[i]);
		i = i + 1;
	}
}

void main(void) {

	int n;

	n = input();

	read(arr,n);

	print(arr,n);
}