001 # ===================================================================
002 # COMMON SPRING BOOT PROPERTIES
003 #
004 # This sample file is provided as a guideline. Do NOT copy it in its
005 # entirety to your own application.               ^^^
006 # ===================================================================
007 
008 # ----------------------------------------
009 # CORE PROPERTIES
010 # ----------------------------------------
011 
012 # SPRING CONFIG (ConfigFileApplicationListener)
013 spring.config.name= # config file name (default to 'application')
014 spring.config.location= # location of config file
015 
016 # PROFILES
017 spring.profiles= # comma list of active profiles
018 
019 # APPLICATION SETTINGS (SpringApplication)
020 spring.main.sources=
021 spring.main.web-environment= # detect by default
022 spring.main.show-banner=true
023 spring.main....= # see class for all properties
024 
025 # LOGGING
026 logging.path=/var/logs
027 logging.file=myapp.log
028 logging.config=
029 
030 # IDENTITY (ContextIdApplicationContextInitializer)
031 spring.application.name=
032 spring.application.index=
033 
034 # EMBEDDED SERVER CONFIGURATION (ServerProperties)
035 server.port=8080
036 server.address= # bind to a specific NIC
037 server.session-timeout= # session timeout in seconds
038 server.context-path= # the context path, defaults to '/'
039 server.servlet-path= # the servlet path, defaults to '/'
040 server.tomcat.access-log-pattern= # log pattern of the access log
041 server.tomcat.access-log-enabled=false # is access logging enabled
042 server.tomcat.protocol-header=x-forwarded-proto # ssl forward headers
043 server.tomcat.remote-ip-header=x-forwarded-for
044 server.tomcat.basedir=/tmp # base dir (usually not needed, defaults to tmp)
045 server.tomcat.background-processor-delay=30; # in seconds
046 server.tomcat.max-threads = 0 # number of threads in protocol handler
047 server.tomcat.uri-encoding = UTF-8 # character encoding to use for URL decoding
048 
049 # SPRING MVC (HttpMapperProperties)
050 http.mappers.json-pretty-print=false # pretty print JSON
051 http.mappers.json-sort-keys=false # sort keys
052 spring.mvc.locale= # set fixed locale, e.g. en_UK
053 spring.mvc.date-format= # set fixed date format, e.g. dd/MM/yyyy
054 spring.mvc.message-codes-resolver-format= # PREFIX_ERROR_CODE / POSTFIX_ERROR_CODE
055 spring.view.prefix= # MVC view prefix
056 spring.view.suffix= # ... and suffix
057 spring.resources.cache-period= # cache timeouts in headers sent to browser
058 spring.resources.add-mappings=true # if default mappings should be added
059 
060 # THYMELEAF (ThymeleafAutoConfiguration)
061 spring.thymeleaf.prefix=classpath:/templates/
062 spring.thymeleaf.suffix=.html
063 spring.thymeleaf.mode=HTML5
064 spring.thymeleaf.encoding=UTF-8
065 spring.thymeleaf.content-type=text/html # ;charset=<encoding> is added
066 spring.thymeleaf.cache=true # set to false for hot refresh
067 
068 # FREEMARKER (FreeMarkerAutoConfiguration)
069 spring.freemarker.allowRequestOverride=false
070 spring.freemarker.allowSessionOverride=false
071 spring.freemarker.cache=true
072 spring.freemarker.checkTemplateLocation=true
073 spring.freemarker.contentType=text/html
074 spring.freemarker.exposeRequestAttributes=false
075 spring.freemarker.exposeSessionAttributes=false
076 spring.freemarker.exposeSpringMacroHelpers=false
077 spring.freemarker.prefix=
078 spring.freemarker.requestContextAttribute=
079 spring.freemarker.settings.*=
080 spring.freemarker.suffix=.ftl
081 spring.freemarker.templateEncoding=UTF-8
082 spring.freemarker.templateLoaderPath=classpath:/templates/
083 spring.freemarker.viewNames= # whitelist of view names that can be resolved
084 
085 # GROOVY TEMPLATES (GroovyTemplateAutoConfiguration)
086 spring.groovy.template.allowRequestOverride=false
087 spring.groovy.template.allowSessionOverride=false
088 spring.groovy.template.cache=true
089 spring.groovy.template.configuration.*= # See Groovy's TemplateConfiguration
090 spring.groovy.template.contentType=text/html
091 spring.groovy.template.prefix=classpath:/templates/
092 spring.groovy.template.suffix=.tpl
093 spring.groovy.template.templateEncoding=UTF-8
094 spring.groovy.template.viewNames= # whitelist of view names that can be resolved
095 
096 # VELOCITY TEMPLATES (VelocityAutoConfiguration)
097 spring.velocity.allowRequestOverride=false
098 spring.velocity.allowSessionOverride=false
099 spring.velocity.cache=true
100 spring.velocity.checkTemplateLocation=true
101 spring.velocity.contentType=text/html
102 spring.velocity.dateToolAttribute=
103 spring.velocity.exposeRequestAttributes=false
104 spring.velocity.exposeSessionAttributes=false
105 spring.velocity.exposeSpringMacroHelpers=false
106 spring.velocity.numberToolAttribute=
107 spring.velocity.prefix=
108 spring.velocity.properties.*=
109 spring.velocity.requestContextAttribute=
110 spring.velocity.resourceLoaderPath=classpath:/templates/
111 spring.velocity.suffix=.vm
112 spring.velocity.templateEncoding=UTF-8
113 spring.velocity.viewNames= # whitelist of view names that can be resolved
114 
115 # INTERNATIONALIZATION (MessageSourceAutoConfiguration)
116 spring.messages.basename=messages
117 spring.messages.cacheSeconds=-1
118 spring.messages.encoding=UTF-8
119 
120 
121 # SECURITY (SecurityProperties)
122 security.user.name=user # login username
123 security.user.password= # login password
124 security.user.role=USER # role assigned to the user
125 security.require-ssl=false # advanced settings ...
126 security.enable-csrf=false
127 security.basic.enabled=true
128 security.basic.realm=Spring
129 security.basic.path= # /**
130 security.headers.xss=false
131 security.headers.cache=false
132 security.headers.frame=false
133 security.headers.contentType=false
134 security.headers.hsts=all # none / domain / all
135 security.sessions=stateless # always / never / if_required / stateless
136 security.ignored=false
137 
138 # DATASOURCE (DataSourceAutoConfiguration & DataSourceProperties)
139 spring.datasource.name= # name of the data source
140 spring.datasource.initialize=true # populate using data.sql
141 spring.datasource.schema= # a schema (DDL) script resource reference
142 spring.datasource.data= # a data (DML) script resource reference
143 spring.datasource.platform= # the platform to use in the schema resource (schema-${platform}.sql)
144 spring.datasource.continueOnError=false # continue even if can't be initialized
145 spring.datasource.separator=; # statement separator in SQL initialization scripts
146 spring.datasource.driverClassName= # JDBC Settings...
147 spring.datasource.url=
148 spring.datasource.username=
149 spring.datasource.password=
150 spring.datasource.max-active=100 # Advanced configuration...
151 spring.datasource.max-idle=8
152 spring.datasource.min-idle=8
153 spring.datasource.initial-size=10
154 spring.datasource.validation-query=
155 spring.datasource.test-on-borrow=false
156 spring.datasource.test-on-return=false
157 spring.datasource.test-while-idle=
158 spring.datasource.time-between-eviction-runs-millis=
159 spring.datasource.min-evictable-idle-time-millis=
160 spring.datasource.max-wait-millis=
161 
162 # MONGODB (MongoProperties)
163 spring.data.mongodb.host= # the db host
164 spring.data.mongodb.port=27017 # the connection port (defaults to 27107)
165 spring.data.mongodb.uri=mongodb://localhost/test # connection URL
166 spring.data.mongo.repositories.enabled=true # if spring data repository support is enabled
167 
168 # JPA (JpaBaseConfiguration, HibernateJpaAutoConfiguration)
169 spring.jpa.properties.*= # properties to set on the JPA connection
170 spring.jpa.openInView=true
171 spring.jpa.show-sql=true
172 spring.jpa.database-platform=
173 spring.jpa.database=
174 spring.jpa.generate-ddl=false # ignored by Hibernate, might be useful for other vendors
175 spring.jpa.hibernate.naming-strategy= # naming classname
176 spring.jpa.hibernate.ddl-auto= # defaults to create-drop for embedded dbs
177 spring.data.jpa.repositories.enabled=true # if spring data repository support is enabled
178 
179 # SOLR (SolrProperties})
180 spring.data.solr.host=http://127.0.0.1:8983/solr
181 spring.data.solr.zkHost=
182 spring.data.solr.repositories.enabled=true # if spring data repository support is enabled
183 
184 # ELASTICSEARCH (ElasticsearchProperties})
185 spring.data.elasticsearch.cluster-name= # The cluster name (defaults to elasticsearch)
186 spring.data.elasticsearch.cluster-nodes= # The address(es) of the server node (comma-separated; if not specified starts a client node)
187 spring.data.elasticsearch.local=true # if local mode should be used with client nodes
188 spring.data.elasticsearch.repositories.enabled=true # if spring data repository support is enabled
189 
190 
191 
192 # FLYWAY (FlywayProperties)
193 flyway.locations=classpath:db/migrations # locations of migrations scripts
194 flyway.schemas= # schemas to update
195 flyway.initVersion= 1 # version to start migration
196 flyway.prefix=V
197 flyway.suffix=.sql
198 flyway.enabled=true
199 flyway.url= # JDBC url if you want Flyway to create its own DataSource
200 flyway.user= # JDBC username if you want Flyway to create its own DataSource
201 flyway.password= # JDBC password if you want Flyway to create its own DataSource
202 
203 # LIQUIBASE (LiquibaseProperties)
204 liquibase.change-log=classpath:/db/changelog/db.changelog-master.yaml
205 liquibase.contexts= # runtime contexts to use
206 liquibase.default-schema= # default database schema to use
207 liquibase.drop-first=false
208 liquibase.enabled=true
209 
210 # JMX
211 spring.jmx.enabled=true # Expose MBeans from Spring
212 
213 # RABBIT (RabbitProperties)
214 spring.rabbitmq.host= # connection host
215 spring.rabbitmq.port= # connection port
216 spring.rabbitmq.addresses= # connection addresses (e.g. myhost:9999,otherhost:1111)
217 spring.rabbitmq.username= # login user
218 spring.rabbitmq.password= # login password
219 spring.rabbitmq.virtualhost=
220 spring.rabbitmq.dynamic=
221 
222 # REDIS (RedisProperties)
223 spring.redis.host=localhost # server host
224 spring.redis.password= # server password
225 spring.redis.port=6379 # connection port
226 spring.redis.pool.max-idle=8 # pool settings ...
227 spring.redis.pool.min-idle=0
228 spring.redis.pool.max-active=8
229 spring.redis.pool.max-wait=-1
230 
231 # ACTIVEMQ (ActiveMQProperties)
232 spring.activemq.broker-url=tcp://localhost:61616 # connection URL
233 spring.activemq.user=
234 spring.activemq.password=
235 spring.activemq.in-memory=true # broker kind to create if no broker-url is specified
236 spring.activemq.pooled=false
237 
238 # HornetQ (HornetQProperties)
239 spring.hornetq.mode= # connection mode (native, embedded)
240 spring.hornetq.host=localhost # hornetQ host (native mode)
241 spring.hornetq.port=5445 # hornetQ port (native mode)
242 spring.hornetq.embedded.enabled=true # if the embedded server is enabled (needs hornetq-jms-server.jar)
243 spring.hornetq.embedded.serverId= # auto-generated id of the embedded server (integer)
244 spring.hornetq.embedded.persistent=false # message persistence
245 spring.hornetq.embedded.data-directory= # location of data content (when persistence is enabled)
246 spring.hornetq.embedded.queues= # comma separate queues to create on startup
247 spring.hornetq.embedded.topics= # comma separate topics to create on startup
248 spring.hornetq.embedded.cluster-password= # customer password (randomly generated by default)
249 
250 # JMS (JmsProperties)
251 spring.jms.pub-sub-domain= # false for queue (default), true for topic
252 
253 # SPRING BATCH (BatchDatabaseInitializer)
254 spring.batch.job.names=job1,job2
255 spring.batch.job.enabled=true
256 spring.batch.initializer.enabled=true
257 spring.batch.schema= # batch schema to load
258 
259 # AOP
260 spring.aop.auto=
261 spring.aop.proxy-target-class=
262 
263 # FILE ENCODING (FileEncodingApplicationListener)
264 spring.mandatory-file-encoding=false
265 
266 # SPRING SOCIAL (SocialWebAutoConfiguration)
267 spring.social.auto-connection-views=true # Set to true for default connection views or false if you provide your own
268 
269 # SPRING SOCIAL FACEBOOK (FacebookAutoConfiguration)
270 spring.social.facebook.app-id= # your application's Facebook App ID
271 spring.social.facebook.app-secret= # your application's Facebook App Secret
272 
273 # SPRING SOCIAL LINKEDIN (LinkedInAutoConfiguration)
274 spring.social.linkedin.app-id= # your application's LinkedIn App ID
275 spring.social.linkedin.app-secret= # your application's LinkedIn App Secret
276 
277 # SPRING SOCIAL TWITTER (TwitterAutoConfiguration)
278 spring.social.twitter.app-id= # your application's Twitter App ID
279 spring.social.twitter.app-secret= # your application's Twitter App Secret
280 
281 # SPRING MOBILE SITE PREFERENCE (SitePreferenceAutoConfiguration)
282 spring.mobile.sitepreference.enabled=true # enabled by default
283 
284 # SPRING MOBILE DEVICE VIEWS (DeviceDelegatingViewResolverAutoConfiguration)
285 spring.mobile.devicedelegatingviewresolver.enabled=true # disabled by default
286 spring.mobile.devicedelegatingviewresolver.normalPrefix=
287 spring.mobile.devicedelegatingviewresolver.normalSuffix=
288 spring.mobile.devicedelegatingviewresolver.mobilePrefix=mobile/
289 spring.mobile.devicedelegatingviewresolver.mobileSuffix=
290 spring.mobile.devicedelegatingviewresolver.tabletPrefix=tablet/
291 spring.mobile.devicedelegatingviewresolver.tabletSuffix=
292 
293 # ----------------------------------------
294 # ACTUATOR PROPERTIES
295 # ----------------------------------------
296 
297 # MANAGEMENT HTTP SERVER (ManagementServerProperties)
298 management.port= # defaults to 'server.port'
299 management.address= # bind to a specific NIC
300 management.contextPath= # default to '/'
301 
302 # ENDPOINTS (AbstractEndpoint subclasses)
303 endpoints.autoconfig.id=autoconfig
304 endpoints.autoconfig.sensitive=true
305 endpoints.autoconfig.enabled=true
306 endpoints.beans.id=beans
307 endpoints.beans.sensitive=true
308 endpoints.beans.enabled=true
309 endpoints.configprops.id=configprops
310 endpoints.configprops.sensitive=true
311 endpoints.configprops.enabled=true
312 endpoints.configprops.keys-to-sanitize=password,secret
313 endpoints.dump.id=dump
314 endpoints.dump.sensitive=true
315 endpoints.dump.enabled=true
316 endpoints.env.id=env
317 endpoints.env.sensitive=true
318 endpoints.env.enabled=true
319 endpoints.health.id=health
320 endpoints.health.sensitive=false
321 endpoints.health.enabled=true
322 endpoints.info.id=info
323 endpoints.info.sensitive=false
324 endpoints.info.enabled=true
325 endpoints.metrics.id=metrics
326 endpoints.metrics.sensitive=true
327 endpoints.metrics.enabled=true
328 endpoints.shutdown.id=shutdown
329 endpoints.shutdown.sensitive=true
330 endpoints.shutdown.enabled=false
331 endpoints.trace.id=trace
332 endpoints.trace.sensitive=true
333 endpoints.trace.enabled=true
334 
335 # MVC ONLY ENDPOINTS
336 endpoints.jolokia.path=jolokia
337 endpoints.jolokia.sensitive=true
338 endpoints.jolokia.enabled=true # when using Jolokia
339 endpoints.error.path=/error
340 
341 # JMX ENDPOINT (EndpointMBeanExportProperties)
342 endpoints.jmx.enabled=true
343 endpoints.jmx.domain= # the JMX domain, defaults to 'org.springboot'
344 endpoints.jmx.unique-names=false
345 endpoints.jmx.enabled=true
346 endpoints.jmx.staticNames=
347 
348 # JOLOKIA (JolokiaProperties)
349 jolokia.config.*= # See Jolokia manual
350 
351 # REMOTE SHELL
352 shell.auth=simple # jaas, key, simple, spring
353 shell.command-refresh-interval=-1
354 shell.command-path-pattern= # classpath*:/commands/**, classpath*:/crash/commands/**
355 shell.config-path-patterns= # classpath*:/crash/*
356 shell.disabled-plugins=false # don't expose plugins
357 shell.ssh.enabled= # ssh settings ...
358 shell.ssh.keyPath=
359 shell.ssh.port=
360 shell.telnet.enabled= # telnet settings ...
361 shell.telnet.port=
362 shell.auth.jaas.domain= # authentication settings ...
363 shell.auth.key.path=
364 shell.auth.simple.user.name=
365 shell.auth.simple.user.password=
366 shell.auth.spring.roles=
367 
368 # GIT INFO
369 spring.git.properties= # resource ref to generated git info properties file