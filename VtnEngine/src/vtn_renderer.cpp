#include <cmath>

#include "vtn_renderer.hpp"
#include "vtn_types.hpp"
#include "vtn_window.hpp"

vtnMAT3X3 vtn_to_camera_mat;

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

vtnVEC2 vtnRender(vtnVEC3 p) {
    if (p.z == 0) {
        p.z = 0.0001f;
    }
    return vtnVEC2(VTN_WIDTH * (p.x + 0.75f * p.z) / (1.5f * p.z), VTN_HEIGHT * (0.75f * p.z - p.y) / (1.5f * p.z));
}

void vtnInitRenderer() {
    
}