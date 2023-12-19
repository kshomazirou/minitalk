/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshoma <kshoma@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:57:41 by kshoma            #+#    #+#             */
/*   Updated: 2023/12/18 17:57:42 by kshoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void signalHandler(int signum) {
    printf("Received signal in child process: %d\n", signum);
}

int main() {
    pid_t childPid;

    // フォークして子プロセスを生成
    childPid = fork();

    if (childPid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {
        // 子プロセスの処理
        signal(SIGUSR1, signalHandler);
        printf("Child process is waiting for signals...\n");

        // 子プロセスはここで無限ループに入ります
        while (1) {
            sleep(1);
        }
    } else {
        // 親プロセスの処理
        printf("Parent process sending signal to child (PID: %d)\n", childPid);

        // 子プロセスに SIGUSR1 シグナルを送信
        kill(childPid, SIGUSR1);

        // 親プロセスはここで待機
        wait(NULL);
    }

    return 0;
}

