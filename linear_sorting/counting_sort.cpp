#include <iostream>
#include <iterator>
#include <cstring>
#include <cstdlib>

const int SIZE = 10;
const int MAX = 1000;

int n[SIZE];

using namespace std;

int* counting_sort(int *begin, int *end) {
    int* count = new int[MAX];
    int* res = new int[MAX];
    
    fill(count, count+MAX, 0);

    for (int* p = begin; p != end; ++p)
        count[*p]++;
    for (int i = 1; i < MAX; ++i) 
        count[i] += count[i-1];
    for (int* p = begin; p != end; ++p)
        res[--count[*p]] = *p;
    return res;
}

int main() {
    for (int i = 0; i < SIZE;++i)
        n[i] = rand()%MAX;

    copy(n, n+SIZE, ostream_iterator<int>(cout, " "));
    cout << endl;
    int* res = counting_sort(n, n + sizeof(n)/sizeof(int));
    copy(res, res+SIZE, ostream_iterator<int>(cout, " "));
    return 0;
}
