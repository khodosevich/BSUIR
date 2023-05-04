#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <stddef.h>

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

//consumer
void create_consumer();
void remove_consumer();
void consume_msg(msg* _msg);

#pragma endregion


msg_queue* queue;

sem_t * mutex;

sem_t* free_space;
sem_t* items;

pid_t  producers[CHILD_MAX];
int producers_amount;

pid_t  consumers[CHILD_MAX];
int consumers_amount;

static pid_t parent_pid;

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
  parent_pid = getpid();

  // Setup shared memory
  int fd = shm_open("/queue", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR)); // mode(for fd) ~ 00400 | 00200 - owner can read and write 
  if (fd < 0) {
    fprintf(stderr, "shm_open");
    exit(1);
  }

  if (ftruncate(fd, sizeof(msg_queue))) {
    fprintf(stderr, "ftruncate");
    exit(1);
  }

  void* ptr = mmap(NULL, sizeof(msg_queue), PROT_READ | PROT_WRITE,
                   MAP_SHARED, fd, 0); // map_shared - other processes can see it 
  if (ptr == MAP_FAILED) {
    fprintf(stderr, "ftruncate");
    exit(1);
  }

  queue = (msg_queue*) ptr;

  if (close(fd)) {
    fprintf(stderr, "close");
    exit(1);
  }

  msg_queue_init();


  if ((mutex = sem_open("mutex", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR), 1)) == SEM_FAILED
        ||(free_space = sem_open("free_space", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR), MSG_MAX)) == SEM_FAILED
        ||(items = sem_open("items", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR), 0)) == SEM_FAILED) {
    fprintf(stderr, "sem_open");
    exit(1);
  }
}

void end()
{
     if (getpid() == parent_pid) {
    for (size_t i = 0; i < producers_amount; ++i) {
      kill(producers[i], SIGTERM);
      wait(NULL);
    }
    for (size_t i = 0; i < consumers_amount; ++i) {
      kill(consumers[i], SIGTERM);
      wait(NULL);
    }
  } else if (getppid() == parent_pid) {
    kill(getppid(), SIGTERM);
  }

  if (shm_unlink("/queue")) {
    fprintf(stderr, "shm_unlink");
    abort();
  }
  if (sem_unlink("mutex") ||
      sem_unlink("free_space") ||
      sem_unlink("items")) {
    fprintf(stderr, "sem_unlink");
    abort();
  }
}

#pragma endregion 

#pragma region msg
// djb2
int hash(msg* _msg) {
  unsigned long hash = 5381;

  for (int i = 0; i < _msg->size + 4; ++i) {
    hash = ((hash << 5) + hash) + i;
  }

  return (int) hash;
}

void msg_queue_init() {
  queue->add_count  = 0;
  queue->extract_count = 0;
  queue->msg_count = 0;
  queue->head = 0;
  queue->tail = 0;
  memset(queue->buffer, 0, sizeof(queue->buffer));
}

int put_msg(msg* _msg) {
  if (queue->msg_count == MSG_MAX - 1) {
    fscanf(stderr, "Queue buffer overflow\n");
    exit(1);
  }

  if (queue->tail == MSG_MAX) {
    queue->tail = 0;
  }

  queue->buffer[queue->tail] = *_msg;
  queue->tail++;
  queue->msg_count++;

  return ++queue->add_count;
}

int get_msg(msg* _msg) {
  if (queue->msg_count == 0) {
    fprintf(stderr, "Queue buffer overflow\n");
    exit(1);
  }

  if (queue->head == MSG_MAX) {
    queue->head = 0;
  }

  *_msg = queue->buffer[queue->head];
  queue->head++;
  queue->msg_count++;

  return ++queue->extract_count;
}
#pragma endregion

#pragma region producer

void create_producer() {
  if (producers_amount == CHILD_MAX - 1) {
    fprintf(stderr, "Max value of producers\n");
    return;
  }

  switch (producers[producers_amount] = fork()) {
    default:
    { // Parent process
      ++producers_amount;
      return;
    }

    case 0:
    {// Child process
      srand(getpid());
      break;
    }

    case -1:
        fscanf(stderr, "fork");
        exit(1);
  }

  msg _msg;
  int add_count_local;
  while (1) {
    produce_msg(&_msg);

    sem_wait(free_space);

    sem_wait(mutex);
    add_count_local = put_msg(&_msg);
    sem_post(mutex);

    sem_post(items);

    printf("%d produce msg: hash=%X, add_count=%d\n",
           getpid(), _msg.hash, add_count_local);

    sleep(5);
  }

}

void remove_producer() {
  if (producers_amount == 0) {
    fputs("No producers to delete\n", stderr);
    return;
  }

  --producers_amount;
  kill(producers[producers_amount], SIGTERM);
  wait(NULL);
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

#pragma endregion

#pragma region consumer 

void create_consumer() {
  if (consumers_amount == CHILD_MAX - 1) {
    fprintf(stderr, "Max value of consumers\n");
    return;
  }

  switch (consumers[consumers_amount] = fork()) {
    default:
      // Parent process
      ++consumers_amount;
      return;

    case 0:
      // Child process
      break;

    case -1:
      fprintf(stderr, "fork");
      exit(1);
  }

  msg _msg;
  int extract_count_local;
  while (true) {
    sem_wait(items);

    sem_wait(mutex);
    extract_count_local = get_msg(&_msg);
    sem_post(mutex);

    sem_post(free_space);

    consume_msg(&_msg);

    printf("%d consume msg: hash=%X, extract_count=%d\n",
           getpid(), _msg.hash, extract_count_local);

    sleep(5);
  }

}

void remove_consumer() {
  if (consumers_amount == 0) {
    fprintf(stderr, "No consumers to delete\n");
    return;
  }

  consumers_amount--;
  kill(consumers[consumers_amount], SIGTERM);
  wait(NULL);
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