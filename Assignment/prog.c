#include <stdio.h>
#include <string.h>
#define SIZE 20

/*  circular warehouse structure */
typedef struct {
    char buffer[SIZE];
    int head;   
    int tail;   
    int count; 
} CircularBuffer;

/* initialization */
void init(CircularBuffer *cb) {
    cb->head  = 0;
    cb->tail  = 0;
    cb->count = 0;
}

/* ===check  if its full=== */
int isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

/* ===check if its empty=== */
int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

/*  ===insert element=== */
void write_cb(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("[Overflow!] the structure is full! '%c'\n", data);
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;  
    cb->count++;
}

/* ===reading=== */
char read_cb(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("[Underflow!] the structure is empty! \n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;  
    cb->count--;
    return data;
}

/* ===== Main function===== */
int main() {
    CircularBuffer cb;
    init(&cb);

    char name[50];
    printf("Enter your name: ");
    scanf("%s", name);

    //Add CE-ESY for name
    strcat(name, "CE-ESY");
    printf(" the text: %s\n", name);

    int len = strlen(name);
    for (int i = 0; i < len; i++) {
        write_cb(&cb, name[i]);
    }

    // read and show
    printf("read from circular buffer: ");
    while (!isEmpty(&cb)) {
        printf("%c", read_cb(&cb));
    }
    printf("\n");

    
    if (isEmpty(&cb)) {
        printf("✓ it is Empty.\n");
    }

    return 0;
}

