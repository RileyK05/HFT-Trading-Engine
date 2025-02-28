#include "hftTradingEngine.h"
#include "execute/Order.h"
#include <curl/curl.h>
#include <iostream>
#include <string>

// Callback function for cURL to write response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t total_size = size * nmemb;
    response->append((char*)contents, total_size);
    return total_size;
}

// Function to test cURL functionality
bool testCurl()
{
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "cURL initialization failed" << std::endl;
        return false;
    }

    // Set URL (use a simple endpoint for testing)
    curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get");

    // Set write callback function
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    bool success = (res == CURLE_OK);
    if (!success) {
        std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
    }
    else {
        std::cout << "cURL request successful. Response:\n" << response << std::endl;
    }

    // Clean up
    curl_easy_cleanup(curl);

    return success;
}

int main()
{
    std::cout << "Testing HFT Trading Engine..." << std::endl;

    // Initialize cURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Test cURL functionality
    bool curlWorks = testCurl();
    std::cout << "cURL is " << (curlWorks ? "working properly!" : "not working correctly.") << std::endl;

    // Clean up cURL global resources
    curl_global_cleanup();

    return 0;
}