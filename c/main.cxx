//
// Created by oldbitsnbytes on 2025-12-05.
//

#include <cctools/mstr.h>


auto main(int argc, char** argv) -> int
{
    cpp::mstr str;
    str << "Hello World!";
    std::cout << str() << std::endl;
    return 0;
}
