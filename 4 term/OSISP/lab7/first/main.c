#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stddef.h>
#include <pthread.h>

#define DATA_MAX (((256 + 3) / 4) * 4)
#define MSG_MAX 4096
#define CHILD_MAX 1024

#pragma region prototypes
//msg
typedef struct {
    int type;
    int hash;
    int size;
    char data[DATA_MAX];
} msg;

typedef struct {
    int add_count;
    int extract_count;

    int msg_count;

    int head;
    int tail;
    msg buffer[MSG_MAX];
} msg_queue;

int hash(msg* _msg);
void msg_queue_init();
int put_msg(msg* _msg);
int get_msg(msg* _msg);

//main
void show_menu();
void init();
void end();

//producer
void create_producer();
void remove_producer();
void produce_msg(msg* _msg);
void* produce_handler(void* arg);

//consumer
void create_consumer();
void remove_consumer();
void consume_msg(msg* _msg);
void* consume_handler(void* arg);

#pragma endregion


msg_queue queue;
pthread_mutex_t mutex;

pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;

pthread_t  producers[CHILD_MAX];
int producers_amount;

pthread_t  consumers[CHILD_MAX];
int consumers_amount;

#pragma region main
void show_menu()
{
    printf("---------------------------------\n"
           "| \tEnter:\t\t\t|"
           "\n|\tm - to print menu\t|"
           "\n|\tp - to create producer\t|"
           "\n|\td - to delete producer\t|"
           "\n|\tc - to create consumer\t|"
           "\n|\tr - to delete consumer\t|"
           "\n|\tq - exit\t\t|\n"
           "---------------------------------\n");
}

void init(void) {

    msg_queue_init();

    int res = pthread_mutex_init(&mutex, NULL);
    if (res) {
        fprintf(stderr, "Failed mutex init \n");
        exit(1);
    }

    int ret = pthread_cond_init(&cond_producer, NULL);
    if (ret != 0) {
        fprintf(stderr, "Error initializing cond_producer\n");
        exit(EXIT_FAILURE);
    }

    ret = pthread_cond_init(&cond_consumer, NULL);
    if (ret != 0) {
        fprintf(stderr, "Error initializing cond_consumer\n");
        exit(EXIT_FAILURE);
    }
}

void end()
{
    while(producers_amount){
        --producers_amount;
        if (pthread_cancel(producers[producers_amount]) != 0) {
            fprintf(stderr, "Failed to cancel producer\n");
            exit(EXIT_FAILURE);
        }
        if (pthread_join(producers[producers_amount], NULL) != 0) {
            fprintf(stderr, "Failed to join producer\n");
            exit(EXIT_FAILURE);
        }
    }

    while(consumers_amount)
    {
        --consumers_amount;
        if (pthread_cancel(consumers[consumers_amount]) != 0) {
            fprintf(stderr, "Failed to cancel consumer\n");
            exit(EXIT_FAILURE);
        }
        if (pthread_join(consumers[consumers_amount], NULL) != 0) {
            fprintf(stderr, "Failed to join consumer\n");
            exit(EXIT_FAILURE);
        }
    }

    int res = pthread_mutex_destroy(&mutex);
    if (res != 0) {
        fprintf(stderr, "Failed to destroy mutex: %s\n", strerror(res));
        exit(EXIT_FAILURE);
    }

    res = pthread_cond_destroy(&cond_producer);
    if (res != 0) {
        fprintf(stderr, "Failed to destroy cond_producer: %s\n", strerror(res));
        exit(EXIT_FAILURE);
    }

    res = pthread_cond_destroy(&cond_consumer);
    if (res != 0) {
        fprintf(stderr, "Failed to destroy cond_consumer: %s\n", strerror(res));
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

#pragma endregion

#pragma region msg
int hash(msg* _msg) {
    unsigned long hash = 5381;

    for (int i = 0; i < _msg->size + 4; ++i) {
        hash = ((hash << 5) + hash) + i;
    }

    return (int) hash;
}

void msg_queue_init() {
    memset(&queue, 0, sizeof(queue));
}

int put_msg(msg* _msg) {
    if (queue.msg_count == MSG_MAX - 1) {
        fprintf(stderr, "Queue buffer overflow\n");
        exit(1);
    }

    if (queue.tail == MSG_MAX) {
        queue.tail = 0;
    }

    queue.buffer[queue.tail] = *_msg;
    queue.tail++;
    queue.msg_count++;

    return ++queue.add_count;
}

int get_msg(msg* _msg) {
    if (queue.msg_count == 0) {
        fprintf(stderr, "Queue buffer overflow\n");
        exit(1);
    }

    if (queue.head == MSG_MAX) {
        queue.head = 0;
    }

    *_msg = queue.buffer[queue.head];
    queue.head++;
    queue.msg_count--;

    return ++queue.extract_count;
}
#pragma endregion

#pragma region producer

void create_producer() {
    if (producers_amount == CHILD_MAX - 1) {
        fprintf(stderr, "Max value of producers\n");
        return;
    }

    int res = pthread_create(&producers[producers_amount], NULL,
                             produce_handler, NULL);
    if (res) {
        fprintf(stderr, "Failed to create producer\n");
        exit(1);
    }

    ++producers_amount;
}

void remove_producer() {
    if (producers_amount == 0) {
        fprintf(stderr, "No producers to delete\n");
        return;
    }

    --producers_amount;
    pthread_cancel(producers[producers_amount]);
    pthread_join(producers[producers_amount], NULL);
}

void produce_msg(msg* _msg) {
    int value = rand() % 257;
    if (value == 256) {
        _msg->type = -1;
    } else {
        _msg->type = 0;
        _msg->size = value;
    }

    for (int i = 0; i < value; ++i) {
        _msg->data[i] = (char) (rand() % 256);
    }

    _msg->hash = 0;
    _msg->hash = hash(_msg);
}

_Noreturn void* produce_handler(void* arg) {
    msg _msg;
    int add_count_local;
    while (1) {
        produce_msg(&_msg);

        pthread_mutex_lock(&mutex);

        while (queue.msg_count == MSG_MAX-1) {
            pthread_cond_wait(&cond_producer, &mutex);
        }
        add_count_local = put_msg(&_msg);
        pthread_cond_signal(&cond_consumer);

        pthread_mutex_unlock(&mutex);

        printf("%ld produce msg: hash=%X, add_count=%d\n",
               pthread_self(), _msg.hash, add_count_local);

        sleep(5);
    }
}

#pragma endregion

#pragma region consumer

void create_consumer() {
    if (consumers_amount == CHILD_MAX - 1) {
        fprintf(stderr, "Max value of consumers\n");
        return;
    }

    int res = pthread_create(&consumers[consumers_amount], NULL,
                             consume_handler, NULL);
    if (res) {
        fprintf(stderr, "Failed to create producer\n");
        exit(res);
    }

    ++consumers_amount;

}

void remove_consumer() {
    if (consumers_amount == 0) {
        fprintf(stderr, "No consumers to delete\n");
        return;
    }

    consumers_amount--;
    pthread_cancel(consumers[consumers_amount]);
    pthread_join(consumers[consumers_amount], NULL);
}

void consume_msg(msg* _msg) {
    int msg_hash = _msg->hash;
    _msg->hash = 0;
    int check_sum = hash(_msg);
    if (msg_hash != check_sum) {
        fprintf(stderr, "check_sum=%d not equal msg_hash=%d\n",
                check_sum, msg_hash);
    }
    _msg->hash = msg_hash;
}

_Noreturn void* consume_handler(void* arg) {
    msg  _msg;
    int extract_count_local;
    while (1) {
        pthread_mutex_lock(&mutex);

        while (queue.msg_count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        extract_count_local = get_msg(&_msg);
        pthread_cond_signal(&cond_producer);

        pthread_mutex_unlock(&mutex);

        consume_msg(&_msg);

        printf("%ld consume msg: hash=%X, extract_count=%d\n",
               pthread_self(), _msg.hash, extract_count_local);

        sleep(5);
    }
}

#pragma endregion consumer

int main()
{
    init();
    show_menu();
    while(true)
    {
        switch(getchar())
        {
            case 'm':
            {
                show_menu();
                break;
            }
            case 'p':
            {
                create_producer();
                break;
            }
            case 'd':
            {
                remove_producer();
                break;
            }
            case 'c':
            {
                create_consumer();
                break;
            }
            case 'r':
            {
                remove_consumer();
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