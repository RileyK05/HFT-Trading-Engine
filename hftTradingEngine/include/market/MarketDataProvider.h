#pragma once
#include "MarketData.h" 
#include <curl/curl.h>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

class MarketDataProvider {
private:
    CURL* curl;
    std::string apiKey;
    bool isConnected;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

    std::unordered_map<std::string, Tick> latestTicks;
    std::unordered_set<std::string> subscribedSymbols;

    std::vector<std::function<void(const Tick&)>> tickCallbacks;

public:
    MarketDataProvider(const std::string& apiKey);
    ~MarketDataProvider();

    bool connect();
    void disconnect();
    bool isActive() const;

    bool getTickerData(const std::string& symbol, Tick& outTick);
    std::vector<Tick> getHistoricalData(const std::string& symbol,
        const std::string& startDate,
        const std::string& endDate);

    bool subscribe(const std::string& symbol);
    bool unsubscribe(const std::string& symbol);

    using TickCallback = std::function<void(const Tick&)>;
    void registerTickCallback(TickCallback callback);

    void update();

    Tick parseTickerData(const std::string& jsonData, const std::string& symbol);
};