//  Copyright (c) 2015-2016 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/include/util.hpp>
#include <hpx/util/lightweight_test.hpp>

struct fun
{
    fun() {}
    fun(fun&&) {}
    fun(fun const&) { HPX_TEST(false); }

    void operator()() const {}

    template <typename Archive>
    void serialize(Archive&, unsigned const) {}
};

void test_unique_function_nonser()
{
    // function_nonser -> unique_function_nonser
    {
        hpx::util::function_nonser<void()> f = fun();

        hpx::util::unique_function_nonser<void()> uf = std::move(f);
        HPX_TEST(uf.target<fun>());

        f = fun();
        uf = std::move(f);
        HPX_TEST(uf.target<fun>());
    }

    // unique_function-> unique_function_nonser
    {
        hpx::util::unique_function<void()> f = fun();

        hpx::util::unique_function_nonser<void()> uf = std::move(f);
        HPX_TEST(uf.target<fun>());

        f = fun();
        uf = std::move(f);
        HPX_TEST(uf.target<fun>());
    }

    // function-> unique_function_nonser
    {
        hpx::util::function<void()> f = fun();

        hpx::util::unique_function_nonser<void()> uf = std::move(f);
        HPX_TEST(uf.target<fun>());

        f = fun();
        uf = std::move(f);
        HPX_TEST(uf.target<fun>());
    }
}

void test_unique_function()
{
    // function-> unique_function
    {
        hpx::util::function<void()> f = fun();

        hpx::util::unique_function<void()> uf = std::move(f);
        HPX_TEST(uf.target<fun>());

        f = fun();
        uf = std::move(f);
        HPX_TEST(uf.target<fun>());
    }
}

void test_function_nonser()
{
    // function-> function_nonser
    {
        hpx::util::function<void()> f = fun();

        hpx::util::function_nonser<void()> uf = std::move(f);
        HPX_TEST(uf.target<fun>());

        f = fun();
        uf = std::move(f);
        HPX_TEST(uf.target<fun>());
    }
}

int main(int, char*[])
{
    test_unique_function_nonser();
    test_unique_function(); //! THESE DON'T WORK YET
    test_function_nonser();

    return hpx::util::report_errors();
}