#include <string>
#include <algorithm>
#include <stdexcept>
// load PEM KEY and clean it

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