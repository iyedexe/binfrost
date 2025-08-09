<table align="center" style="width: 100%; max-width: 700px;">
  <tr>
    <td style="width: 300px; vertical-align: middle; padding-right: 20px;">
      <img 
        src="https://github.com/user-attachments/assets/621b8250-6fef-4a25-946c-3e2ff20de9f8" 
        alt="BINFROSTLOGO" 
        width="300" 
        height="300" 
        style="object-fit: cover;"
      />
    </td>
    <td style="vertical-align: middle; color: #bfa14d; font-family: Papyrus, Copperplate, fantasy, cursive, serif; letter-spacing: 1.5px;">
      <h2 style="margin: 0;">
        <strong>A blazing-fast, multi-protocol Binance client library — bridging your code to the Binance universe.</strong>
      </h2>
      <p style="font-style: italic; font-size: 1.1em; margin-top: 10px; color: #d4c270;">
        "Like the mythical Bifrost bridge, Binfrost connects you instantly and securely — only here, it’s crypto, not Asgard."
      </p>
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
- ✅ **FIX** Implemented `placeOrder` & `getFeed`  
- ✅ **FIX** Integrated codegen classes & custom message cracker  
- ✅ **FIX** Dual session config for feeder/broker  

---

## 📋 TODO

- ✅ **FIX** Get Market Info implementation  
- ✅ **FIX** Add response type with code, type, and data  
- ✅ **FIX** `onMessage` handler for user  
- ✅ **WS** Example builds via vcpkg  
- ✅ **LIBRARY** Export as library for RTEX integration  
- ✅ **LIBRARY** Version 0.0 Beta  
- ✅ **CRYPTO** ED25519 key loading  
- ✅ **UTESTS** More coverage for signatures, payloads, key loading  
- ✅ **WS_ALL** Parameter enforcement for request types  
- ✅ **WS_API** Logon without signature after authentication  
- ✅ **ARCHITECTURE** Feeder & broker wrapper  
- ✅ **DEPENDENCIES** Switch from WebSocket++ → Boost.Beast  
- ✅ **FIX** Implement FIX messages fully  
- ✅ **FIX/WS** Feeder-Broker implementation  
- ✅ **FIX** Native SSL using fix8 PR  


## ⚡ Inspiration

The name Binfrost is a nod to the Bifrost bridge from Norse mythology — a rainbow bridge connecting worlds.
Here, it’s the bridge between your C++ code and the Binance trading universe.

## 📜 License

MIT License — free to use, modify, and share.
