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


// (AI GEN)
function getPixels() {

    const ptr = Module._getPixels();
    const heap = Module.HEAP32;

    const base = ptr >> 2;

    const dataPtr = heap[base];
    const length  = heap[base + 1];
    const capacity = heap[base + 2];

    let pixels = [];

    for (let i = 0; i < length; i++) {

        const p = (dataPtr >> 2) + i * 2;

        pixels.push([
        heap[p],
        heap[p + 1]
        ]);
    }

    return pixels;
}


function draw() {

  // wipe black
  CONTEXT.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

  const pixels = getPixels();

  // draw square at each pixel
  for (let i = 0; i < pixels.length; i++) {
    px = pixels[i];
    draw_square(px[X], px[Y], 50);
  }

  // (connect lines)
}


function initialize_data() {
  // for now runs internal initialize test data. 
  // later will have preconfig points, etc

    Module._initialize();
    Module._renderScene();

    // start drawing loop
    draw();
}



// (AI GEN)
function getPoints() {

    const ptr = Module._getPoints();

    const heap32 = Module.HEAP32;
    const heapF32 = Module.HEAPF32;


    // struct location
    const base = ptr >> 2;


    // DynamicPt3Array fields
    const dataPtr = heap32[base];
    const length = heap32[base + 1];


    let points = [];


    for (let i = 0; i < length; i++) {

        // Pt3 = float x, float y, float z
        // 3 floats per point

        const p = (dataPtr >> 2) + i * 3;


        points.push({
            x: heapF32[p],
            y: heapF32[p + 1],
            z: heapF32[p + 2]
        });
    }


    return points;
}

// UI METHOD (ai-gen)
function refreshPointList() {

    const list = document.getElementById("point-list");

    list.innerHTML = "";

    const points = getPoints();


    for (let i = 0; i < points.length; i++) {

        const row = document.createElement("div");
        row.className = "point";


        const text = document.createElement("span");

        text.textContent =
            `[${String(i).padStart(3, "0")}] `
            + `(${points[i].x}, ${points[i].y}, ${points[i].z})`;


        const button = document.createElement("button");

        button.textContent = "DEL";


        button.onclick = () => {

            Module._removePoint(i);

            Module._renderScene();

            draw();

            refreshPointList();
        };


        row.appendChild(text);
        row.appendChild(button);

        list.appendChild(row);
    }
}




// C APIs


function onAddClicked() {

    const x = Number(document.getElementById("x-input").value);
    const y = Number(document.getElementById("y-input").value);
    const z = Number(document.getElementById("z-input").value);

    Module._addPoint(x, y, z);

    Module._renderScene();
    draw();
    refreshPointList();
}












// yes i am doing this in js sue me
function main() {
  // frontend setup
	initialize_canvas();


  // backend setup

  initialize_data();
  draw();

  // draw_line();	
}


// neat and organized! tada!
Module.onRuntimeInitialized = () => {
  main();
};
