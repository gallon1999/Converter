#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include "pindef.h"
#include "inc.h"
#define GPIO_CHIP "/dev/gpiochip4"  // Raspberry Pi 5 預設 GPIO Chip
#define GPIO_PIN  17  // GPIO17

int main() {
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int ret;
    printf("GPIO17_PIN %d\n", GPIO17_PIN);
    // 打開 GPIO chip
    chip = gpiod_chip_open(GPIO_CHIP);
    if (!chip) {
        perror("Failed to open GPIO chip");
        return 1;
    }

    // 取得 GPIO line (GPIO17)
    line = gpiod_chip_get_line(chip, GPIO_PIN);
    if (!line) {
        perror("Failed to get GPIO line");
        gpiod_chip_close(chip);
        return 1;
    }

    // 設置 GPIO 為輸出模式
    ret = gpiod_line_request_output(line, "blink", 0);
    if (ret < 0) {
        perror("Failed to request GPIO as output");
        gpiod_chip_close(chip);
        return 1;
    }

    // 閃爍 10 次
    for (int i = 0; i < 10; i++) {
        gpiod_line_set_value(line, 1);  // 高電平
        printf("LED ON\n");
        sleep(1);

        gpiod_line_set_value(line, 0);  // 低電平
        printf("LED OFF\n");
        sleep(1);
    }

    // 釋放 GPIO
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return 0;
}
