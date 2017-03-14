#include "geometryUtils.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include "utils.h"

template struct lm::tmat4<float>;
template struct lm::tvec4<float>;
template struct lm::tvec3<float>;
template struct lm::tvec2<float>;
template struct lm::tquat<float>;

bool intersectionLinePlane(lm::vec3 &out, const Line &line, const Plane &plane) {
	const auto u = line.end - line.start;
	const auto w = line.start - plane.position;
	const auto ndotu = lm::dot(plane.normal, u);
	if (ndotu == 0)
		return false;
	const auto ndotw = lm::dot(plane.normal, w);
	const auto si = -1.0f * ndotw / ndotu;
	if (si < 0 || si > 1) {
		return false;
	}
	out = line.start + u * si;
	return true;
}
bool intersectionTrianglePlane(Line &out, const Triangle &triangle, const Plane &plane) {
	lm::vec3 intersectionPos1, intersectionPos2, intersectionPos3;
	bool isIntersection1 = intersectionLinePlane(intersectionPos1, Line{ triangle.position1, triangle.position2 }, plane);
	bool isIntersection2 = intersectionLinePlane(intersectionPos2, Line{ triangle.position1, triangle.position3 }, plane);
	uint32_t nrOfIntersection = uint32_t(isIntersection1) + uint32_t(isIntersection2);
	if (nrOfIntersection == 0)
		return false;
	bool isIntersection3 = intersectionLinePlane(intersectionPos3, Line{ triangle.position2, triangle.position3 }, plane);
	nrOfIntersection += uint32_t(isIntersection3);
	if (nrOfIntersection != 2)
		return false;
	if (isIntersection1) {
		out.start = intersectionPos1;
		out.end = isIntersection2 ? intersectionPos2 : intersectionPos3;
	}
	else {
		out.start = intersectionPos2;
		out.end = intersectionPos3;
	}
	return true;
}
std::vector<lm::vec3> intersectionMeshPlane(const std::vector<lm::vec3> &vertices, const Plane &plane) {
	std::vector<lm::vec3> res;
	auto p = lm::dot(plane.position, plane.normal);

	for (uint32_t i = 0; i < vertices.size(); i += 3) {
		auto d0 = lm::dot(vertices[i], plane.normal) - p;
		auto d1 = lm::dot(vertices[i + 1], plane.normal) - p;
		auto d2 = lm::dot(vertices[i + 2], plane.normal) - p;
		// No intersection if all points are on same side of plane
		if ((d0 > 0 && d1 > 0 && d2 > 0) || (d0 < 0 && d1 < 0 && d2 < 0))
			continue;
		Line intersectionLine;
		auto isTriangleIntersecting = intersectionTrianglePlane(
			intersectionLine,
			Triangle{ vertices[i], vertices[i + 1], vertices[i + 2] },
			plane);
		if (isTriangleIntersecting) {
			res.push_back(intersectionLine.start);
			res.push_back(intersectionLine.end);
		}
	}
	return res;
}

std::vector<bool> intersectionPlaneSpheres(const Plane &plane, const std::vector<lm::vec3> &centerPositions, const std::vector<float> &sphereRadius) {
	assert(centerPositions.size() == sphereRadius.size());
	std::vector<bool> res;
	res.reserve(centerPositions.size());
	auto normalLength = length(plane.normal);
	assert(normalLength > (1.0 - 1e-5) && normalLength < (1.0 + 1e-5));

	auto planeDistance = lm::dot(plane.position, plane.normal);
	for (uint32_t i = 0; i < sphereRadius.size(); i++) {
		auto distance = lm::dot(centerPositions[i], plane.normal) - planeDistance;
		res.push_back(std::abs(distance) <= sphereRadius[i]);
	}
	return res;
}
bool getPlanePointerPosition(lm::vec3 &out, const lm::vec2 &mousePos, const Plane &plane, const lm::mat4 &viewMatrix, const lm::mat4 &projectionMatrix, const lm::vec4 &viewPort) {
	auto winX = mousePos.x * viewPort.z;
	auto winY = mousePos.y * viewPort.w;
	auto startPosition = lm::unProject(lm::vec3{ winX, winY, 0 }, viewMatrix, projectionMatrix, viewPort);
	auto endPosition = lm::unProject(lm::vec3{ winX, winY, 1 }, viewMatrix, projectionMatrix, viewPort);

	return intersectionLinePlane(out, Line{ startPosition, endPosition }, plane);
}

lm::vec3 getScreenPositionFromWorldPosition(const lm::vec3 &position, const lm::mat4 &viewMatrix, const lm::mat4 &projectionMatrix, const lm::vec4 &viewPort) {
	return lm::project(position, viewMatrix, projectionMatrix, viewPort);
}
float calculateRadiusForMesh(const std::vector<lm::vec3> &vertices, const lm::vec3 &center) {
	float maxDistance = 0.0f;
	for (uint32_t i = 0; i < vertices.size(); i++) {
		float distance = lm::distance(vertices[i], center);
		maxDistance = std::max(maxDistance, distance);
	}
	return maxDistance;
}

Line intersectionPlanePlane(const Plane &plane1, const Plane &plane2) {
	Line res = {};
	const auto direction = lm::cross(plane1.normal, plane2.normal);
	if (length(direction) < 1e-6)
		return res;
	auto absDirection = abs(direction);
	auto n1DotP1 = lm::dot(plane1.normal, plane1.position);
	auto n2DotP2 = lm::dot(plane2.normal, plane2.position);

	lm::vec3 position;
	if (absDirection.x >= absDirection.y && absDirection.x >= absDirection.z) {
		position = lm::vec3{
			0.f,
			(n2DotP2 * plane1.normal[2] - n1DotP1 * plane2.normal[2]) / (plane1.normal[2] * plane2.normal[1] - plane2.normal[2] * plane1.normal[1]),
			(n2DotP2 * plane1.normal[1] - n1DotP1 * plane2.normal[1]) / (plane1.normal[1] * plane2.normal[2] - plane2.normal[1] * plane1.normal[2])
		};
	}
	else if (absDirection.y >= absDirection.x && absDirection.y >= absDirection.z) {
		position = lm::vec3{
			(n2DotP2 * plane1.normal[2] - n1DotP1 * plane2.normal[2]) / (plane1.normal[2] * plane2.normal[0] - plane2.normal[2] * plane1.normal[0]),
			0,
			(n2DotP2 * plane1.normal[0] - n1DotP1 * plane2.normal[0]) / (plane1.normal[0] * plane2.normal[2] - plane2.normal[0] * plane1.normal[2])
		};
	}
	else {
		position = lm::vec3{
			(n2DotP2 * plane1.normal[1] - n1DotP1 * plane2.normal[1]) / (plane1.normal[1] * plane2.normal[0] - plane2.normal[1] * plane1.normal[0]),
			(n2DotP2 * plane1.normal[0] - n1DotP1 * plane2.normal[0]) / (plane1.normal[0] * plane2.normal[1] - plane2.normal[0] * plane1.normal[1]),
			0
		};
	}
	res.start = position;
	res.end = position + direction;
	return res;
}

lm::vec3 geometricCenter(const std::vector<lm::vec3> &vertices) {
	assert(vertices.size() >= 1);
	lm::vec3 min = vertices[0], max = vertices[0];
	for (uint32_t i = 1; i < vertices.size(); ++i) {
		for (int j = 0; j < 3; j++) {
			min[j] = std::min(min[j], vertices[i][j]);
			max[j] = std::max(max[j], vertices[i][j]);
		}
	}
	return (max + min) / 2.0f;
}
float distancePointFromCircle(const lm::vec3 &point, const lm::vec3 &center, float radius) {
	return std::abs(radius - lm::distance(point, center));
}
float distancePointToLine(const lm::vec3 &point, const Line &line) {
	auto distance = lm::distance(line.start, line.end);
	if (distance == 0) return 0.f;
	auto pointToLine = point - line.start;
	auto lineVec = line.end - line.start;
	auto t = lm::dot(pointToLine, lineVec);
	return t / (distance*distance);
}

std::vector<lm::vec3> getBeamCountourInPatientCoordinates(const BeamData &beamData, float cut) {
	auto distanceFromIso = beamData.sourceAxisDistances * (1.0f - cut);

	auto v0 = lm::vec3{ beamData.jaw.minx * cut, beamData.jaw.maxy * cut, distanceFromIso };
	auto v1 = lm::vec3{ beamData.jaw.maxx * cut, beamData.jaw.maxy * cut, distanceFromIso };
	auto v2 = lm::vec3{ beamData.jaw.maxx * cut, beamData.jaw.miny * cut, distanceFromIso };
	auto v3 = lm::vec3{ beamData.jaw.minx * cut, beamData.jaw.miny * cut, distanceFromIso };

	const uint32_t vertexArraySize = 4;
	lm::vec3 vertexArrayCloseToSource[vertexArraySize] = { v0, v1, v2, v3 };

	auto d = beamData.sourceAxisDistances;
	v0 = lm::vec3{ beamData.jaw.minx * 2.0f, beamData.jaw.maxy * 2.0f, -d };
	v1 = lm::vec3{ beamData.jaw.maxx * 2.0f, beamData.jaw.maxy * 2.0f, -d };
	v2 = lm::vec3{ beamData.jaw.maxx * 2.0f, beamData.jaw.miny * 2.0f, -d };
	v3 = lm::vec3{ beamData.jaw.minx * 2.0f, beamData.jaw.miny * 2.0f, -d };


	lm::vec3 vertexArrayIso[vertexArraySize] = { v0, v1, v2, v3 };

	const uint32_t beamContourSize = vertexArraySize * 6;
	lm::vec3 beamContourArray[vertexArraySize * 6] = {};
	for (uint32_t k = 0; k < vertexArraySize - 1; k++) {
		beamContourArray[k * 6] = vertexArrayCloseToSource[k];
		beamContourArray[k * 6 + 1] = vertexArrayCloseToSource[k + 1];
		beamContourArray[k * 6 + 2] = vertexArrayIso[k];

		beamContourArray[k * 6 + 3] = vertexArrayIso[k];
		beamContourArray[k * 6 + 4] = vertexArrayIso[k + 1];
		beamContourArray[k * 6 + 5] = vertexArrayCloseToSource[k + 1];
	}
	auto last = vertexArraySize - 1;
	beamContourArray[last * 6] = vertexArrayCloseToSource[last];
	beamContourArray[last * 6 + 1] = vertexArrayCloseToSource[0];
	beamContourArray[last * 6 + 2] = vertexArrayIso[last];

	beamContourArray[last * 6 + 3] = vertexArrayIso[0];
	beamContourArray[last * 6 + 4] = vertexArrayIso[last];
	beamContourArray[last * 6 + 5] = vertexArrayCloseToSource[0];

	auto patientToBeamMatrix = getPatientToBeamMatrix(beamData.patientOrientation, beamData.gantryAngle, beamData.couchAngle, beamData.collimatorAngle, beamData.isocenterPosition);
	std::vector<lm::vec3> res;
	res.reserve(beamContourSize);
	for (int i = 0; i < beamContourSize; i++) {
		auto v4 = lm::vec4{ beamContourArray[i][0], beamContourArray[i][1], beamContourArray[i][2], 1.0f };
		auto v = patientToBeamMatrix * v4;
		res.push_back(lm::vec3{ v[0], v[1], v[2] });
	}
	return res;
}


lm::vec3 getPatientOrientationAngles(const std::string &patientOrientation) {
	lm::vec3 res = {};
	if (patientOrientation == "HFS")
		res = { 0.0f, 0.0f, 0.0f };
	else if (patientOrientation == "HFP")
		res = { 0.0f, 0.0f, float(PI) };
	else if (patientOrientation == "FFS")
		res = { 0.0f, float(PI), 0.0f };
	else if (patientOrientation == "FFP")
		res = { float(PI), 0.0f, 0.0f };
	else if (patientOrientation == "HFDL")
		res = { 0.0f, 0.0f, float(PI) / 2.0f };
	else if (patientOrientation == "HFDR")
		res = { 0.0f, 0.0f, 3.0f * float(PI) / 2.0f };
	else if (patientOrientation == "FFDL")
		res = { float(PI), 0.0f, 3 * float(PI) / 2.0f };
	else if (patientOrientation == "FFDR")
		res = { float(PI), 0.0f, float(PI) / 2.0f };
	else if (patientOrientation == "none")
		res = { 0.0f, 0.0f, 0.0f };
	else
		assert(false && "patient orientation is not supported");
	return res;
}
lm::quat getPatientOrientationRotation(const std::string &patientOrientation) {
	auto euler_xyz = getPatientOrientationAngles(patientOrientation);
	auto quat = lm::quat_identity<float>();
	quat = lm::rotateX(quat, euler_xyz[0]);
	quat = lm::rotateY(quat, euler_xyz[1]);
	quat = lm::rotateZ(quat, euler_xyz[2]);
	return lm::quat{};
}

// eic to dicom: a rotation of 90° in the negative direction (ccw) about the x-axis must be performed.
// The beam system is identical to the beam limiting device system
// except the origin is at the isocenter instead of at the beam source.
// PatientSystem -> TableTopSystem -> TableTopEccentricRotationSystem -> PatientSupport -> FixedReference -> GantrySystem -> BeamLimitingDevice
lm::mat4 getPatientToBeamMatrix(const std::string &patientOrientation, const float gantryAngle, const float couchAngle, const float collimatorAngle, const lm::vec3 &isoCenter) {
	auto rotation = getPatientOrientationRotation(patientOrientation);
	auto dest = isoCenter * -1.0;

	auto quatMat = lm::toMatrix(rotation);
	quatMat * lm::vec4{ dest.x, dest.y, dest.z, 1.0 };
	auto q = lm::quat_identity<float>();
	auto q1 = lm::rotateX(q, -float(PI) * 0.5f); // IEC to DICOM
	auto q2 = lm::rotateY(q, collimatorAngle * float(PI) / 180.0f);
	auto q3 = lm::rotateZ(q, -gantryAngle * float(PI) / 180.0f);
	auto q4 = lm::rotateY(q, -couchAngle * float(PI) / 180.0f);

	q = q1 * q2;
	q2 = q * q3;
	q1 = q2 * q4;
	auto m = lm::toMatrix<float>(q1);

	return quatMat * m;
}

std::vector<lm::vec3> createCubeMesh(const lm::vec3 &minCorner, const lm::vec3 &maxCorner) {
	lm::vec3 cubePoints[] = {
		lm::vec3{-1, +1, -1},
		lm::vec3{+1, +1, -1},
		lm::vec3{-1, +1, +1},
		lm::vec3{+1, +1, +1},
		lm::vec3{-1, -1, -1},
		lm::vec3{+1, -1, -1},
		lm::vec3{-1, -1, +1},
		lm::vec3{+1, -1, +1}
	};
	for (auto &point : cubePoints) {
		for (int i = 0; i < 3; i++) {
			point[i] = reinterval(point[i], -1, 1, minCorner[i], maxCorner[i]);
		}
	}
	const lm::ivec3 cubeFaces[] = {
		lm::ivec3{0, 6, 2}, lm::ivec3{0, 4, 6}, // left side
		lm::ivec3{3, 5, 1}, lm::ivec3{3, 7, 5}, // right side
		lm::ivec3{0, 3, 1}, lm::ivec3{0, 2, 3}, // top side
		lm::ivec3{6, 5, 7}, lm::ivec3{6, 4, 5}, // bottom side
		lm::ivec3{2, 7, 3}, lm::ivec3{2, 6, 7}, // front side
		lm::ivec3{1, 4, 0}, lm::ivec3{1, 5, 4}  // back side
	};
	std::vector<lm::vec3> res;
	for (const auto &face : cubeFaces) {
		lm::vec3 v0 = cubePoints[face.x];
		lm::vec3 v1 = cubePoints[face.y];
		lm::vec3 v2 = cubePoints[face.z];
		res.push_back(v0);
		res.push_back(v1);
		res.push_back(v2);
	}
	return res;
}

std::vector<lm::vec3> createTriangleMeshFromIntersectionPoints(const std::vector<lm::vec3> &points) {
	auto center = geometricCenter(points);
	std::vector<lm::vec3> triangles;
	triangles.reserve(points.size() / 2 * 3);
	for (uint32_t i = 0; i < points.size(); i+=2) {
		triangles.push_back(points[i]);
		triangles.push_back(points[i+1] );
		triangles.push_back(center);
	}
	return triangles;
}