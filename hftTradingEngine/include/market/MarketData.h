#pragma once

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <memory>

enum class Conditions {
    REGULAR,
    PRE_MARKET,
    AFTER_MARKET
};

struct PriceInfo {
    long double price, bid, ask, last, open, high, low, close;
};

struct Volume {
    long long volume, bidSize, askSize, accumVolume;
};

struct Time {
    std::chrono::microseconds timestamp;
    uint64_t sequenceNumber; 
};

struct Classifiers {
    Conditions condition; 
    std::string exchange;
};

struct Tick {
    PriceInfo priceInfo;
    Volume volume;
    Time time;
    Classifiers classifiers;
};

class Equity {
private:
    std::string ticker;
    Tick lastTick; 
    std::unordered_map<std::string, std::vector<Tick>> equityInfo;
public:
    std::string getTicker();
    void setString(std::string newTckr);



};