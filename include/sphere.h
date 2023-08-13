#include "ray.h"
#include "vec3.h"
#include "hittable.h"

class Sphere : public hittable{
private:
  point3 centre;
  double radius;

public:
  Sphere(point3 m_centre, double m_radius) {
    centre = m_centre;
    radius = m_radius;
  }

  double hitSphere(const point3 &centre, double &radius, const ray &r) {
    vec3 centreToOrigin = r.origin() - centre;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(r.direction(), centreToOrigin);
    auto c = dot(centreToOrigin, centreToOrigin) - radius * radius;
    auto discriminant = b * b - 4.0*a*c;

    if(discriminant < 0) {
        return -1;
    } else {
        return (-b - sqrt(discriminant) ) / (2.0 * a);
    }
  }
};