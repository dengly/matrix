#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libfahw.h"

int main(int argc, char ** argv) 
{
    int pin = GPIO_PIN(7); 
    int i, value, board;
    int ret = -1;
    
    if ((board = boardInit()) < 0) {
        printf("Fail to init board\n");
        return -1;
    }
    if (board == BOARD_NANOPC_T2 || board == BOARD_NANOPC_T3)
        pin = GPIO_PIN(15);

    int cnt = sizeof(argc) / sizeof(argc[0]);

    if (cnt == 2){
        // 获取状态
        pin = GPIO_PIN(atoi(argv[1]));
    } else if (cnt == 3){
        // 设置状态
        pin = GPIO_PIN(atoi(argv[1]));
        value = atoi(argv[2]);
        if (value % 2) {
            value = GPIO_HIGH;
        } else {
            value = GPIO_LOW;
        }
    } else {
        // 参数错误
        printf("Parameter error\n");
        return -1;
    }
    if ((ret = exportGPIOPin(pin)) == -1) {   
        printf("exportGPIOPin(%d) failed\n", pin);
    }
    if ((ret = setGPIODirection(pin, GPIO_OUT)) == -1) {
        printf("setGPIODirection(%d) failed\n", pin);
    }
    if (cnt == 2){
        // 获取状态
        if ((value = getGPIOValue(pin)) >= 0) {
            printf("GPIO_PIN(%d) value is %d\n", pin, value);
        } else {
            printf("getGPIOValue(%d) failed\n", pin);
        }
    }else if (cnt == 3){
        // 设置状态
        if ((ret = setGPIOValue(pin, value)) > 0) {
            printf("GPIO_PIN(%d) value is %d\n", pin, value);
        } else {
            printf("setGPIOValue(%d) failed\n", pin);
        }
    }

    unexportGPIOPin(pin);
    return 0;
}
