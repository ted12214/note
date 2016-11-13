#NIO
###缓冲区
通道和缓冲区是NIO中的核心对象，几乎在每一个 I/O 操作中都要使用它们。

通道是对原 I/O 包中的流的模拟。到任何目的地(或来自任何地方)的所有数据都必须通过一个Channel对象。一个 Buffer 实质上是一个容器对象。发送给一个通道的所有对象都必须首先放到缓冲区中；同样地，从通道中读取的任何数据都要读到缓冲区中。

Buffer 是一个对象， 它包含一些要写入或者刚读出的数据。 在 NIO 中加入 Buffer 对象，体现了新库与原 I/O 的一个重要区别。在面向流的 I/O 中，您将数据直接写入或者将数据直接读到 Stream 对象中。

在 NIO 库中，所有数据都是用缓冲区处理的。在读取数据时，它是直接读到缓冲区中的。在写入数据时，它是写入到缓冲区中的。任何时候访问 NIO 中的数据，您都是将它放到缓冲区中。

缓冲区实质上是一个数组。通常它是一个字节数组，但是也可以使用其他种类的数组。但是一个缓冲区不仅仅 是一个数组。缓冲区提供了对数据的结构化访问，而且还可以跟踪系统的读/写进程。

最常用的缓冲区类型是 ByteBuffer。一个 ByteBuffer 可以在其底层字节数组上进行 get/set 操作(即字节的获取和设置)。

ByteBuffer 不是 NIO 中唯一的缓冲区类型。事实上，对于每个非布尔原始数据类型都有一种缓冲区类

	ByteBuffer
	CharBuffer
	ShortBuffer
	IntBuffer
	LongBuffer
	FloatBuffer
	DoubleBuffer

每一个 Buffer 类都是 Buffer 接口的一个实例。 除了 ByteBuffer，每一个 Buffer 类都有完全一样的操作，只是它们所处理的数据类型不一样。因为大多数标准 I/O 操作都使用 ByteBuffer，所以它具有所有共享的缓冲区操作以及一些特有的操作。

所有的缓冲区都具有四个属性来提供关于其所包含的数据元素的信息。它们是：

**容量（Capacity）**

> 缓冲区能够容纳的数据元素的最大数量。这一容量在缓冲区创建时被设定，并且永远不能被改变。
> limit 决不能大于 capacity。

**上界（Limit）**

> 缓冲区的第一个不能被读或写的元素limit 变量表明还有多少数据需要取出(在从缓冲区写入通道时)，或者还有多少空间可以放入数据(在从通道读入缓冲区时)。
> position 总是小于或者等于 limit。。或者说，缓冲区中现存元素的计数。

**位置（Position）**

> 下一个要被读或写的元素的索引。位置会自动由相应的get()和put( )方法更新。
> 您可以回想一下，缓冲区实际上就是美化了的数组。在从通道读取时，您将所读取的数据放到底层的数组中。 position 变量跟踪已经写了多少数据。更准确地说，它指定了下一个字节将放到数组的哪一个元素中。因此，如果您从通道中读三个字节到缓冲区中，那么缓冲区的 position 将会设置为3，指向数组中第四个元素。
>同样，在写入通道时，您是从缓冲区中获取数据。 position 值跟踪从缓冲区中获取了多少数据。更准确地说，它指定下一个字节来自数组的哪一个元素。因此如果从缓冲区写了5个字节到通道中，那么缓冲区的 position 将被设置为5，指向数组的第六个元素。

**标记（Mark）**

> 一个备忘位置。调用mark( )来设定mark= postion。调用reset( )设定position=mark。标记在设定前是未定义的(undefined)。

这四个属性之间总是遵循以下关系：0 <= mark <= position <= limit <= capacity

**缓冲区的方法**

	public abstract class Buffer { 
		public final int capacity();
		public final int position();
		public final Buffer position(int newPosition);
		public final int limit();
		public final Buffer limit(int newLimit); 
		public final Buffer mark();
		public final Buffer reset();
		public final Buffer clear();
		public final Buffer flip();
		public final Buffer rewind();
		public final int remaining();
		public final boolean hasRemaining();
		public abstract  boolean isReadOnly(); 
	    }

上面所列出的的Buffer API并没有包括get()或put()方法。每一个Buffer类都有这两个方法，但它们所采用的参数类型，以及它们返回的数据类型，对每个子类来说都是唯一的，所以它们不能在顶层Buffer类中被抽象地声明。

Get和Put可以是相对的或者是绝对的。当相对方法被调用时，位置在返回时前进一。如果位置前进过多，相对运算就会抛出异常。绝对存取需要传递索引参数，方法调用不会影响缓冲区的位置属性，但是如果您所提供的索引超出范围（负数或不小于上界），也将抛出IndexOutOfBoundsException异常。

**字节缓冲区**
字节是操作系统及其I/O设备使用的基本数据类型。当在JVM和操作系统间传递数据时，将其他的数据类型拆分成构成它们的字节是十分必要的。系统层次的I/O面向字节的性质可以在整个缓冲区的设计以及它们互相配合的服务中感受到。

    package java.nio; 
    public abstract class ByteBuffer extends Buffer implements Comparable 
    { 
        public static ByteBuffer allocate (int capacity); 
        public static ByteBuffer allocateDirect (int capacity); 
        public abstract  boolean isDirect(); 
        public static ByteBuffer wrap (byte[] array, int offset, int length); 
        public static ByteBuffer wrap (byte[] array); 
        public abstract ByteBuffer duplicate(); 
        public abstract  ByteBuffer asReadOnlyBuffer(); 
        public abstract  ByteBuffer slice(); 
        public final boolean hasArray(); 
        public final byte[] array(); 
        public final int arrayOffset(); 
        public abstract  byte get(); 
        public abstract byte get (int index); 
        public ByteBuffer get (byte[] dst, int offset, int length); 
        public abstract ByteBuffer put (byte b); 
        public abstract ByteBuffer put (int index, byte b); 
        public ByteBuffer put (ByteBuffer src); 
        public ByteBuffer put (byte[] src, int offset, int length); 
        public final ByteBuffer put (byte[] src); 
        public final ByteOrder order(); 
        public final ByteBuffer order (ByteOrder bo); 
        public abstract  CharBuffer asCharBuffer(); 
        public abstract ShortBuffer asShortBuffer(); 
        public abstract  IntBuffer asIntBuffer(); 
        public abstract LongBuffer asLongBuffer(); 
        public abstract  FloatBuffer asFloatBuffer(); 
        public abstract DoubleBuffer asDoubleBuffer(); 
        public abstract char getChar(); 
        public abstract char getChar (int index); 
        public abstract ByteBuffer putChar (char value); 
        public abstract ByteBuffer putChar (int index, char value); 
        public abstract short getShort(); 
        public abstract short getShort (int index); 
        public abstract ByteBuffer putShort (short value); 
        public abstract ByteBuffer putShort (int index, short value); 
        public abstract int getInt(); 
        public abstract int getInt (int index); 
        public abstract ByteBuffer putInt (int value); 
        public abstract ByteBuffer putInt (int index, int value); 
        public abstract long getLong(); 
        public abstract long getLong (int index); 
        public abstract ByteBuffer putLong (long value); 
        public abstract ByteBuffer putLong (int index, long value); 
        public abstract float getFloat(); 
        public abstract float getFloat (int index); 
        public abstract ByteBuffer putFloat (float value); 
        public abstract ByteBuffer putFloat (int index, float value); 
        public abstract double getDouble(); 
        public abstract double getDouble (int index); 
        public abstract ByteBuffer putDouble (double value); 
        public abstract ByteBuffer putDouble (int index, double value); 
        public abstract ByteBuffer compact(); 
        public boolean equals (Object ob); 
        public int compareTo (Object ob);  
        public String toString(); 
        public int hashCode();
    }

**字节顺序**

多字节数值被存储在内存中的方式一般被称为endian-ness（字节顺序）。如果数字数值的最高字节——big end（大端），位于低位地址，那么系统就是大端字节顺序。字节顺序很少由软件设计者决定；它通常取决于硬件设计。如果最低字节最先保存在内存中，那么小端字节顺序。

当Internet的设计者为互联各种类型的计算机而设计网际协议（IP）时，他们意识到了在具有不同内部字节顺序的系统间传递数值数据的问题。因此，IP协议规定了使用大端的网络字节顺序概念。所有在IP分组报文的协议部分中使用的多字节数值必须先在本地主机字节顺序和通用的网络字节顺序之间进行转换。

在java.nio中，字节顺序由ByteOrder类封装。

    package java.nio; 
    public final class ByteOrder 
    { 
        public static final ByteOrder BIG_ENDIAN;
        public static final ByteOrder LITTLE_ENDIAN; 
        
        public static ByteOrder nativeOrder();
        public String toString();
    }

ByteBuffer类有所不同：默认字节顺序总是ByteBuffer.BIG_ENDIAN，无论系统的固有字节顺序是什么。Java的默认字节顺序是大端字节顺序，这允许类文件等以及串行化的对象可以在任何JVM中工作。如果固有硬件字节顺序是小端，这会有性能隐患。在使用固有硬件字节顺序时，将ByteBuffer的内容当作其他数据类型存取很可能高效得多。

视图缓冲区的字节顺序设定在创建后不能被改变，而且如果原始的字节缓冲区的字节顺序在之后被改变，它也不会受到影响。。

