// fetch_input.cpp
#include <iostream>
#include <string>
#include <curl/curl.h>

#include "fetch_input.h"

// Callback function for libcurl to handle data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    size_t totalSize = size * nmemb;
    userData->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch input from a URL using libcurl
std::string fetchInput(const std::string& url, const std::string& sessionCookie) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize libcurl
    curl = curl_easy_init();
    if (curl) {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the session cookie for authentication
        curl_easy_setopt(curl, CURLOPT_COOKIE, ("session=" + sessionCookie).c_str());

        // Set the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Pass the string buffer to the callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            std::cout << "Data fetched successfully" << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize libcurl" << std::endl;
    }

    return readBuffer;
}
