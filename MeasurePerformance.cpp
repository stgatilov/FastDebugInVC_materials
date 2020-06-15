#include <vector>
#include <algorithm>
#include <time.h>
#include <stdint.h>

#ifdef _MSC_VER
    #define FORCEINLINE __forceinline
    #define NOINLINE __declspec(noinline)
#else
    #define FORCEINLINE __attribute__((always_inline)) inline
    #define NOINLINE __attribute__((noinline))
#endif

double MeasureCallTime(void (*func)(), double expTime = 1.0) {
	clock_t start = clock();
    clock_t expectedEnd = start + clock_t(CLOCKS_PER_SEC * expTime);
	int64_t iters = 0;
    int step = 1;
	do {
		for (int i = 0; i < step; i++)
			func();
		iters += step;
        step <<= 1;
	} while (clock() < expectedEnd);
	double totalTime = double(clock() - start) / CLOCKS_PER_SEC;
	double callTime = totalTime / iters;
	return callTime;
}

static NOINLINE int OrderSum(const std::vector<int> &in) {
    std::vector<int> sorted;
    sorted = in;
    int n = sorted.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (sorted[i] < sorted[j])
                std::swap(sorted[i], sorted[j]);
    int res = 0;
    for (int i = 0; i < n; i++)
        res += sorted[i] * (i+1);
    return res;
}

int64_t GlobalSum;
void FullTest() {
    static const int SIZE = 5;
    std::vector<int> vec;
    for (int i = 0; i < SIZE; i++)
        vec.push_back((i*3)%5 + i);
    for (int q = 0; q < 1000; q++)
        GlobalSum += OrderSum(vec);
}

void VectorOutOfBounds();
void StackCorruption();
void HeapCorruption();

int main() {
    //VectorOutOfBounds();    //accesses std::vector with index out of bounds
    //StackCorruption();      //writes to local array out of bounds
    //HeapCorruption();       //writes to heap-allocated buffer out of bounds

    GlobalSum = 0;
    double timePerCall = MeasureCallTime(FullTest);
    if (GlobalSum % 77 != 0)
        abort();
    printf("One call of OrderSum took %0.3lf ns\n", 1e+6 * timePerCall);
    return 0;
}
