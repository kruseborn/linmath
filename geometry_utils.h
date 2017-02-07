#pragma once
#include "linmath_transform.h"
#include "linmath.h"

#include <vector>
#include <string>

struct Triangle {
	lm::vec3 position1, position2, position3;
};
struct Plane {
	lm::vec3 position;
	lm::vec3 normal;
};
struct Line {
	lm::vec3 start, end;
};

struct Jaw {
	float minx, maxx, miny, maxy;
};
struct BeamData {
	Jaw jaw;
	lm::vec3 isocenterPosition;
	float sourceAxisDistances;
	float gantryAngle, collimatorAngle, couchAngle;
	std::string patientOrientation;

};

#define PI 3.141592653589793238462643383279502884L

bool intersectionLinePlane(lm::vec3 &out, const Line &line, const Plane &plane);
bool intersectionTrianglePlane(Line &out, const Triangle &triangle, const Plane &plane);
Line intersectionPlanePlane(const Plane &plane1, const Plane &plane2);
std::vector<bool> intersectionPlaneSpheres(const Plane &plane, const std::vector<lm::vec3> &centerPositions, const std::vector<float> &sphereRadius);

bool getPlanePointerPosition(lm::vec3 &out, const lm::vec3 &mousePos, const Plane &plane, const lm::mat4 &viewMatrix, const lm::mat4 &projectionMatrix, const lm::vec4 &viewPort);
float calculateRadiusForMesh(const std::vector<lm::vec3> &vertices, const lm::vec3 &center);
lm::vec3 geometricCenter(const std::vector<lm::vec3> &vertices);

float distancePointFromCircle(const lm::vec3 &point, const lm::vec3 &center, float radius);
float distancePointToLine(const lm::vec3 &point, const Line &line);


int intersectionMeshPlane(const lm::vec3 *vertices, const uint32_t size, const Plane &plane);

lm::mat4 getPatientToBeamMatrix(const std::string &patientOrientation, const float gantryAngle, const float couchAngle, const float collimatorAngle, const lm::vec3 &isoCenter);
lm::quat getPatientOrientationRotation(const std::string &patientOrientation);
lm::vec3 getPatientOrientationAngles(const std::string &patientOrientation);
std::vector<lm::vec3> getBeamCountourInPatientCoordinates(const BeamData &beamData, float cut);