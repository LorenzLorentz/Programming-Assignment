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

-jumpifzero在我这里比较稳定？

-程序update在newmain里面（我试着弄了一个pull request不知道你能不能看）

**2024/10/20/22 update**

-现在加入了文件系统

-加入了available carpet机制（大作业文档中是要求的）

-取消了万能头文件（只是因为它在mac的命令行环境无法运行）
