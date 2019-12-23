int main()
{
    int a = 2;
    int *p;
    p = a;
    int array[10];
    array[0] = a;
    a = array[0];
    int *p = &a;
    *p = a;
    a = *p;
    print_int(a);
}
