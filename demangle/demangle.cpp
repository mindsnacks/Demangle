//
//  demangle.cpp
//
//  Created by Karl Stenerud on 10/11/13.
//  Copyright (c) 2013 MindSnacks. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall remain in place
// in this source code.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <iostream>
#include <cxxabi.h>

/**
 * Demangles the supplied argument according to the C++ ABI, and prints the
 * human-readble version to stdout.
 */
int main(int argc, const char * argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <mangled trace entry>" << std::endl;
        exit(1);
    }

    const char* mangled_name = argv[1];
    size_t length = 5000;
    char* buff = (char*)malloc(length);
    int status = 0;
    __cxxabiv1::__cxa_demangle(mangled_name, buff, &length, &status);

    switch (status)
    {
        case 0:
            std::cout << buff << std::endl;
            return 0;
        case -1:
            std::cout << "A memory allocation failiure occurred" << std::endl;
        case -2:
            std::cout << mangled_name << " is not a valid name under the C++ ABI mangling rules" << std::endl;
        case -3:
            std::cout << "Invalid argument" << std::endl;
    }

    return 1;
}

