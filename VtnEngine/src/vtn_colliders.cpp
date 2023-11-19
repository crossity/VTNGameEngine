#include "vtn_types.hpp"
#include "vtn_colliders.hpp"

bool is_collide(vtnNODE *n1, vtnNODE *n2) {
    int proj_colision_count = 0;

    if ((n1->l_collider.x >= n2->l_collider.x && n1->l_collider.x <= n2->r_collider.x) || (n1->r_collider.x >= n2->l_collider.x && n1->r_collider.x <= n2->r_collider.x))
        proj_colision_count++;
    if ((n1->l_collider.y >= n2->l_collider.y && n1->l_collider.y <= n2->r_collider.y) || (n1->r_collider.y >= n2->l_collider.y && n1->r_collider.y <= n2->r_collider.y))
        proj_colision_count++;
    if ((n1->l_collider.z >= n2->l_collider.z && n1->l_collider.z <= n2->r_collider.z) || (n1->r_collider.z >= n2->l_collider.z && n1->r_collider.z <= n2->r_collider.z))
        proj_colision_count++;

    if (proj_colision_count == 3)
        return true;
    else
        return false;
}