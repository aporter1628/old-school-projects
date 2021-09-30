//swap.c - make the top of the stack equal 0
void proc() {
    int n = 0;
}

void swap (int *px, int *py) {
    int *temp;
    *temp = *px;
    *px = *py;
    *py = *temp;
}

int main () {
    int a = 1, b = 2;
    proc();
    swap(&a, &b);
}
