#ifndef REFLECTABLE_HPP
#define REFLECTABLE_HPP

#include <tuple>
#include <string_view>

// Field data holder
template <typename T, typename Struct>
struct FieldInfo {
    std::string_view name;
    T Struct::*ptr;
};

// Main macro (only works inside a struct)
#define REFLECTABLE(Type, ...) \
    static constexpr auto reflect_fields() { \
        using ThisType = Type; \
        return std::make_tuple(__VA_ARGS__); \
    } \
    static constexpr std::size_t reflect_field_count() { \
        return std::tuple_size_v<decltype(reflect_fields())>; \
    }

// Field helper (used inside REFLECTABLE)
#define REFLECT_FIELD(type, name) FieldInfo<type, ThisType>{#name, &ThisType::name}

#endif // REFLECTABLE_HPP
