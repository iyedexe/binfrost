#include <catch2/catch_all.hpp>
#include <string>
#include <algorithm>
#include "BNBBroker_session.hpp"


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
    // test will not pass unless we force
    // private key, api key, timestamp, sender comp id, target comp id
   // std::string sendingTime = "20240627-11:17:25.223";
//    std::string senderCompID = "EXAMPLE";
//    std::string targetCompID = "SPOT"; 

    BNBBroker_session_client client = BNBBroker_session_client(FIX8::BNB::ctx(), FIX8::SessionID(), nullptr, nullptr, nullptr);
    auto logonMessage = client.generate_logon(30, "1");
    
    std::string encodedMsg;
    size_t msgSize = logonMessage->encode(encodedMsg);
    std::replace(encodedMsg.begin(), encodedMsg.end(), static_cast<char>(1), '|');

    std::string expectedMsg="8=FIX.4.4|9=247|35=A|34=1|49=EXAMPLE|52=20240627-11:17:25.223|56=SPOT|95=88|96=4MHXelVVcpkdwuLbl6n73HQUXUf1dse2PCgT1DYqW9w8AVZ1RACFGM+5UdlGPrQHrgtS3CvsRURC1oj73j8gCA==|98=0|108=30|141=Y|553=sBRXrJx2DsOraMXOaUovEhgVRcjOvCtQwnWj8VxkOh1xqboS02SPGfKi2h8spZJb|25035=2|10=227|";

    REQUIRE(compareStringsUnordered(encodedMsg ,expectedMsg)); 
}