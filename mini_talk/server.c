#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 8

volatile sig_atomic_t receivedSignal = 0;
unsigned char receivedBits = 0;
int bitCount = 0;
char receivedString[BUFFER_SIZE + 1];  // +1 for null terminator

void signalHandler(int signum) {
    receivedSignal = signum;
}

void processBit(int bit) {
    receivedBits = (receivedBits << 1) | bit;
    bitCount++;

    if (bitCount == BUFFER_SIZE) {
        receivedString[BUFFER_SIZE] = '\0';  // Null-terminate the string
        printf("Received: %s\n", receivedString);
        fflush(stdout);
        bitCount = 0;
        receivedBits = 0;
        memset(receivedString, 0, sizeof(receivedString));  // Clear the buffer
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("Server PID: %d\n", getpid());

    while (1) {
        if (receivedSignal != 0) {
            if (receivedSignal == SIGUSR1 || receivedSignal == SIGUSR2) {
                processBit(receivedSignal == SIGUSR1 ? 0 : 1);
            }
            if (receivedSignal == SIGUSR1) {
                // '\0' を受信した場合、ループを終了
                break;
            }
            receivedSignal = 0;
        }

        usleep(500);  // 0.5ミリ秒の待機
    }

    return 0;
}
