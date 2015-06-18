
java 内存区域
============
##运行时数据区
###程序计数器(progrem counter register)

每一个进程有一个独立的程序计数器,该区域是JVM唯一没有规定outofmemory情况的区域。

###java虚拟机栈(java vitual machine stacks)

- 线程私有
- 存放基本类型、引用类型、returnAdress类型

###本地方法栈(native method stack)

服务于native方法

###java堆(java heap) 
新生代（from survivor、to survivor）、老年代（edge）

###方法区(method area)
线程共享区

###运行时常量池(running constant pool)
java 虚拟机没有对该部分做细节要求，不同的供应商会按自己的需求来管理该区域

###直接内存区（direct memory）

#GC

如何判断对象是否可以回收：引用计数算法、可达性分析算法；

四种引用类型：

- 强（strong）:
- 软（soft）:第二次垃圾回收时会回收
- 弱（weak）：只能生存到下一次垃圾回收的时间
- 虚（phantom）：在垃圾回收时会收到系统通知