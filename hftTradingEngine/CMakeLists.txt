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
    include/execute/Order.h
    # include/execute/OrderManager.h
    # include/risk/RiskManager.h
)

# Create the executable
add_executable(hftEngine ${SOURCES} ${HEADERS} "src/execute/Order.cpp")

# Add include directories
target_include_directories(hftEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIRS}  # Add cURL include directories
)

# Link cURL library
target_link_libraries(hftEngine PRIVATE ${CURL_LIBRARIES})

# Set compile options for different platforms
if(MSVC)
    target_compile_options(hftEngine PRIVATE /W4)
else()
    target_compile_options(hftEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()