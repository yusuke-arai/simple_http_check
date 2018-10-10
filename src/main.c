#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    return nmemb;
}
 
void print_usage()
{
    printf(
        "NAME\n"
        "     simple_http_check - Check the HTTP status of specified URL.\n"
        "\n" 
        "SYNOPSIS\n"
        "     simple_http_check URL\n"
        "\n" 
        "DESCRIPTION\n"
        "     -f timeout_ms     Timeout in milliseconds.\n"
        "\n" 
    );
}

int request(const char *url, const long timeout)
{
    CURL *handle;
    int res;

    handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback); // discard the response
    curl_easy_setopt(handle, CURLOPT_TIMEOUT_MS, timeout);
    res = curl_easy_perform(handle);

    if (res != CURLE_OK) {
        printf("{\"curl_error_code\":%d,\"curl_error_msg\":\"%s\"}", res, curl_easy_strerror(res));
        return res;
    }

    double timep;
    curl_easy_getinfo(handle, CURLINFO_NAMELOOKUP_TIME, &timep);
    printf("{\"name_lookup\":%.2f", timep * 1000.0);
    curl_easy_getinfo(handle, CURLINFO_CONNECT_TIME, &timep);
    printf(",\"connect\":%.2f", timep * 1000.0);
    curl_easy_getinfo(handle, CURLINFO_APPCONNECT_TIME, &timep);
    printf(",\"ssl_connect\":%.2f", timep * 1000.0);
    curl_easy_getinfo(handle, CURLINFO_STARTTRANSFER_TIME, &timep);
    printf(",\"start_transfer\":%.2f", timep * 1000.0);
    curl_easy_getinfo(handle, CURLINFO_TOTAL_TIME, &timep);
    printf(",\"total\":%.2f", timep * 1000.0);
    printf("}");
    curl_easy_cleanup(handle);
    return res;
}

int main(int argc, char **argv)
{
    int opt;
    long timeout = 10000; // 10sec
    while ((opt = getopt(argc, argv, "t:")) != -1) {
        switch (opt) {
            case 't':
                timeout = atoi(optarg);
                break;
            default:
                print_usage();
                return 1;
        }
    }

    if (argc - optind != 1) {
        print_usage();
        return 1;
    }

    char *url = argv[optind];
    request(url, timeout);

    return 0;
}

