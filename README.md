# bosploit

**Roblox-style executor for Minecraft**  
got kinda bored so just released it open source

[https://bosploit.xyz/](https://bosploit.xyz/)

---

## how to build
change the  scriptPath inside main.cpp to ur own .lua file and then build with vs

---

## Current Features

- Roblox-like scripting interface
- Basic player actions and state functions
- Multi-mapping support (Fabric, Forge, etc.) — *requires manual mapping*

---

## Implemented Functions

```lua
-- Services
local player = game:GetService("Players").LocalPlayer
local chat = game:GetService("ChatService")

-- Actions
player:dropItem(bool fullstack)

-- State
player.Character:setSprinting(bool sprinting)
player.Character:isSprinting()     -- returns boolean
player.Character:isCrouching()     -- returns boolean

-- Chat
chat:sendMessage("Hallo, World!")

-- Position
player.Character:getX()            -- returns double
player.Character:getY()            -- returns double
player.Character:getZ()            -- returns double
```
