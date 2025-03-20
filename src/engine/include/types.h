#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <GL/gl.h>

typedef uint8_t byte;

enum KEY_CODE : byte {
    K_UP,
    K_LEFT,
    K_RIGHT,
    K_DOWN,

    K_ENTER,
    K_BACKSPACE,
    K_ESCAPE,

    K_x,
    K_c,


    KEYS_COUNT
};

struct iVector2 {
    float x, y;

    iVector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    iVector2 operator+(const iVector2& other) const { return iVector2(x + other.x, y + other.y); }
    iVector2 operator-(const iVector2& other) const { return iVector2(x - other.x, y - other.y); }
    iVector2 operator*(const iVector2& other) const { return iVector2(x * other.x, y * other.y); }
    iVector2 operator/(const iVector2& other) const { return iVector2(x / other.x, y / other.y); }

    iVector2 operator*(float scalar) const { return iVector2(x * scalar, y * scalar); }
    iVector2 operator/(float scalar) const { return iVector2(x / scalar, y / scalar); }
};

struct Vector2 {
    float x, y;

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
    Vector2 operator*(const Vector2& other) const { return Vector2(x * other.x, y * other.y); }
    Vector2 operator/(const Vector2& other) const { return Vector2(x / other.x, y / other.y); }

    Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
    Vector2 operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }
};

struct Vector3 {
    float x, y, z;

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
    Vector3 operator-(const Vector3& other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
    Vector3 operator*(const Vector3& other) const { return Vector3(x * other.x, y * other.y, z * other.z); }
    Vector3 operator/(const Vector3& other) const { return Vector3(x / other.x, y / other.y, z / other.z); }

    Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
    Vector3 operator/(float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }
};

struct Color4 {
    float r, g, b, a;

    Color4(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
};



struct TEXT_UI {
    Vector2 position;
    iVector2 size;
    GLuint texture;

    //void load(const char* text, const char* fontPath, int fontSize, Color4 c, Vector2 pos, Uint32 warp, GLuint (*lod_txt_text)(const char *text, const char *fontPath, int fontSize, Color4 c, GLuint& textTexture, int& w, int& h, Uint32 warp, GLenum FILTER));
    ~TEXT_UI();
};


Vector2 parse_iv2(iVector2 iv2);
