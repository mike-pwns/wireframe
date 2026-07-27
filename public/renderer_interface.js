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


// (AI-GENERATED)
function getProjectedVertices() {

    const ptr = Module._getProjectedVertices();

    const heap32 = Module.HEAP32;

    // DynamicPixelArray struct:
    // Pixel* data
    // int numElements
    // int capacity

    const base = ptr >> 2;

    const dataPtr = heap32[base];
    const length = heap32[base + 1];

    let pixels = [];

    for (let i = 0; i < length; i++) {

        // Pixel:
        // int x
        // int y

        const pixelAddress = (dataPtr >> 2) + i * 2;

        pixels.push({
            x: heap32[pixelAddress],
            y: heap32[pixelAddress + 1]
        });
    }

    return pixels;
}

// (AI-GENERATED)
function getEdges() {

    const ptr = Module._getEdges();

    const heap32 = Module.HEAP32;

    // DynamicEdge3Array struct:
    // Edge3* data
    // int numElements
    // int capacity

    const base = ptr >> 2;

    const dataPtr = heap32[base];
    const length = heap32[base + 1];

    let edges = [];

    for (let i = 0; i < length; i++) {

        // Edge3:
        // int startIndex
        // int endIndex

        const edgeAddress = (dataPtr >> 2) + i * 2;

        edges.push({
            start: heap32[edgeAddress],
            end: heap32[edgeAddress + 1]
        });
    }

    return edges;
}


// (PARTIALLY AI)
function draw() {

    CONTEXT.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

    const vertices = getProjectedVertices();
    const edges = getEdges();


    // draw vertices
    for (let i = 0; i < vertices.length; i++) {
        draw_square(
            vertices[i].x,
            vertices[i].y,
            10
        );
    }


    // draw edges
    for (let i = 0; i < edges.length; i++) {

        const edge = edges[i];

        const start = vertices[edge.start];
        const end = vertices[edge.end];

        draw_line(
            [start.x, start.y],
            [end.x, end.y]
        );
    }
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
