#pragma once

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
            arr[i] = *(it + i);
        }
    }

    constexpr VAL& getVal(const ID id)
    {
        const int index{ static_cast<int>(id) };
        const bool IDsMatch{ id == this->arr[index].first };

        assert(IDsMatch);

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