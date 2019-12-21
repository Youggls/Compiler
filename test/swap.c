void swap(int* a1, int* b) {
    int t = *a1;
    *a1 = *b;
    *b = t;
}

int main()
{
    int a = 2;
    int b = 3;
    print_int(a);
    print_int(b);
    int* pa = &a;
    int* pb = &b;
    swap(pa, pb);
    print_int(a);
    print_int(b);
}
