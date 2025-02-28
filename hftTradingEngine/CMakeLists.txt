# Create the executable with just the main.cpp file first
# We'll add other files as you develop them
set(SOURCES
    src/main.cpp
    src/execute/Order.cpp
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
add_executable(hftEngine ${SOURCES} ${HEADERS})

# Add include directories - direct approach to bypass find_package issues
target_include_directories(hftEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    "C:/Users/riley/vcpkg/installed/x64-windows/include"  # Direct cURL include path
)

# Link against cURL - direct approach to bypass find_package issues
target_link_libraries(hftEngine PRIVATE
    "C:/Users/riley/vcpkg/installed/x64-windows/lib/libcurl.lib"
)

# Copy the cURL DLL to the output directory
add_custom_command(TARGET hftEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/Users/riley/vcpkg/installed/x64-windows/bin/libcurl.dll"
    $<TARGET_FILE_DIR:hftEngine>
)

# Set compile options for different platforms
if(MSVC)
    target_compile_options(hftEngine PRIVATE /W4)
else()
    target_compile_options(hftEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()