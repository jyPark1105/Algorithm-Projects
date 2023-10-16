#include <stdio.h>
#include <math.h>      // floor�Լ� ���� ���� ����. 
#include <stdlib.h>    // rand�Լ� ���� ���ؼ� ���̺귯���� ����. 
#include <time.h>      // �õ尪 <- ���� �ð�, srand�Լ� ����Ͽ� �׻� ���� �������� ������ rand�Լ��� Ŀ����. 10�� 4�ڽ±��� ���� �����Ƿ� 100���� ������ ��.
#include <limits.h>      // int_MAX���� ����ϱ� ���� ����ϴ� �Լ�. MergeSort���� ������ �� �κй迭�� �������ε����� ���� �ε��� ���� ���Ѵ밪 �ִ� �� ��� int�� �ִ� �ֱ� 
                  


// 0. ������ ������ ���ϴ� ���α׷� ¥�� 
int Set_The_Numbers_of_Array()                         // " ��(1) " 
{
   	int Num0;
   	printf("Set the number of elements, of Array : ");
   	scanf("%d", &Num0);
   	if(Num0 <= 0)
    {
        printf("The number of elements should be Natural Number.\n\n");		// �Է°��� �ڿ������� ��. 
        Set_The_Numbers_of_Array();
    }
    else
    {
        return Num0;		// ����ڰ� �Է��� ���� �������ش� -> �Է��� ũ�⸦ ���ϴ� ��. 
    }
}
                                                      
// 1. Random�� �迭�� ������ ¥��. 0 <= A[i] <= 100 ������ integer���� ����ְԲ�(i = 0 ~ ArrSize-1), O(n)(���Ұ�����ŭ �ɸ�) 
void Random_Array(int *A, int Num) // pA = &A[0], *(pA+i) = pA[i] = A[i] �̿��Ͽ� �迭 A�� ���. 
{
    srand(time(NULL));            // srand�Լ��� �������ڸ� time�Լ��� �����������ν� �Ź� �ٸ� ������ ���ҵ��� �迭 A�� ���� �� �ְ� �Ǿ���. 
    int Array_Size = Num;      // �迭������ <- ���� ���� �� n
    int i;
    for(i = 0; i < Array_Size; i++)                              // "O(n)"
    {
    	A[i] = rand();      // Random�� ���ڵ�� �迭 A�� ������. 
    }
}   

void Copy_Array(int *A, int *B, int Length)			// �迭�� �������ִ� �Լ��̴�. �� �˰����� ���� �� �� �迭�� ī���Ͽ� �ٽ� ������ �����Ѵ�. 
{
    int i;
    for(i = 0; i < Length; i++)
  	{	
        B[i] = A[i];
   	}
}

void swap(int *p1, int *p2)				// �����͸� Ȱ����, ���� Exchange���ִ� �Լ� 
{
      int temp = *p1;
      *p1 = *p2;
      *p2 = temp;
}

int COMPCOUNT = 0;

int COMPARE(int X, int Y)		// X, Y�̸� X > Y�� �� 1�� �������ְ�, ���� X == -10, Y == -20�̸� COMPCOUNT++�� ���� �׳� �����Ѵ�. 
{
   	COMPCOUNT++;
   	if(X == -10 && Y == -20)
   	{
      	return 1;
   	}	
   	if(X == Y)
   	{
      	return 0;
   	}
   	else if(X > Y)
   	{	
      	return 1;   
   	}
   	else
   	{ 
      	return 0;      // Case : X < Y
   	}
}

void Insertion_Sort(int *A, int Num) // pI = pointer of Insertion sort�� ����, int *pI == A == &A[0](pI�� �迭 A�� ù �ּҸ� ����Ŵ) 
{
    int Array_Size = Num;      // �迭������ <- ���� ���� �� n
    int i, j, key;
    for(j = 1; j < Array_Size; j++)   // 2�� loop�̹Ƿ� T(n) = O(n^2) 
    {
        key = A[j];
        i = j-1;
        while(i >= 0 && COMPARE(A[i], key))		// ���� i > 0�� A[i] > key�� ���ÿ� �����ϸ�, ������ ���� i���� ���� 
        {
          	A[i+1] = A[i];
            i--;								// �� ĭ �� ��������. 
        }
        A[i+1] = key;							// key���� �迭 ���� ���� ������ �������� �ʱ�ȭ�� �����ش�. 
    }
}
         
int Max_Heapify(int *A, int i, int Length_of_Array) 
{
    int HeapSize_of_A = Length_of_Array; // �迭�� ���̰� �� ������ ��ü ��� �� 
    int lchild = 2*i + 1;   // �迭�� ù �ε����� 0�̹Ƿ� ���� 1�� ������� ���డ���ϴ�. 
    int rchild = 2*i + 2;
    int largest = 0;
    if(A[lchild] == NULL && A[rchild] == NULL)   // child node�� 0���� leaf node�� ��� Max_Heapify �ߴ� 
    {
        return NULL;
    }
    if(lchild <= HeapSize_of_A - 1 && COMPARE(A[lchild], A[i]))		// ũ�� �� �ܰ� 
    {
        largest = lchild;
    }
    else 
    {
        largest = i;
    }
    if(rchild <= HeapSize_of_A - 1 && COMPARE(A[rchild], A[largest]))
    {
        largest = rchild;
    }
    if(largest != i)		// largest != i�̸� largest���ҿ� i���ҿ� �����ϰ�, MaxHeapify�� �����Ѵ�. 
    {
        COMPARE(-10, -20);
        swap(&A[i], &A[largest]);
        Max_Heapify(A, largest, HeapSize_of_A);
    }
}

void Build_Max_Heap(int *A, int Num) // # of leaves = ��floor(n/2) �̹Ƿ�, leaf nodes are already sorted!, thus floor(n/2) ~ root node���� MaxHeapify�Լ� ����. 
{
    int Heap_Size_of_A = Num;            // Length of Array A.
    int floor_Size_of_A;               // ������ �ε����� 1���� ����������, �迭�� 0���� �����̹Ƿ� ���� ������ �ʱ�ȭ�Ѵ�. 
    int i;
    floor_Size_of_A = floor(Heap_Size_of_A/2) - 1;   // �캯�� ���� ���� ��� ������ ����� ���� leaf node�� �ƴ� �ε����� �ִ��� ���� �� �ִ�! 
    for(i = floor_Size_of_A; i >= 0; i--)		// ��������� �ٷ� �� �ε������� ��Ʈ������ MAX_HEAPIFY�� �����Ѵ�. 
    {
    	Max_Heapify(A, i, Heap_Size_of_A);
    }
    printf("\nBUILD-MAX-HEAP ���� �� �迭 A\n");		// HEAPSORT�� ù��° ����. �߿��ϹǷ� ����Ͽ���. 
    for(i = 0; i < Heap_Size_of_A; i++)
    {
    	printf("Build_MAX_HEAP_A[%d] = %d\n", i, A[i]);
    }
} 

void Heap_Sort(int *A, int Num)   
{
    int Heap_Size_of_A = Num;
    Build_Max_Heap(A, Heap_Size_of_A);      // ���� �ƽ� ����. O(n) MAXHEAPIFY�� �����ϴ� �����̴�. 
    int i;
    for(i = Heap_Size_of_A - 1; i > 0; i--) // root node�� ���� �ݺ������� n, ���ÿ� Max_Heapify�Լ��� Heap�� height��ŭ ����Ǵ� log n�̴�. �� O(nlogn) 
    {
        COMPARE(-10, -20);
        swap(&A[0], &A[i]);
        Heap_Size_of_A = Heap_Size_of_A - 1;
        Max_Heapify(A, 0, Heap_Size_of_A);
    }
    Heap_Size_of_A = Num; // Heap_Sort�Լ� �����Ѵٰ� HeapSize�� �ٿ��� ������ Sorting ������ �ٽ� ���� ũ��� �ǵ����ش�. 
}

void Merge(int *A, int p, int q, int r)       //   MergeSort �ڵ� �ϼ�. 
{
    int Left_Num = q - p + 1;   // A[p ~ r]������ �迭�� Left Subarray A_Left[p ~ q]�� Right Subarray A_Right[q+1 ~ r]�� ����(Divide Two Subarrays L & R, when the subarray's size is 1.) 
    int Right_Num = r - q;      // r - (q+1) + 1 == r - q
	int Left_Subarray_of_A[Left_Num+1], Right_Subarray_of_A[Right_Num+1];    // ���� �޸� �Ҵ�. not in place�̹Ƿ� extra space�� �ʼ����̴�..
	int i, j, k;
	for(i = 0; i <= Left_Num - 1; i++)   // 0 ~ Left_Num-1���� ���� �ִµ�, Left_Num-1(���� �κй迭�� �� ������ �� <- ������ �ִ��� ����)
    {
    	Left_Subarray_of_A[i] = A[p+i];
    }
    for(j = 0; j <= Right_Num - 1; j++)   // 0 ~ Right_Num-1���� ���� �ִµ�, Right_Num-1(������ �κй迭�� �� ������ �� <- ������ �ִ��� ����)
    {
    	Right_Subarray_of_A[j] = A[q+j+1];   
    }
      // LeftSubArray�� RightSubArray�� ������ �ε����� ��û���� ū ���� �������� ������ NULL���� ���ҵ� ���� ������ �����ϴ� ������ �� �� �־����ϴ�. �׷��� �ٷ� INT_MAX���� �̿��Ͽ����ϴ�! 
    Left_Subarray_of_A[Left_Num] = INT_MAX;      
    Right_Subarray_of_A[Right_Num] = INT_MAX;   
   
      // �ε��� �ʱ�ȭ ��Ű��!
    i = 0, j = 0; 
    for(k = p; k <= r; k++)   // p ~ r���� �����Ѵٴ� ���� �ǹ� -> A�迭�� ù �ε����� p, �� �ε����� r�̴ϱ�, ������ ū ������ ������ �Ͻ��� �� �ִ�. 
    {                  // ���� LeftSubarray�� �ε����� ���Ѵ밪�� ����ִ� �ε������� ���ٸ�, RightSubarray�� ���鸸 A�� ���� �κе鿡 ������� ����ָ� �ȴ�. �ݴ��� ��쵵 ���������̴�. 
    	if(COMPARE(Right_Subarray_of_A[j], Left_Subarray_of_A[i]))		// ���� ����迭 < ������ ����迭 -> ���� �迭�� ���Ұ� 
    	{
        	A[k] = Left_Subarray_of_A[i];
        	i++;
    	}
    	else if(COMPARE(Left_Subarray_of_A[i], Right_Subarray_of_A[j]))	// ���� ����迭 > ������ ����迭 -> ������ �迭�� ���Ұ� 
    	{
        	A[k] = Right_Subarray_of_A[j];
        	j++;
    	}
  	}
}

int Merge_Sort(int *A, int p, int r)		// �������� Merge ����(���� ���� �˰���) 
{
   	int q;
   	if(p < r)
    {
    	q = floor((p+r)/2);
    	Merge_Sort(A, p, q);
       	Merge_Sort(A, q+1, r);
       	Merge(A, p, q, r);
   	}
}   

int Partition_of_Quick_Sort(int *A, int p, int r)	// Version1 �� Version2���� ���δ� 
{
   	int i = p-1;
   	int j;
   	int key = A[r];      // �ᱹ A�� ������ �ε����� �ش��ϴ� ���Ұ� pivot ��(key ��)�� �ȴ�. 
   	int Pivot_idx;
   	for(j = p; j < r; j++)
   	{
       	if(COMPARE(key, A[j]) || A[j] == key) // A[j] <= key
       	{
           	i++;
           	COMPARE(-10, -20);
           	swap(&A[i], &A[j]);
       	}
   	}
   	COMPARE(-10, -20);
   	swap(&A[i+1], &A[r]);
   	Pivot_idx = i+1;
   	return Pivot_idx;
}

int Median_of_Three_Partition(int *A, int p, int r)
{
   	int Leftmost_of_Array = p;
   	int Rightmost_of_Array = r;
   	int Median_of_Array = (Leftmost_of_Array + Rightmost_of_Array)/2;
   	int q_pivot_idx = 0;
   	int i, j, key;
   	if(Leftmost_of_Array == Rightmost_of_Array)      // case of (p == r)
    {
       	q_pivot_idx = Leftmost_of_Array;   
   	}
   // Compare Three Values(pick up the median value in three)
   	if(COMPARE(A[Leftmost_of_Array], A[Rightmost_of_Array])+1 || COMPARE(A[Leftmost_of_Array], A[Median_of_Array]+1))   // �� �Ǵ� ���� ���� ���� ���, ������ �߾Ӱ��� ���� ��! 
   	{
       	q_pivot_idx = Leftmost_of_Array;   
   	}
   	else if(COMPARE(A[Median_of_Array], A[Rightmost_of_Array])+1)      // 3�� �߿� 2���� ���� ��츦 ���� ���̹Ƿ� 3C2 = 3���� ���(�� 2���� + �̰� 1����) 
   	{
       	q_pivot_idx = Median_of_Array;   
   	}
   
   // 3���� �� ���ؾߵǴµ�, �̰��� 3!�� ����� ���̴�.(** LMR != RML�� ������ �ٸ��Ƿ�. ���丮��� ����� ���� ���� ��.) 
   	if(COMPARE(A[Rightmost_of_Array], A[Leftmost_of_Array]) && COMPARE(A[Leftmost_of_Array], A[Median_of_Array]))      // 1. A[M] < A[L] < A[R] -> A[L]�� �� ��. 
   	{
       	q_pivot_idx = Leftmost_of_Array;   
   	}
   	else if(COMPARE(A[Leftmost_of_Array], A[Rightmost_of_Array]) && COMPARE(A[Median_of_Array], A[Leftmost_of_Array]))   // 2. A[R] < A[L] < A[M] 
   	{
       	q_pivot_idx = Leftmost_of_Array;   
   	}
   	else if(COMPARE(A[Median_of_Array], A[Leftmost_of_Array]) && COMPARE(A[Rightmost_of_Array], A[Median_of_Array]))   // 3. A[L] < A[M] < A[R]
   	{
       	q_pivot_idx = Median_of_Array;
   	}
   	else if(COMPARE(A[Leftmost_of_Array], A[Median_of_Array]) && COMPARE(A[Median_of_Array], A[Rightmost_of_Array]))   // 4. A[R] < A[M] < A[L]
   	{
       	q_pivot_idx = Median_of_Array;
  	}
   	else if(COMPARE(A[Rightmost_of_Array], A[Leftmost_of_Array]) && COMPARE(A[Median_of_Array], A[Rightmost_of_Array]))   // 5. A[L] < A[R] < A[M]
   	{
       	q_pivot_idx = Rightmost_of_Array;
   	}
   	else if(COMPARE(A[Leftmost_of_Array], A[Rightmost_of_Array]) && COMPARE(A[Rightmost_of_Array], A[Median_of_Array]))    // 6. A[M] < A[R] < A[L]
   	{
       	q_pivot_idx = Rightmost_of_Array;
   	}
   
   	if(q_pivot_idx == Leftmost_of_Array)	// �� ������ �ε��� -> �Ǻ��� �ε��� 
   	{
    	COMPARE(-10, -20);
    	swap(&A[q_pivot_idx], &A[r]);
       	key = A[r];
       	i = p-1;
       	if(p >= 0)
       	{
           	for(j = p; j < r; j++)
           	{
               	if(COMPARE(key, A[j]) || A[j] == key)
              	{
                    i++;
            		swap(&A[i], &A[j]);
              	}
            }
      	}
    	COMPARE(-10, -20);
       	swap(&A[i+1], &A[r]);
       	return i+1;
   }
   	else if(q_pivot_idx == Median_of_Array) 	// �߰� �ε��� -> �Ǻ��� �ε��� 
   	{
        COMPARE(-10, -20);
       	swap(&A[q_pivot_idx], &A[r]);
       	key = A[r];
       	i = p-1;   
       	if(p >= 0)
       	{
           	for(j = p; j < r; j++)
           	{
               	if(COMPARE(key, A[j]) || A[j] == key)
               	{
                  	i++;
                    swap(&A[i], &A[j]);
              	}
            }
        }
       	COMPARE(-10, -20);
       	swap(&A[i+1], &A[r]);
       	return i+1;
   	}
   	else if(q_pivot_idx == Rightmost_of_Array)	// �� �������� �ε��� -> �Ǻ��� �ε��� 
   	{
       	key = A[r];
       	i = p-1;
       	if(p >= 0)
        {
           	for(j = p; j < r; j++)
            {
               	if(COMPARE(key, A[j]) || A[j] == key)
               	{
                    i++;
                    swap(&A[i], &A[j]);
               	}
           	}
        }
        COMPARE(-10, -20);
        swap(&A[i+1], &A[r]);
        return i+1;
   	}
}

int MiddleIndex_of_MAX_MIN_Partition(int *A, int p, int r)	
{							// Quick Sort Version 4 ���� �ִ��� �ε����� �ּڰ��� �ε����� ��� �ε����� �Ǻ��� �ε����� �ϴ� �˰��� 
   	int n = r-p+1;   // �迭�� ���̸�ŭ
   	int idx1, idx2, i, j, key;
   	int MAX = -INT_MAX;
   	int MIN = INT_MAX;
   	int MAX_IDX, MIN_IDX;
   	int pivot = 0;
   	for(idx1 = p; idx1 <= r; idx1++)      // �迭�� �ִ��� �ε����� ���ϴ� ���� 
   	{
      	if(COMPARE(A[idx1], MAX))
      	{
         	MAX_IDX = idx1;
      	}
  	}
   	for(idx2 = p; idx2 <= r; idx2++)      // �迭�� �ּڰ��� �ε����� ���ϴ� ���� 
   	{
      	if(COMPARE(MIN , A[idx2]))
      	{
         	MIN_IDX = idx2;
      	}
   	}
   	pivot = (MAX_IDX+MIN_IDX)/2;		// (�ִ� �ε��� + �ּڰ� �ε���)/2 -> �Ǻ��� �ε���  
   	key = A[pivot];						// �Ǻ��� -> key�� 
   	i = p-1;
   	if(p >= 0)
   	{
      	for(j = p; j <= r; j++)
      	{   
         	if(j == pivot)				// j == pivot�̸� �׳� �ǳʶ�. 
        	{
            	continue;
         	}
         	else if(COMPARE(key, A[j]) || A[j] == key)	// �� �ܿ��� if���� ��ħ. 
         	{
            	i++;
            	COMPARE(-10, -20);
            	swap(&A[i], &A[j]);
         	}	
      	}
   	}
   	swap(&A[i+1], &A[pivot]);
   	pivot = i+1;
   	return pivot;
}

int Quick_Sort(int *A, int p, int r, int Ver)	// Version1, Version2, Version4�� ����ϴ� ����Ʈ ���� 
{
   	int i, q;
   	if(p < 0)
    {
       	return 0;
    }
    if(Ver == 1)   // Version 1 is the Case : "Last Element" -> Pivot Value
    {
       	if(p < r)
        {
        	q = Partition_of_Quick_Sort(A, p, r);
            Quick_Sort(A, p, q-1, Ver);
            Quick_Sort(A, q+1, r, Ver);
        }
    }
    else if(Ver == 3)   // Version 3 is the Case : "Median-of-Three-Partioning" -> Pivot Value
    {
       	if(p < r)
       	{
           q = Median_of_Three_Partition(A, p, r);	
           Quick_Sort(A, p, q-1, Ver);
           Quick_Sort(A, q+1, r, Ver);   
        }
    }
    else if(Ver == 4)
   	{
        if(p < r)
        {
            q = MiddleIndex_of_MAX_MIN_Partition(A, p, r);
            Quick_Sort(A, p, q-1, Ver);
            Quick_Sort(A, q+1, r, Ver);
      	}
   	}
}

int RANDOM(int p, int r)   // (p >= 0 && r <= length[A] - 1)
{
   	if(p == r)			   // ��ó���� �ǳ��� �ε����� ���ٸ� �׳� �� �ε����� �Ǻ��� �ε����� ���� 
   	{
       return p;
   	}
   	else if(p < r)			// �ƴ� ��쿡�� rand�Լ��� ���� �޴´�. 
    {
       	int RANDOM_NUMBER = rand()%(r-p+1) + p;   // ���� p = 2�̰� r = 5�̸�, 2 ~ 5 ������ �ε����� �����ϰ� ���;� �Ǻ� ������ �������ٵ�
       	return RANDOM_NUMBER;         // �ٸ��� �����غ��� 0 ~ 3�� ������(4�� modulo����)�� ���� �� �ִ� ������ ���� 2�� ���ϸ� ������ 2 ~ 5�� ���� �����ϴ�!!!! 
    }
    else 
    {
    	return NULL;
   	}
}

int Randomized_Partition_of_Quick_Sort(int *A, int p, int r) // QuickSort Version2���� Pivot���� �����ִ� �Լ� 
{
   	int i = RANDOM(p, r); // p���� r����,  
   	if(p == r)			
   	{	
       	return 0;
   	}
   	COMPARE(-10, -20);
   	swap(&A[r], &A[i]);
   	return Partition_of_Quick_Sort(A, p, r);
}

void Randomized_Quick_Sort(int *A, int p, int r)			// Version 2 QuickSort �Լ�. 
{
   	int q;
   	if(p < r)
   	{
       	q = Randomized_Partition_of_Quick_Sort(A, p, r);
       	Randomized_Quick_Sort(A, p, q-1);
       	Randomized_Quick_Sort(A, q+1, r);
   	}
}

int main(void)
{
   	int n = Set_The_Numbers_of_Array(); // ���Ұ��� �����ִ� �Լ� ȣ��. 
   	int VERSION;
   	int Copied_Array_A[n], Original_Array_A[n], i;   // �� �˰����� ���ÿ� ������ �迭 A�� ���ĵ� ���·� �ٸ� �˰��� ���Ƿ�  
   	// �װ��� �����ϱ� ���� �迭�� 2�� ����(����� �迭, ���ĵ� �迭) 
   	Random_Array(Original_Array_A, n);               // ������ ���Ұ�����ŭ�� ������ �迭 A�� �����ϴ� �Լ� ȣ��. 
   	Copy_Array(Original_Array_A, Copied_Array_A, n);   // ���纻 <- ���� �� �ʱ�ȭ(�� �˰��� ���� ���� ���) 
         
   	printf("\n���� �迭 A, �ǽ� �� ��\n");
   	for(i = 0; i < n; i++)            // "O(n)"
   	{
       	printf("Original A[%d] = %d\n", i, Original_Array_A[i]);    // original�� Array A�� Ȯ�� �� ����ϱ� 
    }
   
   	printf("\n\nINSERTION SORT ���� �� �迭 A\n");
   	Insertion_Sort(Copied_Array_A, n);      //�ϼ� S
   	for(i = 0; i < n; i++)            // "O(n)"
    {
       	printf("Insertion_Sorted_A[%d] = %d\n", i, Copied_Array_A[i]); 
	}
   	printf("\nINSERTION SORT ���ൿ�� ��Ƚ�� : %d\n\n", COMPCOUNT);
   
   
   	COMPCOUNT = 0;
   	Copy_Array(Original_Array_A, Copied_Array_A, n);
   	Heap_Sort(Copied_Array_A, n);         //�ϼ� 
   	printf("\n\nHEAP SORT ���� �� �迭 A\n");
   	for(i = 0; i < n; i++)            // "O(n)" 
   	{
       	printf("Heap_Sorted_A[%d] = %d\n", i, Copied_Array_A[i]);
   	}
   	printf("\nHEAP SORT ���� ���� ��Ƚ�� : %d\n\n", COMPCOUNT);
      
    COMPCOUNT = 0;
    Copy_Array(Original_Array_A, Copied_Array_A, n);
    printf("\n\nMERGE SORT ���� �� �迭 A\n");
    Merge_Sort(Copied_Array_A, 0, n-1);      //�ϼ� //�ϼ� 
    for(i = 0; i < n; i++)            // "O(n)" 
    {
        printf("Merge_Sorted_A[%d] = %d\n", i, Copied_Array_A[i]);
    }
    printf("\nMERGE SORT ���� ���� ��Ƚ�� : %d\n\n", COMPCOUNT);
   
    for(VERSION = 1; VERSION <= 4; VERSION++)
    {
        printf("\nQUICK SORT VER %d ���� �� �迭 A\n", VERSION);
        COMPCOUNT = 0;
        if(VERSION == 1)
        {
        	Copy_Array(Original_Array_A, Copied_Array_A, n);
            Quick_Sort(Copied_Array_A, 0, n-1, VERSION);
            for(i = 0; i < n; i++)            // "O(n)" 
            {
               	printf("Quick_Sorted_Ver%d_A[%d] = %d\n", VERSION, i, Copied_Array_A[i]);
            }
            printf("\nQUICK SORT Ver%d ���� ���� ��Ƚ�� : %d\n\n", VERSION, COMPCOUNT);
    	}
      	else if(VERSION == 2)
      	{
         	Copy_Array(Original_Array_A, Copied_Array_A, n);
         	Randomized_Quick_Sort(Copied_Array_A, 0, n-1);
            for(i = 0; i < n; i++)            // "O(n)" 
            {
               	printf("Quick_Sorted_Ver%d_A[%d] = %d\n", VERSION, i, Copied_Array_A[i]);
            }
         	printf("\nQUICK SORT Ver%d ���� ���� ��Ƚ�� : %d\n\n", VERSION, COMPCOUNT);
      	}
      	else if(VERSION == 3)
      	{
         	Copy_Array(Original_Array_A, Copied_Array_A, n);
         	Quick_Sort(Copied_Array_A, 0, n-1, VERSION);
         	for(i = 0; i < n; i++)            // "O(n)" 
            {
               	printf("Quick_Sorted_Ver%d_A[%d] = %d\n", VERSION, i, Copied_Array_A[i]);
            }
         	printf("\nQUICK SORT Ver%d ���� ���� �� Ƚ�� : %d\n", VERSION, COMPCOUNT);
      	}
      	else if(VERSION == 4)
      	{
         	Copy_Array(Original_Array_A, Copied_Array_A, n);
         	Quick_Sort(Copied_Array_A, 0, n-1, VERSION);
         	for(i = 0; i < n; i++)            // "O(n)" 
            {
               	printf("Quick_Sorted_Ver%d_A[%d] = %d\n", VERSION, i, Copied_Array_A[i]);
            }
         	printf("\nQUICK SORT Ver%d ���� ���� �� Ƚ�� : %d\n", VERSION, COMPCOUNT);
      	}
    }
    return 0;
}
