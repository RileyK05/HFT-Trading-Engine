#include <curl/curl.h>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <memory>

struct PriceInfo {
	long double price, bid, ask, last;
};
struct Volume {
	long long volume, bidSize, askSize, accumVolume;
};
struct Time {
	std::chrono::microseconds timestamp;
	uint64_t sequenceNumber;
};

struct Tick {
	PriceInfo priceInfo;
	Volume volume;
	Time time;
};

class Equity {
private:
	std::string ticker;
	std::unordered_map<std::string, Tick> equityInfo; //string represents the ticker
public:

};

