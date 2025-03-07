#ifndef REFLECTIONMACRO_HPP
#define REFLECTIONMACRO_HPP

#include <string>
#include <vector>
#include <cstddef>
#include <nlohmann/json.hpp>
#include <utility>  // for std::declval

// Forward declarations for known registry references
struct MaterialReference; // Add more as needed for other registries

// Holds metadata for a single field
struct FieldInfo {
    std::string name;
    size_t offset;
    std::string typeName;
};

// Type Name Resolver (customizable to your needs)
template<typename T>
std::string getTypeName() {
    if constexpr (std::is_same_v<T, std::string>) {
        return "string";
    } else if constexpr (std::is_same_v<T, bool>) {
        return "bool";
    } else if constexpr (std::is_same_v<T, MaterialReference>) {
        return "MaterialReference";
    } else {
        return "Unknown"; // Safeguard for future expansion
    }
}

// Generates FieldInfo entry for a single field
#define SINGLE_FIELD_INFO(structName, fieldName) \
    FieldInfo{#fieldName, offsetof(structName, fieldName), getTypeName<decltype(std::declval<structName>().fieldName)>()}

// This helper generates the list of fields — comma-separated
#define FIELD_INFO_LIST(structName, ...) \
    EXPAND(FOR_EACH(SINGLE_FIELD_INFO, structName, __VA_ARGS__))

// Main REFLECT macro: generates getFields() and JSON serialization capabilities
#define REFLECT(structName, ...) \
    static_assert(COUNT_ARGS(__VA_ARGS__) <= 12, "REFLECT macro supports up to 12 fields. Add more to ReflectionMacro.hpp if needed."); \
    static const std::vector<FieldInfo>& getFields() { \
        static const std::vector<FieldInfo> fields = { FIELD_INFO_LIST(structName, __VA_ARGS__) }; \
        return fields; \
    } \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(structName, __VA_ARGS__)

// Macro magic to handle variadic field lists
#define EXPAND(x) x

#define FOR_EACH_1(m, s, x) m(s, x)
#define FOR_EACH_2(m, s, x, ...) m(s, x), FOR_EACH_1(m, s, __VA_ARGS__)
#define FOR_EACH_3(m, s, x, ...) m(s, x), FOR_EACH_2(m, s, __VA_ARGS__)
#define FOR_EACH_4(m, s, x, ...) m(s, x), FOR_EACH_3(m, s, __VA_ARGS__)
#define FOR_EACH_5(m, s, x, ...) m(s, x), FOR_EACH_4(m, s, __VA_ARGS__)
#define FOR_EACH_6(m, s, x, ...) m(s, x), FOR_EACH_5(m, s, __VA_ARGS__)
#define FOR_EACH_7(m, s, x, ...) m(s, x), FOR_EACH_6(m, s, __VA_ARGS__)
#define FOR_EACH_8(m, s, x, ...) m(s, x), FOR_EACH_7(m, s, __VA_ARGS__)
#define FOR_EACH_9(m, s, x, ...) m(s, x), FOR_EACH_8(m, s, __VA_ARGS__)
#define FOR_EACH_10(m, s, x, ...) m(s, x), FOR_EACH_9(m, s, __VA_ARGS__)
#define FOR_EACH_11(m, s, x, ...) m(s, x), FOR_EACH_10(m, s, __VA_ARGS__)
#define FOR_EACH_12(m, s, x, ...) m(s, x), FOR_EACH_11(m, s, __VA_ARGS__)

#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,NAME,...) NAME
#define FOR_EACH(m, s, ...) EXPAND(GET_MACRO(__VA_ARGS__, \
    FOR_EACH_12, FOR_EACH_11, FOR_EACH_10, FOR_EACH_9, FOR_EACH_8, \
    FOR_EACH_7, FOR_EACH_6, FOR_EACH_5, FOR_EACH_4, FOR_EACH_3, \
    FOR_EACH_2, FOR_EACH_1)(m, s, __VA_ARGS__))

// Argument counting macro
#define COUNT_ARGS(...) COUNT_ARGS_IMPL(__VA_ARGS__, RSEQ_N())
#define COUNT_ARGS_IMPL(...) ARG_N(__VA_ARGS__)
#define ARG_N( _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,N,...) N
#define RSEQ_N() 12,11,10,9,8,7,6,5,4,3,2,1,0

#endif // REFLECTIONMACRO_HPP
