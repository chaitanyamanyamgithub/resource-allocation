#include <stdio.h>

#define MAX_SERVERS 3
#define SERVER_CAPACITY 10  

typedef struct {
    int id;
    int available_space;
} Server;

void allocateTask(Server servers[], int taskSize) {
    for (int i = 0; i < MAX_SERVERS; i++) {
        if (servers[i].available_space >= taskSize) {
            servers[i].available_space -= taskSize;
            printf(" Task of %d GHz assigned to Server %d\n", taskSize, servers[i].id);
            return;
        }
    }

    for (int i = 0; i < MAX_SERVERS; i++) {
        for (int j = 0; j < MAX_SERVERS; j++) {
            if (i != j && servers[i].available_space >= taskSize - servers[j].available_space) {
                printf(" Swapping %d GHz from Server %d to Server %d to fit task.\n",
                       servers[j].available_space, servers[j].id, servers[i].id);
                servers[i].available_space -= taskSize - servers[j].available_space;
                servers[j].available_space = 0;
                printf(" Task of %d GHz assigned after reallocation.\n", taskSize);
                return;
            }
        }
    }

    printf(" Task of %d GHz cannot be assigned due to lack of space!\n", taskSize);
}

int main() {
    Server servers[MAX_SERVERS] = {
        {1, 3},  
        {2, 7},  
        {3, 10}  
    };

    printf(" Initial Server Status:\n");
    for (int i = 0; i < MAX_SERVERS; i++) {
        printf("Server %d -> Free Space: %d GHz\n", servers[i].id, servers[i].available_space);
    }

    int newTaskSize = 5;
    printf("\n Trying to allocate a new task of %d GHz...\n", newTaskSize);
    allocateTask(servers, newTaskSize);

    printf("\n Final Server Status:\n");
    for (int i = 0; i < MAX_SERVERS; i++) {
        printf("Server %d -> Free Space: %d GHz\n", servers[i].id, servers[i].available_space);
    }

    return 0;
}
