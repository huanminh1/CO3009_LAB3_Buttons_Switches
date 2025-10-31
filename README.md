# MICROCONTROLLER - MICROPROCESSOR  
## LABORATORY 3: LAB3_Buttons_Switches

## 1. FSM
![FSM](https://github.com/huanminh1/CO3009_LAB3_Buttons_Switches/blob/main/Imagine/State%20Machine.png)

Mô tả:
- FSM (Finite State Machine) điều khiển trạng thái của hệ thống đèn giao thông (ví dụ: INIT, RED_GREEN, RED_AMBER, GREEN_RED, AMBER_RED, và các trạng thái manual/modification).
- Mỗi trạng thái thực hiện:
  - Output: cập nhật LED (đèn giao thông) và 7-segment.
  - Input: kiểm tra các nút (button1 chọn mode, button2 tăng giá trị, button3 set).
## 2. Flowchart
![Flowchart](https://github.com/huanminh1/CO3009_LAB3_Buttons_Switches/blob/main/Imagine/Flowchar%20_ManualLed.png)

Mô tả:
- Flowchart minh họa luồng thao tác khi vào chế độ manual: nhấp nháy LED tương ứng, tăng giá trị bằng button2, xác nhận bằng button3, thoát bằng button1 (hoặc giữ button1 > 1s để về auto).

## 3. Schematic
The code was simulated in **Proteus 8.10** using STM32F103C6. Here are the simulation of exercises.
![Proteus Simulation](https://github.com/huanminh1/CO3009_LAB3_Buttons_Switches/blob/main/Imagine/Proteus_Lab3_FullEX.png)

- Sơ đồ kết nối bao gồm:
  - STM32F103C6 (PAx/PBx pins) nối tới: 12 LED (4R/4Y/4G), 4 x 7-seg (common anode/cathode tùy thiết kế), 3 buttons.
  - Các chân enable cho mỗi digit 7-seg (ENx) tách riêng cho main/side road.


## 4. Source Folder Structure (actual)
Dưới đây là cấu trúc thư mục thực tế trong `Core/` dùng cho project này.

```text
Core/
│
├── Inc/                        # Header files
│   ├── common.h
│   ├── input_reading.h
│   ├── led_display.h
│   ├── main.h
│   ├── software_timer.h
│   ├── stm32f1xx_hal_conf.h
│   ├── stm32f1xx_it.h
│   └── traffic_light.h
│
├── Src/                        # Source files
│   ├── common.c
│   ├── input_reading.c         # Debounce + button buffers + is_button_pressed API
│   ├── led_display.c           # 7-seg scan, displayTrafficLight, helpers
│   ├── main.c                  # Project entry; initialize peripherals, main loop
│   ├── software_timer.c        # setTimer/runTimer helper, timer flags
│   ├── stm32f1xx_hal_msp.c     # HAL MSP init
│   ├── stm32f1xx_it.c          # Interrupt handlers (SysTick, TIM)
│   ├── syscalls.c
│   ├── sysmem.c
│   ├── system_stm32f1xx.c      # System clock/config
│   └── traffic_light.c         # FSM + traffic control logic
│
└── Startup/
    └── startup_stm32f103c6ux.s # Startup assembly
```

## 5. Build & Simulation
1. Mở project bằng STM32CubeIDE. Kiểm tra cấu hình clock, GPIO (pull-up/pull-down) và timer.
2. Build project (`Project > Build Project`). Nếu gặp lỗi liên quan đến kiểu dữ liệu shared (ví dụ `LightState`), đảm bảo header `traffic_light.h` được include trước nơi dùng.
3. Nạp file .hex vào Proteus. Trong Proteus, thêm model STM32F103C6 và mapping pin tương ứng.
4. Kiểm tra:
   - Timer quét 7-seg (tần số ~2–5ms per digit).
   - Hàm đọc nút được gọi đều (mỗi 10ms) để debounce.
   - FSM hoạt động theo flowchart, các mode chuyển khi nhấn button1, chỉnh bằng button2, set bằng button3.

## 6. Tips & Debug
- Nếu 7-seg không hiển thị: kiểm tra enable lines (EN pins) và hàm `Scan_2digit` có `break` cho mỗi case.
- Nếu nút bị nhận nhấn ngay khi khởi động: kiểm tra pull-up/pull-down cấu hình và giá trị macro `BUTTON_IS_PRESSED`.
- Để multiplex không dùng `HAL_Delay`, dùng `setTimer(TIMER_SCAN_..., ms)` + kiểm tra `isFlag()` trong `led_display.c`.
- Giữ cấu trúc: input_reading (debounce) → traffic_light (FSM) → led_display (output).

