#pragma once
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sodium.h>

inline std::vector<unsigned char> hexStringToVector(const std::string &hexStr)
{
    std::vector<unsigned char> vec;
    for (size_t i = 0; i < hexStr.length(); i += 2)
    {
        std::string byteString = hexStr.substr(i, 2); // Take two characters (one byte)
        unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
        vec.push_back(byte);
    }
    return vec;
}

inline std::string vectorToHexString(const std::vector<unsigned char> &vec)
{
    std::ostringstream oss;
    for (unsigned char byte : vec)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return oss.str();
}

// Function that derives the public key from a private key
inline std::vector<unsigned char> derivePublicKeyFromPrivate(const std::vector<unsigned char> &seed)
{
    std::vector<unsigned char> pk(crypto_sign_PUBLICKEYBYTES);
    std::vector<unsigned char> sk(crypto_sign_SECRETKEYBYTES);

    if (crypto_sign_seed_keypair(pk.data(), sk.data(), seed.data()) != 0)
    {
        throw std::runtime_error("Failed to derive public key");
    }
    return pk;
}

inline std::string getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

    std::tm now_tm;
    gmtime_r(&now_time, &now_tm); // Use gmtime_r for UTC time

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y%m%d-%H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << millis;

    return oss.str();
}

inline std::string stripPrivateKey(const std::string &pem_key)
{
    std::string pemHeader = "-----BEGIN PRIVATE KEY-----";
    std::string pemFooter = "-----END PRIVATE KEY-----";
    size_t pem_start = pem_key.find(pemHeader);
    size_t pem_end = pem_key.find(pemFooter);
    if (pem_start == std::string::npos || pem_end == std::string::npos)
    {
        throw std::runtime_error("Invalid PEM format.");
    }
    std::string result = pem_key.substr(pem_start + pemHeader.size() + 1, pem_key.size() - pemHeader.size() - pemFooter.size() - 2); // Strip PEM headers

    result.erase(result.begin(), std::find_if_not(result.begin(), result.end(),
                                                  [](unsigned char ch)
                                                  { return std::isspace(ch) || ch == '\n' || ch == '\t'; }));

    result.erase(std::find_if_not(result.rbegin(), result.rend(),
                                  [](unsigned char ch)
                                  { return std::isspace(ch) || ch == '\n' || ch == '\t'; })
                     .base(),
                 result.end());
    return result;
}

inline std::vector<unsigned char> loadPrivateKeyFromString(const std::string &pem_key)
{
    if (sodium_init() < 0)
    {
        throw std::runtime_error("libsodium initialization failed.");
    }
    std::string barePemKey = stripPrivateKey(pem_key);

    // Decode base64-encoded PEM content into binary
    std::vector<unsigned char> privateKey(crypto_sign_ed25519_SECRETKEYBYTES);
    if (sodium_base642bin(privateKey.data(), privateKey.size(),
                          barePemKey.c_str(), barePemKey.size(),
                          nullptr, nullptr, nullptr,
                          sodium_base64_VARIANT_ORIGINAL) != 0)
    {
        throw std::runtime_error("Failed to decode PEM key.");
    }
    std::vector<unsigned char> secretKey(privateKey.begin() + 16, privateKey.end() - 16);
    return secretKey;
}

inline std::string readPemFile(const std::string &filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open private key file: " + filepath);
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    std::string pem_key = oss.str();
    return pem_key;
}

inline std::string json_array(const std::vector<std::string> &xs)
{
    std::ostringstream os;
    os << "[";
    for (size_t i = 0; i < xs.size(); ++i)
    {
        os << '"';
        // minimal JSON escape for quotes/backslashes
        for (char c : xs[i])
        {
            if (c == '\\' || c == '"')
                os << '\\';
            os << c;
        }
        os << '"';
        if (i + 1 < xs.size())
            os << ',';
    }
    os << "]";
    return os.str();
}

inline std::string getTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return std::to_string(milliseconds);
}

inline std::string getEnvVar(const char *varName)
{
    const char *val = std::getenv(varName);
    return val ? std::string(val) : std::string();
}
