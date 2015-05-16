# haiku

分支来自```10e57f6```

＠xinyx

## linux_hello module移植

linux_hello是ldd3的hello示例驱动，header-gen分析结果位于
```bash
driver@166.111.132.191:/home/driver/header-gen/linux/results/hello_ldd
port 10220
```

### 实现linux兼容层compat

```bash
$ cd haiku/src/libs/compat/

$ mkdir linux_hello; cd linux_hello
# 将header-gen生成的hello_ldd.dummy.c拷贝到上目录，重命名为hello_dummy.c
# 用haiku提供的内核函数重写其中的linux的printk函数

$ mkdir compat
# 将header-gen生成的hello_ldd.d中的内容拷贝到上面compat

$ vim compat/linux/types.h
# 13行：删除umode_t的定义（与haiku冲突）

$ vim compat/linux/printk.h
# 18行：修改printk声明，使其兼容hello_dummy.c中的定义

$ vim Jamfile
# 用Jamfile将本兼容层生存静态库，供linux驱动使用

$ cd ..; vim Jamfile
# 修改Jamfile，加进linux_hello
```

### 移植linux_hello

```bash
$ cd haiku/src/add-ons/kernel/drivers
$ mkdir linux_hello; cd linux_hello
# 将原先的hello文件拷贝到此目录

$ vim linux_hello.c
# 重写/重用驱动代码

$ vim Jamfile
# 设置编译规则，引用我们生成的linux兼容层静态库

$ cd ..; vim Jamfile
# 修改Jamfile，加进linux_hello
```

### 修改编译链，加进新驱动

```bash
$ vim haiku/build/jam/packages/Haiku
$ vim haiku/build/jam/packages/HaikuBootstrap
$ vim haiku/build/jam/packages/HaikuDevel
# 加进linux_hello
```

### 调试关键
用jam target调试单个小目标能有效加快调试速度


