## MyISAM存储引擎

第一个文件的名字以表的名字开始，扩展名指出文件类型。.frm文件存储表定义。数据文件的扩展名为.MYD (MYData)。索引文件的扩展名是.MYI (MYIndex)。

要明确表示你想要用一个MyISAM表格，请用ENGINE表选项指出来：

```SQL

CREATE TABLE t (i INT) ENGINE = MYISAM;

```

MySQL最大的优势在于MyISAM引擎下的简单SELECT，INSERT和UPDATE快速操作。
MyISAM类型的数据文件可以在不同操作系统中COPY，这点很重要，布署的时候方便点。

以下是一些细节和具体实现的差别：
1. InnoDB不支持FULLTEXT类型的索引。
2. InnoDB 中不保存表的具体行数，也就是说，执行*select count(\*) from table*时，InnoDB要扫描一遍整个表来计算有多少行，但是MyISAM只要简单的读出保存好的行数即可。注意的是，当count(*)语句包含 where条件时，两种表的操作是一样的。

### 压缩索引

PACK_KEYS参数来指定索引压缩方式

1. MyISAM表的存储格式

> 当表不包含变量长度列（VARCHAR, BLOB, 或TEXT）时，使用这个格式。每一行用固定字节数存储。

2. 静态（固定长度）表特征

> 一个MyISAM表包含任何可变长度 列（VARCHAR, BLOB或TEXTDynamic），或者如果一个表被用ROW_FORMAT=DYNAMIC选项来创建，动态存储格式被使用。

15.1.3.2. 动态表特征

15.1.3.3. 已压缩表特征

## InnoDB存储引擎

### 转换MyISAM表到InnoDB

InnoDB表比MyISAM表需要大得多的磁盘空间。如果一个ALTER TABLE耗尽了空间，它就开始一个 回滚，并且如果它是磁盘绑定的，回滚可能要几个小时。对于插入，InnoDB使用插入缓冲区来以成批地合并第二个索引记录到索引中。那样节省了大量磁盘I/O。在回滚中，没有使用这样的机制，而回滚要花比插入长30倍的时间来完成。