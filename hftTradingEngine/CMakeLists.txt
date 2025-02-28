# Create the executable with just the main.cpp file first
# We'll add other files as you develop them
set(SOURCES
    src/main.cpp
)

# Add header files
set(HEADERS
    # We'll uncomment these as you implement them
    # include/strategy/Strategy.h
    # include/strategy/PairsStrategy.h
    # include/strategy/VwapStrategy.h
    # include/market/MarketData.h
    # include/market/MarketDataProvider.h
    # include/execute/Order.h
    # include/execute/OrderManager.h
    # include/risk/RiskManager.h
)

# Create the executable
add_executable(hftEngine ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(hftEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set compile options for different platforms
if(MSVC)
    target_compile_options(hftEngine PRIVATE /W4)
else()
    target_compile_options(hftEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()