#pragma once
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <sodium.h>

inline std::vector<unsigned char> hexStringToVector(const std::string& hexStr) {
    std::vector<unsigned char> vec;
    for (size_t i = 0; i < hexStr.length(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);  // Take two characters (one byte)
        unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
        vec.push_back(byte);
    }
    return vec;
}

inline std::string vectorToHexString(const std::vector<unsigned char>& vec) {
    std::ostringstream oss;
    for (unsigned char byte : vec) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return oss.str();
}

// Function that derives the public key from a private key
inline std::vector<unsigned char> derivePublicKeyFromPrivate(const std::vector<unsigned char>& seed) {
    std::vector<unsigned char> pk(crypto_sign_PUBLICKEYBYTES);
    std::vector<unsigned char> sk(crypto_sign_SECRETKEYBYTES);

    if (crypto_sign_seed_keypair(pk.data(), sk.data(), seed.data()) != 0) {
        throw std::runtime_error("Failed to derive public key");
    }
    return pk;
}

inline std::string getCurrentTimestamp() {
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


inline std::string stripPrivateKey(const std::string& pem_key) {
    std::string pemHeader = "-----BEGIN PRIVATE KEY-----";
    std::string pemFooter = "-----END PRIVATE KEY-----";
    size_t pem_start = pem_key.find(pemHeader);
    size_t pem_end = pem_key.find(pemFooter);
    if (pem_start == std::string::npos || pem_end == std::string::npos) {
        throw std::runtime_error("Invalid PEM format.");
    }
    std::string result =  pem_key.substr(pem_start + pemHeader.size()+1, pem_key.size() - pemHeader.size() - pemFooter.size() - 2); // Strip PEM headers

    result.erase(result.begin(), std::find_if_not(result.begin(), result.end(),
                    [](unsigned char ch) { return std::isspace(ch) || ch == '\n' || ch == '\t'; }));


    result.erase(std::find_if_not(result.rbegin(), result.rend(),
                    [](unsigned char ch) { return std::isspace(ch) || ch == '\n' || ch == '\t'; }).base(), result.end());
    return result;
}

inline std::vector<unsigned char> loadPrivateKeyFromString(const std::string& pem_key) {
    if (sodium_init() < 0) {
      throw std::runtime_error("libsodium initialization failed.");
    }
    std::string barePemKey = stripPrivateKey(pem_key);

    // Decode base64-encoded PEM content into binary
    std::vector<unsigned char> privateKey(crypto_sign_ed25519_SECRETKEYBYTES);
    if (sodium_base642bin(privateKey.data(), privateKey.size(),
                          barePemKey.c_str(), barePemKey.size(),
                          nullptr, nullptr, nullptr,
                          sodium_base64_VARIANT_ORIGINAL) != 0) {
        throw std::runtime_error("Failed to decode PEM key.");
    }
    std::vector<unsigned char> secretKey(privateKey.begin() + 16, privateKey.end() - 16);
    return secretKey;
}

inline std::string readPemFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open private key file: " + filepath);
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    std::string pem_key = oss.str();
    return pem_key;
}

inline std::string logonRawData(
                        std::vector<unsigned char>& private_key,
                        std::vector<unsigned char>& public_key,
                        const std::string& sender_comp_id,
                        const std::string& target_comp_id,
                        const std::string& msg_seq_num,
                        const std::string& sending_time) 
    {

    std::vector<unsigned char> full_secret_key;
    full_secret_key.insert(full_secret_key.end(), private_key.begin(), private_key.end());
    full_secret_key.insert(full_secret_key.end(), public_key.begin(), public_key.end());

    // Initialize the vector with the first element "A" and separator '\x01'
    std::vector<unsigned char> payload{'A', 1};

    // Helper lambda to append a string and separator to the result vector
    auto appendWithSeparator = [&payload](const std::string& value) {
        payload.insert(payload.end(), value.begin(), value.end());
        payload.push_back(1);
    };

    // Append each element with the separator
    appendWithSeparator(sender_comp_id);
    appendWithSeparator(target_comp_id);
    appendWithSeparator(msg_seq_num);
    appendWithSeparator(sending_time);
    payload.pop_back();
    
    // Sign payload
    std::vector<unsigned char> signature(crypto_sign_ed25519_BYTES);
    if (crypto_sign_detached(signature.data(),
                                nullptr,
                                payload.data(),
                                payload.size(),
                                full_secret_key.data())!= 0) {
        throw std::runtime_error("Signing failed.");
    }

    // Encode signature in Base64
    std::vector<char> b64_signature(sodium_base64_encoded_len(signature.size(), sodium_base64_VARIANT_ORIGINAL));
    sodium_bin2base64(b64_signature.data(),
                      b64_signature.size(),
                      signature.data(),
                      signature.size(),
                      sodium_base64_VARIANT_ORIGINAL);

    return std::string(b64_signature.data());
}


inline std::string json_array(const std::vector<std::string>& xs) {
    std::ostringstream os;
    os << "[";
    for (size_t i = 0; i < xs.size(); ++i) {
        os << '"' ;
        // minimal JSON escape for quotes/backslashes
        for (char c : xs[i]) {
            if (c == '\\' || c == '"') os << '\\';
            os << c;
        }
        os << '"';
        if (i + 1 < xs.size()) os << ',';
    }
    os << "]";
    return os.str();
}

inline std::string getTimestamp(){
    auto now = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return std::to_string(milliseconds);
}
