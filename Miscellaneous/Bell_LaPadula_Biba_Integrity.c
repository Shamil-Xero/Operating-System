#include <stdio.h>
#include <stdlib.h>

typedef enum {LOW, MEDIUM, HIGH} SecurityLevel;

typedef struct {
    char *name;
    SecurityLevel level;
} Subject;

typedef struct {
    char *data;
    SecurityLevel level;
} Object;

// Bell-LaPadula: No read up
int canRead(Subject *subject, Object *object) {
    return subject->level >= object->level;
}

// Bell-LaPadula: No write down
int canWrite(Subject *subject, Object *object) {
    return subject->level <= object->level;
}

// Biba: No write up
int canWriteBiba(Subject *subject, Object *object) {
    return subject->level >= object->level;
}

// Biba: No read down
int canReadBiba(Subject *subject, Object *object) {
    return subject->level <= object->level;
}

int main() {
    Subject alice = {"Alice", HIGH};
    Subject bob = {"Bob", LOW};
    Object secret = {"Secret Data", HIGH};
    Object public = {"Public Data", LOW};

    printf("Bell-LaPadula Model:\n");
    printf("Can Alice read secret? %s\n", canRead(&alice, &secret) ? "Yes" : "No");
    printf("Can Bob read secret? %s\n", canRead(&bob, &secret) ? "Yes" : "No");
    printf("Can Alice write to public? %s\n", canWrite(&alice, &public) ? "Yes" : "No");
    printf("Can Bob write to secret? %s\n", canWrite(&bob, &secret) ? "Yes" : "No");

    printf("\nBiba Model:\n");
    printf("Can Alice write to secret? %s\n", canWriteBiba(&alice, &secret) ? "Yes" : "No");
    printf("Can Bob write to public? %s\n", canWriteBiba(&bob, &public) ? "Yes" : "No");
    printf("Can Alice read public? %s\n", canReadBiba(&alice, &public) ? "Yes" : "No");
    printf("Can Bob read secret? %s\n", canReadBiba(&bob, &secret) ? "Yes" : "No");

    return 0;
}
