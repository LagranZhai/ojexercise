#include <ctime>
#include <cstdio>
#include <random>
#include <iostream>

void fwc(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) fwc(x / 10);
    putchar(x % 10 + '0');
}

void fwcpp(int x) {
    if (x < 0) std::cout.put('-'), x = -x;
    if (x > 9) fwc(x / 10);
    std::cout.put(x % 10 + '0');
}

std::mt19937 eng;
std::uniform_int_distribution<int> dis(-(1 << 30), 1 << 30);

int main() {
    static int arr[int(2e7)];
    for (int i = 0; i < 2e7; ++i) arr[i] = dis(eng);

    int output_mode = 0;
    fprintf(stderr, "Please input mode: ");
    scanf("%d", &output_mode);

    freopen(".\\output_test.txt", "w", stdout);
    const char *firstline[] = {"cout with sync", "printf", "C fastwrite",
                               "C++ fastwrite", "C++ fastwrite without sync", "cout without sync"};
    fputs(firstline[output_mode - 1], stderr);
    fputc('\n', stderr);

    auto ts = clock();
    if (output_mode == 1)
        for (int i = 0; i < 2e7; ++i)
            std::cout << arr[i] << ' ';
    if (output_mode == 2)
        for (int i = 0; i < 2e7; ++i)
            printf("%d ", arr[i]);
    if (output_mode == 3)
        for (int i = 0; i < 2e7; ++i)
            fwc(arr[i]), putchar(' ');
    if (output_mode == 4)
        for (int i = 0; i < 2e7; ++i)
            fwcpp(arr[i]), std::cout.put(' ');
    if (output_mode == 5) {
        std::ios::sync_with_stdio(false);
        for (int i = 0; i < 2e7; ++i)
            fwcpp(arr[i]), std::cout.put(' ');
    }
    if (output_mode == 6) {
        std::ios::sync_with_stdio(false);
        for (int i = 0; i < 2e7; ++i)
            std::cout << arr[i] << ' ';
    }

    auto te = clock();
    fprintf(stderr, "used time: %ld.%03ld\n", (te - ts) / 1000, (te - ts) % 1000);
    return 0;
}
