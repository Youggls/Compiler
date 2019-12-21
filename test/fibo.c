int fibo(int n) {
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    }
    int a = fibo(n - 1);
    int b = fibo(n - 2);
    return a + b;
}

int main() {
    int d = fibo(5);
    print_int(d);
}
