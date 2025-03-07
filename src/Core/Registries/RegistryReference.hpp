#ifndef REFERENCE_REGISTRY_HPP
#define REFERENCE_REGISTRY_HPP

#define DEFINE_REGISTRY_REFERENCE(Type, RegistryType)                \
    struct Type##Reference {                                          \
        std::string name;                                             \
                                                                      \
        const Type* resolve() const {                                 \
            return RegistryType::get().find_by_name(name);            \
        }                                                             \
                                                                      \
        bool is_valid() const {                                       \
            return resolve() != nullptr;                              \
        }                                                             \
    };                                                                \
                                                                      \
    inline void to_json(nlohmann::json& j, const Type##Reference& ref) { \
        j = ref.name;                                                 \
    }                                                                 \
                                                                      \
    inline void from_json(const nlohmann::json& j, Type##Reference& ref) { \
        j.get_to(ref.name);                                           \
    }

    #endif // REFERENCE_REGISTRY_HPP