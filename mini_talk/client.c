#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 8

void sendBits(pid_t serverPid, char *message) {
    char buffer[BUFFER_SIZE] = {0};  // 8ビットのバッファ
    int bufferIndex = 0;

    for (int i = 0; i < strlen(message); i++) {
        for (int j = 7; j >= 0; j--) {
            // メッセージの各ビットをバッファに追加
            buffer[bufferIndex] = (message[i] >> j) & 1;
            bufferIndex++;
            if (bufferIndex == BUFFER_SIZE) {
                for (int k = 0; k < BUFFER_SIZE; k++) {
                    if (buffer[k] == 0) {
                        kill(serverPid, SIGUSR1);
                    } else {
                        kill(serverPid, SIGUSR2);
                    }
                }
                bufferIndex = 0;  // バッファをクリア
            }
        }
    }

    // メッセージ終端の '\0' を送信
    for (int k = 0; k < BUFFER_SIZE; k++) {
        if (buffer[k] == 0) {
            kill(serverPid, SIGUSR1);
        } else {
            kill(serverPid, SIGUSR2);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t serverPid = atoi(argv[1]);
    char *message = argv[2];
    // クライアントはサーバーにビットを送信
    sendBits(serverPid, message);

    // 送信完了を示す '\0' を送信
    sendBits(serverPid, "\0");

    return 0;
}
