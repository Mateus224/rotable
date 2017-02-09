/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCanvas3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0]
Qt.include("gl-matrix.js")
//! [0]

//
// Draws a cube that has the Qt logo as decal texture on each face.
// A simple per vertex lighting equation is used to emulate light landing on the rotating cube.
//

var gl;
var cubeTexture = 0;
var vertexPositionAttribute;
var textureCoordAttribute;
var vertexNormalAttribute;
var mvMatrix = mat4.create();
var pMatrix  = mat4.create();
var nMatrix  = mat4.create();
var pMatrixUniform;
var mvMatrixUniform;
var nUniform;
var width = 0;
var height = 0;
var canvas3d;
var pixelSize;

// cube properties after mouse drag
var pozX = 0;
var pozY = 0;
var diffX = 0;
var diffY = 0;

function initializeGL(canvas) {
    canvas3d = canvas;
    //! [1]
    // Get the OpenGL context object that represents the API we call
    gl = canvas.getContext("canvas3d", {depth:true, antialias:true, alpha:false});
    //! [1]

    //! [2]
    // Setup the OpenGL state
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LESS);
    gl.enable(gl.CULL_FACE);
    gl.cullFace(gl.BACK);
    gl.clearColor(0.98, 0.98, 0.98, 1.0);
    gl.clearDepth(1.0);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, false);
    //! [2]

    // Set viewport
    gl.viewport(0, 0, canvas.width, canvas.height);

    // Initialize the shader program
    initShaders();

    // Initialize vertex and color buffers
    initBuffers();

    // Load the textures
    var qtLogoImage = TextureImageFactory.newTexImage();
    //! [8]
    qtLogoImage.imageLoaded.connect(function() {
        console.log("Texture loaded, "+qtLogoImage.src);
        // Create the Canvas3DTexture object
        cubeTexture = gl.createTexture();
        // Bind it
        gl.bindTexture(gl.TEXTURE_2D, cubeTexture);
        // Set the properties
        gl.texImage2D(gl.TEXTURE_2D,    // target
                      0,                // level
                      gl.RGBA,          // internalformat
                      gl.RGBA,          // format
                      gl.UNSIGNED_BYTE, // type
                      qtLogoImage);     // pixels
        // Set texture filtering parameters
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
        // Generate mipmap
        gl.generateMipmap(gl.TEXTURE_2D);
    });
    //! [8]
    qtLogoImage.imageLoadingFailed.connect(function() {
        console.log("Texture load FAILED, "+qtLogoImage.errorString);
    });
    qtLogoImage.src = "qrc:/client/games/Cubes/qtlogo.png";
}

function resizeGL(canvas)
{
    var pixelRatio = canvas.devicePixelRatio;
    canvas.pixelSize = Qt.size(canvas.width * pixelRatio,
                               canvas.height * pixelRatio);
}

function degToRad(degrees) {
    return degrees * Math.PI / 180;
}

// Gathering information about cursor position
function cubePressed(event){
    pozX = event.x;
    pozY = event.y;
}

// Counting length of mouse drag, and transforming it into final position of rotation animation
function cubeReleased(event){
    diffX = event.x - pozX;
    diffX = Math.round(diffX / 100);
    diffY = pozY - event.y;
    diffY = Math.round(diffY / 100);
    console.log("diffX " + diffX);
    console.log("diffY " + diffY);
    objAnimationX.to = 360 * diffX;  // multiply by 360 to always stop dice flat on its side - not at some angle, same reason for rounding diffX & diffY
    objAnimationX.running = true;
    objAnimationX.running = false;
    objAnimationY.to = 360 * diffY;
    objAnimationY.running = true;
    objAnimationY.running = false;
}

function paintGL(canvas) {
    //! [9]
    var pixelRatio = canvas.devicePixelRatio;
    var currentWidth = canvas.width * pixelRatio;
    var currentHeight = canvas.height * pixelRatio;
    if (currentWidth !== width || currentHeight !== height ) {
        width = currentWidth;
        height = currentHeight;
        gl.viewport(0, 0, width, height);
        mat4.ortho(pMatrix, -40, 40, -40, 40, 0.1, 100.0);
    //    mat4.perspective(pMatrix, degToRad(145), width / height, 0.1, 500.0);
        gl.uniformMatrix4fv(pMatrixUniform, false, pMatrix);
    }
    //! [9]

    //! [10]
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    //! [10]

    //! [11]
    mat4.identity(mvMatrix);
    mat4.translate(mvMatrix, mvMatrix, [(canvas.xRotAnim -  60.0) / 50.0,
                                        (canvas.yRotAnim -  60.0) / 50.0,
                                        -10.0]);
    mat4.rotate(mvMatrix, mvMatrix, degToRad(canvas.xRotAnim), [0, 1, 0]);
    mat4.rotate(mvMatrix, mvMatrix, degToRad(-canvas.yRotAnim), [1, 0, 0]);
    mat4.rotate(mvMatrix, mvMatrix, degToRad(canvas.zRotAnim), [0, 0, 1]);
    gl.uniformMatrix4fv(mvMatrixUniform, false, mvMatrix);
    //! [11]

    //! [12]
    mat4.invert(nMatrix, mvMatrix);
    mat4.transpose(nMatrix, nMatrix);
    gl.uniformMatrix4fv(nUniform, false, nMatrix);
    //! [12]

    //! [13]
    gl.drawElements(gl.TRIANGLES, 36, gl.UNSIGNED_SHORT, 0);
    //! [13]
}

function initBuffers()
{
    var cubeVertexPositionBuffer = gl.createBuffer();
    cubeVertexPositionBuffer.name = "cubeVertexPositionBuffer";
    gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
    gl.bufferData(
                gl.ARRAY_BUFFER,
                new Float32Array([// Front face
                                        -1.0, -1.0,  1.0,
                                        1.0, -1.0,  1.0,
                                        1.0,  1.0,  1.0,
                                        -1.0,  1.0,  1.0,

                                        // Back face
                                        -1.0, -1.0, -1.0,
                                        -1.0,  1.0, -1.0,
                                        1.0,  1.0, -1.0,
                                        1.0, -1.0, -1.0,

                                        // Top face
                                        -1.0,  1.0, -1.0,
                                        -1.0,  1.0,  1.0,
                                        1.0,  1.0,  1.0,
                                        1.0,  1.0, -1.0,

                                        // Bottom face
                                        -1.0, -1.0, -1.0,
                                        1.0, -1.0, -1.0,
                                        1.0, -1.0,  1.0,
                                        -1.0, -1.0,  1.0,

                                        // Right face
                                        1.0, -1.0, -1.0,
                                        1.0,  1.0, -1.0,
                                        1.0,  1.0,  1.0,
                                        1.0, -1.0,  1.0,

                                        // Left face
                                        -1.0, -1.0, -1.0,
                                        -1.0, -1.0,  1.0,
                                        -1.0,  1.0,  1.0,
                                        -1.0,  1.0, -1.0
                                       ]),
                gl.STATIC_DRAW);
    gl.vertexAttribPointer(vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

    //! [7]
    var cubeVertexIndexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER,
                  new Uint16Array([
                                            0,  1,  2,      0,  2,  3,    // front
                                            4,  5,  6,      4,  6,  7,    // back
                                            8,  9,  10,     8,  10, 11,   // top
                                            12, 13, 14,     12, 14, 15,   // bottom
                                            16, 17, 18,     16, 18, 19,   // right
                                            20, 21, 22,     20, 22, 23    // left
                                        ]),
                  gl.STATIC_DRAW);
    //! [7]

    var cubeVerticesTextureCoordBuffer = gl.createBuffer();
    cubeVerticesTextureCoordBuffer.name = "cubeVerticesTextureCoordBuffer";
    gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesTextureCoordBuffer);
    var textureCoordinates = [
                // Front
                1.0,  0.0,
                0.0,  0.0,
                0.0,  1.0,
                1.0,  1.0,
                // Back
                1.0,  0.0,
                0.0,  0.0,
                0.0,  1.0,
                1.0,  1.0,
                // Top
                1.0,  0.0,
                0.0,  0.0,
                0.0,  1.0,
                1.0,  1.0,
                // Bottom
                1.0,  0.0,
                0.0,  0.0,
                0.0,  1.0,
                1.0,  1.0,
                // Right
                1.0,  0.0,
                0.0,  0.0,
                0.0,  1.0,
                1.0,  1.0,
                // Left
                1.0,  0.0,
                0.0,  0.0,
                0.0,  1.0,
                1.0,  1.0
            ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates),
                  gl.STATIC_DRAW);
    gl.vertexAttribPointer(textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);


    var cubeVerticesNormalBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesNormalBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array([
                                                              // Front
                                                              0.0,  0.0,  1.0,
                                                              0.0,  0.0,  1.0,
                                                              0.0,  0.0,  1.0,
                                                              0.0,  0.0,  1.0,

                                                              // Back
                                                              0.0,  0.0, -1.0,
                                                              0.0,  0.0, -1.0,
                                                              0.0,  0.0, -1.0,
                                                              0.0,  0.0, -1.0,

                                                              // Top
                                                              0.0,  1.0,  0.0,
                                                              0.0,  1.0,  0.0,
                                                              0.0,  1.0,  0.0,
                                                              0.0,  1.0,  0.0,

                                                              // Bottom
                                                              0.0, -1.0,  0.0,
                                                              0.0, -1.0,  0.0,
                                                              0.0, -1.0,  0.0,
                                                              0.0, -1.0,  0.0,

                                                              // Right
                                                              1.0,  0.0,  0.0,
                                                              1.0,  0.0,  0.0,
                                                              1.0,  0.0,  0.0,
                                                              1.0,  0.0,  0.0,

                                                              // Left
                                                              -1.0,  0.0,  0.0,
                                                              -1.0,  0.0,  0.0,
                                                              -1.0,  0.0,  0.0,
                                                              -1.0,  0.0,  0.0
                                                          ]), gl.STATIC_DRAW);
    gl.vertexAttribPointer(vertexNormalAttribute, 3, gl.FLOAT, false, 0, 0);
}

function initShaders()
{
    //! [3]
    var vertexShader = getShader(gl,
                                 "attribute highp vec3 aVertexNormal;    \
                                  attribute highp vec3 aVertexPosition;  \
                                  attribute highp vec2 aTextureCoord;    \
                                                                         \
                                  uniform highp mat4 uNormalMatrix;      \
                                  uniform mat4 uMVMatrix;                \
                                  uniform mat4 uPMatrix;                 \
                                                                         \
                                  varying mediump vec4 vColor;           \
                                  varying highp vec2 vTextureCoord;      \
                                  varying highp vec3 vLighting;          \
                                                                         \
                                  void main(void) {                      \
                                      gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0); \
                                      vTextureCoord = aTextureCoord;                                   \
                                      highp vec3 ambientLight = vec3(0.5, 0.5, 0.5);                   \
                                      highp vec3 directionalLightColor = vec3(0.75, 0.75, 0.75);       \
                                      highp vec3 directionalVector = vec3(0.85, 0.8, 0.75);            \
                                      highp vec4 transformedNormal = uNormalMatrix * vec4(aVertexNormal, 1.0); \
                                      highp float directional = max(dot(transformedNormal.xyz, directionalVector), 0.0); \
                                      vLighting = ambientLight + (directionalLightColor * directional); \
                                  }", gl.VERTEX_SHADER);
    //! [3]
    //! [4]
    var fragmentShader = getShader(gl,
                                   "varying highp vec2 vTextureCoord;  \
                                    varying highp vec3 vLighting;      \
                                                                       \
                                    uniform sampler2D uSampler;        \
                                                                       \
                                    void main(void) {                  \
                                        mediump vec3 texelColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t)).rgb; \
                                        gl_FragColor = vec4(texelColor * vLighting, 1.0);                                      \
                                    }", gl.FRAGMENT_SHADER);
    //! [4]
    //! [5]
    // Create the Canvas3DProgram for shader
    var shaderProgram = gl.createProgram();

    // Attach the shader sources to the shader program
    gl.attachShader(shaderProgram, vertexShader);
    gl.attachShader(shaderProgram, fragmentShader);

    // Link the program
    gl.linkProgram(shaderProgram);

    // Check the linking status
    if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
        console.log("Could not initialise shaders");
        console.log(gl.getProgramInfoLog(shaderProgram));
    }

    // Take the shader program into use
    gl.useProgram(shaderProgram);
    //! [5]

    //! [6]
    // Look up where the vertex data needs to go
    vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
    gl.enableVertexAttribArray(vertexPositionAttribute);
    textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
    gl.enableVertexAttribArray(textureCoordAttribute);
    vertexNormalAttribute = gl.getAttribLocation(shaderProgram, "aVertexNormal");
    gl.enableVertexAttribArray(vertexNormalAttribute);

    // Get the uniform locations
    pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
    mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
    nUniform = gl.getUniformLocation(shaderProgram, "uNormalMatrix");

    // Setup texture sampler uniform
    var textureSamplerUniform = gl.getUniformLocation(shaderProgram, "uSampler")
    gl.activeTexture(gl.TEXTURE0);
    gl.uniform1i(textureSamplerUniform, 0);
    gl.bindTexture(gl.TEXTURE_2D, 0);
    //! [6]
}

function getShader(gl, str, type) {
    var shader = gl.createShader(type);
    gl.shaderSource(shader, str);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        console.log("JS:Shader compile failed");
        console.log(gl.getShaderInfoLog(shader));
        return null;
    }

    return shader;
}
