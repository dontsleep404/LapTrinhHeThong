#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *MESSAGE_QUEUE_NAME = "./message_queue.txt";
FILE       *messageQueue       = NULL;

void connectToMessageQueue();
void writeMessage(char *message);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }   

    connectToMessageQueue();

    writeMessage(argv[1]);

    fclose(messageQueue);

    return 0;
}
void connectToMessageQueue() {
    messageQueue = fopen(MESSAGE_QUEUE_NAME, "a");
}
void writeMessage(char *message) {
    if (messageQueue != NULL) {
        fprintf(messageQueue, "%s\n", message);
        printf("Message written to queue: %s\n", message);
    }
}