#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "stb_image_write.h"

using namespace std;

class vec3 {
public:
    float x, y, z;

    vec3() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
    vec3(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    vec3 operator + (vec3 const &vec) {
        vec3 result;
        result.x = x + vec.x;
        result.y = y + vec.y;
        result.z = z + vec.z;

        return result;
    }

    vec3 operator + (float const &c) {
        vec3 result;
        result.x = x + c;
        result.y = y + c;
        result.z = z + c;

        return result;
    }

    vec3 operator - (vec3 const &vec) {
        vec3 result;
        result.x = x - vec.x;
        result.y = y - vec.y;
        result.z = z - vec.z;

        return result;
    }

    float operator * (vec3 const &vec) {
        float result = 0.0f;
        result += x * vec.x;
        result += y * vec.y;
        result += z * vec.z;

        return result;
    }

    vec3 operator * (float const c) {
        vec3 result;
        result.x = x * c;
        result.y = y * c;
        result.z = z * c;

        return result;
    }

    vec3 normalize() {
        vec3 result;
        float len = length();
        result.x = x / len;
        result.y = y / len;
        result.z = z / len;

        return result;
    }

    float length() {
        float result = 0.0f;
        result += x * x;
        result += y * y;
        result += z * z;

        return result;
    }

    float angle(vec3 &vec) {
        float result;
        float a = length();
        float b = vec.length();
        if(a * b == 0) return 0;
        float dot = vec3(x, y, z) * vec;
        result = acos(dot / (a * b));

        return result;
    }

    vec3 cross(vec3 &vec) {
        vec3 result;
        result.x = (z * vec.y) - (y * vec.z);
        result.y = (x * vec.z) - (z * vec.x);
        result.z = (y * vec.x) - (x * vec.y);

        return result;
    }

    friend ostream & operator<<(ostream & _stream, vec3 const &vec) {
        _stream << "(" << vec.x <<", " << vec.y << ", " << vec.z << ")";

        return _stream;
    }
};

class vec4 {
public:
    float x, y, z, w;

    vec4() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 0.0f;
    }

    vec4(float _x, float _y, float _z, float _w) {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    vec4 operator + (vec4 const &vec) {
        vec4 result;
        result.x = x + vec.x;
        result.y = y + vec.y;
        result.z = z + vec.z;
        result.w = w + vec.w;

        return result;
    }

    vec4 operator + (float const &c) {
        vec4 result;
        result.x = x + c;
        result.y = y + c;
        result.z = z + c;
        result.w = w;

        return result;
    }

    vec4 operator - (vec4 const &vec) {
        vec4 result;
        result.x = x - vec.x;
        result.y = y - vec.y;
        result.z = z - vec.z;
        result.w = w - vec.w;

        return result;
    }

    float operator * (vec4 const &vec) {
        float result = 0;
        result += x * vec.x;
        result += y * vec.y;
        result += z * vec.z;
        result += w * vec.w;

        return result;
    }

    vec4 operator * (float const c) {
        vec4 result;
        result.x = y * c;
        result.y = x * c;
        result.z = z * c;
        result.w = w * c;

        return result;
    }

    vec4 normalize() {
        vec4 result;
        float len = length();
        result.x = y / len;
        result.y = x / len;
        result.z = z / len;
        result.w = w / len;

        return result;
    }

    float length() {
        float result = 0;
        result += x * x;
        result += y * y;
        result += z * z;
        result += w * w;

        return result;
    }

    float max() {
        return std::max(std::max(x, y), z);
    }

    friend ostream & operator<<(ostream & _stream, vec4 const &vec) {
        _stream << "(" << vec.x <<", " << vec.y << ", " << vec.z << ")";

        return _stream;
    }
};

class Ray {
public:
    vec3 origin;
    vec3 direction;

    Ray() {
        origin = vec3(0.0f, 0.0f, 0.0f);
        direction = vec3(0.0f, 0.0f, 1.0f);
    }

    Ray(vec3 _direction) {
        origin = vec3(0.0f, 0.0f, 0.0f);
        direction = _direction.normalize();
    }

    Ray(vec3 _origin, vec3 _direction) {
        origin = _origin;
        direction = _direction.normalize();
    }

    vec3 get(float t) {
        vec3 result;
        result = origin + (direction * t);

        return  result;
    }
};

class Triangle {
public:
    vec4 color;
    vec3 point1;
    vec3 point2;
    vec3 point3;

    Triangle() {
        point1 = vec3(-0.5f, -0.5f, 2.0f);
        point2 = vec3(0.0f, 0.5f, 2.0f);
        point3 = vec3(0.5f, -0.5f, 2.0f);
        color = vec4(0.819f, 0.066f, 0.254f, 1.0);
    }

    Triangle(vec3 _point1, vec3 _point2, vec3 _point3, vec4 _color) {
        point1 = _point1;
        point2 = _point2;
        point3 = _point3;
        color = _color;
    }

    vec3 normal() {
        vec3 result;
        vec3 a = point3 - point1;
        vec3 b = point2 - point1;
        result = a.cross(b).normalize();

        return result;
    }

    bool Intersect(Ray r, float& t) {
        vec3 N = normal();
        vec3 O = r.origin;
        vec3 dir = r.direction;
        float D = N * point1;

        if((N * dir) == 0) {
            t = MAXFLOAT;
            return false;
        }

        t = ((N * O) + D) / (N * dir);

        vec3 P = r.get(t);

        vec3 E1 = point2 - point1;
        vec3 E2 = point3 - point2;
        vec3 E3 = point1 - point3;

        vec3 P1 = P - point1;
        vec3 C1 = P1.cross(E1);
        vec3 P2 = P - point2;
        vec3 C2 = P2.cross(E2);
        vec3 P3 = P - point3;
        vec3 C3 = P3.cross(E3);

        if((N * C1 <= 0 && N * C2 <= 0 && N * C3 <= 0)
        || (N * C1 >= 0 && N * C2 >= 0 && N * C3 >= 0))
            return true;
        else return false;
    }

    friend ostream & operator<<(ostream & _stream, Triangle const &vec) {
        _stream << "( " << vec.point1 <<",\n" << vec.point2 << ",\n" << vec.point3 <<" )";

        return _stream;
    }

    Triangle operator + (vec3 const &vec) {
        Triangle result = Triangle();

        vector<vec3> points = {point1, point2, point3};
        for(int i = 0; i < 3; i++) {
            result.point1 = point1 + vec;
            result.point2 = point2 + vec;
            result.point3 = point3 + vec;
        }

        return result;
    }

    Triangle operator - (vec3 const &vec) {
        Triangle result = Triangle();

        vector<vec3> points = {point1, point2, point3};
        for(int i = 0; i < 3; i++) {
            result.point1 = point1 - vec;
            result.point2 = point2 - vec;
            result.point3 = point3 - vec;
        }

        return result;
    }

    Triangle operator * (float const c) {
        Triangle result = Triangle();

        vector<vec3> points = {point1, point2, point3};
        for(int i = 0; i < 3; i++) {
            result.point1 = point1 * c;
            result.point2 = point2 * c;
            result.point3 = point3 * c;
        }

        return result;
    }
};

float rad(const float &deg);

class Camera {
public:
    vec3 position;
    float fov;
    vec3 lookAt;
    vec3 up;

    Camera() {
        position = vec3(0.0f, 0.0f, 0.0f);
        lookAt = vec3(0.0f, 0.0f, 1.0f);
        up = vec3(0.0f, 1.0f, 0.0f);
        fov = 45.0f;
    }

    Camera(vec3 _lookAt) {
        position = vec3(0.0f, 0.0f, 0.0f);
        lookAt = _lookAt.normalize();
        up = vec3(0.0f, 1.0f, 0.0f);
        fov = 45.0f;
    }

    void look_at(vec3 _lookAt) {
        lookAt = _lookAt.normalize();
    }

    Ray ConstructRayThroughPixel(int i, int j, float w, float h) {
        Ray ray;
        vec3 origin = position;
        vec3 direction;
        direction.x = (2.0f * (i + 0.5f) / w - 1.0f) * w / h * tan(rad(fov / 2.0f));
        direction.y = (1.0f - 2.0f * (j + 0.5f) / (float)h) * tan(rad(fov / 2.0f));
        direction.z = 1.0f;

        ray.origin = origin;
        ray.direction = direction;

        return ray;
    }

};

float rad(const float &deg) {
    return deg * M_PI / 180.0f;
}

vec3 random_point(float MIN, float MAX) {
    float x = MIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX - MIN)));
    float y = MIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX - MIN)));
    float z = MIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX - MIN)));

    return vec3(x, y, z);
}

float random_float(float MIN, float MAX) {
    float x = MIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX - MIN)));

    return x;
}

int random_index(int max) {
    int i = rand() % max;

    return i;
}

void render(float width, float height, float fov, vector<Triangle> triangles, const char *path);

int main() {
    int num_random_triangles = 20;
    int num_gradient_triangles = 30;
    vector<Triangle> random_triangles;
    vector<Triangle> gradient_triangles;
    vector<Triangle> two_triangles;

    // RANDOM TRIANGLES
    Triangle triangle_template = Triangle();
    for(int i = 0; i < num_random_triangles; i++) {
        vec3 offset = random_point(-1.0f, 1.0f);
        float scale = random_float(0.0f, 0.7f);
        vec4 random_color = vec4(random_float(0.1f, 0.9f), random_float(0.1f, 0.9f), random_float(0.1f, 0.9f), 1.0f);

        Triangle random_triangle = (triangle_template + offset) * scale;
        random_triangle.color = random_color;
        random_triangles.push_back(random_triangle);
    }

    // GRADIENT TRIANGLES
    Triangle first = Triangle();
    first.point1 = first.point1 + -0.8f;
    first.point2 = first.point2 + -0.8f;
    first.point3 = first.point3 + -0.8f;
    first.color = vec4(0.34f, 0.04f, 0.12f, 1.0f);
    Triangle last = first;
    float gradient_step = (1.0f - first.color.max()) / num_gradient_triangles;
    float step = 2.0f / num_gradient_triangles;
    vec3 offset = vec3(step, step, 0.01f);

    for(int i = 0; i < num_gradient_triangles; i++) {
        Triangle triangle = (last + offset);
        triangle.color = last.color + gradient_step;
        last = triangle;

        gradient_triangles.push_back(triangle);
    }

    // TWO LAME TRIANGLES
    two_triangles.push_back(Triangle() + vec3(0.1f, 0.1f, 0.0f));
    vec3 point1 = vec3(-0.8f, -0.8f, 2.0f);
    vec3 point2 = vec3(-0.3f, 0.2f, 2.0f);
    vec3 point3 = vec3(0.2f, -0.8f, 2.0f);
    vec4 random_color = vec4(random_float(0.1f, 0.9f), random_float(0.1f, 0.9f), random_float(0.1f, 0.9f), 1.0f);
    two_triangles.push_back(Triangle(point1, point2, point3, random_color));

    render(512.0f, 512.0f, 45.0f, two_triangles, "../two_triangles.bmp");
    render(512.0f, 512.0f, 90.0f, random_triangles, "../random_triangles.bmp");
    render(512.0f, 512.0f, 95.0f, gradient_triangles, "../gradient_triangles.bmp");

    return 0;
}

void render(float width, float height, float fov, vector<Triangle> triangles, const char *path) {
    Camera camera = Camera();
    camera.fov = fov;
    unsigned char frame[(int)width * (int)height * 3];
    int pix = 0;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            float t_min = MAXFLOAT;
            vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

            Ray ray = camera.ConstructRayThroughPixel(i, j, width, height);
            for(int k = 0; k < triangles.size(); k++) {
                float t;
                bool intersection = triangles[k].Intersect(ray, t);
                if(intersection && (t < t_min)) {
                    t_min = t;
                    color = triangles[k].color;
                }
            }

            // Set the color of current pixel.
            frame[pix] = (int)(color.x * 255);
            frame[pix + 1] = (int)(color.y * 255);
            frame[pix + 2] = (int)(color.z * 255);

            pix += 3;
        }
    }

    stbi_write_bmp(path, (int)width, (int)height, 3, frame);
}
