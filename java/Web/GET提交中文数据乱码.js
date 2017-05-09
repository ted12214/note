#GET提交中文数据乱码

问题描述：form表单用post提交数据到后台好好的但是改用get方式提交到后台却乱码了。

## 相关资源整理

每个页面也都有<%@ page language="java" pageEncoding="UTF-8" %>说明。其中pageEncoding这个参数只对
post起作用。get方法提交时，方法传递是作为报文头提交的，而pageEncoding对报文头是没有作用的，所以仍然按照
iso8859-1编码，所以参数到后台才出现了乱码问题。而post提交的是form表单的内容，pageEncoding指定了它的编码，所以他会按照指定编码传递。

## 问题解决

由于tomcat的servlet实现中ServletRequest.setCharacterEncoding方法未对HTTP报文头的内容进行解码，因此
使用HTTP的GET方法提交的数据将不能正确的解码.
解决方案为修改其服务器的配置server.xml文件中对HTTP协议的
Connector配置，加上URIEncoding="UTF-8"属性，配置完成以后"可能"的内容为
< Connector port="8080"
maxThreads="150" minSpareThreads="25" maxSpareThreads="75"
enableLookups="false" redirectPort="8443" acceptCount="100"
debug="0" connectionTimeout="20000" 
disableUploadTimeout="true" URIEncoding="UTF-8" /> 
大功告成!