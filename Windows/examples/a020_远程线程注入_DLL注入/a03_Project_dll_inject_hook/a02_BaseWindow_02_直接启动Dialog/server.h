#ifndef SERVER_H
#define SERVER_H

typedef void (*UpdateUIFunc)(const char* message);
extern UpdateUIFunc UpdateUI; // 声明为外部变量

void StartServer();

#endif // SERVER_H