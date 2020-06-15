void HeapCorruption() {
    int *arr = new int[16];
    for (int i = 0; i < 17; i++)
        arr[i] = i;
    delete arr;
}
