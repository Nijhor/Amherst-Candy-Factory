#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int empty, full=0;
int in = 0, out = 0;
int i=0, j=0,x=0;
int buffer_size;
int l=0,r=0;
int buffer[50];
int item;
int box_capacity;
int box[100][100];
pthread_mutex_t mutex;

void *producer()
{
    empty--;
    pthread_mutex_lock(&mutex);
    buffer[in]=item;
    in = (in+1)%buffer_size;
    pthread_mutex_unlock(&mutex);
    full++;
    i++;
    pthread_exit(NULL);
}

void *consumer()
{
    full--;
    pthread_mutex_lock(&mutex);
    buffer[out]=-1;
    out = (out+1)%buffer_size;
    pthread_mutex_unlock(&mutex);
    empty++;
    j++;
    pthread_exit(NULL);
}

int candy()
{
    printf("\n1. Toffee\n2. Chewing Gum\n3. Lollipop\n4. Candy Bar\n5. Jelly Candy\n\n");
    int c;
    scanf("%d",&c);
    printf("\n");
    if(c==1)
        return 1;
    if(c==2)
        return 2;
    if(c==3)
        return 3;
    if(c==4)
        return 4;
    if(c==5)
        return 5;
}

void printcandy(int c)
{
    if(c==1)
        printf("Toffee ");
    if(c==2)
        printf("Chewing Gum ");
    if(c==3)
        printf("Lollipop ");
    if(c==4)
        printf("Candy Bar ");
    if(c==5)
        printf("Jelly Candy");
}

int main()
{
    printf("Enter Buffer Size : ");
    scanf("%d",&buffer_size);
    empty=buffer_size;
    box_capacity = buffer_size;
	int n;

    pthread_t prod[buffer_size],cons[buffer_size];
    pthread_mutex_init(&mutex, NULL);

	while(1)
	{
	    printf("\n1. Produce Candy \n2. Consume Candy \n3. Exit\n\n");
        scanf("%d",&n);
        if(n==1)
        {
            if(empty>=1)
            {
                item=candy();
                pthread_create(&prod[i], NULL, (void *)producer, NULL);

                printcandy(item);
                printf(" produced in Box index %d\n",in+1);
            }
            else
            {
                printf("Box Capacity is full.\n");
            }
        }
        else if(n==2)
        {
            if(full>0)
            {
                pthread_create(&cons[j], NULL, (void *)consumer, NULL);

                printcandy(buffer[x]);
                printf("Consumed from Box index %d\n",out+1);
                x= (x+1)%buffer_size;
            }
            else
            {
                printf("Box is empty.\n");
            }
        }

        else if(n==3)
        {
            break;
        }
        else
        {
            printf("Command Unrecognized");
        }

	}
    pthread_mutex_destroy(&mutex);
	return 0;
}
