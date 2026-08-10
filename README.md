**full disclosure:** the front end is basically 100% AI. im not a frontend guy; aint a react wizard (*yet*), aint gonna pretend to be one for *this* project. if youre here to actually look at code i wrote, stick to `src/` and `include/`. Enjoy!

# WIREFRAME (SUMMER 2026)  
  
Pretty chill project for me to apply math i learned for graphics.  

note that this isnt a triple A game studio renderer, just sticks and stones put together cuz i wanned to know how 3d stuff shows up on a 2d screen. soo... dont go thinking this is gonna be bug-free - I aint got 50 years of graphics programming experience to work out every intricate bug. here for the general idea first, then later if i wanna do something bigger, i already have this base knowledge

## What is this actually  
  
this project is a 3d wireframe renderer with logic derived from vector math. you can float around and explore the "world". more on the inspiration later in this readme.

it has 7 built in models you can explore 
1. CUBE,
2. PYRAMID,
3. SPHERE,
4. OCTAHEDRON,
5. TORUS,
6. SYNTHSCAPE (<-- my personal favorite), and
7. PENGUIN.

theres also a custom builder where you can place your own verts/edges.

didnt make a save feature, it so just admire and if you really wanna save it, note the points and edges on paper or on a text file.

## screenshots 

// main screen + fullscreen with custom model of a "quadratic" (22 verts)

<img width="1920" height="953" alt="Screenshot_2026-08-10_07-54-40" src="https://github.com/user-attachments/assets/4d641848-c891-47e7-a728-63ec5a34906b" />
<img width="1920" height="953" alt="Screenshot_2026-08-10_07-54-29" src="https://github.com/user-attachments/assets/4596e046-7321-48dd-9f13-d14da102e23e" />
  
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

since this repo (which you probably cloned) already has `renderer.js`, it will just be overwritten with any changes made to the source files - note that if you add a function you want js to use, you must add it to `EXPORTED_FUNCTIONS`
  
### 4. go into the public directory, and start http server  
```
cd public/

# by default this opens the server on port 8000
python3 -m http.server  
```

### 5. head on over to `localhost:8000/index.html` (or whatever port you used) on any browser and youre golden.  

just note that if you wanna make changes and play around with the C, you gotta recompile with the command from #3 each time, but theres no need to restart this server

## inspiration  
  
graphics as a whole have been pretty interesting to me for years, but when i did `vector_vr` i was much more intrigued by using virtual space to show things: concepts, ideas, etc. i was super hyped to start learning linear algebra in the vectors "sub-course" in my math class (which i ended up skipping like 80% of anyways) because it would enable me to understand the fundamentals of computers as we know em now (not ai, but screens); not just blocks in a room that interact with some physical medium but rather with a digitized multi-purpose interface. 

anyways, i really liked the aesthetic too - hacker green, numbers flyin everywhere; abstracting space itself, i mean that just sounds cool, no? Also, a question i got while making this a few times was **why c and wasm instead of just using js for the whole thing?** which did make me think and remember getting some experience in C itself was an inspiration for this project. The main factors with that were:

1. js makes no sense and is quite frankly pretty stupid!!!!!!! (in reality im too lazy to get an ide that catches syntax of js + js is super inconsistent + it is also just plain doesnt say what is wrong!! Like gee whiz i dont wanna use ai for everything but js doesnt make it easy!!!! "oh but just use typescript" - good point, but im not on that stack yet, maybe another time)

2. i attended some systems programming lectures in the spring. i found the concepts super cool, and was inspired to learn a bit and work on something even more bare bones; to have a have a full "build it yourself" experience rather than just use already hella abstracted libraries (btw shoutout prof - if youre reading this i didnt do pointer arithmetic in this proj cuz my ai agent really wanted to do it, but i promise i understand the idea). Also i heard c is faster and is used with wasm for higher performance on web apps/games, so just some cool tech to be familiar with.
  
## challenges 

honestly i wanted to start this project back in april, back when i was a jit and still had no idea anything past what a vector was - my biggest mistake was making this (3d rendering) out to be some monster, i was stressed this would be some "omagah this is gonna be so hard!!". It was, and it wasnt.

you know the saying "you gotta learn the thing twice to understand it"? for OOP i had to learn it like 4 times over half a year to actually get it. similar case here: though here i was going for more of an intuition-based influence on the programming logic rather than someone telling me "this is how we do it so youre gonna do it like this too", so the challenge was in deriving the idea from scratch rather than just reading and doing - which made the challenge more interesting. 

i kid you not this picture was the only thing i needed to see to get the idea; this is what caused everything to click
<img width="1180" height="632" alt="Screenshot_2026-07-23_12-52-05" src="https://github.com/user-attachments/assets/449377a0-0ee5-4d47-82f0-78c677eeb2d1" />

in april i came up with some version of orthographic projection that genuinely might as well be from hell, and frankly looking back i can only laugh at myself then - but then again, i tried and i made it here. frankly, i dont know any of the formal terms (i think what im doing is called rasterization with perspective projection, even after all this im still uncertain - thats the extent to how self-derived this stuff was)

so my success was mainly just seeing different pieces over time until everything linked. i read some journals / guides on computer graphics (id link them but i cant find them), but a lot of them were talking about some bs for 3 entries or overcomplicated the math (i say that, having done the math), generally a lot of them didnt get to the point i was looking for. maybe ill write my own "no bs guide"

after i finally got the logic down, implementing was super ez - C wasnt that different from java syntax-wise - yeah had to get used to structs and the lack of convenient features i took for granted, but not too bad. the extra math i didnt know was easy enough to figure out, so not much of a challenge there. ui and ai was hella annoying - ai tried to argue with me at one point, get that? 

the smaller details like camera movement, transformations (reverse order, etc) were all just extra learning moments which i used resources to learn how to fix (since at that point i got the big idea and was cool on leaning on other people's solutions to the problems muwahahaha). 

Whatever, it was a fun experience nonetheless. 8/10 would recommend
  
## what id do differently (project-planning wise for future projects)  

i dont think learning can be "rushed" for something like this - prior to this final product, i made
1. "wasm_test" --> just to learn how wasm is compiled and how to call c methods from js
<img width="1920" height="953" alt="Screenshot_2026-08-10_08-48-07" src="https://github.com/user-attachments/assets/e745d026-3180-462d-8b78-c9dc12d40d04" />

2. "clockz" --> get better with C, write basic vector math library (+ learn rotation), and understand the canvas apis
<img width="1920" height="953" alt="Screenshot_2026-08-10_08-49-43" src="https://github.com/user-attachments/assets/be716c5c-536e-450a-a454-0cb85f4a7560" />

this is the same procedure i have for other learning projects: break up into components and do individual mini projects. that way i have some experience with the chisels before i work on the good marble yknow? Time was a bit of a pain though.. focused effort is certainly a better idea i suppose

it took like 3 months of ruminating directionlessly on this topic (1.5 if you consider me being capable of this only after i learned planes and lines) before anything came about - it wasnt focused per se - more so that this was just something i wanted to do. Only after i had the "how" could i chase doing the "what".

for future projects, if there is something to learn - maybe not for curiousity sake, but because its an assignment and i need to submit it - there should be focus; ie consistent effort put into understanding the concepts(rather than what i was doing, just sitting around until the idea came to me). 

so the immediate actionable steps for the next project is to **commit daily to the *learning* process (not necessarily to the final project in mind) regardless of how much you know**

## Credits / Sources

- AI - chatgpt (early on for confirming my understanding), claude (for ui)
- some websites, i genuinely forget what they are, but they were cool tutorials, ill put them here if i find them
- people (theres a lot of people, for privacy sake i wont just name drop) - for advice on dynamic array implementation, some sources for research, linear algebra knowledge, and encouragement/positive words
- [3Blue1Brown](https://www.youtube.com/@3blue1brown) - for extended linear algebra research

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
