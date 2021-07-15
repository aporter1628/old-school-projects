#include <stdlib.h>
#include <pthread.h> 

typedef struct rwlock{
	bool heldWriter; //true if a writer is holding
	bool heldReader[100]; //true if a reader is holding
	int writersWaiting; //the number of writers waiting
	int readers; //the number of readers holding
}rwlock;

void pthread_rwlock_init(rwlock lock){
	//Initially nobody holds the lock and nobody is waiting
	lock.heldWriter = FALSE;
	lock.writersWaiting = 0;
	lock.readers = 0;
	for(int i = 0; i < 100; i++){
		lock.heldReader[i] = FALSE;
	}
}

void pthread_rwlock_destroy(rwlock lock){
	free(lock);
}

void pthread_rwlock_rdlock(rwlock lock){
	//If there are no writers waiting then a reader can acquire the lock
	if(lock.heldWriter == FALSE && lock.writersWaiting == 0){
		if(lock.readers == 0)
			lock.heldReader[0] = TRUE;
		else{
			lock.readers++;
			lock.heldReader[readers] = TRUE;
		}
	}
}

void pthread_rwlock_wrlock(rwlock lock){
	//If no writer is holding the lock then this writer can acquire it
	if(lock.heldWriter == FALSE){
		lock.heldWriter = TRUE;
		if(lock.writersWaiting > 0){
			lock.writersWaiting--; //decrement writersWaiting if it's not 0
		}
		else{
			lock.writersWaiting++; //increment writersWaiting to show that someone is waiting for the lock
		}
	}
}

void pthread_rwlock_unlock(){
	bool heldWriter = FALSE; //have the writer release the lock
	for(int i = 0; i < readers; i++){
		lock.heldReader[i] = FALSE; //have all readers release the lock
	}
	lock.readers = 0; //there is no longer anyone reading
}