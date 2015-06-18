SOAP-Simple Object Access Protocol（简单对象访问协议）
=====================================================

SOAP是Simple Object Access Protocol（简单对象传输协议）的缩写。SOAP消息是基于XML格式进行传输的，流行的web service就是使用SOAP进行客户端和服务器之间的通信的。在这篇文章中我将介绍基础的SOAP格式（1.2版），包括：

- SOAP XML格式
- SOAP 消息样式
- SOAP MEP（Message Exchange Patterns 消息交换模式 ）
- SOAP 消息路由选择
- SOAP 通过HTTP传输


SOAP 消息格式
-------------
下面是一个简单的SOAP消息：

    <?xml version="1.0"?>
    <soap:Envelope xmlns:soap="http://www.w3.org/2001/12/soap-envelope" >
    
    <soap:Header>
    </soap:Header>
    
    <soap:Body>
    
      <-- Fault element is optional,
          used only if a fault occurs in web service.
      -->
      <soap:Fault>
      </soap:Fault>
    
    </soap:Body>
    
    </soap:Envelope>

正如你看到的，一条SOAP消息包括一个*envelope*元素，在*envelope*元素中可以嵌套了一个*Header*元素和一个*Body*元素。如果在这个web service 处理消息过程中产生了一个错误，在*Body*元素中可以嵌套一个*Fault*元素。在接下来的SOAP的文章中将会依次介绍SOAP消息中的这些元素。

SOAP请求和响应都使用Envelope命名空间
------------------------------
在早期的SOAP规范中从客户端发送请求到服务器和从服务器发送响应到客户端都使用相同的SOAP数据格式，因此SOAP请求和响应消息格式是一致的。这不同于HTTP协议中请求和响应报文采用了不同的数据格式。

SOAP Envelope元素
=================
SOAP的*Envelope*元素是SOAP消息的根元素，在*Envelope*元素内可以嵌套到一个*Header*元素（可选的）和一个*Body*元素。
下边是一个关于SOAP *Envelope*元素的例子（内容中粗体内容为*Envelope*元素）

    <?xml version="1.0"?>
    <env:Envelope  xmlns:env="http://www.w3.org/2002/06/soap-envelope" >
    
    <env:Header>
    </env:Header>
    
    <env:Body>
    </env:Body>
    
    </env:Envelope>

注意到命名空间*env*在*Envelope*元素中有如下定义

    xmlns:env="http://www.w3.org/2002/06/soap-envelope"

命名空间的定义必须总是出现在SOAP *Envelope*元素内，前缀（env）可以视自己的喜好定义。

SOAP的Header元素
=====================

> **内容列表**   
  - Header 子元素属性
  - mustUnderstand  
  - encodingStyle
  - role         	
  - relay
  
SOAP *Header*元素是*Envelope*元素的一个可选的子元素，在*Header*元素内你可以放置SOAP信息中Body部分一外的内容，其中的内容可以完全由你来指定，例如，它可以是关于这条SOAP请求处理的最大时间，或者是其它没有在SOAP消息中直接被指明的内容。

下边是一个关于SOAP *Header*元素的例子（内容中粗体内容为*Header*元素）

    <?xml version="1.0"?>
    <env:Envelope  xmlns:env="http://www.w3.org/2001/12/soap-envelope" >
    
      <env:Header>
        <jj:maxTime value="10000" xmlns:jj="http://jenkov.com"/>
      </env:Header>
    
      <env:Body>
      </env:Body>
    
    </env:Envelope>

上边的例子展示了仅有一个“SOAP 头信息块”的*Header*元素。
更多的关于*Header*元素的使用类似于*Envelope*元素的XML命名空间的内容请参考SOAP规范。

Header子元素属性
-------------------------
*Header*元素的子元素有以下几个标准属性：
- mustUndersstand
- encodingStyle
- role
- relay

接下来的部分将详细介绍这几个元素属性。

**mustUnderstand**
*mustUnderstand*属性意味着每个处理SOAP的节点必须能够理解（处理）所给出的Header区域。这里所说的“节点”不一定是最终接收SOAP消息的节点，这条SOAP消息在到达最终接收/处理消息的节点（web service）之前可能经过了中间某些节点。
假如中间的一个节点不能理解含有*mustUnderstand*属性的header区域中的内容，那么必须返回SOAP错误信息。

错误信息例子如下：

    <env:Header>
      <jj:maxTime value="10000" xmlns:jj="http://jenkov.com"
                   mustUnderstand="true"
        />
    </env:Header>

**encodingStyle**
*encodingStyle*属性内容省略。

**role**

某个节点在处理/转发SOAP消息过程中都扮演者一个或多个SOAP角色，Header区域（元素）能够将信息发送给消息路径中的特定的角色，换句话说，如果Header区域中指定了"ultimateReceiver"角色，那么消息路径中“ultimateReceiver”角色必须处理Header区域，消息路径中的其它节点将不对Header区域中的内容进行处理。
SOAP角色详细解释见[“SOAP 角色”](http://tutorials.jenkov.com/soap/roles.html)
下边是一个使用*role*属性的例子：

    <env:Header>
      <jj:maxTime value="10000" xmlns:jj="http://jenkov.com"
        role="http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver"
        />
    </env:Header>

在这个例子中header元素<maxTime ...>仅指定为该SOAP消息的最终接收者处理，消息路径的中间节点将忽略*header*元素中的内容。

**relay**

*relay*属性决定了如果header区域没有被处理是否可以被转发，换句话说，如果消息路径中的中间节点没有处理Header元素中的内容，在转发SOAP消息的过程中需要根据*relay*属性来判断header元素是否可以被转发？
relay属性只有两个合法的值：
1. true
2. false

如果relay属性设置为'true'那么没有处理的Header元素可以被转发。
如果relay属性设置为'false'那么没有处理的Header元素不可以被转发。

缺省relay条件情况下等同于relay属性设置为'false'。
下边是一个使用*relay*属性的例子：

    <env:Header>
      <jj:maxRelayTime value="10000" xmlns:jj="http://jenkov.com"
           role="http://www.w3.org/2003/05/soap-envelope/role/next"
           relay="true"
        />
    </env:Header>

在这个例子中Header元素<maxRelayTime ...>必须在节点间进行转发，就算已经被处理过了，换句话说，SOAP消息在消息路径中转发过程中Header元素不应该被省去。正如你所看到的*role*属性被设置为"next"，这意味着所有消息路径中的节点都需要处理Header元素。

SOAP Body元素
===============
SOAP Body元素是客户端和web serveice服务器端处理的SOAP消息中的最主要的部分，SOAP消息中Header元素是可选的但是Body元素是必须要有的元素，SOAP消息中必须包含Body元素。

下边是一个关于SOAP *Header*元素的例子（内容中粗体内容为*Header*元素）

    <?xml version="1.0"?>
    <env:Envelope  xmlns:env="http://www.w3.org/2001/12/soap-envelope" >
    
      <env:Header>
        <jj:maxTime value="10000" xmlns:jj="http://jenkov.com"/>
      </env:**Header**>
    
      <env:Body>
      </env:Body>
    
    </env:Envelope>

上边的例子展示了仅有一个“SOAP 头信息块”的*Header*元素。
更多的关于*Header*元素的使用类似于*Envelope*元素的XML命名空间的内容请参考SOAP规范。

Header元素的子元素的属性
-------------------------
*Header*元素的子元素有以下几个标准属性：
- mustUndersstand
- encodingStyle
- role
- relay

每一个元素将会在接下来进行详细的介绍。

**mustUnderstand**
*mustUnderstand*属性意味着每个处理SOAP的节点必须能够理解（处理）所给出的Header区域。这里所说的“节点”不一定是最终接收SOAP消息的节点，这条SOAP消息在到达最终接收/处理消息的节点（web service）之前可能已经经过了消息路径中的某些节点。
假如中间的一个节点不能理解含有*mustUnderstand*属性的header区域中的内容，那么必须返回SOAP错误信息。
错误信息例子如下：

    <env:Header>
      <jj:maxTime value="10000" xmlns:jj="http://jenkov.com"
                   mustUnderstand="true"
        />
    </env:Header>

**encodingStyle**
*encodingStyle*属性内容省略

**role**

某个节点在处理/转发SOAP消息过程中都扮演者一个或多个SOAP角色，Header区域（元素）能够将信息发送给消息路径中的特定的角色，换句话说，如果Header区域中指定了"ultimateReceiver"角色，Name只有消息路径中“ultimateReceiver”角色必须处理Header区域，消息路径中的其它节点将不对Header区域中的内容进行处理。
SOAP角色详细解释见[“SOAP 角色”](http://tutorials.jenkov.com/soap/roles.html)
下边是一个使用*role*属性的例子：

    <env:Header>
      <jj:maxTime value="10000" xmlns:jj="http://jenkov.com"
        role="http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver"
        />
    </env:Header>

在这个例子中header元素<maxTime ...>仅指定为该SOAP消息的最终接收者处理，消息路径的中间节点将忽略*header*元素中的内容。

**relay**

*relay*属性决定了如果header区域没有被处理是否可以被转发，换句话说，如果消息路径中的中间节点没有处理Header元素中的内容在转发SOAP消息的过程中需要根据*relay*属性来判断header元素是可以被转发？
relay属性只有两个合法的值：
1. true
2. false

如果relay属性设置为'true'那么没有处理的Header元素可以被转发。
如果relay属性设置为'false'那么没有处理的Header元素不可以被转发。

缺省relay条件情况下等同于relay属性设置为'false'。
下边是一个使用*relay*属性的例子：

    <env:Header>
      <jj:maxRelayTime value="10000" xmlns:jj="http://jenkov.com"
           role="http://www.w3.org/2003/05/soap-envelope/role/next"
           relay="true"
        />
    </env:Header>

在这个例子中Header元素<maxRelayTime ...>必须在节点间进行转发，就算已经被处理过了，换句话说，Header元素不应该被省去。正如你所看到的*role*属性被设置为"next"，这意味着所有消息路径中的节点都需要处理Header元素。

SOAP Body元素
===============
SOAP Body元素是客户端和web serveice服务器端处理的SOAP消息中的最主要的部分，Header元素是可选的但是Body元素是强制的，SOAP消息中必须包含Body元素。

下边是一个关于SOAP *Body*元素的例子（内容中粗体内容为*Body*元素）

    <?xml version="1.0"?>
    <env:Envelope  xmlns:env="http://www.w3.org/2001/12/soap-envelope" >
    
    <env:Header>
    </env:Header>
    
    <env:Body>
    </env:Body>
    
    </env:Envelope>

SOAP消息的Body部分可以包含几乎所有的你想放置的格式正确的XML数据，然而你不能在Body元素内直接放置文本内容，文本内容应该放置在Body元素的子元素内。

推荐Body元素的子元素使用符合规范的命名空间。

这里有两个关于*Body*元素的例子。第一个例子中*Body*元素中包含了4个元素，第二个例子这4个元素嵌套在了<service>元素内。

        <?xml version="1.0"?>
        <env:Envelope  xmlns:env="http://www.w3.org/2001/12/soap-envelope" >
        
          <env:Body>
        
            <jj:operation name="setName"
                xmlns:jj="http://jenkov.com/operation" />
        
            <jj:param name="userId" value="123456"
                xmlns:jj="http://jenkov.com/params" />
        
            <jj:param name="firstName" value="Jakob"
                xmlns:jj="http://jenkov.com/params" />
        
            <jj:param name="lastName"  value="Jenkov"
                xmlns:jj="http://jenkov.com/params" />
        
          </env:Body>
        
        </env:Envelope>
------

    <?xml version="1.0"?>
    <env:Envelope  xmlns:env="http://www.w3.org/2001/12/soap-envelope" >
    
        <env:Body>
    
          <jj:service name="userService"
              xmlns:jj="http://jenkov.com/service" >
    
              <jj:operation name="setName" />
    
              <jj:param name="userId" value="123456" />
    
              <jj:param name="firstName" value="Jakob" />
    
              <jj:param name="lastName"  value="Jenkov" />
    
          </jj:service name="userService"
    
        </env:Body>
    
    </env:Envelope>


SOAP Fault元素
==================


>   **内容列表**
- SOAP Fault元素结构
 - code 
- Reason   
- Node         	 
- Role
- Detail			 

如果消息路径中的节点在处理SOAP消息的过程中产生了错误，Fault元素出现在从web service（或中间节点）返回的SOAP消息中的Body元素中。

下边是一个关于SOAP *Fault*元素的例子（内容中粗体内容为*Fault*元素）

    <?xml version="1.0"?>
    <env:Envelope  xmlns:env="http://www.w3.org/2001/12/soap-envelope" >
        <env:Body>
            <env:Fault>
    
              <env:Code>
                <env:Value>env:Sender</env:Value>
              </env:Code>
    
              <env:Reason>
                <env:Text xml:lang="en-US">Processing error</env:Text>
                <env:Text xml:lang="da">Processerings-fejl</env:Text>
              </env:Reason>
    
            </env:Fault>
        </env:Body>
    </env:Envelope>

**SOAP Fault元素结构**

SOAP Fault元素有如下的结构：

    <env:Fault>
    
      <env:Code>
        <env:Value>env:Sender</env:Value>
        <env:Subcode>
            <env:Value>env:Sender</env:Value>
            <env:Subcode> <-- recursive Subcode's possible -->
            </env:Subcode>
        </env:Subcode>
      </env:Code>
    
      <env:Reason>
       <env:Text xml:lang="en-US">Error in Input Data</env:Text>
       <env:Text xml:lang="da">Fejl i input data</env:Text>
      </env:Reason>
    
      <env:Node>http://jenkov.com/theNodeThatFailed</env:Node>
    
      <env:Role>
        http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver
      </env:Role>
    
      <env:Detail
        <jj:maxRelayTime
            xmlns:jj="http://jenkov.com" >10000</jj:MaxRelayTime>
      </env:Detail>
    
    </env:Fault>

*Code*元素和*Reasong*元素是必须要有的，*Node*、*Role*和*Detail*元素是可选的

**Code**

*Code*元素是必须要有的，在*Code*元素内可以嵌套*Value*元素，如果你需要分解错误码还可以添加可选的*SubCode*子元素。

*Value*子元素只能包含以下列表中的值，这些值必须添加命名空间信息，这就意味着如果你在SOAP消息中添加了*Envelope*元素的命名空间信息映射前缀为"env"，你也需要为下边列表中的值添加前缀"env"，例如："env:Sender"。

>Value                               Describe
>VersionMismath               消息路径中的节点发现在SOAP消息中的根节点不是有效是*Envelope*元素将会报告这个错误

>MustUnderstand	            消息路径中的节点不能理解*Header*元素的某一个含有*mustUnderstand*属性的子元素，这样的一个目标节点将会报  
                                          告这个错误，换句话说消息路径中的此节点不能理解此*Header*元素假设他能理解的元素的意思。

>DataEncodingUnknow       消息路径中的节点不能理解假定被理解的元素的编码（由*encodingStyle*属性被指定）
>
Sender                             SOAP消息格式错误、不包含有效的数据或者缺少数据等，换句话说，消息的发送方发送了错误的SOAP消息。
>
Receiver                          SOAP消息的接收者不能处理此消息。责任完全在消息的接收方，例如：web service需要数据库支持但是数据库
                                            宕机了。

更多信息关于 SOAP Fault在SOAP spec - fault codes section.http://www.w3.org/TR/2007/REC-soap12-part1-20070427/#faultcodes

你可以自己定义*Subcode*元素包含任何值到*Value*子元素中，*Subcode*元素可以循环嵌套*Subcode*元素

下面是*Code*元素的例子

    <env:Code>
    
      <env:Value>env:Sender</env:Value>
    
      <env:Subcode>
        <env:Value>env:Sender</env:Value>
        <env:Subcode> <-- recursive Subcode's possible -->
        </env:Subcode>
      </env:Subcode>
    
    </env:Code>

**Reason**

*Reason*元素是强制要有的，*Reason*元素可以包含一个或者多个*Text*元素作为子元素，*Text*元素包含任何语言格式的错误的原因，*Text*元素的*lang*属性可以是ISO规定的语言代码值。

下面是包含相同错误信息的英语和丹麦语的例子

    <env:Reason xmlns:xml="http://www.w3.org/XML/1998/namespace" >
     <env:Text >Error in Input Data</env:Text>
     <env:Text xml:lang="da">Fejl i input data</env:Text>
    </env:Reason>

**Node**

*Node*元素是可选的，他应该包含当前发生错误的URI标识符，URI标识符可以自定义。

下面是例子：

    <env:Node>http://jenkov.com/theNodeThatFailed</env:Node>

**Role**

*Role*元素是可选的，他应该包含消息路径中产生错误的节点的角色，“角色”详细信息见“SOAP 角色”相关内容。

下面是例子

    <env:Role>
        http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver
    </env:Role>

**Detail**

*Detail*元素是可选的，他应该包含描述错误产生详细信息的子元素，不能直接将文本信息放置在*Detail*元素内，所有的文本信息需要放置在Detail元素的子元素内。
所有的*Detail*元素的子元素应该使用合法的命名空间，表明这些子元素属于自己的命名空间。

下面是例子：

    <env:Detail
        <jj:maxRelayTime
            xmlns:jj="http://jenkov.com" >10000</jj:MaxRelayTime>
      </env:Detail>


SOAP Roles元素
==============

>内容
- 预定义SOAP Roles
- 用户SOAP Roles
- Header元素中的SOAP Roles
- Fault元素中的SOAP Roles

消息路径中处理/转发SOAP消息的节点被认为是扮演着一个或多个SOAP角色，这里有一个示意图展示了包含3个节点的SOAP消息处理过程：


![Alt text](http://tutorials.jenkov.com/images/soap/soap-roles-1.png)
                                         **处理过程中节点角色.**

第一个节点是消息的发送者，这个节点的角色在SOAP规范中没有被提及。

第二个节点是进行SOAP消息转发的中间节点，中间的节点也可以改变SOAP消息的内容，例如：它们可以添加、修改或者是删除Header元素或者改变Body元素中的内容，中间节点被定义为扮演者"next"角色。

图中SOAP消息中的最后一个节点是"ultimateReceiver"，最终的接收节点是最终的SOAP消息的处理者，是"web service"的另一个说法，可以理解为"web service"实际上包含了整个处理SOAP消息的所有节点不仅仅是最终的接收者。

**预定义的SOAP角色**

SOAP规范预定义的三个角色：

>**SOAP Roles**
角色名称            角色URI
next                http://www.w3.org/2003/05/soap-envelope/role/next
none                http://www.w3.org/2003/05/soap-envelope/role/none
ultimateReceiver    http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver

所有的中间节点和最终接收节点被假定为next角色

none角色比较特殊，不包含任何节点，到达该角色的SOAP消息Header区域在该节点的左侧没有被处理过或者是在处理其它Header区域时已经被使用过。

ultimateReceiver角色为SOAP消息的最总接收者保留，没有该角色属性的Header区域不能处理此区域。

**用户自定义SOAP Roles**

SOAP角色并不仅限于上一节中预定义的三种角色，SOAP角色可以是任何自定义的角色，如果你定义了你自己的角色，你也必须同时定义角色的语义，换句话说你必须决定这些自定义角色所执行操作的意义。

**Header元素中SOAP角色**

SOAP Header元素可以使用SOAP角色

下面是Header元素使用*role*属性：

    <env:Header>
      <jj:maxTime value="10000" xmlns:jj="http://jenkov.com"
        role="http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver"
        />
    </env:Header>

当Header元素的子元素包含*role*属性，只有作为这个角色的节点才可以处理此元素，所有其它节点都不做处理。

**Fault元素中的SOAP角色**

SOAP 角色也可以用在*Fault*元素，*Fault*元素中的角色信息用来说明产生错误的节点的角色。
下面是*Fault*元素嵌套*Role*元素的例子：

    <env:Fault>
    
      <env:Code>
        <env:Value>env:Sender</env:Value>
      </env:Code>
    
      <env:Reason>
       <env:Text xml:lang="en-US">Error in Input Data</env:Text>
      </env:Reason>
    
      <env:Node>http://jenkov.com/theNodeThatFailed</env:Node>
    
      <env:Role>
        http://www.w3.org/2003/05/soap-envelope/role/ultimateReceiver
      </env:Role>
    
    </env:Fault>

SOAP消息交换模式
====================

>**内容**
- 请求-响应模式
- 响应模式

SOAP规范提到了一个概念"message exchange patterns" (MEP) 。在SOAP规范中有两种消息交换模式：
1. 请求-响应
2. 响应

本小节将对这两种消息交换模式进行描述。

**请求-响应模式**

请求-响应消息交换模式是SOAP客户端发送一个SOAP请求消息到服务器端，服务器端以SOAP格式的消息返回客户端。

当SOAP服务需要SOAP客户端发送的数据才能执行任务时，请求-响应消息交换模式是必要的，例如：如果客户端需要将数据存储在服务器端，那么客户端必须把需要被存储的数据发送到服务器端。

下边图例描述了请求-响应消息交换：

![Alt text](http://tutorials.jenkov.com/images/soap/soap-mep-1.png)
                                **SOAP请求-响应消息交换**


**响应模式**

响应消息交换模式是SOAP客户端连接到服务器端，但是不向服务器发送SOAP消息内容，而是发送一个简单的HTTP请求,然后服务器返回响应的SOAP消息。

这种消息交换模式和浏览器与web服务器进行通讯的方式相似，浏览器发送一个HTTP请求去请求相应的页面，但是这个HTTP请求没有携带任何额外的数据，然后web服务器返回请求的页面。

响应消息交换模式的图例：

![Alt text](http://tutorials.jenkov.com/images/soap/soap-mep-2.png)
                                    **SOAP响应消息交换**


原文地址：http://tutorials.jenkov.com/soap/index.html

作者： Jakob Jenkov

译者：赵亮

