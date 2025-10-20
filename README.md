# BMP390 altitude and temperature calculator based on STM32F426

This code is modified from https://github.com/DuePonto/BMP388-STM32-HAL
## Poject Framework
The project follows the standard STM32CubeIDE structure, divided into the driver layer (BMP390X), main program, and HAL configuration. Below is the directory tree :
```
BMP390_Drone_Altimeter/
├── Core/
│   ├── Inc/                  # Header files
│   │   ├── main.h
│   │   ├── bmp390.h          # BMP390X driver header
│   │   └── stm32f4xx_it.h    # Interrupt handlers (Cube-generated)
│   ├── Src/                  # Source files
│   │   ├── main.c            # Main program: initialization, measurement loop, UART output
│   │   ├── bmp390.c          # BMP390X driver implementation: register read/write, compensation algorithm
│   │   ├── stm32f4xx_it.c    # Interrupt callbacks (Cube-generated)
│   │   └── system_stm32f4xx.c # System clock (Cube-generated)
├── Drivers/                  # HAL library (Cube-generated)
│   ├── STM32F4xx_HAL_Driver/
│   │   └── ... (standard HAL files)
│   └── CMSIS/
│       └── ... (core CMSIS)
├── BMP390_Drone_Altimeter.ioc # CubeMX project file (configures I2C1, USART2)
├── README.md                 # Project documentation (this Markdown)
└── BMP390_Drone_Altimeter.map # Build map file (optional)
```