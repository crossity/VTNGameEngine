#include <cmath>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#include "vtn_renderer.hpp"
#include "vtn_types.hpp"
#include "vtn_window.hpp"
#include "vtn_math.hpp"
#include "vtn_draw.hpp"

vtnMAT3X3 vtn_to_camera_mat;
vtnMAT4X4 vtn_projection_mat;
vtnVEC2 vtn_view_port;
vtnVEC3 vtn_camera_pos;
float vtn_near_plane;

/*
public static Matrix3D PrespectiveFromHV(double fieldOfViewY, double aspectRatio, double zNearPlane, double zFarPlane, double mod)
    {
        double height = 1.0 / Math.Tan(fieldOfViewY / 2.0);
        double width = height / aspectRatio;
        double d = zNearPlane - zFarPlane;
        var rm = Math.Round(mod, 1);
        var m = new Matrix3D(
                width, 0, 0, 0,
                0, height, 0, 0,
                0, 0, (zFarPlane / d) * rm, (zNearPlane * zFarPlane / d) * rm,
                0, 0, (-1 * rm), (1 - rm)
            );
        return m;
    }
*/

void vtnUpadateCameraRot(vtnCAMERA &camera, vtnVEC3 rot) {
    vtnMAT3X3 m{0};
    float csx = cos(rot.x), csy = cos(rot.y), csz = cos(rot.z);
    float snx = sin(rot.x), sny = sin(rot.y), snz = sin(rot.z);

    camera.rot = rot;

    vtn_to_camera_mat = vtnMAT3X3(0);
    vtn_to_camera_mat.v[0][0] = 1;
    vtn_to_camera_mat.v[1][1] = csx;
    vtn_to_camera_mat.v[1][2] = snx;
    vtn_to_camera_mat.v[2][1] = -snx;
    vtn_to_camera_mat.v[2][2] = csx;

    m.v[0][0] = csy;
    m.v[0][2] = -sny;
    m.v[1][1] = 1;
    m.v[2][0] = sny;
    m.v[2][2] = csy;

    vtn_to_camera_mat = vtn_to_camera_mat * m;

    m.v[0][0] = csz;
    m.v[0][1] = snz;
    m.v[1][0] = -snz;
    m.v[1][1] = csz;
    m.v[2][2] = 1;

    vtn_to_camera_mat = vtn_to_camera_mat * m;
}

void vtnUpadateCameraPos(vtnCAMERA &camera, vtnVEC3 pos) {
    vtn_camera_pos = (camera.pos = pos);
}

vtnVEC2 vtnRender(vtnVEC3 p) {
    vtnVEC4 p_proj{p.x, p.y, p.z, 1};
    vtnVEC2 ret;

    p_proj = p_proj * vtn_projection_mat;

    ret = vtnVEC2(p_proj.x, p_proj.y);

    if (p_proj.w != 0)
        ret.x /= p_proj.w, ret.y /= p_proj.w;
    
    ret.y *= -1;

    ret.x += 1.0;
    ret.y += 1.0;

    ret.x *= 0.5 * vtn_view_port.x;
    ret.y *= 0.5 * vtn_view_port.y;

    return ret;
}

void vtnRenderScene(vtnSCENE &scene) {
    std::vector<vtnTRI> tris(scene.tris.size());
    memcpy(tris.data(), scene.tris.data(), sizeof(vtnTRI) * scene.tris.size());
    std::sort(tris.begin(), tris.end(), [&](vtnTRI a, vtnTRI b) {
        vtnVEC3 ca = scene.vert_buffer.v[a.p[0]] + scene.vert_buffer.v[a.p[1]] + scene.vert_buffer.v[a.p[2]];
        vtnVEC3 cb = scene.vert_buffer.v[b.p[0]] + scene.vert_buffer.v[b.p[1]] + scene.vert_buffer.v[b.p[2]];
        ca = ca / 3.f;
        cb = cb / 3.f;
        float da = vtnDist2(vtn_camera_pos, ca);
        float db = vtnDist2(vtn_camera_pos, cb);
        return db < da;
    });

    for (int i = 0; i < tris.size(); i++) {
        vtnVEC3 t_center = ((scene.vert_buffer).v[tris[i].p[0]] + (scene.vert_buffer).v[tris[i].p[1]] + (scene.vert_buffer).v[tris[i].p[2]]) / 3.f;
        vtnVEC3 camera_ray = vtnVecNorm(t_center - vtn_camera_pos);
        vtnVEC3 line1 = (scene.vert_buffer).v[tris[i].p[1]] - (scene.vert_buffer).v[tris[i].p[0]];
        vtnVEC3 line2 = (scene.vert_buffer).v[tris[i].p[2]] - (scene.vert_buffer).v[tris[i].p[0]];
        vtnVEC3 n = vtnVecNorm(vtnCrossProduct(line1, line2));
        float dp = vtnDotProduct(n, camera_ray * -1);
        if (dp >= 0) {
            vtnVEC3 t_p1 = vtn_to_camera_mat * ((scene.vert_buffer).v[tris[i].p[0]] - vtn_camera_pos);
            vtnVEC3 t_p2 = vtn_to_camera_mat * ((scene.vert_buffer).v[tris[i].p[1]] - vtn_camera_pos);
            vtnVEC3 t_p3 = vtn_to_camera_mat * ((scene.vert_buffer).v[tris[i].p[2]] - vtn_camera_pos);

            std::vector<vtnVEC3> tri_queue;
            tri_queue.push_back(t_p1);
            tri_queue.push_back(t_p2);
            tri_queue.push_back(t_p3);

            vtnTriangleClip(vtnVEC3(0, 0, vtn_near_plane), vtnVEC3(0, 0, 1), tri_queue);

            float light_dp = 0;

            for (int j = 0; j < scene.lights.size(); j++)
                light_dp += std::fmax(vtnDotProduct(scene.lights[j], n), 0.f);
            light_dp = std::fmin(light_dp, 1.f);

            for (int j = 0; j < tri_queue.size(); j += 3) {
                vtnVEC2 p1 = vtnRender(tri_queue[j]);
                vtnVEC2 p2 = vtnRender(tri_queue[j + 1]);
                vtnVEC2 p3 = vtnRender(tri_queue[j + 2]);
                vtnDrawTriangle(p1, p2, p3, tris[i].color * light_dp);
            }
        }
    }
}

void vtnInitRenderer(vtnCAMERA &camera, vtnVEC2 view_port) {
    vtnUpadateCameraRot(camera, camera.rot);
    vtn_view_port = view_port;
    vtn_camera_pos = camera.pos;
    vtn_near_plane = camera.z_near;

    vtn_projection_mat = vtnMAT4X4(0);
    vtn_projection_mat.v[0][0] = (view_port.y / view_port.x) * (1 / tan(camera.fov * 0.5));
    vtn_projection_mat.v[1][1] = 1 / tan(camera.fov * 0.5);
    vtn_projection_mat.v[2][2] = camera.z_far / (camera.z_far - camera.z_near);
    vtn_projection_mat.v[3][2] = (-camera.z_far * camera.z_near) / (camera.z_far - camera.z_near);
    vtn_projection_mat.v[2][3] = 1;
}