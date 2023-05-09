#define MAX_QUEUE_SIZE 100

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef char element ;
typedef struct {
    element data[MAX_QUEUE_SIZE] ;
    int front, rear ;
} QueueType ;

void init_queue(QueueType *qptr) {
    qptr->front = qptr->rear = 0 ;
}

int is_empty(QueueType *qptr) {
    return (qptr->front == qptr->rear) ;
}

int is_full(QueueType *qptr) {
    return (qptr->rear+1) % MAX_QUEUE_SIZE == qptr->front ;
}

void enqueue(QueueType *qptr, element item) {
    if(is_full(qptr)) {
        fprintf(stderr, "Queue is Full\n") ;
    }
    else {
        qptr->rear = (qptr->rear+1) % MAX_QUEUE_SIZE ;
        qptr->data[qptr->rear] = item ;
    }
}

element dequeue(QueueType *qptr) {
    if(is_empty(qptr)) {
        fprintf(stderr, "Queue is Empty\n") ;
        return -1 ;
    }
    else {
        qptr->front = (qptr->front + 1) % MAX_QUEUE_SIZE ;
        return (qptr->data[qptr->front]) ;
    }
}

void queue_print(QueueType *qptr) {
    printf("Queue(front = %d, rear = %d) = ", qptr->front, qptr->rear);
    if(!is_empty(qptr)) {
        int i = qptr->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%d | ", qptr->data[i]);
        } while (i != qptr->rear);
    }
    printf("\n");
}

element delete_rear(QueueType *qptr) {
    int prev ;
    prev = qptr -> rear ;
    if(is_empty(qptr)) {
        fprintf(stderr, "Queue is Empty\n") ;
        return -1 ;
    }
    else {
        qptr->rear = (qptr->rear + MAX_QUEUE_SIZE - 1) % MAX_QUEUE_SIZE ;
        return(qptr->data[prev]) ;
    }
}

void add_front(QueueType *qptr, element item) {
    if(is_full(qptr)) {
        fprintf(stderr, "Queue is Full\n") ;
    }
    else {
        qptr->data[qptr->front] = item ;
        qptr->front = (qptr->front+MAX_QUEUE_SIZE - 1) % MAX_QUEUE_SIZE ;
    }
}

bool is_palindrome(QueueType *qptr) {
    int start = qptr->front ;
    int end = qptr->rear ;

    while (start != end && (start + 1) % MAX_QUEUE_SIZE != end) {
        char start_char = tolower(qptr->data[(start + 1) % MAX_QUEUE_SIZE]) ;
        char end_char = tolower(qptr->data[end]) ;

        if (!isalnum(start_char)) {
            start = (start + 1) % MAX_QUEUE_SIZE ; 
            continue ;
        }
        if (!isalnum(end_char)) {
            end = (end + MAX_QUEUE_SIZE - 1) % MAX_QUEUE_SIZE ;
            continue ;
        }

        if (start_char != end_char) {
            return false ;
        }
        start = (start + 1) % MAX_QUEUE_SIZE ;
        end = (end + MAX_QUEUE_SIZE - 1) % MAX_QUEUE_SIZE ;
    }
    return true ;
}

int main() {
    char input_string[MAX_QUEUE_SIZE] ;
    QueueType queue ;
    init_queue(&queue) ;

    while(1) {
        printf("문장을 입력하세요(종료 : exit) : ") ;
        scanf(" %[^\n]", input_string) ; // 공백 포함 입력 받기

        if(strcmp(input_string, "exit") == 0) {
            exit(1) ;
        }
        
        for(int i=0; i<strlen(input_string); i++) {
            if (isalnum(input_string[i])) {
                enqueue(&queue, input_string[i]) ;
            }
        }

        if(is_palindrome(&queue)) {
            printf("회문입니다.\n") ;
        }
        else {
            printf("회문이 아닙니다.\n") ;
        }
        
        init_queue(&queue) ;
    }
}