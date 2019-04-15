// change this to your id
static const char* student_id = "0416313" ;
//
// do your homework here
//
//

void swap(int & x1, int & x2) {
	int k;
	k = x1;
	x1 = x2;
	x2 = k;
}

void min_heapify(int * input_array, int size, int position) {
	// I'll give you an array without ordered
	// please adjust the subtree which root is position
	//
	// Example:
	//      input : { 7, 14, 6, 5, 1, 3, 8 } ,7, 2
	//   expected : { 7, 14, 3, 5, 1, 6, 8 }
	int a[1000];
	for (int i = 1; i <= size; i++) a[i] = input_array[i - 1];
	int s = position + 1;
	int tmp = s * 2;  //tmp == position*2 + 1
	while (tmp <= size) {
		if ((tmp < size) && (a[tmp] > a[tmp + 1])) tmp++;
		if (a[tmp] > a[s]) break;
		if (a[tmp] <= a[s]) {
			swap(a[tmp], a[s]);
			s = tmp;
			tmp = tmp * 2;
		}
	}
	for (int i = 1; i <= size; i++) input_array[i - 1] = a[i];
}

void min_heap_build(int * input_array, int size) {
	// I'll give you an array without ordered
	// please make this whole array as a min-heap tree
	//
	// Example:
	//      input : { 7, 14, 6, 5, 1, 3, 8 } ,7
	//   expected : { 1, 5, 3, 7, 14, 6, 8 }
	int s;
	s = size / 2;
	while (s) {
		min_heapify(input_array, size, s - 1);
		s--;
	}
}

void min_heap_insert(int * input_heap, int size, int key) {
	// I'll give you an array which is a min heap has one more space
	// (finally value 999 is not a true value)
	// please change the 999 into key
	// and make this array as a min-heap tree
	//
	// Example:
	//      input : { 1, 5, 3, 7, 14, 6, 8, 999 }, 8, 4
	//   expected : { 1, 4, 3, 5, 14, 6, 8 ,7}
	int a[1000];
	int s = size - 1;
	int tmp = (size + 1) / 2 - 1;
	input_heap[s] = key;
	while (tmp) {
		min_heapify(input_heap, size, tmp);
		tmp--;
	}
}

void min_heap_minimum(int * input_heap, int size, int * output_key) {
	// I'll give you an array which is a min heap
	// please show the smallest value
	//
	// Example:
	//      input : { 1, 4, 3, 5, 14, 6, 8 ,7} , 8, &output_key
	//   expected : output_key == 1
	*output_key = input_heap[0];
}

void min_heap_extract(int * input_heap, int size, int * output_key) {
	// I'll give you an array which is a min heap
	// please tell me which is the smallest value
	// and delete that value , then adjust as heap
	// (make the final value 999 as fake)
	//
	// Example:
	//      input : { 1, 4, 3, 5, 14, 6, 8 ,7} , 8, &output_key
	//   expected : { 3, 4, 6, 5, 14, 7, 8, 999} ,output_key == 1
	*output_key = input_heap[0];
	input_heap[0] = input_heap[size - 1];
	input_heap[size - 1] = 999;
	min_heap_build(input_heap, size);
}

void min_heap_sort(int* input_heap, int size) {
	//
	// you cannot use library sort function!
	//
	// I'll give you an array which is a min heap
	// please sort it
	//
	// Example:
	//      input : { 1, 4, 3, 5, 14, 6, 8 ,7} ,8
	//   expected : { 1, 3, 4, 5, 6, 7, 8, 14} 
	int n = size;
	int a[1000];
	for (int i = 0; i < size; i++)a[i] = input_heap[i];
	for (int j = size - 1; j >= 0; j--) {
		swap(a[j], a[0]);
		min_heapify(a, j, 0);
	}
	for (int i = 0; i < size; i++) input_heap[i] = a[size - i - 1];
}


void min_heap_decrease_key(int * input_heap, int size, int position, int decrease) {
	// I'll give you an array which is a min heap
	// the position need to be decrease by a value
	// please adjust the result as a min-heap
	//
	// Example:
	//      input : { 1, 4, 3, 5, 14, 6, 8, 7}, 8, 3, 5
	//   expected : { 0, 1, 3, 4, 14, 6, 8, 7} 
	input_heap[position] = input_heap[position] - decrease;
	min_heap_build(input_heap, size);
}
