#include "market/MarketDataProvider.h"
#include <iostream>

MarketDataProvider::MarketDataProvider(const std::string& key) : apiKey(key), isConnected(false) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

MarketDataProvider::~MarketDataProvider() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

bool MarketDataProvider::connect() {
    if (!curl) {
        curl = curl_easy_init();
        if (!curl) return false;
    }
    isConnected = true;
    return true;
}

void MarketDataProvider::disconnect() {
    isConnected = false;
}

bool MarketDataProvider::isActive() const {
    return isConnected && curl != nullptr;
}

size_t MarketDataProvider::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool MarketDataProvider::getTickerData(const std::string& symbol, Tick& outTick) {
    if (!isActive()) return false;

    std::string url = "https://api.marketdata.com/v1/quotes?symbol=" + symbol + "&apikey=" + apiKey;
    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    // Here you would parse the JSON response
    // For simplicity, we're just creating a dummy tick
    outTick.priceInfo.price = 150.25;
    outTick.priceInfo.bid = 150.20;
    outTick.priceInfo.ask = 150.30;
    outTick.priceInfo.last = 150.25;

    outTick.volume.volume = 100;
    outTick.volume.bidSize = 500;
    outTick.volume.askSize = 300;

    // Store in cache
    latestTicks[symbol] = outTick;

    return true;
}

std::vector<Tick> MarketDataProvider::getHistoricalData(const std::string& symbol,
    const std::string& startDate,
    const std::string& endDate) {
    std::vector<Tick> historicalData;

    if (!isActive()) return historicalData;

    std::string url = "https://api.marketdata.com/v1/historical?symbol=" + symbol +
        "&start=" + startDate + "&end=" + endDate + "&apikey=" + apiKey;
    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return historicalData;
    }

    // Parse the JSON response here
    // For now, return empty vector

    return historicalData;
}

bool MarketDataProvider::subscribe(const std::string& symbol) {
    subscribedSymbols.insert(symbol);
    return true;
}

bool MarketDataProvider::unsubscribe(const std::string& symbol) {
    subscribedSymbols.erase(symbol);
    return true;
}

void MarketDataProvider::registerTickCallback(TickCallback callback) {
    tickCallbacks.push_back(callback);
}

void MarketDataProvider::update() {
    if (!isActive()) return;

    for (const auto& symbol : subscribedSymbols) {
        Tick latestData;
        if (getTickerData(symbol, latestData)) {
            for (const auto& callback : tickCallbacks) {
                callback(latestData);
            }
        }
    }
}

