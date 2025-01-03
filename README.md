# DONE: 
## Read Docs: 
https://developers.binance.com/docs/binance-spot-api-docs/testnet/fix-api.   
https://fix8.org/howitworks.html.  
https://fix8.org/fix8/html/index.html.   

## Install FIX8 dependencies:
```
git clone -b poco-1.14.0-release https://github.com/pocoproject/poco.git   
mkdir cmake-build    
cd cmake-build   
cmake ..   
sudo cmake --build . --target install   

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib   
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib64   
```
## Install FIX8: (HARD)
```
git clone git@github.com:fix8/fix8.git   
./bootstrap   
./configure  
make  
make install  
```
## Generate Fix code using xml:
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/360487/3.+Using+f8c+-+the+Fix8+compiler.   

## Configure and use generated Code.   


## Constructuing a message:    
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/360514/7.+Constructing+a+new+message.   

## Sign ED25519 payload.  (VERY HARD)
https://developers.binance.com/docs/binance-spot-api-docs/testnet/fix-api#signaturecomputation.   
https://doc.libsodium.org/public-key_cryptography/public-key_signatures#detached-mode.   

# TODO : 
## Why no log on response ?

## SSL configuration :
https://fix8engine.atlassian.net/wiki/spaces/FX/pages/15368200/4.+Configuring+SSL+Clients+and+Servers.    

## Fix manual setup
setting export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib64.   
running source credentials.sh.   
code generation manually add to cmake.   

