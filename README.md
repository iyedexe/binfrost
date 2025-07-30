# Description
This repo aims to build a simple to use client library for Binance.       
Client supports FIX, Websockets and Rest APIs.   
Order Entry, Market Data, Drop Copy (FIX) connections to be supported.   
Performance and ease of use are key.    

# Building on windows:
```
VCPKG_ROOT=C:\Users\Administrator\Desktop\workbench\vcpkg
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
cmake --build build
```

# Building on linux:
Make sure VCPKG is installed and VCPKG_ROOT and PATH are configured
```
export VCPKG_ROOT=$HOME/workbench/vcpkg
export PATH=$PATH:$VCPKG_ROOT

```
Build the project
```
make .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
```

# DONE :
[FIX] Build basic client.   
[FIX] Connect TLS to binance.   
[FIX] Generate ED25519 signature.   
[FIX] add unit tests.   
[FIX] separate client session and client router.     
[WS_API] Implement base.   
[UTILS] refactor utils and add hmac.   
[REST_CLIENT] Implement.   
[WS_STREAMS] test user streams.   
[WS_STREAMS] Refactor streams client.   
[WS_API] Default constructor for all requests, parameter addition operator.  
[WS_API] Implement critical messages : Exchange info.    
[WS_API] Implement critical messages : Place order, Test Order, Cancel All Orders.  
[BUILD] git pull binance xml.   
[FIX] Clean up architecture and reorganize code gen.   
[FIX] Set host name in the ssl certificate verification
[BUILD] use vcpkg for dependencies
[BUILD] build on windows
[FIX] add start script with source creds and stunnel hooks. (CANCELED).    
[FIX] clean fix8 reliquat and build on vpckg

# TODO : 
[FIX] migrate from fix8 to quick fix for better integrability
[BUILD] make the lib more portable.  
[LIBRARY] Export project as library and use in RTEX.   
[LIBRARY] Make version 0.0 Beta.   
[CRYPTO] Add support for ed25519 key loading.   
[UTESTS] Unit tests for signatures, payload generation, Key loading.   
[UTESTS] Unit tests for .   
[WS_ALL] Enforce parameters for request types.  
[WS_API] Implement critical messages : Logon and no signature on messages once logged in.   
[ARCHITECTURE] Feeder and broker wrapper.   
[WS_STREAMS] Impelemnt critical messages maybe ?.      
[DEPENDECIES] User boost beast instead of websocketspp.   
[FIX] Implement messages.  
[WS] Feeder Broker Implement.   
[FIX] Feeder Broker Implement.   
[FIX] native ssl using fix8 pull request.   
more unit tests.


# Submodules :
## Websocketspp for websocket usage. 
```
https://github.com/zaphoyd/websocketpp  
```

## Nlohmann Json for json parsing and build.
```
https://github.com/nlohmann/json  
```

## Quill for logging.
```
https://github.com/odygrd/quill  
```

# ISSUES:


# Read Docs: 
https://www.codeproject.com/Articles/429147/The-FIX-client-and-server-implementation-using-Qui
https://developers.binance.com/docs/binance-spot-api-docs/testnet/fix-api.   
https://fix8.org/howitworks.html.  
https://fix8.org/fix8/html/index.html.   
