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


## Generate Fix code using xml:
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/360487/3.+Using+f8c+-+the+Fix8+compiler.   
```
f8c -p BNBBroker -n BNB spot-fix-oe.xml
```

## Configure and use generated Code.   
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/360504/6.+Session+configuration.   

## Constructuing a message:    
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/360493/4.+Using+the+generated+code.    
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/360514/7.+Constructing+a+new+message.   

## Sign ED25519 payload.  (VERY HARD)
https://developers.binance.com/docs/binance-spot-api-docs/testnet/fix-api#signaturecomputation.   
https://doc.libsodium.org/public-key_cryptography/public-key_signatures#detached-mode.   

## SSL configuration :
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/15368200/4.+Configuring+SSL+Clients+and+Servers.    
## due to the tls issue with the POCO library stunnel is used


## Set header and footer on LogonMessage
https://developers.binance.com/docs/binance-spot-api-docs/testnet/fix-api#message-components.   

# perform unit tests on message construction to match bnb
https://developers.binance.com/docs/binance-spot-api-docs/testnet/fix-api#how-to-sign-logona-request.   


# TODO : 
git pull binance xml.   
add start script with source creds and stunnel hooks.   
separate client session and client router.  
change namespaces for broker.  
implement feeder example.   
native ssl using fix8 pull request.   
more unit tests.
