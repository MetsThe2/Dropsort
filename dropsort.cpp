#include <iostream>
#include <cstring>
#include <cassert>
#include <random>

#define MEM_PUT(arr, index, len) \
	memmove(arr + index + 1, arr + index, sizeof(*arr) * (len - index))
#define MEM_DEL(arr, index, len) \
	memmove(arr + index, arr + index + 1, sizeof(*arr) * (len - index - 1))

#define ARR_LEN(a) (sizeof(a) / sizeof(*a))

template <typename T>
void print_arr(T *arr, size_t arr_len)
{
	for (size_t i = 0; i < arr_len; ++i) std::cout << arr[i] << "\n";
	std::cout << std::endl;
}

template <typename T>
void merge_arr(T *dst, size_t arr_len, T *other, size_t other_len)
{
	assert(arr_len != 0 && other_len != 0);
	
	size_t dst_top = arr_len + other_len - 1;
	
	T arr[arr_len];
	memcpy(arr, dst, arr_len * sizeof(*arr));
	
	while (true) {
		if (arr[arr_len - 1] > other[other_len - 1]) {
			dst[dst_top] = arr[--arr_len];
			if (arr_len == 0) {
				while (other_len != 0) dst[dst_top--] = other[--other_len];
				break;
			}
		} else {
			dst[dst_top] = other[--other_len];
			if (other_len == 0) {
				while (arr_len != 0) dst[dst_top--] = arr[--arr_len];
				break;
			}
		}
		--dst_top;
	}
}

static unsigned recur_num = 0;
template <typename T>
void dropsort(T *arr, size_t arr_len)
{
	if (arr_len < 2) return;

	const size_t original_len = arr_len;
	T unsorted[original_len];
	size_t unsorted_len = 0;

	for (size_t i = 1; i < arr_len; ) {
		if (arr[i] > arr[i - 1]) {
			++i;
		} else {
			assert(unsorted_len < original_len);
			unsorted[unsorted_len++] = arr[i];
			MEM_DEL(arr, i, arr_len);
			--arr_len;
		}
	}

	++recur_num;
	dropsort(unsorted, unsorted_len);

	assert(arr_len + unsorted_len == original_len);
	merge_arr(arr, arr_len, unsorted, unsorted_len);
}

int main() {
	unsigned test_arr[] = {1, 5, 2, 4, 2, 41, 4, 5612, 3, 564, 3};
	dropsort(test_arr, ARR_LEN(test_arr));
	print_arr(test_arr, ARR_LEN(test_arr));
	return 0;
}
