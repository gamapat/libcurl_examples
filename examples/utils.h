#pragma once
#include <curl/curl.h>
#include <memory>
#include <functional>
#include <stdexcept>

class CurlGlobalStateGuard
{
public:
    inline CurlGlobalStateGuard() { curl_global_init(CURL_GLOBAL_DEFAULT); }
    inline ~CurlGlobalStateGuard() { curl_global_cleanup(); }
};


void curl_deinit(CURL* ptr);
void curl_multi_deinit(CURLM* ptr);

using EasyHandle = std::unique_ptr<CURL, std::function<void(CURL*)>>;
using MultiHandle = std::unique_ptr<CURLM, std::function<void(CURLM*)>>;

EasyHandle CreateEasyHandle();
MultiHandle CreateMultiHandle();

int download_synchronous();
int download_asynchronous();
int download_multiplexing();

void set_ssl(CURL* curl);
void to_memory(CURL* curl);