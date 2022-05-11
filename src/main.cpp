#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

// Author: Rodolfo 'nuk3RR' Tavares
// The Dining Philosophers Problem

pthread_mutex_t mutex_fork[5];
pthread_t philosopher[5];
int id[5];


void get_forks(int * philo) { //philosofer try to get the fork
    pthread_mutex_lock(&(mutex_fork[*philo])); // lock one fork
    if (*philo < 4) {
        pthread_mutex_lock(&(mutex_fork[*philo+1])); // lock another fork, get fork one more position
    } else {
        pthread_mutex_lock(&(mutex_fork[0])); // if it is the fifth philosopher it blocks the fork from position 0, not one position more than it
    }
}

void drop_forks(int * philo) {
    pthread_mutex_unlock(&(mutex_fork[*philo])); // philosofer drop one fork
    if( * philo < 4) {
        pthread_mutex_unlock(&(mutex_fork[*philo+1])); // philosofer drops another fork
    } else {
        pthread_mutex_unlock(&(mutex_fork[0]));  // if the philosopher is the last one, fork at position 0 will be released
        printf("[*] - Philosofer %d finished eat.. \n", *philo);
    }
}

void * philo_life(void * var) { // eating or thinking, philosopher life.. 
    int * philo = (int *) (var);
    while(1) {
        // thinking about
        int think = (rand() % 10 + 2); // calculating time to think randomly
        printf("* - [THINKING] - Philosopher %d : To be or not to be, that's the question.... \n thinking about %d seconds...\n\n", *philo, think );
        sleep(think);
        // philosopher are hungry, because stop thinking
        get_forks(philo);
        int eat = (rand()%5+1); // time to thinking
        printf("! - [EATING] - Philosopher %d is  eating for %d seconds\n\n", *philo, eat);
        sleep(eat); // eating
        drop_forks(philo); //drop forks because philosopher stop eating
    }
    pthread_exit(NULL);
}

int main() {
    for(int aux = 0; aux <= 4;  ++aux) { // philosopher threads..
        pthread_mutex_init(&(mutex_fork[aux]), NULL); // creating critical memory
    }
    for(int aux2 = 0; aux2 <= 4; ++aux2) {
        id[aux2]=aux2;
        pthread_create(&philosopher[aux2], NULL, &philo_life,(void *) &id[aux2]); // creating threads
    }

    while(1) {
        // LOL while true xD eternal looping
    }
    return 0;
}
