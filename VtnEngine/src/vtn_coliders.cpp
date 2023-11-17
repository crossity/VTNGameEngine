#include "vtn_types.hpp"
#include "vtn_coliders.hpp"

bool is_colide(vtnNODE *n1, vtnNODE *n2) {
    int proj_colision_count = 0;

    if (n1->l_colider.x >= n2->l_colider.x && n1->r_colider.x <= n2->r_colider.x)
        proj_colision_count++;
    if (n1->l_colider.y >= n2->l_colider.y && n1->r_colider.y <= n2->r_colider.y)
        proj_colision_count++;
    if (n1->l_colider.z >= n2->l_colider.z && n1->r_colider.z <= n2->r_colider.z)
        proj_colision_count++;

    if (proj_colision_count >= 2)
        return true;
    else
        return false;
}