/**
 * SOLUTION 1: Brute Force - O(n²) time, O(1) space
 * Simple and guaranteed to work on any platform
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    
    // Should never reach here based on problem constraints
    free(result);
    *returnSize = 0;
    return NULL;
}

/*
 * SOLUTION 2: Using sorting + two pointers (modifies original array)
 * O(n log n) time, O(n) space
 * Note: This approach requires keeping track of original indices
 */

typedef struct {
    int value;
    int index;
} NumWithIndex;

int compare(const void* a, const void* b) {
    NumWithIndex* numA = (NumWithIndex*)a;
    NumWithIndex* numB = (NumWithIndex*)b;
    return numA->value - numB->value;
}

int* twoSumSorted(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    // Create array of {value, original_index} pairs
    NumWithIndex* arr = (NumWithIndex*)malloc(numsSize * sizeof(NumWithIndex));
    for (int i = 0; i < numsSize; i++) {
        arr[i].value = nums[i];
        arr[i].index = i;
    }
    
    // Sort by value
    qsort(arr, numsSize, sizeof(NumWithIndex), compare);
    
    // Two pointers approach
    int left = 0, right = numsSize - 1;
    while (left < right) {
        int sum = arr[left].value + arr[right].value;
        if (sum == target) {
            result[0] = arr[left].index < arr[right].index ? arr[left].index : arr[right].index;
            result[1] = arr[left].index > arr[right].index ? arr[left].index : arr[right].index;
            free(arr);
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    // Should never reach here
    free(arr);
    free(result);
    *returnSize = 0;
    return NULL;
}

/*
 * SOLUTION 3: Simple hash table using array (for limited range)
 * Only works if the range of numbers is reasonable
 * O(n) time, O(k) space where k is the range of values
 */
#define HASH_SIZE 20000
#define OFFSET 10000  // To handle negative numbers

int* twoSumSimpleHash(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    // Simple hash table using array
    // hash[value + OFFSET] = index + 1 (0 means not found)
    int hash[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        hash[i] = -1;  // -1 means not found
    }
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        
        // Check if complement is in valid range and exists in hash
        if (complement + OFFSET >= 0 && complement + OFFSET < HASH_SIZE) {
            if (hash[complement + OFFSET] != -1) {
                result[0] = hash[complement + OFFSET];
                result[1] = i;
                return result;
            }
        }
        
        // Store current number if in valid range
        if (nums[i] + OFFSET >= 0 && nums[i] + OFFSET < HASH_SIZE) {
            hash[nums[i] + OFFSET] = i;
        }
    }
    
    // Should never reach here
    free(result);
    *returnSize = 0;
    return NULL;
}