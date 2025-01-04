#include <catch2/catch_all.hpp>
#include <sodium.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "utils.hpp"

TEST_CASE("Extract private key from PEM string", "[loadPrivateKeyFromString]") {
    std::string pem_private_key = 
        "-----BEGIN PRIVATE KEY-----\n"
        "MC4CAQAwBQYDK2VwBCIEIIJEYWtGBrhACmb9Dvy+qa8WEf0lQOl1s4CLIAB9m89u\n"
        "-----END PRIVATE KEY-----";

    std::vector<unsigned char> privateKey = loadPrivateKeyFromString(pem_private_key);
    std::string expectedKey = "8244616b4606b8400a66fd0efcbea9af1611fd2540e975b3808b20007d9bcf6e";

    REQUIRE(vectorToHexString(privateKey) == expectedKey);  // Replace with your expected output
}

TEST_CASE("Derive public key from private key", "[derivePublicKeyFromPrivate]") {
    std::string pem_private_key = 
        "-----BEGIN PRIVATE KEY-----\n"
        "MC4CAQAwBQYDK2VwBCIEIIJEYWtGBrhACmb9Dvy+qa8WEf0lQOl1s4CLIAB9m89u\n"
        "-----END PRIVATE KEY-----";
    // Load private key from PEM string
    std::vector<unsigned char> privateKey = loadPrivateKeyFromString(pem_private_key);
    std::vector<unsigned char> publicKey = derivePublicKeyFromPrivate(privateKey);

    std::string expectedKey = "19420abfd752a565c15625e9da6eaf0086fc40c14960183214442c14996a800d";
    REQUIRE(vectorToHexString(publicKey) == expectedKey);  // Replace with your expected output
}

TEST_CASE("Test logonRawData function", "[logonRawData]") {
    std::string pem_private_key = 
        "-----BEGIN PRIVATE KEY-----\n"
        "MC4CAQAwBQYDK2VwBCIEIIJEYWtGBrhACmb9Dvy+qa8WEf0lQOl1s4CLIAB9m89u\n"
        "-----END PRIVATE KEY-----";

    std::vector<unsigned char> privateKey = loadPrivateKeyFromString(pem_private_key);
    std::vector<unsigned char> publicKey = derivePublicKeyFromPrivate(privateKey);
    
    // Call the function to test
    std::string result = logonRawData(
        privateKey,
        publicKey,
        "EXAMPLE",
        "SPOT",
        "1",
        "20240627-11:17:25.223"
    );

    // Assert that the function returns the expected output
    REQUIRE(result == "4MHXelVVcpkdwuLbl6n73HQUXUf1dse2PCgT1DYqW9w8AVZ1RACFGM+5UdlGPrQHrgtS3CvsRURC1oj73j8gCA==");  // Replace with your expected output
}
