<table align="center">
  <tr>
    <td>
      <img src="https://github.com/user-attachments/assets/621b8250-6fef-4a25-946c-3e2ff20de9f8" alt="BINFROSTLOGO" width="150" height="150" />
    </td>
    <td style="padding-left: 15px; vertical-align: middle;">
      <strong>A blazing-fast, multi-protocol Binance client library — bridging your code to the Binance universe.</strong><br />
      <em>"Like the mythical Bifrost bridge, Binfrost connects you instantly and securely — only here, it’s crypto, not Asgard."</em>
    </td>
  </tr>
</table>



---

## 🚀 Overview
**Binfrost** is a C++ client library for Binance with a focus on **performance** and **ease of use**.  
It supports:
- **FIX protocol**
- **WebSocket streams**
- **REST API**

You can establish **Order Entry**, **Market Data**, and **Drop Copy** FIX connections.  
The architecture is designed for **low latency**, **cross-platform builds**, and **scalability**.

---

## 📦 Features

- ✅ **FIX Protocol** — TLS connections, custom message cracker, order management  
- ✅ **WebSocket API** — Exchange info, order placement, cancel orders, test orders, user streams  
- ✅ **REST API** — Fully integrated with HMAC signing and examples  
- ✅ **Portable Build** — Windows & Linux with [vcpkg](https://vcpkg.io)  
- ✅ **Unit Tests** — For key components (signatures, payloads, key loading)  
- ✅ **Performance-Oriented** — Designed for low-latency trading systems  

---

## 🛠️ Building

### Windows
```powershell
set VCPKG_ROOT=C:\Users\Administrator\Desktop\workbench\vcpkg
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
cmake --build build
```

### Linux

Make sure vcpkg is installed and VCPKG_ROOT & PATH are configured:
```
export VCPKG_ROOT=$HOME/workbench/vcpkg
export PATH=$PATH:$VCPKG_ROOT
```

Build from the build folder:

```
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
make
```
## ✅ DONE

- ✅ **FIX** Build basic client  
- ✅ **FIX** Connect TLS to Binance  
- ✅ **FIX** ED25519 signature generation  
- ✅ **FIX** Unit tests added  
- ✅ **FIX** Separated client session & router  
- ✅ **WS_API** Base implementation  
- ✅ **UTILS** Refactored utils, added HMAC  
- ✅ **REST_CLIENT** Full implementation  
- ✅ **WS_STREAMS** User streams tested & refactored  
- ✅ **WS_API** Exchange info, Place/Test/Cancel Orders  
- ✅ **BUILD** vcpkg dependencies, cross-platform builds  
- ✅ **FIX** Migrated from **fix8** → **QuickFIX**  
- ✅ **FIX** Implemented `placeOrder` & `subscribeToFeed`  
- ✅ **FIX** Integrated codegen classes & custom message cracker  
- ✅ **FIX** Dual session config for feeder/broker  
- ✅ **FIX** `onMessage` handler for user  
- ✅ **CRYPTO** ED25519 key loading  
- ✅ **FIX** Feeder & broker wrapper  

---

## 📋 TODO

- ✅ **FIX** Get Market Info implementation  
- ✅ **FIX** Add response type with code, type, and data  
- ✅ **WS** Example builds via vcpkg  
- ✅ **LIBRARY** Export as library for RTEX integration  
- ✅ **LIBRARY** Version 0.0 Beta  
- ✅ **WS_API** Rework WS to use beast instead of wspp
- ✅ **WS_API** Logon without signature after authentication  
- ✅ **REST** Remove singleton request builder and aggregate to client  
- ✅ **WS** Remove singleton request builder and aggregate to client  
- ✅ **UTESTS** More coverage for signatures, payloads, key loading  
- ✅ **WS_ALL** Parameter enforcement for request types  
- ✅ **FIX** Implement FIX messages fully  
- ✅ **WS** Feeder-Broker implementation  
- ✅ **CRYPTO** RSA key loading and sign  


## ⚡ Inspiration

The name Binfrost is a nod to the Bifrost bridge from Norse mythology — a rainbow bridge connecting worlds.
Here, it’s the bridge between your C++ code and the Binance trading universe.

## 📜 License

MIT License — free to use, modify, and share.
