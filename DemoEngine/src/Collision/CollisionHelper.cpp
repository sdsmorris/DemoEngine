#include "CollisionHelper.h"
#include <iostream>
#include <vector>

/*CollisionInfo CollisionHelper::isAABBInsideAABB(glm::vec3 aMin, glm::vec3 aMax, glm::vec3 bMin, glm::vec3 bMax)
{
	return CollisionInfo((aMin.x <= bMax.x && aMax.x >= bMin.x) && (aMin.y <= bMax.y && aMax.y >= bMin.y) && (aMin.z <= bMax.z && aMax.z >= bMin.z));
}*/

CollisionInfo CollisionHelper::isAABBInsideAABB(glm::vec3 aMin, glm::vec3 aMax, glm::vec3 bMin, glm::vec3 bMax)
{
	return CollisionInfo((aMin.x <= bMax.x && aMax.x >= bMin.x) && (aMin.y <= bMax.y && aMax.y >= bMin.y) && (aMin.z <= bMax.z && aMax.z >= bMin.z));
}

bool CollisionHelper::isPointInsideAABB(glm::vec3 point, glm::vec3 bboxMin, glm::vec3 bboxMax)
{
	return (point.x >= bboxMin.x && point.x <= bboxMax.x) && (point.y >= bboxMin.y && point.y <= bboxMax.y) && (point.z >= bboxMin.z && point.z <= bboxMax.z);
}

bool CollisionHelper::isSphereInsideSphere(glm::vec3 sphere, float sphereRadius, glm::vec3 otherSphere, float otherSphereRadius)
{
	float dist = glm::sqrt((sphere.x - otherSphere.x) * (sphere.x - otherSphere.x) + (sphere.y - otherSphere.y) * (sphere.y - otherSphere.y) + (sphere.z - otherSphere.z) * (sphere.z - otherSphere.z));
	return dist <= (sphereRadius + otherSphereRadius);
}

bool CollisionHelper::isPointInsideSphere(glm::vec3 point, glm::vec3 sphere, float radius)
{
	float distance = glm::sqrt((point.x - sphere.x) * (point.x - sphere.x) + (point.y - sphere.y) * (point.y - sphere.y) + (point.z - sphere.z) * (point.z - sphere.z));
	return distance < radius;
}

bool CollisionHelper::isSphereInsideAABB(glm::vec3 sphere, float radius, glm::vec3 bboxMin, glm::vec3 bboxMax)
{
	float x = glm::max(bboxMin.x, glm::min(sphere.x, bboxMax.x));
	float y = glm::max(bboxMin.y, glm::min(sphere.y, bboxMax.y));
	float z = glm::max(bboxMin.z, glm::min(sphere.z, bboxMax.z));
	float distance = glm::sqrt((x - sphere.x) * (x - sphere.x) + (y - sphere.y) * (y - sphere.y) + (z - sphere.z) * (z - sphere.z));
	return distance < radius;
}

bool SATTriangleAABBCheck(glm::vec3 axis, glm::vec3 bboxMin, glm::vec3 bboxMax, glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3)
{
	//Dot triangle vertices
	float triVert1 = glm::dot(axis, tri1);
	float triVert2 = glm::dot(axis, tri2);
	float triVert3 = glm::dot(axis, tri3);

	float triMin = glm::min(glm::min(triVert1, triVert2), triVert3);
	float triMax = glm::max(glm::max(triVert1, triVert2), triVert3);

	//Dot cube vertices
	float v1 = glm::dot(axis, glm::vec3(bboxMin.x, bboxMin.y, bboxMin.z));
	float v2 = glm::dot(axis, glm::vec3(bboxMax.x, bboxMax.y, bboxMax.z));
	float v3 = glm::dot(axis, glm::vec3(bboxMax.x, bboxMax.y, bboxMin.z));
	float v4 = glm::dot(axis, glm::vec3(bboxMax.x, bboxMin.y, bboxMax.z));
	float v5 = glm::dot(axis, glm::vec3(bboxMax.x, bboxMin.y, bboxMin.z));
	float v6 = glm::dot(axis, glm::vec3(bboxMin.x, bboxMax.y, bboxMax.z));
	float v7 = glm::dot(axis, glm::vec3(bboxMin.x, bboxMin.y, bboxMax.z));
	float v8 = glm::dot(axis, glm::vec3(bboxMin.x, bboxMax.y, bboxMin.z));

	float aabbMin = glm::min(glm::min(glm::min(glm::min(glm::min(glm::min(glm::min(v1, v2), v3), v4), v5), v6), v7) ,v8);
	float aabbMax = glm::max(glm::max(glm::max(glm::max(glm::max(glm::max(glm::max(v1, v2), v3), v4), v5), v6), v7), v8);

	if (triMin < aabbMax && triMin > aabbMin)
		return true;
	if (triMax < aabbMax && triMax > aabbMin)
		return true;
	if (aabbMin < triMax && aabbMin > triMin)
		return true;
	if (aabbMax < triMax && aabbMax > triMin)
		return true;

	return false;
}

glm::vec3 CalcSurfaceNormal(glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3); //for aabb-tri func below

bool CollisionHelper::isAABBIntersectingTriangle(glm::vec3 bboxMin, glm::vec3 bboxMax, glm::vec3 tri1, glm::vec3 tri2,  glm::vec3 tri3)
{	//We swapped blenders XYZ so we may need to swap normal positions as well
	//If we rotate we need to recalculate the normals

	//1. We need to get all the axis' to check against
	//Axes to check against are:
	//three face normals of AABB, since its axis aligned we know (1, 0, 0), (0, 1, 0), and (0, 0, 1)
	//triangle face normal
	//Nine axes given the cross products of the combination of edges from both

	std::vector<glm::vec3> axes;
	//AABB face normals
	glm::vec3 axis1(1, 0, 0);
	glm::vec3 axis2(0, 1, 0);
	glm::vec3 axis3(0, 0, 1);

	//Triangle face normals
	glm::vec3 axis4 = CalcSurfaceNormal(tri1, tri2, tri3);

	glm::vec3 e1 = tri2 - tri1;
	glm::vec3 e2 = tri3 - tri1;
	glm::vec3 e3 = tri3 - tri2;
	glm::vec3 e4 = glm::vec3(bboxMax.x, bboxMax.y, bboxMax.z) - glm::vec3(bboxMin.x, bboxMax.y, bboxMax.z);
	glm::vec3 e5 = glm::vec3(bboxMax.x, bboxMax.y, bboxMax.z) - glm::vec3(bboxMax.x, bboxMin.y, bboxMax.z);
	glm::vec3 e6 = glm::vec3(bboxMax.x, bboxMax.y, bboxMax.z) - glm::vec3(bboxMax.x, bboxMax.y, bboxMin.z);

	//Cross products of each edge
	glm::vec3 axis5 = glm::cross(e1, e4);
	if (axis5 != glm::vec3(0, 0, 0)) { axis5 = glm::normalize(axis5); axes.push_back(axis5); }
	glm::vec3 axis6 = glm::cross(e1, e5);
	if (axis6 != glm::vec3(0, 0, 0)) { axis6 = glm::normalize(axis6); axes.push_back(axis6); }
	glm::vec3 axis7 = glm::cross(e1, e6);
	if (axis7 != glm::vec3(0, 0, 0)) { axis7 = glm::normalize(axis7); axes.push_back(axis7); }
	glm::vec3 axis8 = glm::cross(e2, e4);
	if (axis8 != glm::vec3(0, 0, 0)) { axis8 = glm::normalize(axis8); axes.push_back(axis8); }
	glm::vec3 axis9 = glm::cross(e2, e5);
	if (axis9 != glm::vec3(0, 0, 0)) { axis9 = glm::normalize(axis9); axes.push_back(axis9); }
	glm::vec3 axis10 = glm::cross(e2, e6);
	if (axis10 != glm::vec3(0, 0, 0)) { axis10 = glm::normalize(axis10); axes.push_back(axis10); }
	glm::vec3 axis11 = glm::cross(e3, e4);
	if (axis11 != glm::vec3(0, 0, 0)) { axis11 = glm::normalize(axis11); axes.push_back(axis11); }
	glm::vec3 axis12 = glm::cross(e3, e5);
	if (axis12 != glm::vec3(0, 0, 0)) { axis12 = glm::normalize(axis12); axes.push_back(axis12); }
	glm::vec3 axis13 = glm::cross(e3, e6);
	if (axis13 != glm::vec3(0, 0, 0)) { axis13 =  glm::normalize(axis13); axes.push_back(axis13); }

	//std::cout << "e1 " << e1.x << " " << e1.y << " " << e1.z << " e4 " << e4.x << " " << e4.y << " " << e4.z << "\n";
	//std::cout << "e1e4 cross " << glm::cross(e1, e4).x << " " << glm::cross(e1, e4).y << " " << glm::cross(e1, e4).z << "\n";
	//std::cout << axis5.x << " " << axis5.y << " " << axis5.z << "\n";

	for (int i = 0; i < axes.size(); i++)
		if (!SATTriangleAABBCheck(axes[i], bboxMin, bboxMax, tri1, tri2, tri3)) return false;

	//If no overlap on all axes, return they are not colliding, should work but isnt
	//if (!SATTriangleAABBCheck(axis1, bboxMin, bboxMax, tri1, tri2, tri3)) return false;	//else std::cout << "Passed axis 1\n";
	//if (!SATTriangleAABBCheck(axis2, bboxMin, bboxMax, tri1, tri2, tri3)) return false;	//else std::cout << "Passed axis 2\n";
	//if (!SATTriangleAABBCheck(axis3, bboxMin, bboxMax, tri1, tri2, tri3)) return false;	//else std::cout << "Passed axis 3\n";
	//if (!SATTriangleAABBCheck(axis4, bboxMin, bboxMax, tri1, tri2, tri3)) return false;	//else std::cout << "Passed axis 4\n";
	//if (!SATTriangleAABBCheck(axis5, bboxMin, bboxMax, tri1, tri2, tri3)) return false; //	else std::cout << "Passed axis 5\n";
	//if (!SATTriangleAABBCheck(axis6, bboxMin, bboxMax, tri1, tri2, tri3)) return false;	//else std::cout << "Passed axis 6\n";
	//if (!SATTriangleAABBCheck(axis7, bboxMin, bboxMax, tri1, tri2, tri3)) return false;	//else std::cout << "Passed axis 7\n";
	//if (!SATTriangleAABBCheck(axis8, bboxMin, bboxMax, tri1, tri2, tri3)) return false;	//else std::cout << "Passed axis 8\n";
	//if (!SATTriangleAABBCheck(axis9, bboxMin, bboxMax, tri1, tri2, tri3)) return false;	//else std::cout << "Passed axis 9\n";
	//if (!SATTriangleAABBCheck(axis10, bboxMin, bboxMax, tri1, tri2, tri3)) return false;// else std::cout << "Passed axis 10\n";
	//if (!SATTriangleAABBCheck(axis11, bboxMin, bboxMax, tri1, tri2, tri3)) return false;// else std::cout << "Passed axis 11\n";
	//if (!SATTriangleAABBCheck(axis12, bboxMin, bboxMax, tri1, tri2, tri3)) return false;// else std::cout << "Passed axis 12\n";
	//if (!SATTriangleAABBCheck(axis13, bboxMin, bboxMax, tri1, tri2, tri3)) return false;// else std::cout << "Passed axis 13\n";

	return true;
}

bool CollisionHelper::isSphereIntersectingTriangle(glm::vec3 sphere, float radius, glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3)
{
	float dist1 = glm::sqrt((sphere.x - tri1.x) * (sphere.x - tri1.x) + (sphere.y - tri1.y) * (sphere.y - tri1.y) + (sphere.z - tri1.z) * (sphere.z - tri1.z));
	float dist2 = glm::sqrt((sphere.x - tri2.x) * (sphere.x - tri2.x) + (sphere.y - tri2.y) * (sphere.y - tri2.y) + (sphere.z - tri2.z) * (sphere.z - tri2.z));
	float dist3 = glm::sqrt((sphere.x - tri3.x) * (sphere.x - tri3.x) + (sphere.y - tri3.y) * (sphere.y - tri3.y) + (sphere.z - tri3.z) * (sphere.z - tri3.z));
	float closestDist = glm::min(glm::min(dist1, dist2), dist3);
	/* return closestDist < radius;*/
	glm::vec3 v;
	if (closestDist == dist1)
		v = tri1 - sphere;
	else if (closestDist == dist2)
		v = tri2 - sphere;
	else if (closestDist == dist3)
		v = tri3 - sphere;
	else
		std::cout << "SOMETHING IS WRONG WITH THE SPHERE TO TRIANGLE DETECTION" << "\n";
	return glm::dot(v, v) <= radius * radius;
}

glm::vec3 CalcSurfaceNormal(glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3)
{
	//Subtracts each coordinate respectively
	//glm::vec3 u(tri2.x - tri1.x, tri2.y - tri1.y, tri2.z - tri1.z);
	//glm::vec3 v(tri3.x - tri1.x, tri3.y - tri1.y, tri3.z - tri1.z);
	glm::vec3 u = tri2 - tri1;
	glm::vec3 v = tri3 - tri1;

	//This computes the cross product of the edges
	//glm::vec3 normal((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z), (u.x * v.y) - (u.y * v.x));
	glm::vec3 nrmcross = glm::normalize(glm::cross(u, v));
	//Normalizing gives correct vector axis, 1 and negative 1, x and y components are small floating point error
	//nrmcross = glm::normalize(nrmcross);
	//std::cout << "NormalCrs " << nrmcross.x << " " << nrmcross.y << " " << nrmcross.z << "\n";
	return nrmcross;
}

bool SATTriangleCheck(glm::vec3 axis, glm::vec3 tri1vert1, glm::vec3 tri1vert2, glm::vec3 tri1vert3, glm::vec3 tri2vert1, glm::vec3 tri2vert2, glm::vec3 tri2vert3)
{

	//Dot each vertex with the axis and get the min and max, then check if they are inside each other?
	float t1v1 = glm::dot(axis, tri1vert1);
	float t1v2 = glm::dot(axis, tri1vert2);
	float t1v3 = glm::dot(axis, tri1vert3);
	float t2v1 = glm::dot(axis, tri2vert1);
	float t2v2 = glm::dot(axis, tri2vert2);
	float t2v3 = glm::dot(axis, tri2vert3);

	float t1min = glm::min(t1v1, glm::min(t1v2, t1v3));
	float t1max = glm::max(t1v1, glm::max(t1v2, t1v3));
	float t2min = glm::min(t2v1, glm::min(t2v2, t2v3));
	float t2max = glm::max(t2v1, glm::max(t2v2, t2v3));


	if ((t1min < t2max && t1min > t2min) || (t1max < t2max && t1max > t2min))
			return true;
	if ((t2min < t1max && t2min > t1min) || (t2max < t1max && t2max > t1min))
			return true;

	return false;
}

bool CollisionHelper::isTriangleIntersectingTriangle(glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3, glm::vec3 otherTri1, glm::vec3 otherTri2, glm::vec3 otherTri3)
{
	//TODO: apparently moellers method is faster than this one

	//std::cout << tri1.x << " " << tri1.y << " " << tri1.z << " " << tri2.x << " " << tri2.y << " " << tri2.z << " " << tri3.x << " " << tri3.y << " " << tri3.z << "\n";
	//std::cout << otherTri1.x << " " << otherTri1.y << " " << otherTri1.z << " " << otherTri2.x << " " << otherTri2.y << " " << otherTri2.z << " " << otherTri3.x << " " << otherTri3.y << " " << otherTri3.z << "\n";
	
	std::vector<glm::vec3> axes;

	//Triangle surface normals, 2 axes to test
	glm::vec3 tri1FaceNrml = CalcSurfaceNormal(tri1, tri2, tri3);
	glm::vec3 tri2FaceNrml = CalcSurfaceNormal(otherTri1, otherTri2, otherTri3);

	glm::vec3 tri1Edge1 = tri2 - tri1;
	glm::vec3 tri1Edge2 = tri3 - tri1;
	glm::vec3 tri1Edge3 = tri3 - tri2;
	glm::vec3 tri2Edge1 = otherTri2 - otherTri1;
	glm::vec3 tri2Edge2 = otherTri3 - otherTri1;
	glm::vec3 tri2Edge3 = otherTri3 - otherTri2;

	//axes
	glm::vec3 axis1 = tri1FaceNrml;
	glm::vec3 axis2 = tri2FaceNrml;
	glm::vec3 axis3 = glm::cross(tri1Edge1, tri2Edge1);
	//std::cout << axis3.x << "\n";
	//std::cout << "nrm " <<  axis3.x << "\n";
	//NOTE: interesetingly enough, this works without normalizing the vectors, I mean it makes sense but just becareful if bugs happen take out the "axis3 = glm::normalize(axis3);"
	if (axis3 != glm::vec3(0, 0, 0)) { axis3 = glm::normalize(axis3); axes.push_back(axis3); }
	glm::vec3 axis4 = glm::cross(tri1Edge1, tri2Edge2);
	if (axis4 != glm::vec3(0, 0, 0)) { axis4 = glm::normalize(axis4); axes.push_back(axis4); }
	glm::vec3 axis5 = glm::cross(tri1Edge1, tri2Edge3);
	if (axis5 != glm::vec3(0, 0, 0)) { axis5 = glm::normalize(axis5); axes.push_back(axis5); }
	glm::vec3 axis6 = glm::cross(tri1Edge2, tri2Edge1);
	if (axis6 != glm::vec3(0, 0, 0)) { axis6 = glm::normalize(axis6); axes.push_back(axis6); }
	glm::vec3 axis7 = glm::cross(tri1Edge2, tri2Edge2);
	if (axis7 != glm::vec3(0, 0, 0)) { axis7 = glm::normalize(axis7); axes.push_back(axis7); }
	glm::vec3 axis8 = glm::cross(tri1Edge2, tri2Edge3);
	if (axis8 != glm::vec3(0, 0, 0)) { axis8 = glm::normalize(axis8); axes.push_back(axis8); }
	glm::vec3 axis9 = glm::cross(tri1Edge3, tri2Edge1);
	if (axis9 != glm::vec3(0, 0, 0)) { axis9 = glm::normalize(axis9); axes.push_back(axis9); }
	glm::vec3 axis10 = glm::cross(tri1Edge3, tri2Edge2);
	if (axis10 != glm::vec3(0, 0, 0)) { axis10 = glm::normalize(axis10); axes.push_back(axis10); }
	glm::vec3 axis11 = glm::cross(tri1Edge3, tri2Edge3);
	if (axis11 != glm::vec3(0, 0, 0)) { axis11 = glm::normalize(axis11); axes.push_back(axis11); }
	//std::cout << axis3.x << " " << axis3.y << " " << axis3.z << "\n";

	//std::cout << "TRI " << axis11.x << " " << axis11.y << " " << axis11.z << "\n";

	for (int i = 0; i < axes.size(); i++)
		if (!SATTriangleCheck(axes[i], tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false;

	//Perform SAT
	/*if (!SATTriangleCheck(axis1, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis2, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis3, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis4, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis5, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis6, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis7, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis8, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis9, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false; 
	if (!SATTriangleCheck(axis10, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false;
	if (!SATTriangleCheck(axis11, tri1, tri2, tri3, otherTri1, otherTri2, otherTri3)) return false;*/



	return true;
}
