#ifndef JSON_REGISTRY_BASE_HPP
#define JSON_REGISTRY_BASE_HPP

#include <string>
#include <unordered_map>
#include <fstream>
#include "nlohmann/json.hpp"

// Base class template for any JSON-backed registry
template<typename T, const char* FilePath>
class JsonRegistryBase {
public:
    void load() {
        clear();
        load_from_file(FilePath);
    }

    void save() const {
        save_to_file(FilePath);
    }

    void clear() {
        data.clear();
    }

    bool is_known(const std::string& name) const {
        return data.find(name) != data.end();
    }

    const T* find_by_name(const std::string& name) const {
        auto it = data.find(name);
        if (it != data.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void add_or_update(const T& item) {
        data[item.name] = item;
    }

    void remove(const std::string& name) {
        data.erase(name);
    }

    std::vector<T> get_all() const {
        std::vector<T> all;
        all.reserve(data.size());
        for (const auto& pair : data) {
            all.push_back(pair.second);
        }
        return all;
    }

    std::vector<std::string> get_all_names() const {
        std::vector<std::string> names;
        names.reserve(data.size());
        for (const auto& pair : data) {
            names.push_back(pair.first);
        }
        return names;
    }

protected:
    JsonRegistryBase() = default;
    ~JsonRegistryBase() = default;

private:
    std::unordered_map<std::string, T> data;

    void load_from_file(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + path);
        }

        nlohmann::json json;
        file >> json;

        auto items = json.get<std::vector<T>>();
        for (const auto& item : items) {
            data[item.name] = item;
        }
    }

    void save_to_file(const std::string& path) const {
        std::ofstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for writing: " + path);
        }

        nlohmann::json json = get_all();
        file << json.dump(4);  // pretty print with indent
    }
};

#endif // JSON_REGISTRY_BASE_HPP
