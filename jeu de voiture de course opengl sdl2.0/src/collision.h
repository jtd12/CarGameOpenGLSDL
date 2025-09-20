#include "vector.h"
#include <cmath>
#ifndef COLLISION_H
#define COLLISION_H
#include"objloader.h"
#include <cfloat>   // pour FLT_MAX

const float EPS = 1e-6f;



struct Triangle {
    vector3d A, B, C;
};

// Sphère (voiture simplifiée)
struct Sphere {
    vector3d center;
    float radius;
};


class collision{
	public:
		
	static bool collideSphereTriangle(Sphere& sph, const CollisionTriangle& tri);
	static	bool collideSphereMesh(Sphere& sph, const std::vector<CollisionTriangle>& mesh);
	static bool pointInTriangle(const vector3d& p, const vector3d& a, const vector3d& b, const vector3d& c);
	static vector3d closestPointOnSegment(const vector3d& p, const vector3d& a, const vector3d& b);
	static float raycastDown(const vector3d& origin, const std::vector<CollisionTriangle>& mesh);
	static float distancePointTriangle(const vector3d& p, const vector3d& a, const vector3d& b, const vector3d& c);
	static bool intersectRayTriangle(
    const vector3d& rayOrigin,
    const vector3d& rayDir,
    const CollisionTriangle& tri,
    float& t
);
/*	static bool sphereplane(vector3d& sp,const vector3d& pn,const vector3d& p1,const vector3d& p2,const vector3d& p3,const vector3d& p4, const float& r);
	static bool raysphere(const vector3d& center,const vector3d& direction,const vector3d& startpoint,const float& r);
	static bool rayplane(const vector3d& normal,const vector3d& startpoint,const vector3d& direction,const vector3d& p1,const vector3d& p2,const vector3d& p3,const vector3d& p4);
	static float trianglearea(const vector3d& p1,const vector3d& p2,const vector3d& p3);
	static bool spheresphere(const vector3d& c1,float r1,const vector3d& c2,float r2);*/
};


#endif
