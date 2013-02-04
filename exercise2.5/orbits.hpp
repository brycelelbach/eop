////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2013 Bryce Adelstein-Lelbach
//
//  Based on material from EoP.
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(CXX_8AFFF398_26C1_48EF_9F22_A7B2CBFF9A34)
#define CXX_8AFFF398_26C1_48EF_9F22_A7B2CBFF9A34

#include <tuple>

#include "eop.hpp"

// From Chapter 2 in EoP.
// Nonterminating version of all algorithms used.

template <typename F>
    requires(Transformation(F))
DistanceType(F) distance(Domain(F) x, Domain(F) y, F f)
{
    // Precondition: y is reachable from x under f.
    typedef DistanceType(F) N;
    N n(0);
    while (x != y)
    {
        x = f(x);
        n = n + N(1);
    }
    return n;
}

// For nonterminating orbits.
template <typename F>
    requires(Transformation(F))
Domain(F) collision_point(const Domain(F)& x, F f)
{
    // Precondition: the orbit of x under f is not terminating.
    Domain(F) slow = x;     // slow = f^0(x)
    Domain(F) fast = f(x);  // fast = f^1(x)
                            // n <- 0 (completed iterations)
    while (fast != slow)    // slow = f^n(x) and fast = f^{2n+1}(x)
    {
        slow = f(slow);     // slow = f^{n+1}(x) and fast = f^{2n+1}(x)
        fast = f(fast);     // slow = f^{n+1}(x) and fast = f^{2n+2}(x)
        fast = f(fast);     // slow = f^{n+1}(x) and fast = f^{2n+3}(x)
                            // n <- n + 1
    }
    return fast;            // slow = f^n(x) and fast = f^{2n+1}(x) 
    // Postcondition: return value is terminal point or collision point.
}

template <typename F>
    requires(Transformation(F))
Domain(F) convergent_point(Domain(F) x0, Domain(F) x1, F f)
{
    while (x0 != x1)
    {
        x0 = f(x0);
        x1 = f(x1);
    }
}

// For nonterminating orbits.
template <typename F>
    requires(Transformation(F))
Domain(F) connection_point(const Domain(F)& x, F f)
{
    return convergent_point(
        x,
        f(collision_point(x, f)),
        f);
}

// For nonterminating orbits.
template <typename F>
    requires(Transformation(F))
std::tuple<DistanceType(F), DistanceType(F), Domain(F)>
orbit_structure(const Domain(F)& x, F f)
{
    typedef DistanceType(F) N;
    Domain(F) y = connection_point(x, f);
    return std::tuple<N, N, Domain(F)>(distance(x, y, f),
                                       distance(f(y), y, f),
                                       y);
}

#endif // CXX_8AFFF398_26C1_48EF_9F22_A7B2CBFF9A34

