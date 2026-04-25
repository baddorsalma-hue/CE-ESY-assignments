#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

// تعريف هيكل المخزن الدائري
typedef struct {
    char buffer[MAX_SIZE];
    int head;
    int tail;
    int count;
    int size;
} CircularBuffer;

// تهيئة المخزن
void initBuffer(CircularBuffer *cb, int size) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
    cb->size = size;
}

// التحقق من الامتلاء
int isFull(CircularBuffer *cb) {
    return cb->count == cb->size;
}

// التحقق من الفراغ
int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// إدخال عنصر
int enqueue(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("المخزن ممتلئ!\n");
        return 0;
    }

    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % cb->size;
    cb->count++;
    return 1;
}

// قراءة عنصر
int dequeue(CircularBuffer *cb, char *data) {
    if (isEmpty(cb)) {
        printf("المخزن فارغ!\n");
        return 0;
    }

    *data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % cb->size;
    cb->count--;
    return 1;
}

// تخزين سلسلة داخل المخزن
void storeString(CircularBuffer *cb, char *text) {
    for (int i = 0; i < strlen(text); i++) {
        if (!enqueue(cb, text[i])) {
            printf("توقف الإدخال بسبب امتلاء المخزن\n");
            break;
        }
    }
}

// قراءة السلسلة من المخزن
void readString(CircularBuffer *cb, char *output) {
    int i = 0;
    char ch;

    while (!isEmpty(cb)) {
        dequeue(cb, &ch);
        output[i++] = ch;
    }

    output[i] = '\0';
}

// دالة اختبار بحجم معين
void testBuffer(int size, char *text) {
    CircularBuffer circularBuffer;
    char output[150];

    printf("\n--- اختبار بحجم %d ---\n", size);

    initBuffer(&circularBuffer, size);

    storeString(&circularBuffer, text);
    readString(&circularBuffer, output);

    printf("الناتج: %s\n", output);

    if (isEmpty(&circularBuffer))
        printf("المخزن فارغ ✔\n");
}

int main() {
    char inputName[100];
    char finalString[150];

    printf("ادخل الاسم: ");
    fgets(inputName, sizeof(inputName), stdin);

    // إزالة newline
    inputName[strcspn(inputName, "\n")] = 0;

    // دمج النص
    strcpy(finalString, inputName);
    strcat(finalString, "CE-ESY");

    printf("بعد الإضافة: %s\n", finalString);

    // اختبارين
    testBuffer(10, finalString);   // حجم صغير
    testBuffer(50, finalString);   // حجم كبير

    return 0;
}
