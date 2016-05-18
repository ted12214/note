#store 的用法
Store.getCount()返回的是store中的所有数据记录，然后使用for循环遍历整个store，从而得到每条记录。
除了使用getCount()的方法外，还可以使用each()函数，如下面的代码所示。

``` javaScript
store.each(function(record) {   
    alert(record.get('name'));   
});  

store.each(function(record) {
    alert(record.get('name'));
});
```
Each()可以接受一个函数作为参数，遍历内部record，并将每个record作为参数传递给function()处理。
如果希望停止遍历，可以让function()返回false。
也可以使用getRange()函数连续获得多个record，只需要指定开始和结束位置的索引值，如下面的代码所示。
``` javaScript
var records = store.getRange(0, 1);   
  
for (var i = 0; i < records.length; i++) {   
    var record = records[i];   
    alert(record.get('name'));   
}  

var records = store.getRange(0, 1);

for (var i = 0; i < records.length; i++) {
    var record = records[i];
    alert(record.get('name'));
}
```

##查找
如果确实不知道record的id，也可以根据record本身的id从store中获得对应的record，如下面的代码所示。
store.getById(1001).get('name')  
store.getById(1001).get('name')

EXT还提供了函数find()和findBy()，可以利用它们对store中的数据进行搜索，如下面的代码所示。
find( String property, String/RegExp value, [Number startIndex], [Boolean anyMatch],[Boolean caseSensitive] )   
find( String property, String/RegExp value, [Number startIndex], [Boolean anyMatch],[Boolean caseSensitive] ) 

在这5个参数中，只有前两个是必须的。
第一个参数property代表搜索的字段名；
第二个参数value是匹配用字符串或正则表达式；
第三个参数startIndex表示从第几行开始搜索;
第四个参数anyMatch为true时，不必从头开始匹配；
第五个参数caseSensitive为true时，会区分大小写。

如下面的代码所示：
``` javaScript
var index = store.find('name','g');   
alert(store.getAt(index).get('name'));  
var index = store.find('name','g');
alert(store.getAt(index).get('name'));
```

与find()函数对应的findBy()函数的定义格式如下：
findBy( Function fn, [Object scope], [Number startIndex] ) : Number  
findBy( Function fn, [Object scope], [Number startIndex] ) : Number

findBy()函数允许用户使用自定义函数对内部数据进行搜索。
fn返回true时，表示查找成功，于是停止遍历并返回行号。
fn返回false时，表示查找失败（即未找到），继续遍历，如下面的代码所示。
``` javaScript
index = store.findBy(function(record, id) {   
    return record.get('name') == 'girl' && record.get('sex') == 1;   
});   
  
alert(store.getAt(index).get('name'));  

index = store.findBy(function(record, id) {
    return record.get('name') == 'girl' && record.get('sex') == 1;
});

alert(store.getAt(index).get('name'));
```

通过findBy()函数，我们可以同时判断record中的多个字段，在函数中实现复杂逻辑。
我们还可以使用query和queryBy函数对store中的数据进行查询。
与find和findBy不同的是，query和queryBy返回的是一个MixCollection对象，里面包含了搜索得到的数据，如下面的代码所示。

``` javaScript
alert(store.query('name', 'boy'));   
  
alert(store.queryBy(function(record) {   
    return record.get('name') == 'girl' && record.get('sex') == 1;   
}));  

alert(store.query('name', 'boy'));

alert(store.queryBy(function(record) {
    return record.get('name') == 'girl' && record.get('sex') == 1;
}));
```

##Ext.data.Store更新store中的数据
###添加
可以使用add(Ext.data.Record[] records)向store末尾添加一个或多个record，使用的参数可以是一个record实例，如下面的代码所示。
``` javaScript
store.add(new PersonRecord({   
    name: 'other',   
    sex: 0   
}));  

store.add(new PersonRecord({
    name: 'other',
    sex: 0
}));
```

Add()的也可以添加一个record数组，如下面的代码所示：
``` javaScript
store.add([new PersonRecord({   
    name: 'other1',   
    sex: 0   
}), new PersonRecord({   
    name: 'other2',   
    sex: 0   
})]);  

store.add([new PersonRecord({
    name: 'other1',
    sex: 0
}), new PersonRecord({
    name: 'other2',
    sex: 0
})]);
```

Add()函数每次都会将新数据添加到store的末尾，这就有可能破坏store原有的排序方式。如果希望根据store原来的排序方式将新数据插入到对应的位置，可以使用addSorted()函数。它会在添加新数据之后立即对store进行排序，这样就可以保证store中的数据有序地显示，如下面的代码所示。
``` javaScript
store.addSorted(new PersonRecord({   
    name: 'lili',   
    sex: 1   
}));  

store.addSorted(new PersonRecord({
    name: 'lili',
    sex: 1
}));
```

store会根据排序信息查找这条record应该插入的索引位置，然后根据得到的索引位置插入数据，从而实现对整体进行排序。这个函数需要预先为store设置本地排序，否则会不起作用。
如果希望自己指定数据插入的索引位置，可以使用insert()函数。它的第一个参数表示插入数据的索引位置，可以使用record实例或record实例的数组作为参数，插入之后，后面的数据自动后移，如下面的代码所示。
``` javaScript
store.insert(3, new PersonRecord({   
    name: 'other',   
    sex: 0   
}));   
  
store.insert(3, [new PersonRecord({   
    name: 'other1',   
    sex: 0   
}), new PersonRecord({   
    name: 'other2',   
    sex: 0   
})]);  

store.insert(3, new PersonRecord({
    name: 'other',
    sex: 0
}));

store.insert(3, [new PersonRecord({
    name: 'other1',
    sex: 0
}), new PersonRecord({
    name: 'other2',
    sex: 0
})]);
```
###删除
删除操作可以使用remove()和removeAll()函数，它们分别可以删除指定的record和清空整个store中的数据，如下面的代码所示。
``` javaScript
store.remove(store.getAt(0));   
store.removeAll();  

store.remove(store.getAt(0));
store.removeAll();
```
### 修改
store中没有专门提供修改某一行record的操作，我们需要先从store中获取一个record。对这个record内部数据的修改会直接反映到store上，如下面的代码所示。

store.getAt(0).set('name', 'xxxx');  
store.getAt(0).set('name', 'xxxx');

修改record的内部数据之后有两种选择：执行rejectChanges()撤销所有修改，将修改过的record恢复到原来的状态；执行commitChanges()提交数据修改。在执行撤销和提交操作之前，可以使用getModifiedRecords()获得store中修改过的record数组。

与修改数据相关的参数是pruneModifiedRecords，如果将它设置为true，当每次执行删除或reload操作时，都会清空所有修改。这样，在每次执行删除或reload操作之后，getModifiedRecords()返回的就是一个空数组，否则仍然会得到上次修改过的record记录

## Ext.data.Store加载及显示数据

store创建好后，需要调用load()函数加载数据，加载成功后才能对store中的数据进行操作。load()调用的完整过程如下面的代码所示。
``` javaScript
store.load({   
    params: {start:0,limit:20},   
    callback: function(records, options, success){   
        Ext.Msg.alert('info', '加载完毕');   
    },   
    scope: store,   
    add: true  
});  

store.load({
    params: {start:0,limit:20},
    callback: function(records, options, success){
        Ext.Msg.alert('info', '加载完毕');
    },
    scope: store,
    add: true
});
```

1. params是在store加载时发送的附加参数。
2. callback是加载完毕时执行的回调函数，它包含3个参数：records参数表示获得的数据，options表示执行load()时传递的参数，success表示是否加载成功。
3. Scope用来指定回调函数执行时的作用域。
4. Add为true时，load()得到的数据会添加在原来的store数据的末尾，否则会先清除之前的数据，再将得到的数据添加到store中。

一般来说，为了对store中的数据进行初始化，load()函数只需要执行一次。如果用params参数指定了需要使用的参数，以后再次执行reload()重新加载数据时，store会自动使用上次load()中包含的params参数内容。

如果有一些需要**固定传递的参数**，也可以使用baseParams参数执行，它是一个JSON对象，里面的数据会作为参数发送给后台处理，如下面的代码所示。
``` javaScript
store.baseParams.start = 0;   
store.baseParams.limit = 20;  

store.baseParams.start = 0;
store.baseParams.limit = 20;
```

为store加载数据之后，有时不需要把所有数据都显示出来，这时可以使用函数filter和filterBy对store中的数据进行过滤，只显示符合条件的部分，如下面的代码所示。
``` javaScript
filter( String field, String/RegExp value, [Boolean anyMatch], [Boolean caseSensitive] ) : void  
filter( String field, String/RegExp value, [Boolean anyMatch], [Boolean caseSensitive] ) : void
```

filter()函数的用法与之前谈到的find()相似，如下面的代码所示。
``` javaScript
store.filter('name', 'boy');  
store.filter('name', 'boy');
```

对应的filterBy()与findBy()类似，也可以在自定义的函数中实现各种复杂判断，如下面的代码所示。
``` javaScript
store.filterBy(function(record) {   
    return record.get('name') == 'girl' && record.get('sex') == 1;   
});  

store.filterBy(function(record) {
    return record.get('name') == 'girl' && record.get('sex') == 1;
});
```

如果想取消过滤并显示所有数据，那么可以调用clearFilter()函数，如下面的代码所示。
``` javaScript
store.clearFilter();  
store.clearFilter();
```

如果想知道store上是否设置了过滤器，可以通过isFiltered()函数进行判断。

## Ext.data.Store其他功能

除了上面提到的数据获取、排序、更新、显示等功能外，store还提供了其他一些功能函数。
``` javaScript
collect( String dataIndex, [Boolean allowNull], [Boolean bypassFilter] ) : Array  
collect( String dataIndex, [Boolean allowNull], [Boolean bypassFilter] ) : Array
```

collect函数获得指定的dataIndex对应的那一列的数据，当allowNull参数为true时，返回的结果中可能会包含null、undefined或空字符串，否则collect函数会自动将这些空数据过滤掉。当bypassFilter参数为true时，collect的结果不会受查询条件的影响，无论查询条件是什么都会忽略掉，返回的信息是所有的数据，如下面的代码所示。
``` javaScript
alert(store.collect('name'));  
alert(store.collect('name'));
```

这样会获得所有name列的值，示例中返回的是包含了'boy'和'girl'的数组。

getTotalCount()用于在翻页时获得后台传递过来的数据总数。如果没有设置翻页，get- TotalCount()的结果与getCount()相同，都是返回当前的数据总数，如下面的代码所示。
``` javaScript
alert(store.getTotalCount());  
alert(store.getTotalCount());
```

indexOf(Ext.data.Record record)和indexOfId(String id)函数根据record或record的id获得record对应的行号，如下面的代码所示。
``` javaScript
alert(store.indexOf(store.getAt(1)));   
alert(store.indexOfId(1001));  

alert(store.indexOf(store.getAt(1)));
alert(store.indexOfId(1001));
```

loadData(object data, [Boolean append])从本地JavaScript变量中读取数据，append为true时，将读取的数据附加到原数据后，否则执行整体更新，如下面的代码所示。
``` javaScript
store.loadData(data, true);  
store.loadData(data, true);
```

Sum(String property, Number start, Number end):Number用于计算某一个列从start到end的总和，如下面的代码所示。
``` javaScript
alert(store.sum('sex'));  
alert(store.sum('sex'));
```

如果省略参数start和end，就计算全部数据的总和。

store还提供了一系列事件（见下表），让我们可以为对应操作设定操作函数。

表　 store提供的事件

|事件名|参　　数|
|------|---------|
|**add**|( Store this, Ext.data.Record[] records, Number index )|
|**beforelaod**|( Store this, Object options )
|**clear** |( Store this )
|**datachanged** |( Store this )
|**load** |( Store this, Ext.data.Record[] records, Object options )
|**loadexception** |()
|**metachange** |( Store this, Object meta. )
|**remove** |( Store this, Ext.data.Record record, Number index )
|**update** |( Store this, Ext.data.Record record, String operation )
