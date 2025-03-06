#ifndef REFLECTIONMACRO_HPP
#define REFLECTIONMACRO_HPP

#include <string>
#include <vector>
#include <typeinfo>
#include <cstddef>
#include <nlohmann/json.hpp>

// Holds metadata for a single field
struct FieldInfo {
    std::string name;
    size_t offset;
    std::string typeName;
};

// Generates FieldInfo entry for a single field
#define SINGLE_FIELD_INFO(structName, fieldName) \
    FieldInfo{#fieldName, offsetof(structName, fieldName), typeid(decltype(structName::fieldName)).name()}

// This helper generates the list of fields — comma-separated
#define FIELD_INFO_LIST(structName, ...) \
    EXPAND(FOR_EACH(SINGLE_FIELD_INFO, structName, __VA_ARGS__))

// Main REFLECT macro: generates getFields() and JSON serialization capabilities
#define REFLECT(structName, ...) \
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
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define FOR_EACH(m, s, ...) EXPAND(GET_MACRO(__VA_ARGS__, FOR_EACH_4, FOR_EACH_3, FOR_EACH_2, FOR_EACH_1)(m, s, __VA_ARGS__))

#endif // REFLECTIONMACRO_HPP
