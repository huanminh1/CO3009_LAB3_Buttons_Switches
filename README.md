# MICROCONTROLLER - MICROPROCESSOR  
## LABORATORY 3: LAB3_Buttons_Switches

## 1. Schematic
The code was simulated in **Proteus 8.10** using STM32F103C6. Here are the simulation of exercises.

![Proteus Simulation](https://github.com/huanminh1/CO3009_LAB3_Buttons_Switches/blob/main/Imagine/Proteus_Lab3_FullEX.png)

## 4. Source Folder Structure

The main code for each exercise is organized in the `Core/` directory as follows:

```text
Core/
│
├── Src/                        # Main embedded source code
│   ├── exercise1.c             # Exercise 1 implementation
│   ├── exercise2.c             # Exercise 2 implementation
│   ├── exercise3.c             # Exercise 3 implementation
│   ├── exercise4.c             # Exercise 4 implementation
│   ├── exercise5.c             # Exercise 5 implementation
│   ├── exercise6.c             # Exercise 6 implementation
│   ├── exercise7.c             # Exercise 7 implementation
│   ├── exercise8.c             # Exercise 8 implementation
│   ├── exercise9.c             # Exercise 9 implementation
│   ├── exercise10.c            # Exercise 10 implementation
│   ├── software_timer.c        # Common software timer module
│   ├── display7SEG.c           # Common 7-segment display module (if present)
│   ├── main.c                  # Entry point, macro to select exercise
│   ├── stm32f1xx_hal_msp.c     # HAL MSP init
│   ├── stm32f1xx_it.c          # Interrupt handlers
│   ├── syscalls.c              # System call stubs
│   ├── sysmem.c                # System memory allocation
│   └── system_stm32f1xx.c      # System clock/config
│
├── Inc/                        # Header files for each exercise and main
│   ├── exercise1.h
│   ├── exercise2.h
│   ├── exercise3.h
│   ├── exercise4.h
│   ├── exercise5.h
│   ├── exercise6.h
│   ├── exercise7.h
│   ├── exercise8.h
│   ├── exercise9.h
│   ├── exercise10.h
│   ├── software_timer.h        # Common software timer header
│   ├── main.h
│   ├── stm32f1xx_hal_conf.h
│   └── stm32f1xx_it.h
│
└── Startup/
    └── startup_stm32f103c6ux.s   # Startup assembly code
