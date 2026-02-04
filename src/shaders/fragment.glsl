#version 330 core

out vec4 screenColor;

// Camera
uniform vec3 eye;
uniform vec2 screenSize;
uniform float L, R, B, T, N;
uniform vec3 cameraFront;
uniform vec3 cameraRight;
uniform vec3 cameraUp;

// Plane
uniform vec3 planePoint;
uniform vec3 planeNormal;
uniform vec3 planeColor;

// Sphere
uniform vec3 sphereCenter;
uniform float sphereRadius;
uniform vec3 sphereColor;
uniform float sphereReflectivity;

// Cylinder
uniform vec3 cylinderCenter;
uniform float cylinderRadius;
uniform float cylinderHeight;
uniform vec3 cylinderColor;

// Cube
uniform vec3 cubeCenter;
uniform float cubeLength;
uniform vec3 cubeColor;

// Light
uniform vec3 lightSource;

// Material constants
const vec3 MATERIAL = vec3(0.4, 0.6, 0.6);
const float SHININESS = 100.0;
const float EPSILON = 0.001;
const float SHADOW_FACTOR = 0.5;

// Function declarations
float planeIntersect(vec3 rayOrigin, vec3 rayDir, vec3 point, vec3 normal);
float sphereIntersect(vec3 rayOrigin, vec3 rayDir, vec3 center, float r);
float cylinderIntersect(vec3 rayOrigin, vec3 dir, vec3 center, float r, float h);
float cubeIntersect(vec3 rayOrigin, vec3 rayDir, vec3 center, float length);
vec3 cubeNormal(vec3 hit, vec3 center, float length);
vec3 phong(float t, vec3 rayOrigin, vec3 direction, vec3 normal, vec3 color);
float shadow(vec3 hit, vec3 normal);
int findClosestHit(vec3 origin, vec3 dir, out float t);


void main() {
    float pixelX = gl_FragCoord.x;
    float pixelY = gl_FragCoord.y;

    float stepX = (R - L) / screenSize.x;
    float stepY = (T - B) / screenSize.y;

    float x = L + stepX * (pixelX + 0.5);
    float y = B + stepY * (pixelY + 0.5);

    // Ray direction using camera basis vectors for full rotation support
    vec3 direction = normalize(cameraFront * N + cameraRight * x + cameraUp * y);

    float t;
    int hitShape = findClosestHit(eye, direction, t);

    if (hitShape == 1) {
        // Sphere
        vec3 hitPoint = eye + t * direction;
        vec3 normal = normalize(hitPoint - sphereCenter);
        vec3 color = phong(t, eye, direction, normal, sphereColor);

        if (sphereReflectivity > 0.0) {
            vec3 reflectDir = reflect(direction, normal);
            vec3 reflectOrigin = hitPoint + normal * EPSILON;
            float tReflect;
            int reflectHit = findClosestHit(reflectOrigin, reflectDir, tReflect);

            vec3 reflectColor = vec3(0.0);

            if (reflectHit >= 0) {
                vec3 reflectPoint = reflectOrigin + tReflect * reflectDir;
                vec3 reflectNormal;

                if (reflectHit == 0) {
                    reflectNormal = planeNormal;
                    reflectColor = phong(tReflect, reflectOrigin, reflectDir, reflectNormal, planeColor);
                } else if (reflectHit == 1) {
                    reflectNormal = normalize(reflectPoint - sphereCenter);
                    reflectColor = phong(tReflect, reflectOrigin, reflectDir, reflectNormal, sphereColor);
                } else if (reflectHit == 2) {
                    reflectNormal = reflectPoint - cylinderCenter;
                    reflectNormal.y = 0.0;
                    reflectNormal = normalize(reflectNormal);
                    reflectColor = phong(tReflect, reflectOrigin, reflectDir, reflectNormal, cylinderColor);
                } else if (reflectHit == 3) {
                    reflectNormal = cubeNormal(reflectPoint, cubeCenter, cubeLength);
                    reflectColor = phong(tReflect, reflectOrigin, reflectDir, reflectNormal, cubeColor);
                }
            }

            color = mix(color, reflectColor, sphereReflectivity);
        }

        screenColor = vec4(color, 1.0);
    } else if (hitShape == 2) {
        // Cylinder
        vec3 hitPoint = eye + t * direction;
        vec3 normal = hitPoint - cylinderCenter;
        normal.y = 0.0;
        normal = normalize(normal);
        screenColor = vec4(phong(t, eye, direction, normal, cylinderColor), 1.0);
    } else if (hitShape == 3) {
        // Cube
        vec3 hitPoint = eye + t * direction;
        vec3 normal = cubeNormal(hitPoint, cubeCenter, cubeLength);
        screenColor = vec4(phong(t, eye, direction, normal, cubeColor), 1.0);
    } else if (hitShape == 0) {
        // Plane
        vec3 hitPoint = eye + t * direction;
        float shadowFactor = shadow(hitPoint, planeNormal);
        vec3 color = phong(t, eye, direction, planeNormal, planeColor) * shadowFactor;
        screenColor = vec4(color, 1.0);
    } else {
        // Background
        screenColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}


float shadow(vec3 hit, vec3 normal) {
    vec3 toLight = normalize(lightSource - hit);
    vec3 offsetHit = hit + normal * EPSILON;

    float t = sphereIntersect(offsetHit, toLight, sphereCenter, sphereRadius);

    if (t > 0.0) {
        return SHADOW_FACTOR;
    }
    return 1.0;
}


float planeIntersect(vec3 rayOrigin, vec3 rayDir, vec3 point, vec3 normal) {
    float denom = dot(normal, rayDir);

    if (abs(denom) < EPSILON) {
        return -1.0;
    }

    vec3 F = point - rayOrigin;
    float t = dot(F, normal) / denom;

    return t;
}


float sphereIntersect(vec3 rayOrigin, vec3 rayDir, vec3 center, float r) {
    vec3 origin = rayOrigin - center;

    float a = 1.0;
    float b = 2.0 * dot(rayDir, origin);
    float c = dot(origin, origin) - r * r;
    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return -1.0;
    }

    float sqrtDisc = sqrt(discriminant);
    float t1 = (-b - sqrtDisc) / (2.0 * a);
    float t2 = (-b + sqrtDisc) / (2.0 * a);

    if (t1 > 0.0) return t1;
    if (t2 > 0.0) return t2;
    return -1.0;
}


float cylinderIntersect(vec3 rayOrigin, vec3 dir, vec3 center, float r, float h) {
    vec3 origin = rayOrigin - center;

    float a = dir.x * dir.x + dir.z * dir.z;
    float b = 2.0 * (origin.x * dir.x + origin.z * dir.z);
    float c = origin.x * origin.x + origin.z * origin.z - r * r;

    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return -1.0;
    }

    float sqrtDisc = sqrt(discriminant);
    float t1 = (-b - sqrtDisc) / (2.0 * a);
    float t2 = (-b + sqrtDisc) / (2.0 * a);

    float y1 = rayOrigin.y + t1 * dir.y;
    float y2 = rayOrigin.y + t2 * dir.y;

    float bottom = center.y - h / 2.0;
    float top = center.y + h / 2.0;

    // Check if t1 hit is within height bounds
    if (t1 > 0.0 && y1 >= bottom && y1 <= top) {
        return t1;
    }
    // Check if t2 hit is within height bounds (inside cylinder, exiting)
    if (t2 > 0.0 && y2 >= bottom && y2 <= top) {
        return t2;
    }

    return -1.0;
}


float cubeIntersect(vec3 rayOrigin, vec3 rayDir, vec3 center, float length) {
    vec3 halfSize = vec3(length / 2.0);

    vec3 cmin = center - halfSize;
    vec3 cmax = center + halfSize;

    vec3 tmin = (cmin - rayOrigin) / rayDir;
    vec3 tmax = (cmax - rayOrigin) / rayDir;

    float t1 = max(max(min(tmin.x, tmax.x), min(tmin.y, tmax.y)), min(tmin.z, tmax.z));
    float t2 = min(min(max(tmin.x, tmax.x), max(tmin.y, tmax.y)), max(tmin.z, tmax.z));

    if (t1 <= t2 && t2 > 0.0) {
        if (t1 > 0.0) return t1;
        return t2;
    }
    return -1.0;
}


vec3 cubeNormal(vec3 hit, vec3 center, float length) {
    vec3 localHit = hit - center;
    vec3 halfSize = vec3(length / 2.0);

    vec3 d = abs(localHit) / halfSize;

    if (d.x > d.y && d.x > d.z) {
        return vec3(sign(localHit.x), 0.0, 0.0);
    } else if (d.y > d.z) {
        return vec3(0.0, sign(localHit.y), 0.0);
    } else {
        return vec3(0.0, 0.0, sign(localHit.z));
    }
}


vec3 phong(float t, vec3 rayOrigin, vec3 direction, vec3 normal, vec3 color) {
    vec3 hit = rayOrigin + t * direction;

    vec3 N = normal;
    vec3 L = normalize(lightSource - hit);
    vec3 V = normalize(rayOrigin - hit);
    vec3 R = reflect(-L, N);

    vec3 ambient = MATERIAL.x * color;

    float dotNL = max(dot(N, L), 0.0);
    vec3 diffuse = MATERIAL.y * dotNL * color;

    float dotRV = max(dot(R, V), 0.0);
    vec3 specular = MATERIAL.z * pow(dotRV, SHININESS) * color;

    return ambient + diffuse + specular;
}


// Returns: hitShape (-1=none, 0=plane, 1=sphere, 2=cylinder, 3=cube)
int findClosestHit(vec3 origin, vec3 dir, out float t) {
    t = -1.0;
    int hitShape = -1;

    float tPlane = planeIntersect(origin, dir, planePoint, planeNormal);
    float tSphere = sphereIntersect(origin, dir, sphereCenter, sphereRadius);
    float tCylinder = cylinderIntersect(origin, dir, cylinderCenter, cylinderRadius, cylinderHeight);
    float tCube = cubeIntersect(origin, dir, cubeCenter, cubeLength);

    if (tPlane > 0.0) { t = tPlane; hitShape = 0; }
    if (tSphere > 0.0 && (t < 0.0 || tSphere < t)) { t = tSphere; hitShape = 1; }
    if (tCylinder > 0.0 && (t < 0.0 || tCylinder < t)) { t = tCylinder; hitShape = 2; }
    if (tCube > 0.0 && (t < 0.0 || tCube < t)) { t = tCube; hitShape = 3; }

    return hitShape;
}
