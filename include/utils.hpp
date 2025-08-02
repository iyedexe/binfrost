#pragma once
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

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
