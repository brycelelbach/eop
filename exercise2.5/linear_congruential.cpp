////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2013 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <boost/cstdint.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>

#include "orbits.hpp"

// X_{n+1} = (a X_n + c) % (1 << mp)
template <typename T, T A, T C, T MP>
struct linear_congruential
{
    typedef T domain;
    typedef T distance_type;

    enum
    {
        a = A,
        c = C,
        mp = MP
    };

    domain operator()(domain x)
    {
        return (a * x + c) % (1LLU << mp);
    }
};

int main()
{
//    typedef linear_congruential<boost::uint64_t, 0x5DEECE66D, 0xB, 48>
//        prng;

    typedef linear_congruential<boost::uint64_t, 0xDEAD, 0xB, 16>
        prng;

    using namespace boost::accumulators;

    accumulator_set<prng::distance_type, stats<tag::mean> > m0;
    accumulator_set<prng::distance_type, stats<tag::mean> > m1;
    accumulator_set<prng::domain, stats<tag::mean> > m2;

    for (boost::uint64_t i = 0; i < (1LLU << prng::mp); ++i)
    {
        auto structure = orbit_structure(i, prng());

        m0(std::get<0>(structure));
        m1(std::get<1>(structure));
        m2(std::get<2>(structure));
    }

    std::cout << "m0 = " << mean(m0) << std::endl
              << "m1 = " << mean(m1) << std::endl
              << "m2 = " << mean(m2) << std::endl;
}

