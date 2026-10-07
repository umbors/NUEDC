# K210 视觉识别与 PID 巡线备份

本目录于 2026-10-07 从所有者桌面 `backup` 文件夹归档，保存全部 13 个原始文件。原文件名与内容均保持不变，校验值见 `SHA256SUMS`。

这是 **K210 / MaixPy** 程序，使用 `KPU`、`fpioa_manager`、LCD 和 `.kmodel` 模型。它作为独立备份保存在 `2021-Nuedc` 分支，不替换该分支已有的比赛程序。

## 文件用途

| 文件 | 用途 |
| --- | --- |
| `boot.py` | 主业务程序：YOLOv2 识别、图像直线回归、PID 偏差计算、串口通信及定时转发 |
| `main.py` | MaixPy 欢迎界面 |
| `pid.py` | `boot.py` 导入的 PID 实现 |
| `out_txm.kmodel`、`anchors_txm.txt`、`lable_txm.txt` | 当前业务代码加载的条码检测模型及参数；标签为 `barcode` |
| `out_zimu.kmodel`、`anchors_zimu.txt`、`lable_zimu.txt` | 字母模型及参数；标签表包含 26 个字母 |
| `out.kmodel`、`anchors.txt`、`lable.txt` | 数字模型及参数；标签表包含数字 0–9，保持原有类别顺序 |
| `oupp.kmodel` | 原始备份中的额外模型；用途未确认，保留原名称 |

## 运行配置与版本边界

`boot.py` 从 `/sd/out_txm.kmodel` 加载模型，按相对路径读取 `anchors_txm.txt`、`lable_txm.txt`，并通过 `from pid import PID` 导入 PID 模块。实际部署时需按所用 MaixPy 固件的启动流程及工作目录放置文件；本目录路径用于 GitHub 归档。

代码将引脚 8/7 映射为 UART1 RX/TX，将引脚 9/10 映射为 UART2 RX/TX；两路串口配置均为 115200。UART 报文采用 `0xAA 0xFF` 帧头以及累加和、累加和的累加校验。

这份备份与仓库现有 K210 主程序不是相同版本，部分 `0xF1` 消息的子类型含义也不同。例如本目录 `check_num()` 将识别编号放在子类型 `0x01` 中，而现有 TM4C 的 `Drv_K210.c` 将该子类型解析为 X 轴方向和偏移量。与比赛系统组合运行前，需要核对对应的控制端协议。

部分原文件时间显示为 2060 年，不能据此认定代码版本日期。此处日期仅表示归档日期。未修改程序逻辑，也未进行硬件运行验证。
