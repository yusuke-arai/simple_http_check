# Simple HTTP check #

Check the status of specified URL via [libcurl](https://curl.haxx.se/libcurl/c/libcurl.html).
Return the status as a JSON.

## Build ##

```
cd simple_http_check
make
```

libcurl is needed.
Executable is created in `bin`.

## Run ##

```
simple_check_http https://example.com/
```

You can also specify timeout in milliseconds (default 10,000).

```
simple_check_http -t 5000 https://example.com/
```

### Output on success ###

```
{
    "name_lookup": 5.16,
    "connect": 115.66,
    "ssl_connect": 364.25,
    "start_transfer": 471.11,
    "total":471.15
}
```

* `name_lookup` : Time in milliseconds from start until name resolving completed. See [CURLINFO_NAMELOOKUP_TIME](https://curl.haxx.se/libcurl/c/CURLINFO_NAMELOOKUP_TIME.html).
* `connect` : Time in milliseconds from start until remote host or proxy completed. See [CURLINFO_CONNECT_TIME](https://curl.haxx.se/libcurl/c/CURLINFO_CONNECT_TIME.html).
* `ssl_connect` : Time in milliseconds from start until SSL/SSH handshake completed. See [CURLINFO_APPCONNECT_TIME](https://curl.haxx.se/libcurl/c/CURLINFO_APPCONNECT_TIME.html).
* `start_transfer` : Time in milliseconds from start until just when the first byte is received. See [CURLINFO_STARTTRANSFER_TIME](https://curl.haxx.se/libcurl/c/CURLINFO_STARTTRANSFER_TIME_T.html).
* `total` : Total time in milliseconds of previous transfer. See [CURLINFO_TOTAL_TIME](https://curl.haxx.se/libcurl/c/CURLINFO_TOTAL_TIME.html).

### Output on failure ###

```
{
    "curl_error_code": 28,
    "curl_error_msg": "Timeout was reached"
}
```

* `curl_error_code`: Error code. See [libcurl error codes](https://curl.haxx.se/libcurl/c/libcurl-errors.html).
* `curl_error_msg`: String describing error code. See [curl_easy_strerror](https://curl.haxx.se/libcurl/c/curl_easy_strerror.html).
