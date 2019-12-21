int main() {
    int a, b = 1;
    int c = 3;
    a = b + (10 / 2) ^ 3; // pay attention to operation priority
    if (a != 0) {
        print_int(a);
        while (a < 10 && b < 10) {
            print_int(a);
            a = a * b * c;
            b = b % 2;
        }
        for (int i = 0; i < 1; i=1+i) { // it's OK if you cannot handle the operator "++"
            i = b + a;
        }
    }
    print_int(a); // you can change this to your output function
    return a;
}
