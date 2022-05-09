#pragma once

#include <array>
#include <cassert>
#include <iostream>

template<typename ID, typename VAL>
class EnumArray
{
    using IdValPair = std::pair<ID, VAL>;

private:
    std::array<IdValPair, static_cast<int>(ID::SIZE)> arr;

public:
    constexpr EnumArray(const std::initializer_list<IdValPair>& il)
    {
        for (int i = 0; i < this->arr.size(); ++i)
        {
            const auto& it{ il.begin() };
            const IdValPair pair{ *(it + i) };

            const bool IDsOrdered{ pair.first == static_cast<ID>(i) };

            assert(IDsOrdered);

            arr[i] = pair;
        }
    }

    constexpr VAL& getVal(const ID id)
    {
        const int index{ static_cast<int>(id) };

        return this->arr[index].second;
    }

    // warning: VAL needs operator== to use
    constexpr ID getID(const VAL& val)
    {
        for (auto [id, value] : this->arr)
        {
            if (value == val)
                return id;
        }

        // there is an error if we cannot fine the id for the value you searched
        // every value should have unique ID mapped and visa versa (atleast that's the point)
        assert(true);
        return ID::SIZE;
    }

};

/* Usage example:

enum class FooID
{
    a,
    b,
    SIZE
};

struct Foo
{
    int x, y;

    // Optional
    const bool operator==(const Foo& other)
    {
        return
            this->x == other.x &&
            this->y == other.y;
    }
};

int main()
{
    constexpr Foo FOO1{ 10, 11 };
    constexpr Foo FOO2{ 20, 21 };

    EnumArray<FooID, Foo> foos{
        {FooID::a, FOO1}
        {FooID::b, FOO2},
    };

    foos.getID(FOO1); // only works if operator== exists
    std::cout << FOO1.y << " == " << foos.getVal(FooID::a).y << '\n';


    const bool idTest1{ foos.getID(FOO1) == FooID::a };
    std::cout << (idTest1 ? "passed" : "failed") << " : " << (int)foos.getID(FOO1) << " ==  0" << '\n';


    const bool idTest2{ foos.getID(FOO2) == FooID::b };
    std::cout << (idTest2 ? "passed" : "failed") << " : " << (int)foos.getID(FOO2) << " ==  1" << '\n';

    const bool valTest1{ foos.getVal(FooID::a) == FOO1 };
    std::cout << (valTest1 ? "passed" : "failed") << " : " << foos.getVal(FooID::a).x << " ==  10" << '\n';
    const bool valTest2{ foos.getVal(FooID::b) == FOO2 };
    std::cout << (valTest2 ? "passed" : "failed") << " : " << foos.getVal(FooID::b).x << " ==  20" << '\n';
}
*/