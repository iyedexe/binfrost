#include <string>

namespace crypto {
    class ikey {
    public:
        ikey();
        virtual ~ikey();

        virtual std::string sign(const std::string& payload);
    };
  
    enum class KeyType : uint8_t {  
        HMAC,
        ED25519,
        RSA,
    };
}