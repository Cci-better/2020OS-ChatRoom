# PSP 2.1

| 阶段 | 预估时间（分钟） | 实际时间（分钟）|
| :-: | :-: | :-: |
| **计划：明确需求和其他因素，估计以下的各个任务需要多少时间** | **20** | **30** |
| **开发** | **400** |  |
| 需求分析（包括学习新技术、新工具的时间） | 60 | 60 |
| 生成设计文档（整体框架的设计、各模块的接口、用时序图、快速原型等方法） | 30 |  |
| 设计复审（和同事审核设计文档，或者自己复审） | 10 |  |
| 代码规范（为目前的开发制定或选择合适的规范） | 10 |  |
| 具体设计（用伪代码、流程图等方法设计具体模块） | 60 |  |
| 具体编码 | 180 |  |
| 代码复审 | 20 |  |
| 测试（自我测试，修改代码，提交修改） | 30 |  |
| **报告** | **80** |  |
| 测试报告（发现了多少 Bug ，修复了多少） | 10 |  |
| 计算工作量（多少行代码，多少次签入，多少测试用例，其他工作量） | 10 |  |
| 事后总结，并提出改进计划（包括写文档、写博客的时间） | 60 |  |
| **总耗时** | 500 |  |

# 需求

聊天室

用户通过命令行参数或键入方式输入服务器的 IP 地址和端口号连接到服务器。

每个用户可以设定自己的 ID，ID 可以通过命令行参数或用户键入给定，如果用户输入的 ID 为空则使用用户端 IP 地址作为默认 ID，服务器保证 ID 不重复，若重复则要求客户端重新输入 ID。

加入聊天室后，任何一个用户发送的信息将会被实时显示在其他用户的屏幕上。

聊天框有命令系统：任何以 # 开头的输入内容都将被作为命令处理。使用 ## 发送单独的 # 号。

服务器保存用户的聊天记录，保存数量可以由服务器的配置文件指定。用户端可以使用 #h <条数> 查看聊天记录。若条数为空则默认显示 30 条。

聊天室支持文件收发：用户端使用 #f <文件路径> 发送文件。发送的文件保存在服务器端，在聊天记录中以 [用户ID] 发送了文件 <文件名> 显示。用户可以使用 #d <文件名> 下载需要的文件，若文件名为空则默认下载最新的文件，若文件不存在则提示。

服务器支持 MOTD，MOTD 可通过配置文件指定，其内容可保存在文件中。

匿名聊天支持：使用#A <消息内容> 发送匿名消息，匿名消息不显示用户 ID。

复读功能：使用 #+ 发送聊天记录中的最后一条消息。

# 设计
