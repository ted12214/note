###java 内存模型
JVM主要管理两种类型内存：堆和非堆，堆内存（Heap Memory）是在 Java 虚拟机启动时创建，非堆内存(Non-heap Memory)是在JVM堆之外的内存。
简单来说，堆是Java代码可及的内存，留给开发人员使用的；非堆是JVM留给自己用的，包含方法区、JVM内部处理或优化所需的内存（如 JIT Compiler，Just-in-time Compiler，即时编译后的代码缓存）、每个类结构（如运行时常数池、字段和方法数据）以及方法和构造方法的代码。

**JVM内存申请过程如下：**
1. JVM 会试图为相关Java对象在Eden中初始化一块内存区域
2. 当Eden空间足够时，内存申请结束；否则到下一步
3. JVM 试图释放在Eden中所有不活跃的对象（这属于1或更高级的垃圾回收）,释放后若Eden空间仍然不足以放入新对象，则试图将部分Eden中活跃对象放入Survivor区
4. Survivor区被用来作为Eden及OLD的中间交换区域，当OLD区空间足够时，Survivor区的对象会被移到Old区，否则会被保留在Survivor区
5. 当OLD区空间不够时，JVM 会在OLD区进行完全的垃圾收集（0级）
6. 完全垃圾收集后，若Survivor及OLD区仍然无法存放从Eden复制过来的部分对象，导致JVM无法在Eden区为新对象创建内存区域，则出现”out of memory”错误

资料:Java 内存模型及GC原理(http://blog.csdn.net/ithomer/article/details/6252552)

###transient关键字的使用
大体介绍序列化的内容 
http://www.cnblogs.com/lanxuezaipiao/p/3369962.html




