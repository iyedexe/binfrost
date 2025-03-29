#include <catch2/catch_all.hpp>
#include <string>
#include <algorithm>
#include <utils.hpp>

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

bool compareStringsUnordered(const std::string& str1, const std::string& str2) {

    std::vector<std::string> tokens1 = splitString(str1, '|');
    std::vector<std::string> tokens2 = splitString(str2, '|');

    std::sort(tokens1.begin(), tokens1.end());
    std::sort(tokens2.begin(), tokens2.end());

    return tokens1 == tokens2;
}

TEST_CASE("Generate logon message", "[generateLogon]") {

    std::string pem_private_key = 
        "-----BEGIN PRIVATE KEY-----\n"
        "MC4CAQAwBQYDK2VwBCIEIIJEYWtGBrhACmb9Dvy+qa8WEf0lQOl1s4CLIAB9m89u\n"
        "-----END PRIVATE KEY-----";

   std::vector<unsigned char> privateKey = loadPrivateKeyFromString(pem_private_key);
   std::vector<unsigned char> publicKey = derivePublicKeyFromPrivate(privateKey);
   std::string sendingTime = "20240627-11:17:25.223";
   const unsigned sequence_number = 1;
   std::string senderCompID = "EXAMPLE";
   std::string targetCompID = "SPOT"; 
   std::string apiKey = "sBRXrJx2DsOraMXOaUovEhgVRcjOvCtQwnWj8VxkOh1xqboS02SPGfKi2h8spZJb";

   std::string raw_data = logonRawData(
      privateKey,
      publicKey,
      senderCompID,
      targetCompID,
      std::to_string(sequence_number),
      sendingTime
   );

    //auto logonRequest = RequestBuilder::buildLogonRequest(raw_data, 30, apiKey);
    
    
    // std::replace(encodedMsg.begin(), encodedMsg.end(), static_cast<char>(1), '|');

    // std::string expectedMsg="8=FIX.4.4|9=247|35=A|34=1|49=EXAMPLE|sBRXrJx2DsOraMXOaUovEhgVRcjOvCtQwnWj8VxkOh1xqboS02SPGfKi2h8spZJb52=20240627-11:17:25.223|56=SPOT|95=88|96=4MHXelVVcpkdwuLbl6n73HQUXUf1dse2PCgT1DYqW9w8AVZ1RACFGM+5UdlGPrQHrgtS3CvsRURC1oj73j8gCA==|98=0|108=30|141=Y|553=sBRXrJx2DsOraMXOaUovEhgVRcjOvCtQwnWj8VxkOh1xqboS02SPGfKi2h8spZJb|25035=2|10=227|";

    // REQUIRE(compareStringsUnordered(encodedMsg ,expectedMsg)); 
}