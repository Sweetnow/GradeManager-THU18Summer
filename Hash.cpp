#include"Hash.h"
PWDTYPE BKDRHash(std::string str) {
    PWDTYPE seed = 13131; // 31 131 1313 13131 131313 etc..
    PWDTYPE hash = 0;
    int length = str.length();
    for (int i = 0; i < length; i++) {
        hash = hash * seed + str[i];
    }
    return (hash & 0x7FFFFFFFFFFFFFFF);
}