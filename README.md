# MICROCONTROLLER - MICROPROCESSOR  
## LABORATORY 3: LAB3_Buttons_Switches

## 1. FSM
![FSM](https://github.com/huanminh1/CO3009_LAB3_Buttons_Switches/blob/main/Imagine/State%20Machine.png)

Mô tả & hướng dẫn:
- FSM (Finite State Machine) điều khiển trạng thái của hệ thống đèn giao thông (ví dụ: INIT, RED_GREEN, RED_AMBER, GREEN_RED, AMBER_RED, và các trạng thái manual/modification).
- Mỗi trạng thái thực hiện:
  - Output: cập nhật LED (đèn giao thông) và 7-segment.
  - Input: kiểm tra các nút (button1 chọn mode, button2 tăng giá trị, button3 set).
- Hướng dẫn sử dụng:
  - Đọc file `Core/Inc/traffic_light.h` để xem enum `LightState` và prototype các hàm FSM.
  - Xem `Core/Src/traffic_light.c` để hiểu chuyển trạng thái, thời gian mặc định và cách gọi `display`/`start_auto_mode`/`start_manual_mode`.
  - Khi phát triển: tránh thao tác I/O trực tiếp trong hàm đọc nút; chỉ cập nhật buffer/flag ở `input_reading.c`, FSM sử dụng các hàm `is_button_pressed()` / `is_button_pressed_1s()` để quyết định chuyển trạng thái.

## 2. Flowchart
![Flowchart](https://github.com/huanminh1/CO3009_LAB3_Buttons_Switches/blob/main/Imagine/Flowchar%20_ManualLed.png)

Mô tả & hướng dẫn:
- Flowchart minh họa luồng thao tác khi vào chế độ manual: nhấp nháy LED tương ứng, tăng giá trị bằng button2, xác nhận bằng button3, thoát bằng button1 (hoặc giữ button1 > 1s để về auto).
- Hướng dẫn kiểm thử:
  - Chạy mô phỏng; nhấn button1 để chuyển qua các mode (1→2→3→4).
  - Ở mode chỉnh (2,3,4): nhấn button2 để tăng, kiểm tra 7-seg hiển thị giá trị đang chỉnh, nhấn button3 để lưu.
  - Giữ button1 > 1s để thoát về chế độ tự động (auto).
- Mẹo phát triển:
  - Tách rõ: đọc nút (debounce) —> FSM xử lý —> display update. Điều này giúp flowchart dễ theo dõi và code modular.

## 3. Schematic
The code was simulated in **Proteus 8.10** using STM32F103C6. Here are the simulation of exercises.
![Proteus Simulation](https://github.com/huanminh1/CO3009_LAB3_Buttons_Switches/blob/main/Imagine/Proteus_Lab3_FullEX.png)

Mô tả & hướng dẫn:
- Sơ đồ kết nối bao gồm:
  - STM32F103C6 (PAx/PBx pins) nối tới: 12 LED (4R/4Y/4G), 4 x 7-seg (common anode/cathode tùy thiết kế), 3 buttons.
  - Các chân enable cho mỗi digit 7-seg (ENx) tách riêng cho main/side road.
- Hướng dẫn khớp phần cứng và phần mềm:
  - Kiểm tra cấu hình chân trong `Core/Inc/main.h` và `MX_GPIO_Init()` trong `Core/Src/main.c`.
  - Nếu mô phỏng không hiện đúng 7-seg: kiểm tra multiplex (Scan_2digit / timer hoặc setTimer), enable lines, và định nghĩa tên pin (`SEG_x_M_Pin`, `SEG_x_S_Pin`, `EN_x`).
  - Buttons nên dùng pull-up (active-low) hoặc pull-down tùy thiết kế; điều chỉnh macro `BUTTON_IS_PRESSED` trong `input_reading.c`.
- Proteus tips:
  - Dùng đúng package STM32F103C6 và cấu hình clock phù hợp.
  - Kết nối nguồn VDDA/VSSA cho 7-seg nếu cần show sáng chính xác.

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

Ghi chú:
- Các file `input_reading.c` và `traffic_light.c` phải làm việc cùng nhau qua API (ví dụ `is_button_pressed()`, `is_button_pressed_1s()`), không gọi trực tiếp FSM từ hàm đọc nút.
- `led_display.c` chứa 7-seg multiplex logic (Scan_2digit) và các hàm enable/disable digit. Quét 7-seg nên được gọi định kỳ (timer hoặc software timer).

## 5. Build & Simulation
1. Mở project bằng STM32CubeIDE. Kiểm tra cấu hình clock, GPIO (pull-up/pull-down) và timer.
2. Build project (`Project > Build Project`). Nếu gặp lỗi liên quan đến kiểu dữ liệu shared (ví dụ `LightState`), đảm bảo header `traffic_light.h` được include trước nơi dùng.
3. Nạp file .elf vào Proteus (hoặc chạy debug trong IDE). Trong Proteus, thêm model STM32F103C6 và mapping pin tương ứng.
4. Kiểm tra:
   - Timer quét 7-seg (tần số ~2–5ms per digit).
   - Hàm đọc nút được gọi đều (mỗi 10ms) để debounce.
   - FSM hoạt động theo flowchart, các mode chuyển khi nhấn button1, chỉnh bằng button2, set bằng button3.

## 6. Tips & Debug
- Nếu 7-seg không hiển thị: kiểm tra enable lines (EN pins) và hàm `Scan_2digit` có `break` cho mỗi case.
- Nếu nút bị nhận nhấn ngay khi khởi động: kiểm tra pull-up/pull-down cấu hình và giá trị macro `BUTTON_IS_PRESSED`.
- Để multiplex không dùng `HAL_Delay`, dùng `setTimer(TIMER_SCAN_..., ms)` + kiểm tra `isFlag()` trong `led_display.c`.
- Giữ cấu trúc: input_reading (debounce) → traffic_light (FSM) → led_display (output).

---
Nếu cần, tôi có thể tạo README chi tiết hơn cho từng file (mô tả hàm chính trong mỗi file) hoặc cung cấp checklist debug cho Proteus/STM32CubeIDE.
