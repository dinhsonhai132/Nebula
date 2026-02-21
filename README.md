# Nebula
A Game Engine for Suny using C++

Nebula is a lightweight 2D game engine built in C++ designed to power the Suny scripting language.  
It provides a simple runtime, rendering layer, and scripting bridge to build games quickly and efficiently.

# Requirements

- C++17 or later
- SDL2 (or your chosen rendering backend)
- Make

# Build
```
cd Nebula
make
```

# Example
```lua
width = 800
height = 600
title = "DVD Cube"

squareX = 200
squareY = 150
squareSize = 80

velX = 200
velY = 300

squareR = 143
squareG = 200
squareB = 123

function init() do
    print("DVD cube start")
end 

function update(dt) do

    squareX = squareX + velX * dt
    squareY = squareY + velY * dt

    if squareX <= 0 then
        squareX = 0
        velX = -velX
    end

    if squareX + squareSize >= width then
        squareX = width - squareSize
        velX = -velX
    end

    if squareY <= 0 then
        squareY = 0
        velY = -velY
    end

    if squareY + squareSize >= height then
        squareY = height - squareSize
        velY = -velY
    end
end

function draw() do
    draw_rect(squareX, squareY, squareSize, squareSize, squareR, squareG, squareB)
end
```

**Run**

```
game main.suny
```
