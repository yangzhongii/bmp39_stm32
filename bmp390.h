#ifndef BMP390_H
#define BMP390_H

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <math.h>

// BMP390 I2C地址 (默认0x77)
#define BMP390_I2C_ADDR          0x77

// 寄存器地址 (基于Bosch BMP3 API)
#define BMP390_REG_CHIP_ID       0x00  // 0x50 for BMP390
#define BMP390_REG_ERR_REG       0x02
#define BMP390_REG_STATUS        0x03
#define BMP390_REG_CTRL_MEAS     0x1D
#define BMP390_REG_CONFIG        0x1F
#define BMP390_REG_CTRL_ADV      0x1E
#define BMP390_REG_PRESSURE_LSB  0x04
#define BMP390_REG_PRESSURE_MSB  0x05
#define BMP390_REG_PRESSURE_XLSB 0x06
#define BMP390_REG_TEMP_LSB      0x07
#define BMP390_REG_TEMP_MSB      0x08
#define BMP390_REG_TEMP_XLSB     0x09
#define BMP390_REG_CALIB_DATA    0x10  // 校准数据起始

// 配置值
#define BMP390_ODR_62_5HZ        0x05  // 输出数据率
#define BMP390_OSR_PRESS_4X      0x03  // 压力过采样
#define BMP390_OSR_TEMP_2X       0x01  // 温度过采样
#define BMP390_IIR_FILTER_2      0x01  // IIR滤波
#define BMP390_CHIP_ID_VAL       0x50  // BMP390 ID

// 返回类型
typedef int8_t bmp390_status_t;

// 传感器数据结构体
typedef struct {
    float temperature;  // °C
    float pressure;     // hPa
    float altitude;     // m (计算)
} bmp390_data_t;

// 函数原型
bmp390_status_t bmp390_init(I2C_HandleTypeDef *hi2c);
bmp390_status_t bmp390_read_data(I2C_HandleTypeDef *hi2c, bmp390_data_t *data);
bmp390_status_t bmp390_deinit(I2C_HandleTypeDef *hi2c);
float bmp390_calc_altitude(float pressure_hpa);  // 高度计算

#endif /* BMP390_H */