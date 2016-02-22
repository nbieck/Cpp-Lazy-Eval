#pragma once

#include <functional>

namespace cpplazy
{
    //This is the central unit of the lazy evaluation. 
    //A thunk encapsulates a computation that returns a value of type T.
    template <typename T>
    class thunk
    {
    public:

        template <typename... Args>
        thunk(std::function<T(Args...)> f, Args... args);

        operator T();

        const T& get();

    private:

        // This is the function that produces the value
        std::function<T(void)> m_call;

        //the computed value is chached here to avoid recomputation
        T m_value;

        //a flag telling us whether we already have the value computed or not
        bool m_computed;
    };
}
