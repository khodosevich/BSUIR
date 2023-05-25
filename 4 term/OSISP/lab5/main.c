#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stddef.h>
#include <pthread.h>

#define DATA_MAX (((256 + 3) / 4) * 4)
#define MSG_MAX 4096
int max = 0;
#define CHILD_MAX 1024

#pragma region prototypes
typedef struct
{
    int type;
    int hash;
    int size;
    char data[DATA_MAX];
} msg;

typedef struct
{
    int addCount;
    int extractCount;

    int msgCount;

    int head;
    int tail;
    msg buffer[MSG_MAX];
} msgQueue;

int hash(msg* _msg);
void msgQueueInit();
int putMsg(msg* _msg);
int getMsg(msg* _msg);

void menu();
void init();
void end();

void createProducer();
void removeProducer();
void produceMsg(msg* _msg);
void* handlerProduce(void* arg);

void createConsumer();
void removeConsumer();
void consumeMsg(msg* _msg);
void* handlerConsume(void* arg);

#pragma endregion


msgQueue queue;
pthread_mutex_t mutex;

sem_t* free_space;
sem_t* items;

pthread_t  producers[CHILD_MAX];
int producersAmount;

pthread_t  consumers[CHILD_MAX];
int consumersAmount;

static pid_t parent_pid;

#pragma region main
void menu()
{
    printf("---------------------------------\n"
           "| \tEnter:\t\t\t|"
           "\n|\tm - to print menu\t|"
           "\n|\tp - to create producer\t|"
           "\n|\td - to delete producer\t|"
           "\n|\tc - to create consumer\t|"
           "\n|\tr - to delete consumer\t|"
           "\n|\t+ - increment size\t|"
           "\n|\t- - decrement size\t|"
           "\n|\tl - size\t\t|"
           "\n|\tq - exit\t\t|\n"
           "---------------------------------\n");

}

void init(void)
{

    msgQueueInit();

    int res = pthread_mutex_init(&mutex, NULL);
    if (res)
    {
        fprintf(stderr, "Failed mutex init \n");
        exit(1);
    }

    if ((free_space = sem_open("free_space", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR), max)) == SEM_FAILED ||
        (items = sem_open("items", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR), 0)) == SEM_FAILED) {
        fprintf(stderr, "sem_open");
        exit(1);
    }
}

void end()
{
    int res = pthread_mutex_destroy(&mutex);
    if (res)
    {
        fprintf(stderr, "Failed mutex destroy\n");
        exit(1);
    }
    if (sem_unlink("free_space") ,
            sem_unlink("items")) {
        fprintf(stderr, "sem_unlink");
        abort();
    }
}

#pragma endregion

#pragma region msg
int hash(msg* _msg)
{
    unsigned long hash = 5381;

    for (int i = 0; i < _msg->size + 4; ++i)
    {
        hash = ((hash << 5) + hash) + i;
    }

    return (int) hash;
}

void msgQueueInit()
{
    memset(&queue, 0, sizeof(queue));
}

int putMsg(msg* _msg) {
    if (queue.msgCount == max )
    {
        fprintf(stderr, "Queue buffer overflow\n");
        exit(1);
    }

    if (queue.tail == max)
    {
        queue.tail = 0;
    }

    queue.buffer[queue.tail] = *_msg;
    queue.tail++;
    queue.msgCount++;

    return ++queue.addCount;
}

int getMsg(msg* _msg)
{
    if (queue.msgCount == 0)
    {
        fprintf(stderr, "Queue buffer overflow\n");
        exit(1);
    }

    if (queue.head == max)
    {
        queue.head = 0;
    }

    *_msg = queue.buffer[queue.head];
    queue.head++;
    queue.msgCount++;

    return ++queue.extractCount;
}
#pragma endregion

#pragma region producer

void createProducer()
{
    if (producersAmount == CHILD_MAX - 1)
    {
        fprintf(stderr, "Max value of producers\n");
        return;
    }

    int res = pthread_create(&producers[producersAmount], NULL,
                             handlerProduce, NULL);
    if (res)
    {
        fprintf(stderr, "Failed to create producer\n");
        exit(1);
    }

    ++producersAmount;


}

void removeProducer()
{
    if (producersAmount == 0)
    {
        fprintf(stderr, "No producers to delete\n");
        return;
    }

    --producersAmount;
    pthread_cancel(producers[producersAmount]);
    pthread_join(producers[producersAmount], NULL);
}
void produceMsg(msg* _msg)
{
    int value = rand() % 257;
    if (value == 256) {
        _msg->type = -1;
    } else {
        _msg->type = 0;
        _msg->size = value;
    }

    for (int i = 0; i < value; ++i)
    {
        _msg->data[i] = (char) (rand() % 256);
    }

    _msg->hash = 0;
    _msg->hash = hash(_msg);
}

_Noreturn void* handlerProduce(void* arg)
{
    msg _msg;
    int addCountLocal;
    while (1) {
        produceMsg(&_msg);

        sem_wait(free_space);

        pthread_mutex_lock(&mutex);
        addCountLocal = putMsg(&_msg);
        pthread_mutex_unlock(&mutex);

        sem_post(items);

        printf("%ld produce msg: hash=%X, addCount=%d\n",
               pthread_self(), _msg.hash, addCountLocal);

        sleep(5);
    }
}

#pragma endregion

#pragma region consumer

void createConsumer()
{
    if (consumersAmount == CHILD_MAX - 1) {
        fprintf(stderr, "Max value of consumers\n");
        return;
    }

    int res = pthread_create(&consumers[consumersAmount], NULL,
                             handlerConsume, NULL);
    if (res) {
        fprintf(stderr, "Failed to create producer\n");
        exit(res);
    }

    ++consumersAmount;

}

void removeConsumer()
{
    if (consumersAmount == 0) {
        fprintf(stderr, "No consumers to delete\n");
        return;
    }

    consumersAmount--;
    pthread_cancel(consumers[consumersAmount]);
    pthread_join(consumers[consumersAmount], NULL);
}

void consumeMsg(msg* _msg) {
    int msghash = _msg->hash;
    _msg->hash = 0;

    _msg->hash = msghash;
}

_Noreturn void* handlerConsume(void* arg) {
    msg  _msg;
    int extractCountLocal;
    while (1) {
        sem_wait(items);

        pthread_mutex_lock(&mutex);
        extractCountLocal = getMsg(&_msg);
        pthread_mutex_unlock(&mutex);

        sem_post(free_space);

        consumeMsg(&_msg);

        printf("%ld consume msg: hash=%X, extractCount=%d\n",
               pthread_self(), _msg.hash, extractCountLocal);

        sleep(5);
    }


}




int main()
{
    int value;
    printf("Enter max queue size (0-4096):\n\n");
    scanf("%d", &max);

    while(max < 0)
    {
        printf("You entered bad number!\n");
        printf("Enter max queue size (0-4096):\n\n");
        scanf("%d", &max);
    }


    init();
    menu();

    while(true)
    {
        switch(getchar())
        {
            case 'm':
            {
                menu();
                break;
            }
            case 'p':
            {
                createProducer();
                break;
            }
            case 'd':
            {
                removeProducer();
                break;
            }
            case 'c':
            {
                createConsumer();
                break;
            }
            case 'r':
            {
                removeConsumer();
                break;
            }
            case '+':
            {
                max++;
                sem_post(free_space);
                break;
            }
            case '-':
            {

                if(sem_getvalue(free_space,&value) == -1){
                    printf("error");
                }
                if(value != 0)
                {
                    max--;
                    sem_wait(free_space);
                }else{
                    printf("\n\nQueue is full! Create customer\n\n");
                }

                break;
            }
            case 'l':
            {
                printf("\n\nsize: %d\n\n" , max );
                break;
            }
            case 'q':
            {
                end();
                return 0;
            }


            default:
                break;
        }
    }
}
