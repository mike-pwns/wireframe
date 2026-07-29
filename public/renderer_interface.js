// universal coords n whatnot
const X = 0;
const Y = 1;

// customizations
const HACKER_GREEN = "#20C20E";
const STROKE_WIDTH = 10; // in px


// canvas thing

const CANVAS = document.getElementById("canvas");
const CONTEXT = CANVAS.getContext("2d");
const CANVAS_WIDTH = 1024; // in px
const CANVAS_HEIGHT = 1024; // in px

function initialize_canvas() {

	// size remains the same on html
	// just changes the resolution
	CANVAS.width = CANVAS_WIDTH;
	CANVAS.height = CANVAS_HEIGHT;

	// this would change the actual css
	// CANVAS.style.width = CANVAS_WIDTH + "px";
	// CANVAS.style.height = CANVAS_HEIGHT + "px";

	// set line drawing stuff
	CONTEXT.strokeStyle = HACKER_GREEN;
	CONTEXT.fillStyle = HACKER_GREEN;
	CONTEXT.lineWidth = STROKE_WIDTH;

	// CONTEXT.fillStyle='#000000';  // can export as a global var

	CANVAS_MATHEMATICAL_ORIGIN = [CANVAS_WIDTH/2, CANVAS_HEIGHT/2];

}

// uses canvas coords
// inputs are arrays [x, y]

function draw_line(start, end) {
	CONTEXT.beginPath();
	CONTEXT.moveTo(start[X], start[Y]);
	CONTEXT.lineTo(end[X], end[Y]);
	CONTEXT.stroke();
}

// uses canvas coords
function draw_circle(x, y, radius) {
	CONTEXT.beginPath();
	CONTEXT.arc(x, y, radius, 0, Math.PI * 2); 
	CONTEXT.fill();
}

// "centered at" the coord given; "accurate point"
// cirlce just looked weird as a point, so using square
function draw_square(x, y, side_len) {

	let actX = (x - side_len/2);
	let actY = (y - side_len/2);

	CONTEXT.beginPath();
	CONTEXT.fillRect(actX, actY, side_len, side_len);

	// replaces the following (with proper centering):
	// CONTEXT.fillRect(512, 512, 100, 100);
	
}


// read data and parse from c


function getRenderResult() {

    const ptr = Module._getRenderResult();

    const heap32 = Module.HEAP32;
    const base = ptr >> 2;


    // RenderedResult:
    // DynamicRenderedPixelArray pixels
    // DynamicRenderedLineArray lines

    const pixelsPtr = base;
    const linesPtr = base + 3; // assuming each dynamic array is ptr + int + int


    // pixels array
    const pixelDataPtr = heap32[pixelsPtr];
    const pixelLength = heap32[pixelsPtr + 1];


    let pixels = [];

    for (let i = 0; i < pixelLength; i++) {

        // RenderedPixel:
        // Pixel = int x, int y
        // int isInFrontOfCamera

        const p = (pixelDataPtr >> 2) + i * 3;

        pixels.push({
            x: heap32[p],
            y: heap32[p + 1],
            inFront: heap32[p + 2]
        });
    }



    // lines array
    const lineDataPtr = heap32[linesPtr];
    const lineLength = heap32[linesPtr + 1];


    let lines = [];

    for (let i = 0; i < lineLength; i++) {

        // RenderedLine:
        // startPixel x,y
        // endPixel x,y

        const l = (lineDataPtr >> 2) + i * 4;

        lines.push({
            start: {
                x: heap32[l],
                y: heap32[l + 1]
            },

            end: {
                x: heap32[l + 2],
                y: heap32[l + 3]
            }
        });
    }


    return {
        pixels: pixels,
        lines: lines
    };
}


// (PARTIALLY AI)
function draw() {

    CONTEXT.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

    const result = getRenderResult();


    for (let i = 0; i < result.pixels.length; i++) {

        const pixel = result.pixels[i];

        draw_square(
            pixel.x,
            pixel.y,
            10
        );
    }


    for (let i = 0; i < result.lines.length; i++) {

        const line = result.lines[i];

        draw_line(
            [line.start.x, line.start.y],
            [line.end.x, line.end.y]
        );
    }
}

function initialize_data() {
  // for now runs internal initialize test data. 
  // later will have preconfig points, etc

    Module._initialize();
    // Module._renderScene();

    // start drawing loop
    // draw();
}




const FPS = 60; 
const TRANSLATION_SPEED = 2; // world units/s (i think)
const ROTATION_SPEED = 2 // rad/s (i think)

const W = 0;
const A = 1;
const S = 2;
const D = 3;
const SHIFT = 4;
const SPACE = 5;
const UP = 6;
const DOWN = 7;
const LEFT = 8;
const RIGHT = 9;
let KEYS_PRESSED = [false, false, false, false, // W A S D 
                    false, false,               // SHIFT SPACE
                    false, false, false, false] // UP DOWN LEFT RIGHT

// yeah culd do 0 0 0 0 whatever

let lastTime;

function updateCamera(dt) {
    
    // note2self: adding means itll cancel

    // forward/back
    let z = 0;
    if (KEYS_PRESSED[W]) {
      z += 1;
    }
    if (KEYS_PRESSED[S]) {
      z -= 1;
    }

    // left/right
    let x = 0;
    if (KEYS_PRESSED[A]) {
      x -= 1;
    }
    if (KEYS_PRESSED[D]) {
      x += 1;
    }

    // up down
    let y = 0;
    if (KEYS_PRESSED[SHIFT]) {
      y -= 1;
    }
    if (KEYS_PRESSED[SPACE]) {
      y += 1;
    }

    // pitch
    // for some reason is up +=1 then goes down
    let pitch = 0
    if (KEYS_PRESSED[UP]) {
      pitch -= 1;
    }
    if (KEYS_PRESSED[DOWN]) {
      pitch += 1;
    }

    // yaw
    let yaw = 0;
    if (KEYS_PRESSED[LEFT]) {
      yaw -=1;
    }
    if (KEYS_PRESSED[RIGHT]) {
      yaw += 1;
    }

    // roll here but we "forget about it"
    let roll = 0;

    Module._transformCamera(
        x * TRANSLATION_SPEED * dt,
        y * TRANSLATION_SPEED * dt,
        z * TRANSLATION_SPEED * dt,
        pitch * ROTATION_SPEED * dt,
        yaw * ROTATION_SPEED * dt,
        roll * ROTATION_SPEED * dt
    );

}


function simulationLoop() {

    // manage time
    let now = performance.now();
    let dt = (now - lastTime) / 1000;
    lastTime = now;

    // apply transformations to cam
    updateCamera(dt);

    // update render var in c
    Module._renderScene();

    // draw (by reading then drawing)
    // TODO separate getRender and draw
    draw();

    // 
    setTimeout(simulationLoop, (1/FPS)*1000);
}


function initialize_key_listeners() {
  
  document.addEventListener("keydown", (event) => {
    switch(event.key.toLowerCase()) {
      case 'w': 
        KEYS_PRESSED[W] = true;
        break;
      case 'a':
        KEYS_PRESSED[A] = true;
        break;
      case 's':
        KEYS_PRESSED[S] = true;
        break;
      case 'd':
        KEYS_PRESSED[D] = true;
        break;
      case 'shift':
        KEYS_PRESSED[SHIFT] = true;
        break;
      case ' ':
        KEYS_PRESSED[SPACE] = true;
        break;
    }
  });

  document.addEventListener("keydown", (event) => {
    switch(event.key) {
      case "ArrowDown":
        KEYS_PRESSED[DOWN] = true;
        break;
      case "ArrowUp":
        KEYS_PRESSED[UP] = true;
        break;
      case "ArrowLeft":
        KEYS_PRESSED[LEFT] = true;
        break;
      case "ArrowRight":
        KEYS_PRESSED[RIGHT] = true;
        break;  
    }
  });

  document.addEventListener("keyup", (event) => {
    switch(event.key.toLowerCase()) {
      case 'w':
        KEYS_PRESSED[W] = false;
        break;
      case 'a':
        KEYS_PRESSED[A] = false;
        break;
      case 's':
        KEYS_PRESSED[S] = false;
        break;
      case 'd':
        KEYS_PRESSED[D] = false;
        break;
      case 'shift':
        KEYS_PRESSED[SHIFT] = false;
        break;
      case ' ':
        KEYS_PRESSED[SPACE] = false;
        break;
    }
  });

   document.addEventListener("keyup", (event) => {
    switch(event.key) {
      case "ArrowDown":
        KEYS_PRESSED[DOWN] = false;
        break;
      case "ArrowUp":
        KEYS_PRESSED[UP] = false;
        break;
      case "ArrowLeft":
        KEYS_PRESSED[LEFT] = false;
        break;
      case "ArrowRight":
        KEYS_PRESSED[RIGHT] = false;
        break;  
    }
  });
}

function main() {
  // frontend setup
	initialize_canvas();
  initialize_data();
  initialize_key_listeners();

  // starting simulation loop
  lastTime = performance.now();
  simulationLoop();
  
}



// neat and organized! tada!
Module.onRuntimeInitialized = () => {
  main();

  
};
