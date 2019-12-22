struct test {
    int a;
    int b;
    int c;
    int d;
};

int main() {
    struct test t;
    t.a = 1;
    t.b = 2;
    t.c = 3;
    t.d = t.b * t.c;
    print_int(t.d);
}
