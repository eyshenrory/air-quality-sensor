# LOG

Дневник проекта: что сделано, что пошло не так, чему научился.

## 2026-10-10 — Плата видна в DFU из WSL

- Поставил usbipd-win (Windows), usbutils и dfu-util (WSL).
- Разобрался по RM0383 §2.4, как ножки BOOT0/BOOT1 выбирают, откуда стартует STM32F411: Flash, system memory (загрузчик ST) или SRAM. Ножки защёлкиваются после выхода из сброса.
- Black Pill в DFU: `0483:df11`, проброшен в WSL через `usbipd attach --auto-attach`. `dfu-util -l` видит Internal Flash по `0x08000000`.
- **Проблема:** первый `dfu-util -l` завис намертво (процесс в состоянии `D`). Windows считала устройство отключённым (`Shared`), а Linux держал его подключённым: полуоткрытое соединение USB/IP. В `dmesg` знакомство с устройством застряло на `SetAddress`, рядом были ошибки сети WSL `getaddrinfo() failed`. Помогли detach через `/sys/devices/platform/vhci_hcd.0/detach` и повторный attach. Корневая причина не доказана.
- Без `sudo` dfu-util не может открыть устройство: нужно udev-правило.

**Дальше:** тулчейн `arm-none-eabi-gcc` и путь от сброса до `main()`.
