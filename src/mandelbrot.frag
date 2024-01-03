#version 330 core
precision highp float;

#define ARRAY_SIZE 1024

uniform vec2 center;
uniform float zoom;
uniform vec2 resolution;
uniform int max_iteration;
uniform vec3 colors[ARRAY_SIZE];


// Square of a complex number
vec2 square(vec2 z) {
    return vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y);
}


vec3 mandelbrot(in vec2 pos) {
    vec2 z = vec2(0.0);
    float iterations = 0.0;

    while (iterations < max_iteration && dot(z, z) <= (1 << 16)) {
        z = square(z) + pos;    // z = z^2 + c
        iterations += 1.0;
    }

    if (iterations == max_iteration) return vec3(0.0);

    // Сolors interpolation
    float log_zn = log2(dot(z, z)) / 2.0;
    iterations += 1.0 - log2(log_zn);

    vec3 color_one = colors[int(iterations / max_iteration * ARRAY_SIZE)];
    vec3 color_two = colors[int(iterations / max_iteration * ARRAY_SIZE) + 1];

    return mix(color_one, color_two, fract(iterations));
}
 
void main() {
    float axis = 2.5f;  // `y` is within [-1.25; 1.25]
    float ratio = resolution.x / resolution.y;

    vec2 coord = ((gl_FragCoord.xy / resolution - vec2(0.5f)) * zoom + center) * axis;
    coord.x *= ratio;

    gl_FragColor = vec4(mandelbrot(coord), 1.0f);
}
