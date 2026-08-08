/*
████████████████████████████████████████████████████████████████████████████████████████
███  THE FINAL VERSION OF THIS FILE WAS ALMOST ENTIRELY WRITTEN BY AI (CLAUDE; ~85%) ███
████████████████████████████████████████████████████████████████████████████████████████
*/

const X = 0;
const Y = 1;

const MODEL_CUBE = 0;
const MODEL_PYRAMID = 1;
const MODEL_SPHERE = 2;
const MODEL_OCTAHEDRON = 3;
const MODEL_TORUS = 4;
const MODEL_SYNTHSCAPE = 5;
const MODEL_PENGUIN = 6;
const MODEL_CUSTOM = 7;

const HACKER_GREEN = "#20C20E";
let STROKE_WIDTH = 10;

const CANVAS = document.getElementById("canvas");
const CONTEXT = CANVAS.getContext("2d");
const CANVAS_WIDTH = 1024;
const CANVAS_HEIGHT = 1024;

let FPS = 60;
let TRANSLATION_SPEED = 2;
let ROTATION_SPEED = 2;

let isFullscreen = false;
let fullscreenOriginalParent = null;
let fullscreenOriginalNextSibling = null;

const W = 0; const A = 1; const S = 2; const D = 3; const SHIFT = 4; const SPACE = 5;
const UP = 6; const DOWN = 7; const LEFT = 8; const RIGHT = 9;

let KEYS_PRESSED = [false, false, false, false,
                    false, false,
                    false, false, false, false];

const CAPTURED_KEYS = new Set([
    "w", "a", "s", "d", "shift", " ",
    "arrowup", "arrowdown", "arrowleft", "arrowright"
]);

let lastTime;

const READOUT_POS_X = document.getElementById("readoutPosX");
const READOUT_POS_Y = document.getElementById("readoutPosY");
const READOUT_POS_Z = document.getElementById("readoutPosZ");
const READOUT_PITCH = document.getElementById("readoutPitch");
const READOUT_YAW = document.getElementById("readoutYaw");

function getCameraTransform() {
    const ptr = Module._getCameraTransform();
    const base = ptr >> 2;
    return {
        x: Module.HEAPF32[base],
        y: Module.HEAPF32[base + 1],
        z: Module.HEAPF32[base + 2],
        pitch: Module.HEAPF32[base + 3],
        yaw: Module.HEAPF32[base + 4],
        roll: Module.HEAPF32[base + 5]
    };
}

function updateCameraReadout() {
    const cam = getCameraTransform();
    if (READOUT_POS_X) READOUT_POS_X.textContent = `X ${cam.x.toFixed(1)}`;
    if (READOUT_POS_Y) READOUT_POS_Y.textContent = `Y ${cam.y.toFixed(1)}`;
    if (READOUT_POS_Z) READOUT_POS_Z.textContent = `Z ${cam.z.toFixed(1)}`;
    const pitchDeg = Math.round(cam.pitch * (180 / Math.PI));
    const yawDeg = Math.round(cam.yaw * (180 / Math.PI));
    if (READOUT_PITCH) READOUT_PITCH.textContent = `PITCH ${pitchDeg}\u00B0`;
    if (READOUT_YAW) READOUT_YAW.textContent = `YAW ${yawDeg}\u00B0`;
}

function initialize_canvas() {
    CANVAS.width = CANVAS_WIDTH;
    CANVAS.height = CANVAS_HEIGHT;
    CONTEXT.strokeStyle = HACKER_GREEN;
    CONTEXT.fillStyle = HACKER_GREEN;
    CONTEXT.lineWidth = STROKE_WIDTH;
    CANVAS_MATHEMATICAL_ORIGIN = [CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2];
}

function draw_line(start, end) {
    CONTEXT.beginPath();
    CONTEXT.moveTo(start[X], start[Y]);
    CONTEXT.lineTo(end[X], end[Y]);
    CONTEXT.stroke();
}

function draw_circle(x, y, radius) {
    CONTEXT.beginPath();
    CONTEXT.arc(x, y, radius, 0, Math.PI * 2);
    CONTEXT.fill();
}

function draw_square(x, y, side_len) {
    let actX = (x - side_len / 2);
    let actY = (y - side_len / 2);
    CONTEXT.beginPath();
    CONTEXT.fillRect(actX, actY, side_len, side_len);
}

function getRenderResult() {
    const ptr = Module._getRenderResult();
    const heap32 = Module.HEAP32;
    const base = ptr >> 2;

    const pixelsPtr = base;
    const linesPtr = base + 3;

    const pixelDataPtr = heap32[pixelsPtr];
    const pixelLength = heap32[pixelsPtr + 1];

    let pixels = [];
    for (let i = 0; i < pixelLength; i++) {
        const p = (pixelDataPtr >> 2) + i * 3;
        pixels.push({ x: heap32[p], y: heap32[p + 1], inFront: heap32[p + 2] });
    }

    const lineDataPtr = heap32[linesPtr];
    const lineLength = heap32[linesPtr + 1];

    let lines = [];
    for (let i = 0; i < lineLength; i++) {
        const l = (lineDataPtr >> 2) + i * 4;
        lines.push({
            start: { x: heap32[l], y: heap32[l + 1] },
            end: { x: heap32[l + 2], y: heap32[l + 3] }
        });
    }

    return { pixels: pixels, lines: lines };
}

function draw() {
    CONTEXT.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
    const result = getRenderResult();

    for (let i = 0; i < result.pixels.length; i++) {
        const pixel = result.pixels[i];
        draw_square(pixel.x, pixel.y, 10);
    }

    for (let i = 0; i < result.lines.length; i++) {
        const line = result.lines[i];
        draw_line([line.start.x, line.start.y], [line.end.x, line.end.y]);
    }
}

function initialize_data() {
    Module._initialize();
}

function switchModel(modelId, buttonEl) {
    customPoints = [];
    customEdges = [];

    Module._switchModel(modelId);

    document.querySelectorAll(".gallery__item").forEach((btn) => {
        btn.classList.remove("is-active");
    });

    if (buttonEl) {
        buttonEl.classList.add("is-active");
    }

    renderPointList();
    renderEdgeOptions();
    renderEdgeList();

    const panel = document.getElementById("customPanel");
    if (panel) {
        panel.classList.toggle("is-unlocked", modelId === MODEL_CUSTOM);
    }
}

function initialize_gallery() {
    const buttons = document.querySelectorAll(".gallery__item");
    buttons.forEach((btn) => {
        btn.addEventListener("click", () => {
            const modelId = parseInt(btn.dataset.modelId, 10);
            switchModel(modelId, btn);
        });
    });
}


function toggleFullscreen() {
    const frame = document.getElementById("viewportFrame");
    const overlay = document.getElementById("fullscreenOverlay");
    const toggleBtn = document.getElementById("fullscreenToggle");

    if (!isFullscreen) {
        fullscreenOriginalParent = frame.parentElement;
        fullscreenOriginalNextSibling = frame.nextElementSibling;

        overlay.appendChild(frame);
        overlay.classList.add("is-active");

        if (toggleBtn) toggleBtn.textContent = "[ exit ]";
        isFullscreen = true;
    } else {
        if (fullscreenOriginalNextSibling) {
            fullscreenOriginalParent.insertBefore(frame, fullscreenOriginalNextSibling);
        } else {
            fullscreenOriginalParent.appendChild(frame);
        }

        overlay.classList.remove("is-active");

        if (toggleBtn) toggleBtn.textContent = "[ fullscreen ]";
        isFullscreen = false;
    }
}

function initialize_fullscreen() {
    const toggleBtn = document.getElementById("fullscreenToggle");
    if (toggleBtn) {
        toggleBtn.addEventListener("click", toggleFullscreen);
    }

    document.addEventListener("keydown", (event) => {
        if (event.key === "Escape" && isFullscreen) {
            toggleFullscreen();
        }
    });
}

function updateCamera(dt) {
    let z = 0;
    if (KEYS_PRESSED[W]) z += 1;
    if (KEYS_PRESSED[S]) z -= 1;

    let x = 0;
    if (KEYS_PRESSED[A]) x -= 1;
    if (KEYS_PRESSED[D]) x += 1;

    let y = 0;
    if (KEYS_PRESSED[SHIFT]) y -= 1;
    if (KEYS_PRESSED[SPACE]) y += 1;

    let pitch = 0;
    if (KEYS_PRESSED[UP]) pitch -= 1;
    if (KEYS_PRESSED[DOWN]) pitch += 1;

    let yaw = 0;
    if (KEYS_PRESSED[LEFT]) yaw -= 1;
    if (KEYS_PRESSED[RIGHT]) yaw += 1;

    let roll = 0;

    const dx = x * TRANSLATION_SPEED * dt;
    const dy = y * TRANSLATION_SPEED * dt;
    const dz = z * TRANSLATION_SPEED * dt;
    const dPitch = pitch * ROTATION_SPEED * dt;
    const dYaw = yaw * ROTATION_SPEED * dt;
    const dRoll = roll * ROTATION_SPEED * dt;

    Module._transformCamera(dx, dy, dz, dPitch, dYaw, dRoll);
}

function simulationLoop() {
    let now = performance.now();
    let dt = (now - lastTime) / 1000;
    lastTime = now;

    updateCamera(dt);
    Module._renderScene();
    draw();
    updateCameraReadout();

    setTimeout(simulationLoop, (1 / FPS) * 1000);
}

let customPoints = [];
let customEdges = [];

function rebuildCustomModel() {
    Module._clearCustomModel();

    for (let i = 0; i < customPoints.length; i++) {
        const p = customPoints[i];
        Module._addCustomVertex(p.x, p.y, p.z);
    }

    for (let i = 0; i < customEdges.length; i++) {
        const e = customEdges[i];
        Module._connectCustomVertices(e.a, e.b);
    }

    document.querySelectorAll(".gallery__item").forEach((btn) => {
        btn.classList.remove("is-active");
    });
    const customBtn = document.querySelector('.gallery__item[data-model-id="7"]');
    if (customBtn) customBtn.classList.add("is-active");
}

function addCustomPoint() {
    const xInput = document.getElementById("newPointX");
    const yInput = document.getElementById("newPointY");
    const zInput = document.getElementById("newPointZ");

    const x = parseFloat(xInput.value) || 0;
    const y = parseFloat(yInput.value) || 0;
    const z = parseFloat(zInput.value) || 0;

    customPoints.push({ x, y, z });
    rebuildCustomModel();
    renderPointList();
    renderEdgeOptions();

    xInput.value = 0;
    yInput.value = 0;
    zInput.value = 0;
}

function deleteCustomPoint(index) {
    customPoints.splice(index, 1);

    customEdges = customEdges
        .filter((e) => e.a !== index && e.b !== index)
        .map((e) => ({
            a: e.a > index ? e.a - 1 : e.a,
            b: e.b > index ? e.b - 1 : e.b
        }));

    rebuildCustomModel();
    renderPointList();
    renderEdgeOptions();
    renderEdgeList();
}

function updateCustomPointCoord(index, axis, value) {
    customPoints[index][axis] = parseFloat(value) || 0;
    rebuildCustomModel();
}

function addCustomEdge(startIndex, endIndex) {
    if (isNaN(startIndex) || isNaN(endIndex) || startIndex === endIndex) {
        return;
    }

    const alreadyExists = customEdges.some(
        (e) => (e.a === startIndex && e.b === endIndex) || (e.a === endIndex && e.b === startIndex)
    );
    if (alreadyExists) return;

    customEdges.push({ a: startIndex, b: endIndex });
    rebuildCustomModel();
    renderEdgeList();
}

function deleteCustomEdge(index) {
    customEdges.splice(index, 1);
    rebuildCustomModel();
    renderEdgeList();
}

function renderPointList() {
    const list = document.getElementById("pointList");
    list.innerHTML = "";

    if (customPoints.length === 0) {
        list.innerHTML = `<p class="builder__empty">no points yet - add one to start.</p>`;
        return;
    }

    customPoints.forEach((p, i) => {
        const row = document.createElement("div");
        row.className = "builder__row";

        row.innerHTML = `
            <span class="builder__row-label">P${i}</span>
            <input type="number" class="builder__coord" step="0.1" value="${p.x}" data-axis="x" aria-label="P${i} x coordinate">
            <input type="number" class="builder__coord" step="0.1" value="${p.y}" data-axis="y" aria-label="P${i} y coordinate">
            <input type="number" class="builder__coord" step="0.1" value="${p.z}" data-axis="z" aria-label="P${i} z coordinate">
            <button class="builder__delete" aria-label="Delete P${i}">&times;</button>
        `;

        row.querySelectorAll(".builder__coord").forEach((input) => {
            input.addEventListener("change", (event) => {
                updateCustomPointCoord(i, event.target.dataset.axis, event.target.value);
            });
        });

        row.querySelector(".builder__delete").addEventListener("click", () => {
            deleteCustomPoint(i);
        });

        list.appendChild(row);
    });
}

function renderEdgeOptions() {
    const startSelect = document.getElementById("edgeStartSelect");
    const endSelect = document.getElementById("edgeEndSelect");

    [startSelect, endSelect].forEach((select) => {
        select.innerHTML = "";
        customPoints.forEach((p, i) => {
            const opt = document.createElement("option");
            opt.value = i;
            opt.textContent = `P${i}`;
            select.appendChild(opt);
        });
    });

    if (endSelect.options.length > 1) {
        endSelect.selectedIndex = 1;
    }
}

function renderEdgeList() {
    const list = document.getElementById("edgeList");
    list.innerHTML = "";

    if (customEdges.length === 0) {
        list.innerHTML = `<p class="builder__empty">no edges yet.</p>`;
        return;
    }

    customEdges.forEach((e, i) => {
        const row = document.createElement("div");
        row.className = "builder__row";

        row.innerHTML = `
            <span class="builder__row-label">P${e.a} &rarr; P${e.b}</span>
            <button class="builder__delete" aria-label="Delete edge P${e.a} to P${e.b}">&times;</button>
        `;

        row.querySelector(".builder__delete").addEventListener("click", () => {
            deleteCustomEdge(i);
        });

        list.appendChild(row);
    });
}

function initialize_builder() {
    const addPointBtn = document.getElementById("addPointBtn");
    const connectBtn = document.getElementById("connectBtn");

    if (addPointBtn) {
        addPointBtn.addEventListener("click", addCustomPoint);
    }

    if (connectBtn) {
        connectBtn.addEventListener("click", () => {
            const startIndex = parseInt(document.getElementById("edgeStartSelect").value, 10);
            const endIndex = parseInt(document.getElementById("edgeEndSelect").value, 10);
            addCustomEdge(startIndex, endIndex);
        });
    }

    renderPointList();
    renderEdgeOptions();
    renderEdgeList();
}

function initialize_key_listeners() {
    document.addEventListener("keydown", (event) => {
        if (CAPTURED_KEYS.has(event.key.toLowerCase())) {
            event.preventDefault();
        }

        switch (event.key.toLowerCase()) {
            case 'w': KEYS_PRESSED[W] = true; break;
            case 'a': KEYS_PRESSED[A] = true; break;
            case 's': KEYS_PRESSED[S] = true; break;
            case 'd': KEYS_PRESSED[D] = true; break;
            case 'shift': KEYS_PRESSED[SHIFT] = true; break;
            case ' ': KEYS_PRESSED[SPACE] = true; break;
        }
    });

    document.addEventListener("keydown", (event) => {
        switch (event.key) {
            case "ArrowDown": KEYS_PRESSED[DOWN] = true; break;
            case "ArrowUp": KEYS_PRESSED[UP] = true; break;
            case "ArrowLeft": KEYS_PRESSED[LEFT] = true; break;
            case "ArrowRight": KEYS_PRESSED[RIGHT] = true; break;
        }
    });

    document.addEventListener("keyup", (event) => {
        switch (event.key.toLowerCase()) {
            case 'w': KEYS_PRESSED[W] = false; break;
            case 'a': KEYS_PRESSED[A] = false; break;
            case 's': KEYS_PRESSED[S] = false; break;
            case 'd': KEYS_PRESSED[D] = false; break;
            case 'shift': KEYS_PRESSED[SHIFT] = false; break;
            case ' ': KEYS_PRESSED[SPACE] = false; break;
        }
    });

    document.addEventListener("keyup", (event) => {
        switch (event.key) {
            case "ArrowDown": KEYS_PRESSED[DOWN] = false; break;
            case "ArrowUp": KEYS_PRESSED[UP] = false; break;
            case "ArrowLeft": KEYS_PRESSED[LEFT] = false; break;
            case "ArrowRight": KEYS_PRESSED[RIGHT] = false; break;
        }
    });
}

function main() {
    initialize_canvas();
    initialize_data();
    initialize_key_listeners();
    initialize_gallery();
    initialize_fullscreen();
    initialize_builder();

    lastTime = performance.now();
    simulationLoop();
}

Module.onRuntimeInitialized = () => {
    main();
};
