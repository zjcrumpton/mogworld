# 📖 **Mogworld Engine**

Welcome to **Mogworld Engine** — a custom-built C++ game engine designed to support **RPG-like games** with a focus on flexible world-building, traits-based materials, and extensibility. This project is built to support both **headless gameplay** and a **Qt-powered editor**. Users of the engine and fans of the game can build their own clients as they wish.

---

## 🚀 Quick Start Guide (WSL/Linux)

### ✅ Step 1 - Install Dependencies
Run this in your terminal:
```bash
sudo apt update
sudo apt install -y qt6-base-dev qt6-base-dev-tools g++ make
```

---

### ✅ Step 2 - Clone the Repository
```bash
git clone <repo-url>
cd mogworld
```

---

### ✅ Step 3 - Build the Project
```bash
make
```

This will build two executables:

| Target | Description |
|---|---|
| `out/mogworld` | The game itself (headless for now) |
| `out/mogworld_editor` | The Qt-based editor for editing traits and content |

---

### ✅ Step 4 - Run the Game
```bash
./out/mogworld
```

---

### ✅ Step 5 - Run the Editor
```bash
./out/mogworld_editor
```

---

# 🗂️ Project Structure

```
.
├── assets/                 # Game data (like traits.json)
├── src/                     # Game engine source code
├── editor/                   # Editor GUI source code
├── include/                  # Shared headers
├── out/                      # Built executables
├── Makefile                   # Build system
├── .vscode/                   # VSCode settings (see below)
```

---

# ⚙️ Editor Development Environment (VSCode Setup)

### WSL Users
Copy the **WSL-friendly IntelliSense config** into place:
```bash
cp .vscode/c_cpp_properties.wsl.json .vscode/c_cpp_properties.json
```

---

### Native Linux Users (Optional)
If you want to work on this **outside WSL**, copy:
```bash
cp .vscode/c_cpp_properties.linux.json .vscode/c_cpp_properties.json
```

---

# 📦 Traits System
This engine uses a **trait system** to describe how materials (like wood, lava, grass) behave. Traits are stored in:
```
assets/traits.json
```

Example trait file:
```json
[
    {
        "name": "flammable",
        "description": "Catches fire when exposed to heat."
    },
    {
        "name": "slippery",
        "description": "Entities slide when moving across this."
    }
]
```

The **editor** allows you to view, edit, and add traits. It writes directly back to this file.

---

# 💻 Recommended Tools
| Tool | Purpose |
|---|---|
| **VSCode** | Editing and IntelliSense |
| **g++** | Compiler |
| **Qt6** | GUI Framework for the editor |
| **make** | Build system (no CMake needed) |

---

# ⚠️ Troubleshooting

| Issue | Possible Fix |
|---|---|
| Qt headers not found in VSCode | Check `c_cpp_properties.json` or re-run: `cp .vscode/c_cpp_properties.wsl.json .vscode/c_cpp_properties.json` |
| Qt not installed | Run `sudo apt install qt6-base-dev qt6-base-dev-tools` |
| Editor crashes on startup | Make sure you have an X server running if using WSL (VcXsrv or X410) |

---

# 📬 Contributing
We welcome contributions! Please follow these guidelines:

✅ Open issues if you find bugs.  
✅ Use descriptive commit messages.  
✅ Run `make clean && make` before pushing to make sure the build is clean.

---

# 📅 Roadmap
- [x] Basic trait system
- [x] Qt-based trait editor
- [ ] Material registry
- [ ] World map loading
- [ ] Entity system (players, NPCs)
- [ ] Basic gameplay loop (movement, interaction)
- [ ] Networking support for multiplayer

---

# 🏗️ License

MIT

---

# ✨ Final Note
If you hit any issues setting up, please open an issue on GitHub or ping the project maintainers.
