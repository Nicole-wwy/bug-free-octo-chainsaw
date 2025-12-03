#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

static inline int64_t fast_read_int() {
    int64_t x = 0;
    int c = getchar_unlocked();
    int sign = 1;
    while (c != '-' && (c < '0' || c > '9')) c = getchar_unlocked();
    if (c == '-') { sign = -1; c = getchar_unlocked(); }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return x * sign;
}

/* Partition used by quickselect */
static int partition(int64_t *a, int l, int r, int pivot_index) {
    int64_t pivot_value = a[pivot_index];
    int i = l;
    int j;
    /* move pivot to end */
    int64_t tmp = a[pivot_index];
    a[pivot_index] = a[r];
    a[r] = tmp;
    for (j = l; j < r; ++j) {
        if (a[j] < pivot_value) {
            tmp = a[i]; a[i] = a[j]; a[j] = tmp;
            ++i;
        }
    }
    tmp = a[i]; a[i] = a[r]; a[r] = tmp;
    return i;
}

/* Quickselect to find k-th (0-based) smallest element */
static int64_t quickselect(int64_t *a, int l, int r, int k) {
    while (l <= r) {
        /* choose pivot_index randomly to avoid worst-case */
        int pivot_index = l + rand() % (r - l + 1);
        int pivot_new_index = partition(a, l, r, pivot_index);
        if (pivot_new_index == k) return a[k];
        else if (k < pivot_new_index) r = pivot_new_index - 1;
        else l = pivot_new_index + 1;
    }
    return a[k];
}

int main(void) {
    srand((unsigned)time(NULL));
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid n\n");
        return 1;
    }

    int64_t *a = (int64_t *)malloc(sizeof(int64_t) * (size_t)n);
    if (!a) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        /* 可以换成 fast_read_int() 如果输入极大且需要更快的速度 */
        a[i] = fast_read_int();
    }

    int k = n / 2; /* 0-based median index (floor) */
    int64_t median = quickselect(a, 0, n - 1, k);

    long long under = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] < median) under += (median - a[i]);
    }

    printf("%lld\n", under);
    free(a);
    return 0;
}