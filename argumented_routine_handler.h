#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include <string_view>
#include <optional>
#include <tuple>

#define ARGUMENTEDROUTINE_FORCEINLINE __forceinline

template<typename routine_prototype>
class argumented_routine_handler
{
private:
    std::unordered_map<std::string_view, std::pair<std::function<routine_prototype>, void*>> routine_map{};
public:

    [[nodiscard]]
    constexpr ARGUMENTEDROUTINE_FORCEINLINE std::size_t return_routine_map_sz() const;

    [[nodiscard]]
    bool validate_routine(const std::string_view routine_name) const;

    [[nodiscard]]
    ARGUMENTEDROUTINE_FORCEINLINE std::optional<std::pair<std::function<routine_prototype>, void*>> return_routine(const std::string_view routine_name) const;

    template<typename... args>
    ARGUMENTEDROUTINE_FORCEINLINE void call_routine(const std::string_view routine_name) const;
    ARGUMENTEDROUTINE_FORCEINLINE void insert_routine(const std::string_view routine_name, std::pair<std::function<routine_prototype>, void*> routine_pair);

    ARGUMENTEDROUTINE_FORCEINLINE void replace_routine(const std::string_view routine_name, std::pair<std::function<routine_prototype>, void*> routine_pair);
    ARGUMENTEDROUTINE_FORCEINLINE void remove_routine(const std::string_view routine_name);

};

template <typename routine_prototype>
[[nodiscard]] bool argumented_routine_handler<routine_prototype>::validate_routine(const std::string_view routine_name) const
{
    try
    {
        this->routine_map.at(routine_name);
        return true;
    }
    catch (const std::out_of_range&)
    {
        std::cerr << "routine " << routine_name << " not in routine map\n";
        return false;
    }
}


template<typename routine_prototype>
void argumented_routine_handler<routine_prototype>::insert_routine(const std::string_view routine_name, std::pair<std::function<routine_prototype>, void*> routine_pair)
{
    this->routine_map.insert(std::make_pair(routine_name, routine_pair));
}

template<typename routine_prototype>
ARGUMENTEDROUTINE_FORCEINLINE void argumented_routine_handler<routine_prototype>::remove_routine(const std::string_view routine_name)
{
    if (!validate_routine(routine_name)) return;

    this->routine_map.erase(routine_name);

}

template <typename routine_prototype>
ARGUMENTEDROUTINE_FORCEINLINE void argumented_routine_handler<routine_prototype>::replace_routine(const std::string_view routine_name, std::pair<std::function<routine_prototype>, void*> routine_pair)
{
    if (!validate_routine(routine_name)) return;

    this->routine_map.at(routine_name) = routine_pair;
    std::cout << "replaced routine " << routine_name << " with new functionality\n";

}

template <typename routine_prototype>
template<typename... args>
ARGUMENTEDROUTINE_FORCEINLINE void argumented_routine_handler<routine_prototype>::call_routine(const std::string_view routine_name) const
{
    if (!validate_routine(routine_name)) return;
    const auto routine_pair = this->routine_map.at(routine_name);
    const auto routine = std::get<0>(routine_pair);
    const auto routine_args = static_cast<std::tuple<args...>*>(std::get<1>(routine_pair));

    std::apply(routine, *routine_args);

}

template<typename routine_prototype>
[[nodiscard]] ARGUMENTEDROUTINE_FORCEINLINE std::optional<std::pair<std::function<routine_prototype>, void*>> argumented_routine_handler<routine_prototype>::return_routine(const std::string_view routine_name) const
{
    if (!validate_routine(routine_name)) return {};
    return this->routine_map.at(routine_name);
}


template <typename routine_prototype>
[[nodiscard]] constexpr ARGUMENTEDROUTINE_FORCEINLINE std::size_t argumented_routine_handler<routine_prototype>::return_routine_map_sz() const
{
    return this->routine_map.size();
}
