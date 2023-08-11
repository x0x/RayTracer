#include "vec3.h"


class Sphere {
    private:
        point3 centre;
        double radius;

    public:
        Sphere (point3 m_centre , double m_radius) {
            centre = m_centre;
            radius = m_radius;
        }
};