/* bankAccount.h simulates a simple bank account
 *
 * Joel Adams, Calvin College, Fall 2013.
 */


// Shared Variables
double bankAccountBalance = 0;
pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;

// add amount to bankAccountBalance
void deposit(double amount) {
   bankAccountBalance += amount;
}

// subtract amount from bankAccountBalance
void withdraw(double amount) {
   bankAccountBalance -= amount;
}

void cleanup() {
	pthread_mutex_destroy(&mutexsum);
}

