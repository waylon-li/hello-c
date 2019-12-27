#####gdb基本用法
```
file xxx
set args/run args

b <行号>
b <函数名>
b *<函数名>
b *<代码地址>

d [断点编号]

c continue
s step into
n step over
p <变量名>
display
i info
q quit
help [命令名称]
l 列出源码
info break 查看断点信息

bt 查看函数堆栈
frame 1 切换1号帧
info local 打印当前栈中局部变量

```

##### 多线程调试
```
info threads
thread ID
set scheduler_locking off/on/step
```

##### -g3 调用时可查看宏
```
查看宏
p macroname(...)
查看宏展开形式
macro expand macroname(...)
查看宏定义
info macro macroname(...)
```

##### gstack pid 查看进程堆栈信息

##### gdb 调试正在运行的程序
```
 1. 编译时候带-g选项。
 2. 运行程序。
 3. ps找到进程号。
 4. 启动gdb，使用attach选项，这时gdb会停止在程序的某处。
 5. 按照GDB调试方法调试。当程序退出之后，依然可以使用run命令重启程序。
 
 gdb
 attach pid
 n
 set var num=1 来修改变量num的值
 
```

##### 用gdb查看内存
```
格式：x /nfu  <addr>
说明
x 是examine 的缩写
n 表示要显示的内存单元的个数
f 表示显示方式，可取如下值：
    x 按十六禁止格式显示变量
    d按十进制格式显示变量
    u 按十进制格式显示无符号变量
    o 按八进制格式显示变量
    a 按十六进制格式显示变量
    i 指令地址格式
    c 按字符格式显示变量
    f 按浮点数格式显示变量
    
u 表示一个地址单元的长度
    b 表示单字节
    h 表示双字节
    w 表示四字节
    g 表示八字节
    
format letters are
o(octal),x(hex),d(decimal),u(unsigned decimal),t(binary),f(float),a(address),i(instruction),c(char) and s(string)
size letters are
b(byte),h(halfword),w(word),g(giant,8bytes)

举例：
x/3uh buf
表示从内存地址buf 读取内
h 表示以双字节为一个单位
3 表示三个单位
u 表示按照无符号十进制显示

gdb
f g_t
b 
r 0xaabbccdd 
p &n
x &n
x /4xw &n
x /4dw &n

```
