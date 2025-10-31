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
- Flowchart minh họa luồng thao tác khi vào chế độ manual:
  - Đèn màu tương ứng nhấp nháy ở 2 Hz để báo chế độ chỉnh.
  - Hai 7‑seg hiển thị giá trị thời gian chỉnh; hai 7‑seg còn lại hiển thị mã mode (vd "02").
  - Button2: tăng giá trị (1..99). Button3: xác nhận (lưu) giá trị.
  - Giữ button1 > 1s: thoát về chế độ tự động (start_auto_mode).
  
## 3. Schematic
The code was simulated in **Proteus 8.10** using STM32F103C6. Here are the simulation of exercises.
![Proteus Simulation](https://github.com/huanminh1/CO3009_LAB3_Buttons_Switches/blob/main/Imagine/Proteus_Lab3_FullEX.png)

- Thành phần chính: STM32F103C6, 12 LED (R/Y/G per direction), 4 x 2‑digit 7‑seg, 3 nút.
- Lưu ý nối:
  - Mỗi segment (a..g, dp) chung cho cả digit; dùng chân EN riêng cho từng digit (multiplex).
  - Tách enable cho main road và side road (2 digit mỗi đường).
  - Buttons: khuyến nghị dùng pull‑up (active‑low); chỉnh macro `BUTTON_IS_PRESSED` tương ứng trong `input_reading.c`.
- Nếu mô phỏng Proteus không hiển thị đúng:
  - Kiểm tra chân EN, kiểu common anode/cathode, và tên chân (SEG_x_M_Pin / SEG_x_S_Pin).
  - Đảm bảo VDDA/VSSA và GND nối đúng.

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

## 6. Troubleshooting
- 7‑seg không nhảy số: kiểm tra multiplex (Scan_2digit), chân EN, và đảm bảo mỗi case trong switch có `break`.
- Nút báo nhấn ngay khi khởi động: kiểm tra cấu hình pull‑up/pull‑down và macro `BUTTON_IS_PRESSED`.
- Biến toàn cục khởi tạo bằng biến khác gây lỗi: khởi tạo bằng hằng hoặc gán trong hàm init (không khởi tạo global bằng biến runtime).
- Nếu FSM "dừng" khi vào chế độ manual: đảm bảo FSM vẫn update display và có logic chuyển trở lại auto khi cần (ví dụ khi nhấn giữ button1 > 1s).

