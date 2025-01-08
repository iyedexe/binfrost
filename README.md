# Description
This repo aims to build a simple fix client for Binance.   
Order Entry, Market Data, Drop Copy sessions to be supported.

# DONE: 
## Read Docs: 
https://developers.binance.com/docs/binance-spot-api-docs/testnet/fix-api.   
https://fix8.org/howitworks.html.  
https://fix8.org/fix8/html/index.html.   

## Install FIX8 dependencies:
### Install openssl
```
sudo yum install openssl
```
### Install POCO
```
sudo yum install poco-devel poco-foundation poco-net poco-netssl poco-crypto
```
## Install FIX8: 
```
git clone git@github.com:fix8/fix8.git   
./bootstrap   
./configure --enable-ssl --enable-debug
make  
sudo make install  
```

## Install libsodium
```
wget https://download.libsodium.org/libsodium/releases/libsodium-1.0.20-stable.tar.gz
./configure 
make && make check
sudo make install
```

## Install stunnel
```
sudo dnf install stunnel
```

## SSL configuration :
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/15368200/4.+Configuring+SSL+Clients+and+Servers.    
## due to the tls issue with the POCO library stunnel is used

# PRESENTATION : 
repo became a full on binance client,
must support WS, REST, FIX for spot endpoints.

# DONE :
[FIX] Build basic client
[FIX] Connect TLS to binance
[FIX] Generate ED25519 signature
[FIX] add unit tests
[FIX] separate client session and client router.  

# TODO : 
[WS_API] Implement.   
[REST_CLIENT] Implement.   
[WS_STREAMS] test user streams.   
[UTILS] refactor utils and add hmac.   
[ARCHITECTURE] Feeder and broker wrapper.   
[WS] Impelemnt messages.   
[FIX] Impeemt messages.  
[WS] Feeder Broker Implement.   
[FIX] Feeder Broker Implement.   

make the lib more portable.  
git pull binance xml.   
add start script with source creds and stunnel hooks.   
change namespaces for broker.  
implement feeder example.   
native ssl using fix8 pull request.   
more unit tests.