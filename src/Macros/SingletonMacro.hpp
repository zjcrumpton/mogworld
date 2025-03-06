#ifndef SINGLETON_MACRO_HPP
#define SINGLETON_MACRO_HPP

#define DECLARE_SINGLETON(ClassName) \
    public:                          \
            static ClassName& get() { \
                static ClassName instance; \
                return instance; \
            } \
    private: \
            ClassName() = default; \
            ~ClassName() = default; \ 
            /* Deleted to prevent copies/clones (singleton enforcement) */ \
            ClassName(const ClassName&) = delete; \
            ClassName& operator=(const ClassName&) = delete; \

#endif // SINGLETON_MACRO_HPP