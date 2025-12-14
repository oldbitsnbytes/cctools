//
// Created by oldbitsnbytes on 2025-12-05.
//

#include <cctools/mstr.h>
#include <cctools/journal.h>



auto main(int argc, char** argv) -> int
{
    sys::message() << rem::fn::func << color::aqua << "cctools" << color::white << "::" << color::deeppink8 << "main" << color::yellow  << "()" << sys::eol;
    sys::log()  << "Hello World!" << sys::eol;
    sys::flush("main.journal");
    return 0;
}
