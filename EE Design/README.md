# Small Design / EE Design

本目录于 2026-10-07 从本地 `D:\Codex\EE Design` 归档到 `umbors/NUEDC` 的 `Small-Design` 分支。分支基于 `main` 的 `cd19d7c6d6b7288f86a3f403c277da499f89dcf0`，既有 NUEDC 工程继续保留；新增资料集中在 `EE Design/`。

## 目录

| 目录 | 内容及入口 |
| --- | --- |
| `300yuan/` | Altium 工程 `300yuan.PrjPcb`、原理图、PCB、自定义元件库、OutJob、PDF/CSV 与原始 ZIP。`300yuan.zip` 内 PCB 与外部 PCB 不同，均保留。 |
| `HoloCubic/` | 硬件、Gerber/BOM、STEP/STP、SolidWorks、STL 等机械资料。可编辑 PCB/原理图 JSON 在 `0.Ref/HoloCubic+电池+扬声器版_4e54f4e5b5ce4ee084e1ccb19972132a.zip` 中；`4.3D Model.zip` 含模型源文件。 |
| `STM32L431RCT6 (8MHz HSE)/Example/` | ADC_DMA、LCD_0.96inch、LCD_1.14inch、RGB_LED、RTC、SDIO+FATFS、SPI2_FLASH、TEST、USART 共 9 套示例，保留各自 CubeMX、Keil、HAL/CMSIS/BSP 依赖。 |
| `STM32L431RCT6 (8MHz HSE)/eide/` | RGB_LED 对应 EIDE 工程、工作区及所需头文件配置。 |
| `STM32L431RCT6 (8MHz HSE)/eide-uart/` | USART 对应 EIDE 工程、工作区及所需头文件配置。 |

HoloCubic 的 `2.Software`、`3.3D-Model`、`4.Others` 原来为空，因此 Git 中没有这些空目录；没有把它描述为包含完整固件。

## 首次打开

1. 获取 `Small-Design` 分支，在 `EE Design/` 内打开相应工程。仓库历史目录存在大小写不同的同名路径，在 Windows 上可仅检出本目录以避免旧工程路径冲突：

   ```powershell
   git clone --no-checkout --single-branch --branch Small-Design https://github.com/umbors/NUEDC.git NUEDC-Small-Design
   cd NUEDC-Small-Design
   git sparse-checkout init --cone
   git sparse-checkout set "EE Design"
   git checkout Small-Design
   ```

2. Altium 打开 `300yuan.PrjPcb`；HoloCubic 按原始 ZIP 内说明导入 JSON，机械源使用对应 CAD 软件打开。
3. STM32 用 STM32CubeMX 打开各示例的 `.ioc`，或 Keil 打开 `MDK-ARM/*.uvprojx`。原 Keil 配置使用 ARMCC 5.06 update 7 build 960；多数工程指定 STM32L4xx_DFP 2.0.0，RGB_LED 指定 2.6.1。驱动、库和 `RTE` 已一起保存。
4. EIDE 工作区引用同一目录下的 Example 工程。配置中的 `../example/...` 与实际 `Example` 大小写不同；两套烧录配置的 `targetName` 为 `stm32l432kc`，而工程目标为 STM32L431RCT6。归档保持原样，实际构建或烧录前应核对路径和芯片。

本次仅归档与核对文件，没有安装工具、重新编译或烧录验证。`Example/keilclean.bat` 是原有历史脚本，包含删除 `.sct` 的规则，本次没有运行。

## 保存范围与校验

保存 1087 个原始文件，约 151.15 MiB；上传副本排除 319 个可重建编译中间文件、报告及个人 IDE/Windows 状态，约 95.26 MiB。本地原目录未修改。

`.hex`、`.axf`、`.bin`、`.s19` 固件成品与 `.sct` 链接脚本保留在原位置。重复出现在各示例中的 HAL/CMSIS 等依赖不做去重，确保各工程的相对目录结构完整。`.gitattributes` 禁止文本换行转换，`SHA256SUMS` 列出所有保存文件的 SHA-256；`archive-manifest.json` 记录原文件清单及排除原因。

本目录是已有资料合集，并不据此声明全部内容为本仓库作者原创。原工程中的第三方许可证、厂商模板与归属说明均保留；使用或再分发时应遵循各自许可。
