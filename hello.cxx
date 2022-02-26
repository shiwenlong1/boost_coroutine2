// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <boost/coroutine2/all.hpp>

void foo(boost::coroutines2::coroutine<int>::push_type &sink)
{
    std::cout << " sink1" << std::endl;
    sink(1); // push {1} back to main-context
    std::cout << " sink2" << std::endl;
    sink(2); // push {2} back to main-context
    std::cout << " sink3" << std::endl;
    sink(3); // push {3} back to main-context
}

int main(int argc, char *argv[])
{
    std::string str1("hello");
    std::string str2("world");
    std::cout<< "start corountine" << std::endl;
    /*
    * 主程序中  使用 pull_type 那么就是从 协程中 拉  数据 类型 git的 pull 与 push
    * 这里使用 pull_type 会立即调用一次协程foo执行， foo中 在sink(1)将执行权让给 主程序
    */
    boost::coroutines2::coroutine<int>::pull_type source(foo);
    std::cout<< "start while" << std::endl;
    while (source) {
        int ret = source.get(); // pushed data,that is the argument of sink()
        std::cout << "move to coroutine-function " << ret << std::endl;
        source(); // context-switch to coroutine-function
        std::cout << "back from coroutine-function " << std::endl;
    }
    return 0;
}
