#include"collision.h"


float collision::distancePointTriangle(const vector3d& p, const vector3d& a, const vector3d& b, const vector3d& c)
{
     vector3d ab = b - a;
    vector3d ac = c - a;
    vector3d n = ab.crossproduct(ac);
    n.normalize();

    // projection du point sur le plan
    float distPlane = (p - a).dotproduct(n);
    vector3d proj = p - n * distPlane;

    // vecteurs pour les coordonnées barycentriques
    vector3d v0 = b - a;
    vector3d v1 = c - a;
    vector3d v2 = proj - a;

    float d00 = v0.dotproduct(v0);
    float d01 = v0.dotproduct(v1);
    float d11 = v1.dotproduct(v1);
    float d20 = v2.dotproduct(v0);
    float d21 = v2.dotproduct(v1);

    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;

    // si le point projeté est dans le triangle
    if (u >= 0 && v >= 0 && w >= 0)
        return fabs(distPlane);

    // sinon, distance minimale au bord du triangle
    float distsq = (closestPointOnSegment(p, a, b) - p).length();
    distsq = std::min(distsq, (closestPointOnSegment(p, b, c) - p).length());
    distsq = std::min(distsq, (closestPointOnSegment(p, c, a) - p).length());

    return sqrt(distsq);
}

// Projection d’un point sur un segment
vector3d collision::closestPointOnSegment(const vector3d& p, const vector3d& a, const vector3d& b) {
    vector3d ab = b - vector3d(a.x,a.y,a.z);
    float t = ab.dotproduct(p - a) / ab.dotproduct(ab);
    t = std::max(0.0f, std::min(1.0f, t));
    return a + ab * t;
}

// Test barycentrique point dans triangle
bool collision::pointInTriangle(const vector3d& p, const vector3d& a, const vector3d& b, const vector3d& c) {
    vector3d v0 = b - a;
    vector3d v1 = c - a;
    vector3d v2 = p - a;

    float d00 = v0.dotproduct(v0);
	float d01 = v0.dotproduct(v1);
	float d11 = v1.dotproduct(v1);
	float d20 = v2.dotproduct(v0);
	float d21 = v2.dotproduct(v1);
    float denom = d00*d11 - d01*d01;
    if (fabs(denom) < EPS) return false;
    float v = (d11*d20 - d01*d21) / denom;
    float w = (d00*d21 - d01*d20) / denom;
    float u = 1.0f - v - w;
    return (u >= -1e-4f && v >= -1e-4f && w >= -1e-4f);
}


float collision::raycastDown(const vector3d& origin, const std::vector<CollisionTriangle>& mesh) {
    float closestY = -FLT_MAX;
    vector3d dir(0, -1, 0);

    for (const auto& tri : mesh)
    {
        vector3d N = (tri.v1 - tri.v0).crossproduct(tri.v2 - tri.v0);
        float denom = N.dotproduct(dir);
        if (fabs(denom) < 1e-6f) continue;

        float t = (tri.v0 - origin).dotproduct(N) / denom;
        if (t < 0) continue;

        vector3d P = origin + dir * t;

        if (pointInTriangle(P, tri.v0, tri.v1, tri.v2))
        {
            // On ne prend que les points **sous l’origine**
            if (P.y <= origin.y && P.y > closestY)
                closestY = P.y;
        }
    }

    return closestY; // -FLT_MAX si aucun hit sous l’origine
}


bool collision::intersectRayTriangle(
    const vector3d& rayOrigin,
    const vector3d& rayDir,
    const CollisionTriangle& tri,
    float& t
) {
    const float EPSILON = 1e-6f;
    vector3d edge1 = tri.v1 - tri.v0;
    vector3d edge2 = tri.v2 - tri.v0;

    vector3d h = rayDir.crossproduct(edge2);
    float a = edge1.dotproduct(h);

    if (fabs(a) < EPSILON) return false; // Rayon parallèle au triangle

    float f = 1.0f / a;
    vector3d s = rayOrigin - tri.v0;
    float u = f * s.dotproduct(h);

    if (u < 0.0f || u > 1.0f) return false;

    vector3d q = s.crossproduct(edge1);
    float v = f * rayDir.dotproduct(q);

    if (v < 0.0f || u + v > 1.0f) return false;

    // Calcul de t (distance le long du rayon)
    t = f * edge2.dotproduct(q);

    if (t > EPSILON) {
        return true; // Intersection trouvée
    }

    return false;
}

bool collision::collideSphereTriangle(Sphere& sph, const CollisionTriangle& tri) {
    vector3d N = (tri.v1 - tri.v0).crossproduct(tri.v2 - tri.v0);
    float nlen = N.length();
    if (nlen < EPS) return false; // Triangle dégénéré
    N = N / nlen;

    // S'assurer que la normale pointe vers le haut (y positif)
    if (N.y < 0) N = vector3d(-N.x,-N.y,-N.z);

    // Distance du centre de la sphère au plan du triangle
    float dist = (sph.center - tri.v0).dotproduct(N);

    // Projection du centre sur le plan
    vector3d proj = sph.center - N * dist;

    bool collided = false;

    // Si la projection est à l'intérieur du triangle
    if (pointInTriangle(proj, tri.v0, tri.v1, tri.v2)) {
        if (dist < sph.radius) {
            float penetration = sph.radius - dist;
            sph.center += N * penetration; // Toujours pousser vers le haut
            collided = true;
        }
    } else {
        // Collision avec les arêtes ou sommets
        float bestDist = 1e9f;
        vector3d bestPoint;

        vector3d pts[3] = {
            closestPointOnSegment(sph.center, tri.v0, tri.v1),
            closestPointOnSegment(sph.center, tri.v1, tri.v2),
            closestPointOnSegment(sph.center, tri.v2, tri.v0)
        };

        for (int i = 0; i < 3; i++) {
            float d = (sph.center - pts[i]).length();
            if (d < bestDist) {
                bestDist = d;
                bestPoint = pts[i];
            }
        }

        if (bestDist < sph.radius) {
            float penetration = sph.radius - bestDist;
            vector3d dir = sph.center - bestPoint;
            if (dir.length() < EPS) dir = N; else dir.normalize();
            sph.center += dir * penetration;
            collided = true;
        }
    }

    return collided;
}

bool collision::collideSphereMesh(Sphere& sph, const std::vector<CollisionTriangle>& mesh) {
    bool hit = false;
    for (const CollisionTriangle& tri : mesh) {
        if (collideSphereTriangle(sph, tri)) hit = true;
    }
    return hit;
}

