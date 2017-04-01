[原文地址:](http://www.baeldung.com/httpclient-post-http-request)http://www.baeldung.com/httpclient-post-http-request

##  Basic POST

simple example and send a POST request using HttpClient.

```JAVA
@Test
public void whenPostRequestUsingHttpClient_thenCorrect()
throws ClientProtocolException, IOException {
    CloseableHttpClient client = HttpClients.createDefault();
    HttpPost httpPost = newHttpPost("http://www.example.com");
    List params = newArrayList();
    params.add(newBasicNameValuePair("username", "John"));
    params.add(newBasicNameValuePair("password", "pass"));
    httpPost.setEntity(newUrlEncodedFormEntity(params));
    CloseableHttpResponse response = client.execute(httpPost);
    assertThat(response.getStatusLine().getStatusCode(), equalTo(200));
    client.close();
}
```


##  POST with Authorization

```JAVA
@Test
public void whenPostRequestWithAuthorizationUsingHttpClient_thenCorrect()
throws ClientProtocolException, IOException, AuthenticationException {
    CloseableHttpClient client = HttpClients.createDefault();
    HttpPost httpPost = newHttpPost("http://www.example.com");
    httpPost.setEntity(newStringEntity("test post"));
    UsernamePasswordCredentials creds
    = newUsernamePasswordCredentials("John", "pass");
    httpPost.addHeader(newBasicScheme().authenticate(creds, httpPost, null));
    CloseableHttpResponse response = client.execute(httpPost);
    assertThat(response.getStatusLine().getStatusCode(), equalTo(200));
    client.close();
}
```
## POST with JSON

```JAVA
@Test
public void whenPostJsonUsingHttpClient_thenCorrect()
throws ClientProtocolException, IOException {
    CloseableHttpClient client = HttpClients.createDefault();
    HttpPost httpPost = new HttpPost("http://www.example.com");
    String json = "{"id":1,"name":"John"}";
    StringEntity entity = newStringEntity(json);
    httpPost.setEntity(entity);
    httpPost.setHeader("Accept", "application/json");
    httpPost.setHeader("Content-type", "application/json");
    CloseableHttpResponse response = client.execute(httpPost);
    assertThat(response.getStatusLine().getStatusCode(), equalTo(200));
    client.close();
}
```
Note how we’re using the StringEntity to set the body of the request.

We are also setting the ContentType header to application/json to give the server the necessary information about the representation of the content we’re sending.

## POST with the HttpClient Fluent API


```JAVA
@Test
public void whenPostFormUsingHttpClientFluentAPI_thenCorrect()
throws ClientProtocolException, IOException {
    HttpResponse response =
    Request.Post("http://www.example.com").bodyForm(
    Form.form().add("username", "John").add("password", "pass").build())
    .execute().returnResponse();
    assertThat(response.getStatusLine().getStatusCode(), equalTo(200));
}
```
##  POST Multipart Request

Now – let’s POST a Multipart Request – in the following example, we’ll post a File, username, and password using MultipartEntityBuilder:
```JAVA
@Test
public void whenSendMultipartRequestUsingHttpClient_thenCorrect()
throws ClientProtocolException, IOException {
    CloseableHttpClient client = HttpClients.createDefault();
    HttpPost httpPost = newHttpPost("http://www.example.com");
    MultipartEntityBuilder builder = MultipartEntityBuilder.create();
    builder.addTextBody("username", "John");
    builder.addTextBody("password", "pass");
    builder.addBinaryBody("file", newFile("test.txt"),
    ContentType.APPLICATION_OCTET_STREAM, "file.ext");
    HttpEntity multipart = builder.build();
    httpPost.setEntity(multipart);
    CloseableHttpResponse response = client.execute(httpPost);
    assertThat(response.getStatusLine().getStatusCode(), equalTo(200));
    client.close();
}
```
## Upload a File using HttpClient

Next – let’s see how to upload a File using the HttpClient – we’ll upload the “test.txt” file using MultipartEntityBuilder:
```JAVA
@Test
publicvoidwhenUploadFileUsingHttpClient_thenCorrect()
throwsClientProtocolException, IOException {
    CloseableHttpClient client = HttpClients.createDefault();
    HttpPost httpPost = newHttpPost("http://www.example.com");
    MultipartEntityBuilder builder = MultipartEntityBuilder.create();
    builder.addBinaryBody("file", newFile("test.txt"),
    ContentType.APPLICATION_OCTET_STREAM, "file.ext");
    HttpEntity multipart = builder.build();
    httpPost.setEntity(multipart);
    CloseableHttpResponse response = client.execute(httpPost);
    assertThat(response.getStatusLine().getStatusCode(), equalTo(200));
    client.close();
}
```
## Get File UploadProgress

```JAVA
@Test
public void whenGetUploadFileProgressUsingHttpClient_thenCorrect()
throws ClientProtocolException, IOException {
    CloseableHttpClient client = HttpClients.createDefault();
    HttpPost httpPost = newHttpPost("http://www.example.com");
    MultipartEntityBuilder builder = MultipartEntityBuilder.create();
    builder.addBinaryBody("file", newFile("test.txt"),
    ContentType.APPLICATION_OCTET_STREAM, "file.ext");
    HttpEntity multipart = builder.build();
    ProgressEntityWrapper.ProgressListener pListener =
    newProgressEntityWrapper.ProgressListener() {
@Override
public void progress(floatpercentage) {
    assertFalse(Float.compare(percentage, 100) > 0);
    }
    };
    httpPost.setEntity(newProgressEntityWrapper(multipart, pListener));
    CloseableHttpResponse response = client.execute(httpPost);
    assertThat(response.getStatusLine().getStatusCode(), equalTo(200));
    client.close();
}
```
And here is the interface ProgressListener that enables us to observe the upload progress:

```JAVA
public static interfaceProgressListener {
  voidprogress(floatpercentage);
}
```
And here our extended version of HttpEntityWrapper “ProgressEntityWrapper“:
```JAVA 
public class ProgressEntityWrapper extendsHttpEntityWrapper {
private ProgressListener listener;
public ProgressEntityWrapper(HttpEntity entity,ProgressListener listener) {
  super(entity);
  this.listener = listener;
}
@Override
public void writeTo(OutputStream outstream) throwsIOException {
  super.writeTo(newCountingOutputStream(outstream,
  listener, getContentLength()));
}
}
```
And the extended version of FilterOutputStream “CountingOutputStream“:
```JAVA
public static class CountingOutputStream extendsFilterOutputStream {
private ProgressListener listener;
private longtransferred;
private longtotalBytes;
public CountingOutputStream(
OutputStream out, ProgressListener listener, longtotalBytes) {
super(out);
this.listener = listener;
transferred = 0;
this.totalBytes = totalBytes;
}
@Override
public void write(byte[] b, intoff, intlen) throwsIOException {
out.write(b, off, len);
transferred += len;
listener.progress(getCurrentProgress());
}
@Override
public void write(intb) throwsIOException {
out.write(b);
transferred++;
listener.progress(getCurrentProgress());
}
private float getCurrentProgress() {
return((float) transferred / totalBytes) * 100;
}
}
```
Note that:

When extending FilterOutputStream to “CountingOutputStream” – we are overriding the write() method to count the written (transferred) bytes
When extending HttpEntityWrapper to “ProgressEntityWrapper” – we are overriding the writeTo() method to use our “CountingOutputStream“
## Conclusion

In this tutorial, we illustrated the most common ways to send POST HTTP Requests with the Apache HttpClient 4.

We learned how to send a POST request with Authorization, how to post using HttpClient fluentAPI and how to upload a file and track its progress.

