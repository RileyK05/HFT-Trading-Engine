#pragma once

#include <iostream>
#include <array>
#include <string>

enum class OrderStatus {
    NEW,
    PENDING,
    ACCEPTED,
    PARTIALLY_FILLED,
    FILLED,
    CANCELLED,
    REJECTED,
    EXPIRED,
    SUSPENDED,
    PENDING_CANCEL,
    PENDING_REPLACE,
    REPLACED,
    DONE_FOR_DAY,
    ERROR
};

enum class OrderTypes {
    MARKET,
    LIMIT, 
    STOP, 
    STOP_LIMIT,
    TRAILING_STOP,
    ICEBERG,
    FILL_OR_KILL,
    IMMEDIATE_OR_CANCEL,
    ALL_OR_NONE,
    GTC,
    GTD,
    AT_THE_OPEN,
    AT_THE_CLOSE,
    PEGGED,
    MIDPOINT
};

class Order {
private:
	std::string ticker;
    OrderStatus orderStatus;
    OrderTypes orderType;
    double quantity;
    long double price;
    long long id;
    time_t timeOfPurchase;
    bool validPurchase;

public:
    //Default constructor, use when no idea about order
    Order() :
        ticker(""),
        orderStatus(OrderStatus::NEW),
        orderType(OrderTypes::MARKET),
        quantity(0.0),
        price(0.0),
        id(0),
        timeOfPurchase(0),
        validPurchase(false)
    {}

    //Parameterized constructor, use when order is placed with all info given
    Order(std::string newTicker, OrderTypes type, double orderQty) :
        ticker(newTicker),
        orderType(type),
        orderStatus(OrderStatus::NEW),
        quantity(orderQty),
        price(getOrderPrice()),
        id(generateId()),
        timeOfPurchase(getOrderTime()),
        validPurchase(isValidPurchase())
    { }


    long double getOrderPrice();
    long long generateId();
    time_t getOrderTime();
    bool isValidPurchase();

};
