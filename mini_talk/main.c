/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshoma <kshoma@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:31:18 by kshoma            #+#    #+#             */
/*   Updated: 2023/12/18 17:57:33 by kshoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// SIGINTに対するハンドラ関数
void sigint_handler(int sig_num)
{
    printf("\nSIGINT信号をキャッチ！\n");

    // 通常はプログラムを終了させる
    exit(0);
}

int main(void)
{
    // SIGINTに対するハンドラを設定する
    if(signal(SIGINT, sigint_handler) == SIG_ERR){
        printf("SIGINTハンドラのセットアップに失敗しました。\n");
        return 1;
    }

    printf("SIGINT信号を待っています。\n");

    // 無限ループでSIGINTを待つ
    while(1){
    }
    pid_t pid = getpid();
	printf("%d\n",pid);
    return 0;
}
