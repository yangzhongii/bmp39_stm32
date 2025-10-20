#include "main.h"
#include "bmp390.h"
#include <stdio.h>
#include <string.h>

I2C_HandleTypeDef hi2c1;  // I2C1
UART_HandleTypeDef huart2;  // USART2

// UART打印
void print_uart(const char *fmt, ...) {
    char buf[128];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();  // Cube生成
    MX_GPIO_Init();
    MX_I2C1_Init();  // 100kHz
    MX_USART2_UART_Init();  // 115200

    bmp390_data_t sensor_data;

    // 初始化BMP390
    if (bmp390_init(&hi2c1) != 0) {
        print_uart("BMP390 Init Failed!\r\n");
        while(1);
    }
    print_uart("BMP390 Initialized. Drone Altitude Monitoring...\r\n");

    while (1) {
        if (bmp390_read_data(&hi2c1, &sensor_data) == 0) {
            print_uart("Temp: %.2f°C | Press: %.2fhPa | Alt: %.2fm\r\n",
                       sensor_data.temperature, sensor_data.pressure, sensor_data.altitude);
            // 无人机应用：如果高度变化>阈值，触发控制 (e.g., 调整电机)
            if (fabsf(sensor_data.altitude - 0.0f) > 1.0f) {  // 示例阈值
                print_uart("Altitude Alert: Adjust Motors!\r\n");
            }
        } else {
            print_uart("Read Error!\r\n");
        }
        HAL_Delay(500);  // 500ms循环
    }
}

// CubeMX生成的初始化 (I2C1: PB6 SCL, PB7 SDA)
void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK) Error_Handler();
}

// UART初始化 (同前例)
void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    // ... (标准配置)
    HAL_UART_Init(&huart2);
}

// GPIO for I2C (MSP)
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (hi2c->Instance == I2C1) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_I2C1_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}