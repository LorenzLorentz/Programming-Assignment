**2024/10/13/00 update**

现在存在以下问题

- inputBar在游戏结束后的初始化 这个我好像改完了
- 操作计数 这个我发现了numsteps的问题：就是他会把比如一开始选关卡的y，1，或者无效输入的行数都加进去。然后我改了一下，但是好像稍微还有点小问题，但我下午有点忙，晚点有空再改
- 循环
- 可用的操作
-jump循环我感觉有点问题，比如关卡2为什么我输入
inbox
copyto 1
inbox
copyto 2
copyfrom 1
sub 2
outbox 
copyfrom 2
sub 1
outbox
jump 1
start
就不大对劲

**2024/10/13/22 update**
现在修复了以下问题

- inputBar
- jumpto与jumpifzero
- 操作计数
- 可用操作

现在还有以下问题

- jumpifzero不稳定出现无法继续的问题，目前不能稳定复现

**2024/10/15/18 update**

现在补充了完善了操作计数算法

更正了jump指令

- jumpifzero在我这里比较稳定？

- 程序update在newmain里面（我试着弄了一个pull request不知道你能不能看）

**2024/10/20/22 update**

- 现在加入了文件系统

- 加入了available carpet机制（大作业文档中是要求的）

- 取消了万能头文件（只是因为它在mac的命令行环境无法运行）

**2024/11/24/11 && 2024/11/28/21update**

- 现在写了一个简陋的图形界面

- 待解决的功能

- 存档相关功能

1.（已解决）读取存档与保存存档，这个之前的版本也已经写好了，要改一改放进来 

2.（已解决）主菜单界面的读取存档，可以制作为选择文件的形式

3.（有bug）自动读取文档按钮，目前好像文件访问权限有点问题？

4. 如果不进行读取，默认自动读取

5. （已解决）显示通过与不通过，只有通过了上一关才能进行下一关，否则报错

- 游戏状态动态显示相关功能：
  
1. （已解决）游戏开始时还不能显示这个游戏的内容，我忘写了

2. （已解决）目前的动态显示使用的方法是回调函数，将状态放入一个std::queue，但是显然有些东西不应该放入queue，也就是说只用显示当前状态，而不用一并显示之前的状态 

3. （解决了一半）人搬东西，这个功能看起来有点复杂，还会涉及到搬了之后的动态变化

4. （大致解决，但怎样好看是个艺术问题）如何把状态显示的更好看一点，比如字体/大小能不能自定义调整一下

- 用户输入：目前的用户输入采用了与命令行相同的逻辑，但这实在是非常的不优雅，可以考虑的改进方向有

1. （已解决）取消指令条数，直接start按键就可以

2. 使用游戏本体相似的选项卡拖动，但是这个应该也有点困难

**2024/12/01/22update**

- bug

  连续游玩的时候小人不能正常移动

- 现在的需求

1. 小人的移动实现的非常原始，有以下方面可以改进

   - 不要瞬移，而是一步步移动
  
   - 给小人添加动作的动画
  
   - 关键点1 如果是缓慢移动，那么其他地方的update加载也需要匹配
  
   - 关键点2 如何给小人制作动作的动画
  
2. 加入选项卡执行输入操作

   - 关键点1 如何实现选项卡
  
   - 关键点2 如何将选项卡和输入耦合
  
   - 关键点3 jump等选项卡如何实现

3. 将游戏变得更美观

   - playgame界面，字体的显示好像有一些问题，进行字体的自定义设置会直接变得很小
  
   - 胜利界面和失败界面可以添加一些小动画
  
   - 游戏开始界面前加入一个加载条
  
   - 游戏内部也可以美化一下，加入一点图片
  
   - 关键点1 如何载入图片
  
   - 关键点2 如何制作小动画

12/18

1. 添加功能

   - 第四关的新ui

   - 随机生成
  
   - 关卡描述

   - jumpifpos jumpifneg

   - hand+ *，hand- *

   - 双参数，带字母的参数
 
   - copyifneg，copyifpos

2. 小人动画

   - 不同栏和手的加载先后
  
   - 手动的细节

3. 游戏美化

   - 字体
  
   - 图片
  
   - 小动画（可选）
  
12/25

1. 游戏美工仍然没有解决 字体与图片

2. 出现了加载存档的bug

3. 小人动画与栏目加载先后匹配

4. 输入栏设计

   4.1 旁边的数字标注

   4.2 按钮点击
