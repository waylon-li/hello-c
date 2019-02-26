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


