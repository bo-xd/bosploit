---

# bosploit

A simple DLL for running Lua scripts in Minecraft 1.21.5.

---

## Setup

1. Change the Lua file path in `main.cpp`:

```cpp
if (luaL_dofile(L, "/minecraft.lua") != LUA_OK) {
```

→ Replace `/minecraft.lua` with your own Lua script path.

2. Build the DLL.

3. Inject the DLL into Minecraft using any injector.

---

## Example Lua script

```lua
local localplayer = game:GetService("Players").LocalPlayer
print(localplayer.Character:getY(), localplayer.Character:getX(), localplayer.Character:getZ())
localplayer.Character:setSprinting(true)
```

---

## Note
* Works only with Minecraft 1.21.5.

