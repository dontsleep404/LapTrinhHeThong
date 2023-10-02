#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *MESSAGE_QUEUE_NAME = "./message_queue.txt";
const char *MESSAGE_INDEX_NAME = "./message_index.txt";
const int   MAX_MESSAGE_SIZE   = 100;
FILE       *messageQueue       = NULL;

void connectToMessageQueue();
int  getMessageIndex();
void setMessageIndex(int index);
int  getMessage(char *data, int index);

int main(int argc, char *argv[]) {
    connectToMessageQueue();
    char *message = malloc(MAX_MESSAGE_SIZE);
    int index = getMessageIndex();
    if (getMessage(message, index)) {
        printf("FIFO >> %s", message);
        setMessageIndex(index + 1);
    }
    free(message);
    fclose(messageQueue);
    return 0;
}
void connectToMessageQueue() {
    messageQueue = fopen(MESSAGE_QUEUE_NAME, "r");
}

int  getMessageIndex() {
    FILE *messageIndex = fopen(MESSAGE_INDEX_NAME, "r");
    if (messageIndex == NULL) {
        setMessageIndex(0);
        messageIndex = fopen(MESSAGE_INDEX_NAME, "r");
    }
    int index;
    fscanf(messageIndex, "%d", &index);
    fclose(messageIndex);
    return index;
}

void setMessageIndex(int index) {
    FILE *messageIndex = fopen(MESSAGE_INDEX_NAME, "w");
    fprintf(messageIndex, "%d", index);
    fclose(messageIndex);
}

int  getMessage(char *data, int index) {
    if (messageQueue == NULL) {
        return 0;
    }
    char *line = malloc(MAX_MESSAGE_SIZE);
    int i = 0;
    while (fgets(line, MAX_MESSAGE_SIZE, messageQueue) != NULL) {
        if (i++ == index) {
            memcpy(data, line, MAX_MESSAGE_SIZE);
            break;
        }
    }
    free(line);
    if(i > index) return 1;
    return 0;  
}