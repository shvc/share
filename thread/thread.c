#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TH_POOL_SZ 5
#define TH_NB_LOOP 100

static pthread_mutex_t th_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t th_cond = PTHREAD_COND_INITIALIZER;

typedef struct th_data {
	int val;
} th_data_t;


static void *cons_runnable(void *arg)
{
	int i;
	th_data_t *data = (th_data_t *)arg;

	for (i = 0; i < TH_NB_LOOP; i ++) {
		if (pthread_mutex_lock(&th_lock) != 0) {
			perror("Failed to lock mutex");
			pthread_exit(NULL);
		}
		printf("Consumer[%d] locked.\n", i);

		while (data->val == 0) {
			printf("Value null, consumer is waiting ...\n");
			if (pthread_cond_wait(&th_cond, &th_lock) != 0) {
				perror("Failed to wait on mutex");
				pthread_exit(NULL);
			}
		}
		printf("Consumer[%d] waked up.\n", i);
		data->val --;
		printf("Consumer[%d] Value decremented.\n", i);

		if (pthread_mutex_unlock(&th_lock) != 0) {
			perror("Failed to unlock mutex");
			pthread_exit(NULL);
		}
		printf("Consumer[%d] unlocked.\n", i);

		if (pthread_cond_signal(&th_cond) != 0) {
			perror("Failed to signal other threads");
			pthread_exit(NULL);
		}
		printf("Consumer[%d] signaled other threads\n", i);

	}
	printf("Consumer terminated.\n");
	pthread_exit(NULL);
}


static void *prod_runnable(void *arg)
{
	int i;
	th_data_t *data = (th_data_t *)arg;

	for (i = 0; i < TH_NB_LOOP; i ++) {
		if (pthread_mutex_lock(&th_lock) != 0) {
			perror("Failed to lock mutex");
			pthread_exit(NULL);
		}
		printf("Producer[%d] locked.\n", i);

		while (data->val == 1) {
			printf("Value set, producer is waiting ...\n");
			if (pthread_cond_wait(&th_cond, &th_lock) != 0) {
				perror("Failed to wait on mutex");
				pthread_exit(NULL);
			}
		}
		printf("Producer[%d] waked up.\n", i);
		data->val ++;
		printf("Value incremented.\n");

		if (pthread_mutex_unlock(&th_lock) != 0) {
			perror("Failed to unlock mutex");
			pthread_exit(NULL);
		}
		printf("Producer[%d] unlocked.\n", i);

		if (pthread_cond_signal(&th_cond) != 0) {
			perror("Failed to signal other threads");
			pthread_exit(NULL);
		}
		printf("Producer[%d] signaled other threads.\n", i);
	}
	printf("Producer terminated.\n");
	pthread_exit(NULL);
}

int main (void)
{

	int i;
	th_data_t data;

	pthread_t th_pool_cons[TH_POOL_SZ];
	pthread_t th_pool_prod[TH_POOL_SZ];
	data.val = 0;
	
	pthread_mutex_init(&th_lock, 0);
	pthread_cond_init(&th_cond, 0);

	for (i = 0; i < TH_POOL_SZ; i ++) {
		if (pthread_create(&th_pool_cons[i], NULL, cons_runnable, &data) != 0) {
			perror("Failed to create consumer thread");
			return -1;
		}
		if (pthread_create(&th_pool_prod[i], NULL, prod_runnable, &data) != 0) {
			perror("Failed to create producer thread");
			return -1;
		}
	}
	printf("%d threads created.\n", TH_POOL_SZ * 2);

	for (i = 0; i < TH_POOL_SZ; i ++) {
		if (pthread_join(th_pool_cons[i], NULL) != 0) {
			perror("Failed to join consumer thread");
			return -1;
		}
	}
	for (i = 0; i < TH_POOL_SZ; i ++) {
		if (pthread_join(th_pool_prod[i], NULL) != 0) {
			perror("Failed to join producer thread");
			return -1;
		}
	}
	printf("%d threads joined.\n", TH_POOL_SZ * 2);

	printf("Final value of data: %d.\n", data.val);
	printf("Fin.\n");
	pthread_mutex_destroy(&th_lock);
	pthread_cond_destroy(&th_cond);
	return 0;
}
