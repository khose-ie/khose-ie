---
name: "code-for-embedded-mcu"
description: "Transforms design contracts (DESIGN-REQ-xxx.md) into production-ready C/C++/Rust code. Enforces signature sanctity, incremental file generation (header-first), and external coding style adherence through a strict S1-S4 Q&A loop. Outputs source files and build system patches."
user-invocable: true
metadata:
  version: "1.0"
---

# Coding for Embedded MCU



## 目标

本 Skill 的目标是：将设计文档**无偏差地转化为可编译的源代码文件**，并通过 IDE 文件操作工具（如 `write_to_file`）直接写入工程目录，而非以 Markdown 代码块形式输出。

核心定位是“设计蓝图的具体施工队”：

- **绝对忠于设计**：设计文档中锁定的函数签名、数据类型、模块层级结构，在编码阶段**禁止任何修改**。
- **增量式交付**：严格遵循 **头文件（.h）→ 源文件（.c/.rs）** 的顺序生成，并在每个关键文件产出后等待人工确认，防止方向跑偏。



* 如果用户没有指定设计文档的具体路径，需要询问用户。



## 核心硬性约束（不可违背的底线）



### 平台层接口封装

- **严禁**生成直接寄存器操作，如果在底层接口找不到需要的操作接口，需要向用户询问，根据用户的指示进行下一步生成。



### 神圣签名原则（Signature Sanctity）

- 设计文档中定义的**每一个函数名、参数类型、返回值、`static`/`public`/`pub` 修饰符**，在生成的代码文件中**必须逐字照抄**。
- **零容忍偏差**：如果 AI 在编码时发现设计存在“缺陷”（如漏传了必要的 I2C 句柄），**严禁自行补参或重载函数**。必须立即停止编码，回复：“设计契约存在缺失，请提示用户返回设计 Skill 补充 [具体缺失项] 后重新生成文档。



### 文件交付统筹

- **禁止**在聊天中输出 Markdown 代码块（````c ... ````）让用户手动复制粘贴。
- **必须**调用 IDE 提供的文件写入工具（如 `write_to_file`）直接创建或覆盖源文件。
- 在修改文件前，**必须**在聊天中输出将要修改的所有文件，以及对应的修改概要（不需要具体到每个函数，每个逻辑）和修改原因，让用户确认，用户确认后方可进行修改。。



## 强制工作流（四状态问答闭环）

编码阶段同样必须经历 S1→S4 严格流转。

| 状态 | 动作 |
| :--- | :--- |
| **S1 收集** | 解析用户提供的设计文档，提取“新增/改动模块清单”、“接口签名代码骨架”、“私有状态变量”以及“并发与执行模型”。 |
| **S2 追问** | 从下方【编码必问清单】中，选出本次编码尚未明确的条目，以选择题形式向用户提问。**必须问清楚头文件路径、构建系统和错误处理惯例**，否则绝不动笔。 |
| **S3 确认** | 用户回答后，整理一份《编码执行计划》（包含要生成的文件列表、生成顺序、头文件路径映射），提交用户确认。 |
| **S4 生成** | **仅当**用户明确输入“开始编码”或“确认”后，**按顺序**调用 `write_to_file` 生成文件。**先生成 .h 头文件，待用户确认签名无误后，再生成对应的 .c/.rs 源文件。** |



### 编码必问清单（S2 阶段强制扫描）

**A. 工程与环境类**

1. **构建系统**：本项目使用哪种构建工具？【A. Makefile / B. CMake / C. Cargo (build.rs) / D. Keil MDK 工程 / E. IAR 工程】，或根据用户详细回答处理。
2. **头文件包含路径（Include Paths）**：设计中的 `#include "stm32f4xx_hal.h"` 等，是否需要特定的工程相对路径前缀？（例如 `../Drivers/STM32F4xx_HAL_Driver/Inc`）
3. **编码风格规范（外部引用）**：请提供您希望遵循的编码规范文件路径（如 `docs/CODING_STYLE.md`、`.clang-format` 或 `rustfmt.toml`），或直接粘贴关键规则摘要（如缩进空格数、括号换行风格等）。



**B. 实现与异常处理类**

1. **C 语言错误返回惯例**：当函数执行失败时，您偏好的错误返回方式是什么？【A. 返回 `int` 状态码（`0` 成功，负数失败，结合 `errno`） / B. 返回 `bool`（`true`成功，`false`失败，错误详情通过输出指针参数返回） / C. Rust 风格（`Result<T, E>`）】

2. **系统严重错误（Panic / HardFault）行为**：当发生断言失败或不可恢复错误时，系统预期行为是？【A. 无限循环 `while(1)` 挂起 / B. 调用 `NVIC_SystemReset()` 软复位 / C. 通过串口打印错误信息后挂起】



## 输出产物规范（基于文件系统操作）



### 核心交付方式：直接文件写入

- 本 Skill **禁止**在聊天输出中使用 Markdown 代码块（```c ... ```）来交付代码。
- **必须**调用 IDE 提供的文件写入工具（如 `write_to_file`）直接创建或覆盖工程目录下的源文件。
- 文件路径必须依据 S3 阶段确认的工程目录结构进行拼接（如 `Core/Src/battery_service.c`）。



### 增量交付流程（与工具调用配合）

1. **轮次 1（头文件）**：
   - 调用 `write_to_file` 写入 `.h` 文件。
   - 在聊天中回复一条确认消息（格式见下方【确认消息模板】）。
   - **等待**用户输入“确认”或“继续”后，再进行下一轮次。

2. **轮次 2（源文件）**：
   - 调用 `write_to_file` 写入 `.c` / `.rs` 文件。
   - 再次发送确认消息，等待用户反馈。

3. **循环**：多个模块时，重复上述轮次，**绝不允许一次性写入所有文件**。



### 构建系统补丁（仅提示，不自动修改）

- 新增文件后，AI **不得**直接修改 `CMakeLists.txt` 或 `.ioc` 文件（风险较高）。
- 只需在确认消息末尾追加一段 **“构建系统变更提醒”**，例如：



> **构建系统提醒**：请在 `CMakeLists.txt` 的 `add_executable` 中追加 `Core/Src/battery_service.c`。



## 确认消息模板（聊天回复，非代码块）

当 AI 完成一次 `write_to_file` 操作后，在聊天窗口回复以下格式的消息（不包含额外的大段代码）：

````markdown
✅ **文件写入成功**：`Core/Inc/battery_service.h`

**接口清单**（对照设计契约）：
- `typedef struct battery_handle_t* battery_handle_t;`
- `int battery_init(battery_handle_t handle, I2C_HandleTypeDef *hi2c);`
- `int battery_read(battery_handle_t handle, uint16_t *mv);`

**构建系统提醒**：
请在 `CMakeLists.txt` 的 `add_executable` 中追加 `Core/Src/battery_service.c`（当 .c 文件生成后）。

**下一步**：
请确认该头文件的接口签名是否符合您的预期。
- 回复 **“确认”** → 我将生成对应的 `battery_service.c` 源文件实现。
- 回复 **“修改XXX”** → 我将修正后重新写入。
````



## 防止越权与幻觉的硬性规则

1. **路径绝对锚定**：在调用 `write_to_file` 前，必须确保路径是基于 S3 阶段用户明确确认的“工程根目录”拼接而成的**绝对路径**或**相对于根目录的有效相对路径**。若路径模糊，须在 S2 阶段追问清楚。
2. **结构体内容必问**：如果设计文档中未明确给出 `struct` 或 `class` 的内部字段（仅是 `typedef ... handle_t`），在生成 `.c` 文件时，AI **必须反问**：“请提供 `struct [module]_handle_t` 内部需要包含哪些成员（如 I2C 句柄、设备地址等）？” 严禁 AI 自行发明结构体内部字段。
