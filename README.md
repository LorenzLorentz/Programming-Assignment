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
