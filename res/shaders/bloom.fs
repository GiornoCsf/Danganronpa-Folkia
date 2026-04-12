#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float intensity; // From your C++ code

out vec4 finalColor;

void main() {
    vec4 texel = texture2D(texture0, fragTexCoord) * colDiffuse * fragColor;
    
    // Create a specific Blue Glow Color (R, G, B, A)
    vec4 glowColor = vec4(0.2, 0.5, 1.0, 1.0); 
    
    // Check if the pixel is bright (white edges)
    float brightness = (texel.r + texel.g + texel.b) / 3.0;
    
    if (brightness > 0.4) {
        // Add blue glow based on intensity
        finalColor = texel + (glowColor * intensity * 0.5);
    } else {
        finalColor = texel;
    }
}

