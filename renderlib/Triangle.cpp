#include "Triangle.h"

// ⃗p = ⃗a + β(⃗b −⃗a) + γ(⃗c −⃗a)

// ⃗p(α, β, γ) = α⃗a + β⃗b + γ⃗c

bool Triangle::hit(const Ray &r, double ray_tmin, double ray_tmax, HitRecord &hitRecord) const {
  // Using the Möller–Trumbore intersection algorithm
  // Set up all the necessary variables
  float _a = a.x() - b.x(),
        _b = a.y() - b.y(),
        _c = a.z() - b.z(),
        _d = a.x() - c.x(),
        _e = a.y() - c.y(),
        _f = a.z() - c.z(),
        _g = r.direction().x(),
        _h = r.direction().y(),
        _i = r.direction().z(),
        _j = a.x() - r.origin().x(),
        _k = a.y() - r.origin().y(),
        _l = a.z() - r.origin().z();
  // Combine units
  float _eihf = _e * _i - _h * _f,
        _gfdi = _g * _f - _d * _i,
        _dheg = _d * _h - _e * _g,
        _akjb = _a * _k - _j * _b,
        _jcal = _j * _c - _a * _l,
        _blkc = _b * _l - _k * _c;

  // Calculate the determinant
  float M = (_a * _eihf) + (_b * _gfdi) + (_c * _dheg);

  // Calculate ray parameter & ensure it's in range
  float t = -(_f * _akjb + _e * _jcal + _d * _blkc) / M;
  if (t < ray_tmin || t > ray_tmax)
    return false;

  // Calculate barycentric coordinates & ensure they're in range
  // Calculate gamma
  float gamma = (_i * _akjb + _h * _jcal + _g * _blkc) / M;
  if (gamma < 0.0f || gamma > 1.0f)
    return false;

  // Calculate beta
  float beta = (_j * _eihf + _k * _gfdi + _l * _dheg) / M;
  if (beta < 0.0f || beta > 1.0f - gamma)
    return false;

  // Set the hit record
  hitRecord.point = r.at(t);
  hitRecord.normal = cross((b - a), (c - a)).normalized();
  hitRecord.t = t;

  return true;
}
