/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
int mysystem(char *command) {
  int pid;
  int status;

  if(command == NULL){
    return 1;
  }
  pid = fork();
  if(pid < 0){
    return -1;
  }
  else if(pid == 0){
    execl("/bin/sh","sh","-c", command, NULL);
    exit(127);
  }else{
    while(wait(&status) != pid){
      ;
    }
  }
  return status;
}

/* 実行例
% make                                                   コンパイル
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c
./mysysmain "ls -l"                                      実行
mysystem:
total 536
-rw-r--r--  1 ariumihiroshito  staff     143  7  4 09:47 Makefile
-rw-r--r--  1 ariumihiroshito  staff    2795  7  4 09:47 README.md
-rw-r--r--@ 1 ariumihiroshito  staff  238232  7  4 09:47 README.pdf
-rwxr-xr-x  1 ariumihiroshito  staff    8832  7  9 16:36 mysysmain
-rw-r--r--  1 ariumihiroshito  staff     925  7  4 09:47 mysysmain.c
-rw-r--r--  1 ariumihiroshito  staff     747  7  9 16:36 mysystem.c
-rw-r--r--  1 ariumihiroshito  staff      90  7  4 09:47 mysystem.h
retval = 00000000
system:
total 536
-rw-r--r--  1 ariumihiroshito  staff     143  7  4 09:47 Makefile
-rw-r--r--  1 ariumihiroshito  staff    2795  7  4 09:47 README.md
-rw-r--r--@ 1 ariumihiroshito  staff  238232  7  4 09:47 README.pdf
-rwxr-xr-x  1 ariumihiroshito  staff    8832  7  9 16:36 mysysmain
-rw-r--r--  1 ariumihiroshito  staff     925  7  4 09:47 mysysmain.c
-rw-r--r--  1 ariumihiroshito  staff     747  7  9 16:36 mysystem.c
-rw-r--r--  1 ariumihiroshito  staff      90  7  4 09:47 mysystem.h
retval = 00000000

systemとmysystemは同じ結果を出力している

% ./mysysmain ls -l                                         エラー時の出力
使い方 : ./mysysmain コマンド文字列
*/
