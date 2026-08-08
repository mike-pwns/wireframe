# WIREFRAME (SUMMER 2026)  
  
Pretty chill project for me to apply math i learned for graphics.  

note that this aint no triple A game studio renderer, just sticks and stones put together cuz i wanned to know how 3d stuff shows up on a 2d screen. soo... dont go thinking this is gonna be bug-free - I aint got 50 years of graphics programming experience to work out every intricate detail

i kinda just looked at some pictures, fell asleep trying to read some "overly complicated" tutorials, and with my genius intuition came to whatever this project was (shoutout Ms. D for teaching line-plane intersection, that was the key to me coming up with the logic!!!) 

## What is this actually  
  
Its a wireframe 3D renderer that runs in browser via WASM. under the hood theres a `Wireframe model`, `Camera cam`, and `Scene world` sitting in main.c doing the heavy lifting, and renderlib.c does all the projection/clipping math. frontend just pokes a `RenderedResult` pointer out of WASM memory (`getRenderResult()`) and draws whatever it finds onto a canvas. the pointer arithmetic is simple in theory, but because of nested structs i was too lazy to keep track of it all, hence that part was AI's problem not mine.  
  
ships with 7 built in models you can flip through in the gallery - 
1. CUBE,
2. PYRAMID,
3. SPHERE,
4. OCTAHEDRON,
5. TORUS,
6. SYNTHSCAPE (<-- my personal favorite), and
7. PENGUIN.

theres also a custom builder where you can place your own verts/edges  
and it just nukes and rebuilds the whole C-side model from scratch every time  
you touch it. meh, sure, but it works.  
  
**full disclosure:** the front end (html/css, ui chrome, buttons, all the "make  
it look nice" stuff) is basically 100% AI. im not a frontend guy, wasnt gonna  
pretend to be one for this. if youre here to actually look at code i wrote,  
stick to `src/` and `include/`.  
  
## Inspiration  
  
[fill in]  
  
## Why C + WASM (and not just... three.js)  
  
[fill in]  
  
## How rendering actually works  
  
[fill in]
  
## Challenges / things that broke my brain  
  
[fill in]  
  
## What I'd do differently  
  
[fill in]  
  
## Running the program  
  
**note: why not just head on over to [the deployed page](https://mike-pwns.github.io/wireframe/) and see for yourself?**  
  
ok ok!! if you REALLY wanna compile it on your own and play around, follow these steps:  

### 1. clone this repo and go into it  
```
git clone https://github.com/mike-pwns/wireframe.git
cd wireframe/ 
```

### 2. make sure you got the dependencies straight

this project uses 2 main dependencies, everything else is written from scratch in C.  

**EMSCRIPTEN** (compiler based on clang for compiling wasm and js files): 
download instructions pulled from [emscripten docs](https://emscripten.org/docs/getting_started/downloads.html)

```
# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
cd emsdk

# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
```

**PYTHON 3** (this is probably already installed, but you can check to be safe with `python3 --version`)  
```
# using apt
sudo apt update
sudo apt install -y python3
```

### 3. compile the files  
make sure you're in the `wireframe/` directory, not the emscripten one (if you just set it up) - to go back just go `cd ..`

now we gotta compile the files!

its kinda messy but just cp it and you'll be good.

```
emcc src/main.c src/linlib.c src/renderlib.c \
  -Iinclude \
  -o public/renderer.js \
  -s EXPORTED_FUNCTIONS='["_initialize","_renderScene","_getRenderResult","_transformCamera","_switchModel","_addCustomVertex","_connectCustomVertices","_clearCustomModel","_getCameraTransform"]' \
  -s EXPORTED_RUNTIME_METHODS='["HEAP32","HEAPF32"]'
```

this should produce an `obj` and `build` directory - those can generally be ignored!
  
### 4. go into the public directory, and start http server  
```
cd public/

# by default this opens the server on port 8000
python3 -m http.server  
```

### 5. head on over to `localhost:8000/index.html` (or whatever port you used) on any browser (preferably chromium-based) and youre golden.  

just note that if you wanna make changes and play around with the C, you gotta recompile with the command from #3 each time, but no need to restart server
  
## Screenshots / Demo  

// ill put screeny here later

  
## Credits  
  
[fill in]  
  
## What's next  
  
stuff im (maybe) getting around to eventually, tracked in `features_to_add.txt`:  

most likely addition: 
- an "info" tab where i write MY OWN tutorial / understanding of rendering logic in my own unique style (analogies, and genuinely just straightforward and ZERO overcomplicating cuz i know it sucks when its... yapadapadoo etc you get the gist). 
- also just a document of my experience learning this with pretty pictures and whatnot

other stuff that could be cool but im too lazy to implement at this moment:
- rotation - spin the model around its center point  
- axes toggle - see the x/y/z axes  
- ui color options - not everything has to be hacker green  
- fov slider - mess with viewport distance  
- more sliders - movement speed, rotation speed, framerate  
- coordinate display - show point coords + camera position/orientation  
- save/import/export - actually persist your custom models instead of losing  
  them on refresh
