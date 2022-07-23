#pragma once

#include <unordered_map>
#include <functional>
#include <string_view>
#include <optional>
#include <iostream>

#define ROUTINE_FORCEINLINE __forceinline

template<typename routine_prototype>
class routine_handler
{
private:
    std::unordered_map<std::string_view, std::function<routine_prototype>> routine_map{};
public:

    void call_routines() const;

    [[nodiscard]]
    ROUTINE_FORCEINLINE std::size_t return_routine_map_sz() const;

    [[nodiscard]]
    bool validate_routine(const std::string_view) const;

    [[nodiscard]]
    ROUTINE_FORCEINLINE std::optional<std::function<routine_prototype>> return_routine(const std::string_view routine_name) const;
    
    ROUTINE_FORCEINLINE void remove_routine(const std::string_view routine_name);
    ROUTINE_FORCEINLINE void replace_routine(const std::string_view routine_name, std::function<routine_prototype> routine);

    ROUTINE_FORCEINLINE void call_routine(const std::string_view routine_name) const;
    ROUTINE_FORCEINLINE void add_routine(const std::string_view, std::function<routine_prototype> routine);
    
};


template <typename routine_prototype>
[[nodiscard]] bool routine_handler<routine_prototype>::validate_routine(const std::string_view routine_name) const
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
ROUTINE_FORCEINLINE ROUTINE_FORCEINLINE void routine_handler<routine_prototype>::add_routine(const std::string_view routine_name, std::function<routine_prototype> routine)
{
    this->routine_map.insert(std::make_pair(routine_name, routine));
}

template<typename routine_prototype>
ROUTINE_FORCEINLINE void routine_handler<routine_prototype>::remove_routine(const std::string_view routine_name)
{
    if (!validate_routine(routine_name)) return;

    this->routine_map.erase(routine_name);
    
}

template <typename routine_prototype>
ROUTINE_FORCEINLINE void routine_handler<routine_prototype>::replace_routine(const std::string_view routine_name, std::function<routine_prototype> routine)
{
    if (!validate_routine(routine_name)) return;

	this->routine_map.at(routine_name) = routine;
    std::cout << "replaced routine " << routine_name << " with new routine functionality\n";
    
}


template<typename routine_prototype>
void routine_handler<routine_prototype>::call_routines() const
{
    for (const auto& [routine_name, routine] : this->routine_map)
    {
        routine();
    }
    std::cout << "called " << return_routine_map_sz() << " routines\n";
}

template <typename routine_prototype>
ROUTINE_FORCEINLINE void routine_handler<routine_prototype>::call_routine(const std::string_view routine_name) const
{
    if (!validate_routine(routine_name)) return;
	const auto routine = this->routine_map.at(routine_name);
    routine();
}

template<typename routine_prototype>
[[nodiscard]] ROUTINE_FORCEINLINE std::optional<std::function<routine_prototype>> routine_handler<routine_prototype>::return_routine(const std::string_view routine_name) const
{
    if (!validate_routine(routine_name)) return {};
	return this->routine_map.at(routine_name);
}


template <typename routine_prototype>
[[nodiscard]] ROUTINE_FORCEINLINE std::size_t routine_handler<routine_prototype>::return_routine_map_sz() const
{
    return this->routine_map.size();
}
