
# <center>HRM游戏制作报告</center>
<center>计48-经42 王鹏杰</center>
<center>计48-经42 高雅菁</center>

—————————————————————————————————————————————
## 一、 游戏概述
<ol>

**本游戏基于Human Resource Machine进行改编，共分为五关。前三关为固定关卡，后两关为自由创新关卡。**

</ol>
<div STYLE="page-break-after: always;"></div>

## 二、设计逻辑
<ol>
 按照玩家真实游玩体验一步一步梳理游戏运行逻辑：

  **1. 关卡选择：** 
   是否通过；选择关卡判断；游戏结束返回关卡选择界面
  **2. 进入游戏内部：**
  1. 显示的内容
  level；关卡描述；inbox；outbox；carpet；hand；可以使用的指令键盘输入；使用start启动
  
  2. 具体操作实现逻辑
   **inbox：** 判定inbox是不是空的；如果是jump就可以空；inbox末尾赋值给hand；inbox末尾删除
   **outbox：** 判定hand有没有东西；hand添加outbox最后一个；hand清空
   **copyto：** 判定hand是不是空的；判定para是不是超范围；覆盖carpet里面的内容；hand不清空
   **copyfrom：** 判定para是不是超范围；判定carpet是不是空的；把carpet内容赋给hand
   **add：** 判定hand是不是空的；判定参数；判定carpet；判定是不是数；hand=hand+carpet
   **sub：** 同理
   **jump：** 先判定那个指令存不存在；是不是在jump之前；通过一个i来跳步骤；inbox空就不执行
   **jumpifzero：** 先判定参数；再判定指令是否存在；判定手里有没有东西；再判定hand里面是不是zero；执行jump
   逐步模拟，输入结束之后才开始模拟
  
  3. 返回success和fail

<div STYLE="page-break-after: always;"></div>
</ol>

## 三、代码工程结构
<ol>
<div STYLE="page-break-after: always;"></div>
</ol>

## 四、游戏界面设计
<ol>
游戏界面采用Qt Creator实现。

### 1. 游戏首页
  首页中间是游戏名称，其下分为三个按钮：PLAYGAME——选择关卡，LOADGAME——初始化游戏，EXIT——退出游戏。
  用户首先需要点击LOADGAME，分别上传levelinfo（关卡信息）和archive（游戏日志），也可选择autoload一键上传。随后点击back返回首页点击PLAYGAME选择关卡。倘若没有初始化游戏就点击PLAYGAME则会出现“You've not load game info”的提示框。

  进入PLAYGAME关卡选择界面后，可看见LEVEL1-5五个选项，如果上传的游戏日志，相应的关卡后会显示PASSED。
  用户可选择想要游玩的关卡，倘若尚未通过前置关卡则会出现“You've not passed previous level”的提示框。

  选择关卡后正式进入游戏内部界面。界面上包括五个模块：
  LOG：在关卡开始之前呈现关卡信息描述，在用户完成输入点击运行后逐步呈现当前执行的指令。
  InboxBar：输入传送带，随着每一步指令的读取实时更新。
  Carpet：空地，随着每一步指令的读取实时更新
  OutboxBar：输出传送带，随着每一步指令的读取实时更新。
  机器人程序：用户在此处输入完整指令后点击START运行测试。
  
  用户输入完成开始运行后，界面进行逐步模拟：
  机器人是一个可移动，手部可旋转的小人，右手上有储存数字的方框。随着指令的读取，机器人可实时连续移动至inboxbar、outboxbar、carpet旁边，对右手方框中储存的数字进行操作。

<div STYLE="page-break-after: always;"></div>
</ol>

## 五、游戏测试（前三关）
<ol>

### 1. Success
### 2. Error Instruction
### 3. 
<div STYLE="page-break-after: always;"></div>
</ol>

## 六、自由创新关卡
<ol>

 ### 1.关卡背景
   
 ### 2.关卡测试
 #### 2.1 新指令介绍
 #### 2.2 成功范例
 ### 3.新代码结构介绍
<div STYLE="page-break-after: always;"></div>
</ol>

## 七、小组分工
