#pragma once
#include <math.h>
#include "vec2.h"
#include "vec3.h"

float clamp(float value, float minValue, float maxValue) {
    return fmax(fmin(value, maxValue), minValue);
}

double sign(double number) {
    return (0 < number) - (number < 0);
}

double step(double edge, double x) {
    return x > edge;
}

float length(vec2 const& vector2D) {
    return sqrt(vector2D.x * vector2D.x + vector2D.y * vector2D.y);
}

float length(vec3 const& vector3D) {
    return sqrt(vector3D.x * vector3D.x + vector3D.y * vector3D.y + vector3D.z * vector3D.z);
}

vec3 norm(vec3 vector3D) {
    return vector3D / length(vector3D);
}

float dot(vec3 const& vectorA, vec3 const& vectorB) {
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}

vec3 abs(vec3 const& vector3D) {
    return vec3(fabs(vector3D.x), fabs(vector3D.y), fabs(vector3D.z));
}

vec3 sign(vec3 const& vector3D) {
    return vec3(sign(vector3D.x), sign(vector3D.y), sign(vector3D.z));
}

vec3 step(vec3 const& edgeVector, vec3 vector3D) {
    return vec3(step(edgeVector.x, vector3D.x), step(edgeVector.y, vector3D.y), step(edgeVector.z, vector3D.z));
}

vec3 reflect(vec3 incomingRay, vec3 normal) {
    return incomingRay - normal * (2 * dot(normal, incomingRay));
}

vec3 rotateX(vec3 vector3D, double angle) {
    vec3 rotatedVector = vector3D;
    rotatedVector.z = vector3D.z * cos(angle) - vector3D.y * sin(angle);
    rotatedVector.y = vector3D.z * sin(angle) + vector3D.y * cos(angle);
    return rotatedVector;
}

vec3 rotateY(vec3 vector3D, double angle) {
    vec3 rotatedVector = vector3D;
    rotatedVector.x = vector3D.x * cos(angle) - vector3D.z * sin(angle);
    rotatedVector.z = vector3D.x * sin(angle) + vector3D.z * cos(angle);
    return rotatedVector;
}

vec3 rotateZ(vec3 vector3D, double angle) {
    vec3 rotatedVector = vector3D;
    rotatedVector.x = vector3D.x * cos(angle) - vector3D.y * sin(angle);
    rotatedVector.y = vector3D.x * sin(angle) + vector3D.y * cos(angle);
    return rotatedVector;
}

vec2 calculateSphereIntersection(vec3 rayOrigin, vec3 rayDirection, vec3 sphereCenter, float sphereRadius) {
    vec3 toSphere = rayOrigin - sphereCenter;
    float b = dot(toSphere, rayDirection);
    float c = dot(toSphere, toSphere) - sphereRadius * sphereRadius;
    float discriminant = b * b - c;
    if (discriminant < 0.0) return vec2(-1.0);
    discriminant = sqrt(discriminant);
    return vec2(-b - discriminant, -b + discriminant);
}


vec2 calculateBoxIntersection(
    vec3 rayOrigin,
    vec3 rayDirection,
    vec3 boxPosition,
    vec3 boxSize,
    vec3& outNormal
) {
    vec3 adjustedOrigin = rayOrigin - boxPosition;  // Коригуємо походження променя відносно позиції куба
    vec3 inverseDirection = vec3(1.0) / rayDirection;
    vec3 scaledOrigin = inverseDirection * adjustedOrigin;
    vec3 scaledDimensions = abs(inverseDirection) * boxSize;

    vec3 entryTime = -scaledOrigin - scaledDimensions;
    vec3 exitTime = -scaledOrigin + scaledDimensions;

    float tNear = fmax(fmax(entryTime.x, entryTime.y), entryTime.z);
    float tFar = fmin(fmin(exitTime.x, exitTime.y), exitTime.z);

    if (tNear > tFar || tFar < 0.0) return vec2(-1.0);

    vec3 entryYZ = vec3(entryTime.y, entryTime.z, entryTime.x);
    vec3 entryZX = vec3(entryTime.z, entryTime.x, entryTime.y);

    outNormal = -sign(rayDirection) * step(entryYZ, entryTime) * step(entryZX, entryTime);

    return vec2(tNear, tFar);
}



float plane(vec3 rayOrigin, vec3 rayDirection, vec3 planeNormal, float planeOffset) {
    return -(dot(rayOrigin, planeNormal) + planeOffset) / dot(rayDirection, planeNormal);
}
