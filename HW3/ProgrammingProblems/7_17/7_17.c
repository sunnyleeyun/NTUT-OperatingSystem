#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/sem.h>

/*number of farmers heading in each direction*/
#define FARMERS_NORTH 5
#define FARMERS_SOUTH 5

/*and takes CROSSINGTIME to make is across the bridge*/
#define CROSSINGTIME 4

/* colors to be fancy like the example*/
#define KORG  "\x1B[35m"
#define RESET "\033[0m"

/* create mutex*/
pthread_mutex_t mutex;

/*farmers heading north*/
void *farmer_north(void * arg)
{
	int *me = (int *) arg;	/*id of particular farmer*/
	pthread_mutex_lock(&mutex);
	printf( "Farmer "KORG"%d"RESET" going north "KORG"on"RESET" the bridge\n", *me );
	sleep( CROSSINGTIME );
	printf( "Farmer "KORG"%d"RESET" going north "KORG"off"RESET" the bridge\n", *me );
	pthread_mutex_unlock(&mutex); 
	pthread_exit( NULL );	/*exit the thread*/
}
/*farmers heading south*/
void *farmer_south(void * arg)
{
	int *me = (int *) arg;	/*id of particular farmer*/
	pthread_mutex_lock(&mutex);
	printf( "Farmer "KORG"%d"RESET" going south "KORG"on"RESET" the bridge\n", *me );
	sleep( CROSSINGTIME );
	printf( "Farmer "KORG"%d"RESET" going south "KORG"off"RESET" the bridge\n", *me );
	pthread_mutex_unlock(&mutex); 
	pthread_exit( NULL );	/*exit the thread*/
}


int main(void)
{
	int i;	/*index*/
	pthread_t farmer_tid_north[FARMERS_NORTH];	/*thread ids of farmers heading east*/
	pthread_t farmer_tid_south[FARMERS_SOUTH];	/*thread ids of farmers heading west*/
	int farmer_id_north[FARMERS_NORTH]; /*farmer north ids of farmers heading east*/
	int farmer_id_south[FARMERS_SOUTH]; /*farmer south ids of farmers heading west*/

	/*set ids of farmers*/
	for(i = 0; i < FARMERS_NORTH; ++i)
		farmer_id_north[i] = i;
	for(i = 0; i < FARMERS_SOUTH; ++i)
		farmer_id_south[i] = i;
	

	/* create threads and check for errors*/
	for (i = 0; i < FARMERS_NORTH; ++i)
		if (pthread_create( &farmer_tid_north[i], NULL, farmer_north, (void *) &farmer_id_north[i] ))
		{
			perror("Could not create thread");
			exit(EXIT_FAILURE);
		}
	for (i = 0; i < FARMERS_SOUTH; ++i)
		if (pthread_create( &farmer_tid_south[i], NULL, farmer_south, (void *) &farmer_id_south[i] ))
		{
			perror("Could not create thread");
			exit(EXIT_FAILURE);
		}
	

	/*join threads*/
	for(i = 0; i < FARMERS_NORTH; ++i)
		if (pthread_join( farmer_tid_north[i], NULL ))
		{
			perror("Thread join failed");
			exit(EXIT_FAILURE);		
		}
	for(i = 0; i < FARMERS_SOUTH; ++i)
		if (pthread_join( farmer_tid_south[i], NULL ))
		{
			perror("Thread join failed");
			exit(EXIT_FAILURE);		
		}
	
	exit(1);
	pthread_mutex_destroy(&mutex); 
	return 0;
}