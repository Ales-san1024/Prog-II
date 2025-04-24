#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/linkedListQueue.h"

void runPrintfTests() {
    CharQueueADT q = mkQueue();
    if (q) {
        printf("[Expected: 1 Got: %d]\n", isEmpty(q));
        printf("[Expected: 1 Got: %d]\n", enqueue(q, 'A'));
        printf("[Expected: 1 Got: %d]\n", enqueue(q, 'B'));
        printf("[Expected: 1 Got: %d]\n", enqueue(q, 'C'));
        printf("[Expected: 0 Got: %d]\n", isEmpty(q));
        printf("[Expected: 3 Got: %d]\n", size(q));

        char peekRes;
        printf("[Expected: 1 Got: %d]\n", peek(q, 0, &peekRes));
        printf("[Expected: 'A' Got: '%c']\n", peekRes);
        printf("[Expected: 1 Got: %d]\n", peek(q, 1, &peekRes));
        printf("[Expected: 'B' Got: '%c']\n", peekRes);
        printf("[Expected: 1 Got: %d]\n", peek(q, 2, &peekRes));
        printf("[Expected: 'C' Got: '%c']\n", peekRes);

        char dequeued;
        printf("[Expected: 1 Got: %d]\n", dequeue(q, &dequeued));
        printf("[Expected: 'A' Got: '%c']\n", dequeued);
        printf("[Expected: 2 Got: %d]\n", size(q));
        printf("[Expected: 1 Got: %d]\n", dequeue(q, &dequeued));
        printf("[Expected: 'B' Got: '%c']\n", dequeued);
        printf("[Expected: 1 Got: %d]\n", size(q));
        printf("[Expected: 1 Got: %d]\n", dequeue(q, &dequeued));
        printf("[Expected: 'C' Got: '%c']\n", dequeued);
        printf("[Expected: 0 Got: %d]\n", isEmpty(q));
        printf("[Expected: 0 Got: %d]\n", dequeue(q, &dequeued));
        printf("[Expected: 0 Got: %d]\n", size(q));

        dsQueue(&q);
        printf("[Expected: 1 Got: %d]\n", q == NULL);
    }
}

void runAssertTests() {
    CharQueueADT q;
    char result;

    q = mkQueue();
    assert(size(q) == 0);
    enqueue(q, 'a');
    assert(size(q) == 1);
    enqueue(q, 'b');
    enqueue(q, 'c');
    assert(size(q) == 3);
    dequeue(q, &result);
    assert(size(q) == 2);
    dequeue(q, &result);
    assert(size(q) == 1);
    dequeue(q, &result);
    assert(size(q) == 0);
    dequeue(q, &result);
    assert(size(q) == 0);
    enqueue(q, 'x');
    assert(size(q) == 1);
    dequeue(q, &result);
    assert(size(q) == 0);
    enqueue(q, 'd');
    enqueue(q, 'e');
    assert(size(q) == 2);
    dequeue(q, &result);
    assert(size(q) == 1);
    enqueue(q, 'f');
    assert(size(q) == 2);
    dequeue(q, &result);
    dequeue(q, &result);
    assert(size(q) == 0);

    for (int i = 0; i < 1000; i++) {
        enqueue(q, 'a');
    }
    assert(size(q) == 1000);
    for (int i = 0; i < 1000; i++) {
        dequeue(q, &result);
    }
    assert(size(q) == 0);
    enqueue(q, 'z');
    assert(size(q) == 1);
    enqueue(q, 'y');
    enqueue(q, 'x');
    assert(size(q) == 3);
    dsQueue(&q);
    q = mkQueue();
    assert(size(q) == 0);
    enqueue(q, 'p');
    enqueue(q, 'q');
    dequeue(q, &result);
    assert(size(q) == 1);
    dequeue(q, &result);
    assert(size(q) == 0);
    dsQueue(&q);
    assert(q == NULL);

    printf("All tests passed!\n");
}

int main() {
    runPrintfTests();
    runAssertTests();
    return 0;
}
