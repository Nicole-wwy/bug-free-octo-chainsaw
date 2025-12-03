# bug-free-octo-chainsaw
#include <stdio.h>
#include <stdlib.h>
int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int n;
    printf("请输入袋子数量 n：");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));
    printf("请输入每个袋子的魔法球数：");
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    qsort(a, n, sizeof(int), cmp);
    int mid = a[n / 2];

    long long under = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < mid) {
            under += mid - a[i];
        }
    }

    printf("最小体力消耗：%lld\n", under);

    free(a);
    return 0;
}
