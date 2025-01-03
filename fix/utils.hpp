#pragma once
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <sodium.h>

inline std::string getCurrentTimestamp() {

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;


    std::tm now_tm;
    localtime_r(&now_time, &now_tm);

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y%m%d-%H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << millis;

    return oss.str();
}

inline std::vector<unsigned char> loadPrivateKey(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open private key file: " + filepath);
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    std::string pem_key = oss.str();

    // Extract raw private key from PEM (Assumes no password)
    std::string pemHeader = "-----BEGIN PRIVATE KEY-----";
    std::string pemFooter = "-----BEGIN PRIVATE KEY-----";
    size_t pem_start = pem_key.find(pemHeader);
    size_t pem_end = pem_key.find(pemFooter);
    if (pem_start == std::string::npos || pem_end == std::string::npos) {
        throw std::runtime_error("Invalid PEM format.");
    }
    pem_key = pem_key.substr(pem_start + pemHeader.size()+1, pem_key.size() - pemHeader.size() - pemFooter.size() - 1); // Strip PEM headers

    std::vector<unsigned char> private_key(crypto_sign_ed25519_SECRETKEYBYTES);
    // Decode base64-encoded PEM content into binary
    if (sodium_base642bin(private_key.data(), private_key.size(),
                          pem_key.c_str(), pem_key.size(),
                          nullptr, nullptr, nullptr,
                          sodium_base64_VARIANT_ORIGINAL) != 0) {
        throw std::runtime_error("Failed to decode PEM key.");
    }
    std::vector<unsigned char> sub_private_key(private_key.begin() + 16, private_key.end() - 16);


    return sub_private_key;
}

inline std::vector<unsigned char> loadPublicKey(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open private key file: " + filepath);
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    std::string pem_key = oss.str();

    // Extract raw private key from PEM (Assumes no password)
    std::string pemHeader = "-----BEGIN PUBLIC KEY-----";
    std::string pemFooter = "-----BEGIN PUBLIC KEY-----";
    size_t pem_start = pem_key.find(pemHeader);
    size_t pem_end = pem_key.find(pemFooter);
    if (pem_start == std::string::npos || pem_end == std::string::npos) {
        throw std::runtime_error("Invalid PUB format.");
    }
    pem_key = pem_key.substr(pem_start + pemHeader.size()+1, pem_key.size() - pemHeader.size() - pemFooter.size() - 1); // Strip PEM headers

    std::vector<unsigned char> public_key(2*crypto_sign_ed25519_PUBLICKEYBYTES);
    // Decode base64-encoded PEM content into binary
    if (sodium_base642bin(public_key.data(), public_key.size(),
                          pem_key.c_str(), pem_key.size(),
                          nullptr, nullptr, nullptr,
                          sodium_base64_VARIANT_ORIGINAL) != 0) {
        throw std::runtime_error("Failed to decode PUB key.");
    }
    std::vector<unsigned char> sub_public_key(public_key.begin() + 12, public_key.end() - 12);


    return sub_public_key;
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
    std::vector<unsigned char> payload{'A', '1'};

    // Helper lambda to append a string and separator to the result vector
    auto appendWithSeparator = [&payload](const std::string& value) {
        payload.insert(payload.end(), value.begin(), value.end());
        payload.push_back('1');
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
