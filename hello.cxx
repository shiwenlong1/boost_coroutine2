// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <boost/coroutine2/all.hpp>

void foo(boost::coroutines2::coroutine<std::string>::pull_type &sink)
{
    std::cout << "get " << sink().get() << "from main() by foo()" << std::endl;
    sink();
    std::cout << "get " << sink().get() << "from main() by foo()" << std::endl;
    sink();
}

int main(int argc, char *argv[])
{
    std::cout << "hello GN\n";
    std::string str1("hello");
    std::string str2("world");
    boost::coroutines2::coroutine<std::string>::push_type source(foo);
    std::cout << "pass " << str1 << " from main() to foo()" << std::endl;
    source(str1);
    std::cout << "pass " << str2 << " from main() to foo()" << std::endl;
    source(str2);
    return 0;
}
