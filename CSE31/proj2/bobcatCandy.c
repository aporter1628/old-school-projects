int newBars(int numBars, int n) {
    if(numBars < n) 
        return 0;
    else {
        numBars = (int) (numBars/n);
        printf("Then you can get another %d bars.\n", numBars);
        return numBars + newBars(numBars, n);
    }
}

int maxBars(int n, int price, int money) {
    int numBars = (int) (money/price);
    printf("You first buy %d bars.\n", numBars);
    numBars += newBars(numBars, n);
    return numBars;
}
int main() {
    int money, price, n;

    printf("Price of bars: ");
    scanf("%d", &price);

    printf("Wrappers to exchange for a bar: ");
    scanf("%d", &n);

    printf("Amount of money ");
    scanf("%d", &money);


    int numBars = maxBars(n, price, money);
    printf("With $%d you will receive a maximum of %d bars.\n", money, numBars);
}

