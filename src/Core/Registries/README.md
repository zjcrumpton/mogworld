
# Registries

This folder contains **global registries** that manage important game data, such as **traits**, **materials**, and other core entities.

---

## 📂 What is a Registry?

A **registry** acts as the single source of truth for a particular type of data. It is responsible for:

✅ Loading data from external files (usually JSON).  
✅ Storing data in memory for fast access.  
✅ Providing query functions (e.g., `get_trait_by_name`).  
✅ Allowing data modification (in editor mode).  
✅ Saving back to disk if modified.

---

## 📋 Current Registries

| Registry | Purpose |
|---|---|
| `TraitRegistry` | Manages all known **Traits**. Traits are properties that can apply to materials, items, etc. Example: Flammable, Slippery. |
| `MaterialRegistry` | Manages all known **Materials**. Materials define what things are made of. Example: Wood, Steel. (Planned) |

---

## 📐 Registry Structure

Every registry should follow this general structure:

### 1️⃣ **Singleton Pattern**
Each registry is globally accessible via:
```cpp
TraitRegistry::get()
```
This ensures there's exactly one instance managing the data.

---

### 2️⃣ **Core Methods**
All registries should expose at least:
- `load()`: Loads data from disk.
- `save()`: Writes data back to disk.
- `clear()`: Clears in-memory data.
- `get_*()`: Lookup methods (by name, etc.).
- `add_or_update_*()`: For editor changes.
- `remove_*()`: For deletions.

---

### 3️⃣ **File Locations**
Each registry loads from a **known file path**, usually inside:
```
assets/
```
For example:
```
assets/traits.json
assets/materials.json
```

---

### 📏 Naming Convention
Each file should follow:
| File Type | Example |
|---|---|
| Header File | `TraitRegistry.hpp` |
| Source File | `TraitRegistry.cpp` |
| JSON Data | `traits.json` |

---

### ➕ Adding a New Registry
To add a new registry, follow these steps:
1. Create `XRegistry.hpp` and `XRegistry.cpp` in this folder.
2. Follow the existing patterns in `TraitRegistry`.
3. Update the editor to load the new registry when launching.
4. Add basic editor UI (like `MaterialEditorWindow`) if necessary.
5. Document the new registry in this file.

---

### 💡 Notes for Contributors
- All registries **must automatically load on startup**.
- Data files should be **human-readable JSON** for easy modification.
- Registries should avoid direct UI dependencies — they are **pure data managers**. Editors (in `editor/`) handle actual user interfaces.

---

### Example Template (For New Registry)

```cpp
// Example: EquipmentRegistry.hpp

class EquipmentRegistry {
public:
    static EquipmentRegistry& get();

    void load();
    void save();
    void clear();

    bool is_known_equipment(const std::string& name) const;
    const Equipment* get_equipment(const std::string& name) const;
    std::vector<Equipment> get_all_equipment() const;
    void add_or_update_equipment(const Equipment& equipment);
    void remove_equipment(const std::string& name);

private:
    EquipmentRegistry() = default;
    ~EquipmentRegistry() = default;

    std::unordered_map<std::string, Equipment> equipment;

    void load_equipment_from_file(const std::string& path);
};
```

---

### 📞 Questions?
If you're unsure about adding/modifying a registry, check with the project lead first!
