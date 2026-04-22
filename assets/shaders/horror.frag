#version 450

layout(location = 0) out vec4 outColor;
layout(binding = 1) sampler2D texSampler;

void main() {
    // Screen resolution normalization
    vec2 uv = gl_FragCoord.xy / vec2(1600.0, 720.0); 
    
    // Low-res "Snap" for that PS1 pixelated look
    float pixels = 256.0;
    uv = floor(uv * pixels) / pixels;

    vec4 color = texture(texSampler, uv);

    // Add film grain/noise for atmosphere
    float noise = (fract(sin(dot(uv, vec2(12.9898,78.233)*2.0)) * 43758.5453));
    color.rgb += noise * 0.08;

    outColor = color;
}
