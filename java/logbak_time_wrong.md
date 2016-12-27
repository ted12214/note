## 起因
有一个项目logbak输出的日志信息总是不对,但是tomcat的日志时间是正确的,开始怀疑是因为springboot 项目的问题,但是没找到,后来将tomcat的 -Dtime.zone=GMT+8还是不好使,最终看log


	{yyyy-MM-dd HH:mm:ss,SSS}
修改为:
	
	{yyyy-MM-dd HH:mm:ss.SSS}

因为在时间格式中","后边的内容表示时区,但是修改之前无法得到"SSS"时区,所以取了默认的时区
