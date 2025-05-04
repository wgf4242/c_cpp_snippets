struct Distance{
    int feet;
    float inch;
};

int main() {
    struct Distance d1, d2;
}
//is equivalent to

typedef struct Distance{
    int feet;
    float inch;
} distances;

int main() {
    distances d1, d2;
}