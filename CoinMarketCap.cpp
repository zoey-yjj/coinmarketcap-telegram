#include "CoinMarketCap.h"
#include "HttpClient.h"
#include <iostream>

CoinMarketCap::CoinMarketCap(const std::string& apiKey) : apiKey(apiKey) {}

Json::Value CoinMarketCap::getMarketData(const std::string& symbol, const std::string& base) {
    std::string url = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?symbol=" + symbol;

    HttpClient httpClient;

    httpClient.addHeader("X-CMC_PRO_API_KEY", apiKey);

    std::string response = httpClient.getRequest(url);

    Json::Value jsonData;
    Json::Reader jsonReader;

    if (!jsonReader.parse(response, jsonData)) {
        std::cerr << "Failed to parse JSON: " << jsonReader.getFormattedErrorMessages() << std::endl;
        return Json::Value();
    }

    return jsonData["data"][symbol]["quote"][base];
}
