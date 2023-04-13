#include <headers/Global.hpp>

std::string NumToString(const unsigned int& i_num) {
    std::stringstream ss;
    ss << i_num;
    return ss.str();
}