#include <stdio.h>
#include <math.h>      // floor함수 쓰기 위해 선언. 
#include <stdlib.h>    // rand함수 쓰기 위해서 라이브러리를 담음. 
#include <time.h>      // 시드값 <- 현재 시간, srand함수 사용하여 항상 같은 랜덤값이 나오는 rand함수를 커버함. 10의 4자승까지 값이 나오므로 100으로 나눠줄 것.
#include <limits.h>      // int_MAX값을 출력하기 위해 사용하는 함수. MergeSort에서 각각의 두 부분배열의 마지막인덱스의 다음 인덱스 값에 무한대값 넣는 것 대신 int형 최댓값 넣기 
                  


// 0. 원소의 개수를 정하는 프로그램 짜기 
int Set_The_Numbers_of_Array()                         // " Θ(1) " 
{
   	int Num0;
   	printf("Set the number of elements, of Array : ");
   	scanf("%d", &Num0);
   	if(Num0 <= 0)
    {
        printf("The number of elements should be Natural Number.\n\n");		// 입력값이 자연수여야 함. 
        Set_The_Numbers_of_Array();
    }
    else
    {
        return Num0;		// 사용자가 입력한 값을 리턴해준다 -> 입력의 크기를 정하는 것. 
    }
}
                                                      
// 1. Random한 배열의 구성을 짜줌. 0 <= A[i] <= 100 사이의 integer값을 담아주게끔(i = 0 ~ ArrSize-1), O(n)(원소개수만큼 걸림) 
void Random_Array(int *A, int Num) // pA = &A[0], *(pA+i) = pA[i] = A[i] 이용하여 배열 A에 담기. 
{
    srand(time(NULL));            // srand함수의 전달인자를 time함수로 설정해줌으로써 매번 다른 랜덤한 원소들의 배열 A를 얻을 수 있게 되었다. 
    int Array_Size = Num;      // 배열사이즈 <- 전달 받은 값 n
    int i;
    for(i = 0; i < Array_Size; i++)                              // "O(n)"
    {
    	A[i] = rand();      // Random한 숫자들로 배열 A를 구성함. 
    }
}   

void Copy_Array(int *A, int *B, int Length)			// 배열을 복사해주는 함수이다. 각 알고리즘이 끝난 후 원 배열을 카피하여 다시 정렬을 진행한다. 
{
    int i;
    for(i = 0; i < Length; i++)
  	{	
        B[i] = A[i];
   	}
}

void swap(int *p1, int *p2)				// 포인터를 활용한, 값을 Exchange해주는 함수 
{
      int temp = *p1;
      *p1 = *p2;
      *p2 = temp;
}

int COMPCOUNT = 0;

int COMPARE(int X, int Y)		// X, Y이면 X > Y일 때 1을 리턴해주고, 만약 X == -10, Y == -20이면 COMPCOUNT++한 이후 그냥 리턴한다. 
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

void Insertion_Sort(int *A, int Num) // pI = pointer of Insertion sort의 약자, int *pI == A == &A[0](pI는 배열 A의 첫 주소를 가리킴) 
{
    int Array_Size = Num;      // 배열사이즈 <- 전달 받은 값 n
    int i, j, key;
    for(j = 1; j < Array_Size; j++)   // 2중 loop이므로 T(n) = O(n^2) 
    {
        key = A[j];
        i = j-1;
        while(i >= 0 && COMPARE(A[i], key))		// 만약 i > 0과 A[i] > key를 동시에 만족하면, 오른쪽 값에 i값을 넣음 
        {
          	A[i+1] = A[i];
            i--;								// 한 칸 씩 왼쪽으로. 
        }
        A[i+1] = key;							// key값은 배열 내에 없기 때문에 마지막에 초기화를 시켜준다. 
    }
}
         
int Max_Heapify(int *A, int i, int Length_of_Array) 
{
    int HeapSize_of_A = Length_of_Array; // 배열의 길이가 곧 히입의 전체 노드 수 
    int lchild = 2*i + 1;   // 배열의 첫 인덱스는 0이므로 각각 1씩 더해줘야 진행가능하다. 
    int rchild = 2*i + 2;
    int largest = 0;
    if(A[lchild] == NULL && A[rchild] == NULL)   // child node가 0개인 leaf node의 경우 Max_Heapify 중단 
    {
        return NULL;
    }
    if(lchild <= HeapSize_of_A - 1 && COMPARE(A[lchild], A[i]))		// 크기 비교 단계 
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
    if(largest != i)		// largest != i이면 largest원소와 i원소와 스왑하고, MaxHeapify를 진행한다. 
    {
        COMPARE(-10, -20);
        swap(&A[i], &A[largest]);
        Max_Heapify(A, largest, HeapSize_of_A);
    }
}

void Build_Max_Heap(int *A, int Num) // # of leaves = 역floor(n/2) 이므로, leaf nodes are already sorted!, thus floor(n/2) ~ root node까지 MaxHeapify함수 진행. 
{
    int Heap_Size_of_A = Num;            // Length of Array A.
    int floor_Size_of_A;               // 히입은 인덱스가 1부터 시작하지만, 배열은 0부터 시작이므로 값을 적절히 초기화한다. 
    int i;
    floor_Size_of_A = floor(Heap_Size_of_A/2) - 1;   // 우변의 식을 통해 모든 히입의 사이즈에 대해 leaf node가 아닌 인덱스의 최댓값을 구할 수 있다! 
    for(i = floor_Size_of_A; i >= 0; i--)		// 리프노드의 바로 앞 인덱스부터 루트노드까지 MAX_HEAPIFY를 진행한다. 
    {
    	Max_Heapify(A, i, Heap_Size_of_A);
    }
    printf("\nBUILD-MAX-HEAP 진행 후 배열 A\n");		// HEAPSORT의 첫번째 과정. 중요하므로 출력하였다. 
    for(i = 0; i < Heap_Size_of_A; i++)
    {
    	printf("Build_MAX_HEAP_A[%d] = %d\n", i, A[i]);
    }
} 

void Heap_Sort(int *A, int Num)   
{
    int Heap_Size_of_A = Num;
    Build_Max_Heap(A, Heap_Size_of_A);      // 빌드 맥스 히입. O(n) MAXHEAPIFY를 진행하는 과정이다. 
    int i;
    for(i = Heap_Size_of_A - 1; i > 0; i--) // root node전 까지 반복문에서 n, 동시에 Max_Heapify함수는 Heap의 height만큼 진행되니 log n이다. 즉 O(nlogn) 
    {
        COMPARE(-10, -20);
        swap(&A[0], &A[i]);
        Heap_Size_of_A = Heap_Size_of_A - 1;
        Max_Heapify(A, 0, Heap_Size_of_A);
    }
    Heap_Size_of_A = Num; // Heap_Sort함수 진행한다고 HeapSize를 줄였기 떄문에 Sorting 끝나면 다시 원래 크기로 되돌려준다. 
}

void Merge(int *A, int p, int q, int r)       //   MergeSort 코딩 완성. 
{
    int Left_Num = q - p + 1;   // A[p ~ r]까지의 배열을 Left Subarray A_Left[p ~ q]와 Right Subarray A_Right[q+1 ~ r]로 분할(Divide Two Subarrays L & R, when the subarray's size is 1.) 
    int Right_Num = r - q;      // r - (q+1) + 1 == r - q
	int Left_Subarray_of_A[Left_Num+1], Right_Subarray_of_A[Right_Num+1];    // 정적 메모리 할당. not in place이므로 extra space가 필수적이다..
	int i, j, k;
	for(i = 0; i <= Left_Num - 1; i++)   // 0 ~ Left_Num-1까지 값을 넣는데, Left_Num-1(왼쪽 부분배열의 맨 마지막 값 <- 정수형 최댓값을 넣음)
    {
    	Left_Subarray_of_A[i] = A[p+i];
    }
    for(j = 0; j <= Right_Num - 1; j++)   // 0 ~ Right_Num-1까지 값을 넣는데, Right_Num-1(오른쪽 부분배열의 맨 마지막 값 <- 정수형 최댓값을 넣음)
    {
    	Right_Subarray_of_A[j] = A[q+j+1];   
    }
      // LeftSubArray와 RightSubArray의 마지막 인덱스에 엄청나게 큰 값을 대입하지 않으면 NULL값이 원소들 간의 정렬을 방해하는 현상을 볼 수 있었습니다. 그래서 바로 INT_MAX값을 이용하였습니다! 
    Left_Subarray_of_A[Left_Num] = INT_MAX;      
    Right_Subarray_of_A[Right_Num] = INT_MAX;   
   
      // 인덱스 초기화 시키기!
    i = 0, j = 0; 
    for(k = p; k <= r; k++)   // p ~ r까지 수행한다는 것의 의미 -> A배열의 첫 인덱스는 p, 끝 인덱스는 r이니까, 굉장히 큰 연관이 있음을 암시할 수 있다. 
    {                  // 만약 LeftSubarray의 인덱스가 무한대값이 들어있는 인덱스까지 간다면, RightSubarray의 값들만 A의 남은 부분들에 순서대로 담아주면 된다. 반대의 경우도 마찬가지이다. 
    	if(COMPARE(Right_Subarray_of_A[j], Left_Subarray_of_A[i]))		// 왼쪽 서브배열 < 오른쪽 서브배열 -> 왼쪽 배열의 원소값 
    	{
        	A[k] = Left_Subarray_of_A[i];
        	i++;
    	}
    	else if(COMPARE(Left_Subarray_of_A[i], Right_Subarray_of_A[j]))	// 왼쪽 서브배열 > 오른쪽 서브배열 -> 오른쪽 배열의 원소값 
    	{
        	A[k] = Right_Subarray_of_A[j];
        	j++;
    	}
  	}
}

int Merge_Sort(int *A, int p, int r)		// 전형적인 Merge 정렬(분할 정복 알고리즘) 
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

int Partition_of_Quick_Sort(int *A, int p, int r)	// Version1 과 Version2에서 쓰인다 
{
   	int i = p-1;
   	int j;
   	int key = A[r];      // 결국 A의 마지막 인덱스에 해당하는 원소가 pivot 값(key 값)이 된다. 
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
   	if(COMPARE(A[Leftmost_of_Array], A[Rightmost_of_Array])+1 || COMPARE(A[Leftmost_of_Array], A[Median_of_Array]+1))   // 둘 또는 셋의 값이 같은 경우, 무조건 중앙값은 같은 값! 
   	{
       	q_pivot_idx = Leftmost_of_Array;   
   	}
   	else if(COMPARE(A[Median_of_Array], A[Rightmost_of_Array])+1)      // 3개 중에 2개가 같은 경우를 고르는 것이므로 3C2 = 3가지 경우(위 2가지 + 이거 1가지) 
   	{
       	q_pivot_idx = Median_of_Array;   
   	}
   
   // 3개를 다 비교해야되는데, 이것은 3!의 경우의 수이다.(** LMR != RML은 엄연히 다르므로. 팩토리얼로 경우의 수를 나눌 것.) 
   	if(COMPARE(A[Rightmost_of_Array], A[Leftmost_of_Array]) && COMPARE(A[Leftmost_of_Array], A[Median_of_Array]))      // 1. A[M] < A[L] < A[R] -> A[L]을 고를 것. 
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
   
   	if(q_pivot_idx == Leftmost_of_Array)	// 맨 왼쪽의 인덱스 -> 피봇의 인덱스 
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
   	else if(q_pivot_idx == Median_of_Array) 	// 중간 인덱스 -> 피봇의 인덱스 
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
   	else if(q_pivot_idx == Rightmost_of_Array)	// 맨 오른쪽의 인덱스 -> 피봇의 인덱스 
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
{							// Quick Sort Version 4 전용 최댓값의 인덱스와 최솟값의 인덱스의 평균 인덱스를 피봇의 인덱스로 하는 알고리즘 
   	int n = r-p+1;   // 배열의 길이만큼
   	int idx1, idx2, i, j, key;
   	int MAX = -INT_MAX;
   	int MIN = INT_MAX;
   	int MAX_IDX, MIN_IDX;
   	int pivot = 0;
   	for(idx1 = p; idx1 <= r; idx1++)      // 배열의 최댓값의 인덱스를 구하는 과정 
   	{
      	if(COMPARE(A[idx1], MAX))
      	{
         	MAX_IDX = idx1;
      	}
  	}
   	for(idx2 = p; idx2 <= r; idx2++)      // 배열의 최솟값의 인덱스를 구하는 과정 
   	{
      	if(COMPARE(MIN , A[idx2]))
      	{
         	MIN_IDX = idx2;
      	}
   	}
   	pivot = (MAX_IDX+MIN_IDX)/2;		// (최댓값 인덱스 + 최솟값 인덱스)/2 -> 피봇의 인덱스  
   	key = A[pivot];						// 피봇값 -> key값 
   	i = p-1;
   	if(p >= 0)
   	{
      	for(j = p; j <= r; j++)
      	{   
         	if(j == pivot)				// j == pivot이면 그냥 건너뜀. 
        	{
            	continue;
         	}
         	else if(COMPARE(key, A[j]) || A[j] == key)	// 그 외에는 if문을 거침. 
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

int Quick_Sort(int *A, int p, int r, int Ver)	// Version1, Version2, Version4를 담당하는 퀵소트 정렬 
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
   	if(p == r)			   // 맨처음과 맨끝이 인덱스가 같다면 그냥 그 인덱스를 피봇의 인덱스로 정함 
   	{
       return p;
   	}
   	else if(p < r)			// 아닌 경우에는 rand함수로 값을 받는다. 
    {
       	int RANDOM_NUMBER = rand()%(r-p+1) + p;   // 만약 p = 2이고 r = 5이면, 2 ~ 5 사이의 인덱스가 랜덤하게 나와야 피봇 설정이 가능할텐데
       	return RANDOM_NUMBER;         // 다르게 생각해보면 0 ~ 3의 나머지(4로 modulo연산)를 가질 수 있는 랜덤한 수에 2를 더하면 범위가 2 ~ 5로 설정 가능하다!!!! 
    }
    else 
    {
    	return NULL;
   	}
}

int Randomized_Partition_of_Quick_Sort(int *A, int p, int r) // QuickSort Version2에서 Pivot값을 정해주는 함수 
{
   	int i = RANDOM(p, r); // p부터 r까지,  
   	if(p == r)			
   	{	
       	return 0;
   	}
   	COMPARE(-10, -20);
   	swap(&A[r], &A[i]);
   	return Partition_of_Quick_Sort(A, p, r);
}

void Randomized_Quick_Sort(int *A, int p, int r)			// Version 2 QuickSort 함수. 
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
   	int n = Set_The_Numbers_of_Array(); // 원소개수 정해주는 함수 호출. 
   	int VERSION;
   	int Copied_Array_A[n], Original_Array_A[n], i;   // 각 알고리즘을 동시에 돌리면 배열 A가 정렬된 상태로 다른 알고리즘에 들어가므로  
   	// 그것을 방지하기 위해 배열을 2개 선언(복사된 배열, 정렬된 배열) 
   	Random_Array(Original_Array_A, n);               // 정해진 원소개수만큼의 랜덤한 배열 A를 생성하는 함수 호출. 
   	Copy_Array(Original_Array_A, Copied_Array_A, n);   // 복사본 <- 원래 값 초기화(각 알고리즘 정렬 이후 사용) 
         
   	printf("\n원래 배열 A, 실습 비교 용\n");
   	for(i = 0; i < n; i++)            // "O(n)"
   	{
       	printf("Original A[%d] = %d\n", i, Original_Array_A[i]);    // original한 Array A를 확인 차 출력하기 
    }
   
   	printf("\n\nINSERTION SORT 진행 후 배열 A\n");
   	Insertion_Sort(Copied_Array_A, n);      //완성 S
   	for(i = 0; i < n; i++)            // "O(n)"
    {
       	printf("Insertion_Sorted_A[%d] = %d\n", i, Copied_Array_A[i]); 
	}
   	printf("\nINSERTION SORT 진행동안 비교횟수 : %d\n\n", COMPCOUNT);
   
   
   	COMPCOUNT = 0;
   	Copy_Array(Original_Array_A, Copied_Array_A, n);
   	Heap_Sort(Copied_Array_A, n);         //완성 
   	printf("\n\nHEAP SORT 진행 후 배열 A\n");
   	for(i = 0; i < n; i++)            // "O(n)" 
   	{
       	printf("Heap_Sorted_A[%d] = %d\n", i, Copied_Array_A[i]);
   	}
   	printf("\nHEAP SORT 진행 동안 비교횟수 : %d\n\n", COMPCOUNT);
      
    COMPCOUNT = 0;
    Copy_Array(Original_Array_A, Copied_Array_A, n);
    printf("\n\nMERGE SORT 진행 후 배열 A\n");
    Merge_Sort(Copied_Array_A, 0, n-1);      //완성 //완성 
    for(i = 0; i < n; i++)            // "O(n)" 
    {
        printf("Merge_Sorted_A[%d] = %d\n", i, Copied_Array_A[i]);
    }
    printf("\nMERGE SORT 진행 동안 비교횟수 : %d\n\n", COMPCOUNT);
   
    for(VERSION = 1; VERSION <= 4; VERSION++)
    {
        printf("\nQUICK SORT VER %d 진행 후 배열 A\n", VERSION);
        COMPCOUNT = 0;
        if(VERSION == 1)
        {
        	Copy_Array(Original_Array_A, Copied_Array_A, n);
            Quick_Sort(Copied_Array_A, 0, n-1, VERSION);
            for(i = 0; i < n; i++)            // "O(n)" 
            {
               	printf("Quick_Sorted_Ver%d_A[%d] = %d\n", VERSION, i, Copied_Array_A[i]);
            }
            printf("\nQUICK SORT Ver%d 진행 동안 비교횟수 : %d\n\n", VERSION, COMPCOUNT);
    	}
      	else if(VERSION == 2)
      	{
         	Copy_Array(Original_Array_A, Copied_Array_A, n);
         	Randomized_Quick_Sort(Copied_Array_A, 0, n-1);
            for(i = 0; i < n; i++)            // "O(n)" 
            {
               	printf("Quick_Sorted_Ver%d_A[%d] = %d\n", VERSION, i, Copied_Array_A[i]);
            }
         	printf("\nQUICK SORT Ver%d 진행 동안 비교횟수 : %d\n\n", VERSION, COMPCOUNT);
      	}
      	else if(VERSION == 3)
      	{
         	Copy_Array(Original_Array_A, Copied_Array_A, n);
         	Quick_Sort(Copied_Array_A, 0, n-1, VERSION);
         	for(i = 0; i < n; i++)            // "O(n)" 
            {
               	printf("Quick_Sorted_Ver%d_A[%d] = %d\n", VERSION, i, Copied_Array_A[i]);
            }
         	printf("\nQUICK SORT Ver%d 진행 동안 비교 횟수 : %d\n", VERSION, COMPCOUNT);
      	}
      	else if(VERSION == 4)
      	{
         	Copy_Array(Original_Array_A, Copied_Array_A, n);
         	Quick_Sort(Copied_Array_A, 0, n-1, VERSION);
         	for(i = 0; i < n; i++)            // "O(n)" 
            {
               	printf("Quick_Sorted_Ver%d_A[%d] = %d\n", VERSION, i, Copied_Array_A[i]);
            }
         	printf("\nQUICK SORT Ver%d 진행 동안 비교 횟수 : %d\n", VERSION, COMPCOUNT);
      	}
    }
    return 0;
}
