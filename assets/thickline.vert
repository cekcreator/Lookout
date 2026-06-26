#version 150 core

in vec3  aPos;    // this vertex's endpoint (A for verts 0&1, B for verts 2&3)
in vec3  aOther;  // the opposite endpoint
in float aSign;   // +1 or -1 — which side of the quad

uniform mat4 ciModelViewProjection;
uniform vec2 uResolution;
uniform float uWidth;

void main()
{
    vec4 clipPos   = ciModelViewProjection * vec4(aPos,   1.0);
    vec4 clipOther = ciModelViewProjection * vec4(aOther, 1.0);

    // Perspective divide → NDC
    vec2 ndcPos   = clipPos.xy   / clipPos.w;
    vec2 ndcOther = clipOther.xy / clipOther.w;

    // Screen-space direction and perpendicular
    vec2 dir  = normalize((ndcOther - ndcPos) * uResolution);
    vec2 perp = vec2(-dir.y, dir.x);

    // Offset in NDC units — divide by half-res to convert px → NDC
    vec2 ndcOffset = perp * (uWidth / uResolution) * aSign;

    // Write final position: expand in NDC, then re-pack into clip space
    vec2 finalNdc = ndcPos + ndcOffset;
    gl_Position = vec4(finalNdc * clipPos.w, clipPos.z, clipPos.w);
}
