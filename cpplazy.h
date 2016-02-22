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

        //A thunk can be constructed from a function returning T, and
        //taking an arbitrary number of arguments, all of which have to
        //be provided.
        //Keep in mind that functions taking pointers might not be suited
        //because the location pointed to might no longer be valid
        template <typename F, typename... Args>
        thunk(F f, Args&&... args)
            : m_call(std::bind(f, std::forward<Args>(args)...)), m_computed(false)
        {}

        operator T()
        {
            if (!m_computed)
                ComputeValue();

            return m_value;
        }

        const T& get()
        {
            if (!m_computed)
                ComputeValue();

            return m_value;
        }

    private:

        void ComputeValue()
        {
            m_value = m_call();
            m_computed = true;
        }

        // This is the function that produces the value
        std::function<T(void)> m_call;

        //the computed value is chached here to avoid recomputation
        T m_value;

        //a flag telling us whether we already have the value computed or not
        bool m_computed;
    };
}
