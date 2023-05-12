#include "spatial/common.hpp"
#include "spatial/core/geometry/geometry.hpp"
#include "spatial/core/geometry/vertex_vector.hpp"
namespace spatial {

namespace core {

//------------------------------------------------------------------------------
// Point
//------------------------------------------------------------------------------

string Point::ToString() const {
	if (IsEmpty()) {
		return "POINT EMPTY";
	}
	auto &vert = vertices[0];
	if (std::isnan(vert.x) && std::isnan(vert.y)) {
		// This is a special case for WKB. WKB does not support empty points,
		// and instead writes a point with NaN coordinates. We therefore need to
		// check for this case and return POINT EMPTY instead to round-trip safely
		return "POINT EMPTY";
	}
	return "POINT (" + std::to_string(vertices[0].x) + " " + std::to_string(vertices[0].y) + ")";
}

bool Point::IsEmpty() const {
	return vertices.Count() == 0;
}

Vertex &Point::GetVertex() {
	return vertices[0];
}

const Vertex &Point::GetVertex() const {
	return vertices[0];
}

//------------------------------------------------------------------------------
// LineString
//------------------------------------------------------------------------------

double LineString::Length() const {
	return vertices.Length();
}

bool LineString::IsEmpty() const {
	return vertices.Count() == 0;
}

Geometry LineString::Centroid() const {
	throw NotImplementedException("Centroid not implemented for LineString");
}

string LineString::ToString() const {
	auto count = vertices.Count();
	if (count == 0) {
		return "LINESTRING EMPTY";
	}

	string result = "LINESTRING (";
	for (uint32_t i = 0; i < vertices.Count(); i++) {
		result += std::to_string(vertices[i].x) + " " + std::to_string(vertices[i].y);
		if (i < vertices.Count() - 1) {
			result += ", ";
		}
	}
	result += ")";
	return result;
}

uint32_t LineString::Count() const {
	return vertices.Count();
}


//------------------------------------------------------------------------------
// Polygon
//------------------------------------------------------------------------------

double Polygon::Area() const {
	double area = 0;
	for (uint32_t i = 0; i < num_rings; i++) {
		if (i == 0) {
			area += rings[i].SignedArea();
		} else {
			area -= rings[i].SignedArea();
		}
	}
	return std::abs(area);
}

bool Polygon::IsEmpty() const {
	return num_rings == 0;
}

double Polygon::Perimiter() const {
	if (IsEmpty()) {
		return 0;
	}
	return rings[0].Length();
}

Geometry Polygon::Centroid() const {
	throw NotImplementedException("Polygon::Centroid()");
}

string Polygon::ToString() const {

	// check if the polygon is empty
	uint32_t total_verts = 0;
	for (uint32_t i = 0; i < num_rings; i++) {
		total_verts += rings[i].Count();
	}
	if (total_verts == 0) {
		return "POLYGON EMPTY";
	}

	string result = "POLYGON (";
	for (uint32_t i = 0; i < num_rings; i++) {
		result += "(";
		for (uint32_t j = 0; j < rings[i].Count(); j++) {
			result += std::to_string(rings[i][j].x) + " " + std::to_string(rings[i][j].y);
			if (j < rings[i].Count() - 1) {
				result += ", ";
			}
		}
		result += ")";
		if (i < num_rings - 1) {
			result += ", ";
		}
	}
	result += ")";
	return result;
}

uint32_t Polygon::Count() const {
	return num_rings;
}

//------------------------------------------------------------------------------
// MultiPoint
//------------------------------------------------------------------------------

string MultiPoint::ToString() const {
	if (num_points == 0) {
		return "MULTIPOINT EMPTY";
	}
	string str = "MULTIPOINT (";
	for (uint32_t i = 0; i < num_points; i++) {
		if (points[i].IsEmpty()) {
			str += "EMPTY";
		} else {
			auto &vert = points[i].GetVertex();
			str += std::to_string(vert.x) + " " + std::to_string(vert.y);
		}
		if (i < num_points - 1) {
			str += ", ";
		}
	}
	return str + ")";
}

bool MultiPoint::IsEmpty() const {
	return num_points == 0;
}

uint32_t MultiPoint::Count() const {
	return num_points;
}

Point& MultiPoint::operator[](uint32_t index) {
	return points[index];
}

const Point& MultiPoint::operator[](uint32_t index) const {
	return points[index];
}

const Point* MultiPoint::begin() const {
	return points;
}
const Point* MultiPoint::end() const {
	return points + num_points;
}
Point* MultiPoint::begin() {
	return points;
}
Point* MultiPoint::end() {
	return points + num_points;
}

//------------------------------------------------------------------------------
// MultiLineString
//------------------------------------------------------------------------------

string MultiLineString::ToString() const {
	if (count == 0) {
		return "MULTILINESTRING EMPTY";
	}
	string str = "MULTILINESTRING (";

	bool first = true;
	for (auto &line : *this) {
		str += "(";

		if(first) {
			first = false;
		} else {
			str += ", ";
		}
		first = true;
		for (auto &vert : line.Vertices()) {
			if (first) {
				first = false;
			} else {
				str += ", ";
			}
			str += std::to_string(vert.x) + " " + std::to_string(vert.y);
		}
		str += ")";
	}
	return str + ")";
}

double MultiLineString::Length() const {
	double length = 0;
	for (uint32_t i = 0; i < count; i++) {
		length += lines[i].Length();
	}
	return length;
}

bool MultiLineString::IsEmpty() const {
	return count == 0;
}

uint32_t MultiLineString::Count() const {
	return count;
}

LineString& MultiLineString::operator[](uint32_t index) {
	return lines[index];
}

const LineString& MultiLineString::operator[](uint32_t index) const {
	return lines[index];
}

const LineString* MultiLineString::begin() const {
	return lines;
}
const LineString* MultiLineString::end() const {
	return lines + count;
}
LineString* MultiLineString::begin() {
	return lines;
}
LineString* MultiLineString::end() {
	return lines + count;
}


//------------------------------------------------------------------------------
// MultiPolygon
//------------------------------------------------------------------------------

string MultiPolygon::ToString() const {
	if (count == 0) {
		return "MULTIPOLYGON EMPTY";
	}
	string str = "MULTIPOLYGON (";
	
	bool first = true;
	for (auto &poly : *this) {
		str += "(";
		if (first) {
			first = false;
		} else {
			str += ", ";
		}
		first = true;
		for (auto &ring : poly.Rings()) {
			str += "(";
			if (first) {
				first = false;
			} else {
				str += ", ";
			}
			first = true;
			for (auto &vert : ring) {
				if (first) {
					first = false;
				} else {
					str += ", ";
				}
				str += std::to_string(vert.x) + " " + std::to_string(vert.y);
			}
			str += ")";
		}
		str += ")";
	}

	return str + ")";
}
double MultiPolygon::Area() const {
	double area = 0;
	for (uint32_t i = 0; i < count; i++) {
		area += polygons[i].Area();
	}
	return area;
}

bool MultiPolygon::IsEmpty() const {
	return count == 0;
}

uint32_t MultiPolygon::Count() const {
	return count;
}

Polygon& MultiPolygon::operator[](uint32_t index) {
	return polygons[index];
}

const Polygon& MultiPolygon::operator[](uint32_t index) const {
	return polygons[index];
}

const Polygon* MultiPolygon::begin() const {
	return polygons;
}

const Polygon* MultiPolygon::end() const {
	return polygons + count;
}

Polygon* MultiPolygon::begin() {
	return polygons;
}

Polygon* MultiPolygon::end() {
	return polygons + count;
}

//------------------------------------------------------------------------------
// GeometryCollection
//------------------------------------------------------------------------------

string GeometryCollection::ToString() const {
	if (count == 0) {
		return "GEOMETRYCOLLECTION EMPTY";
	}
	string str = "GEOMETRYCOLLECTION (";
	for (uint32_t i = 0; i < count; i++) {
		str += geometries[i].ToString();
		if (i < count - 1) {
			str += ", ";
		}
	}
	return str + ")";
}

bool GeometryCollection::IsEmpty() const {
	return count == 0;
}

uint32_t GeometryCollection::Count() const {
	return count;
}

Geometry& GeometryCollection::operator[](uint32_t index) {
	D_ASSERT(index < count);
	return geometries[index];
}

const Geometry& GeometryCollection::operator[](uint32_t index) const {
	D_ASSERT(index < count);
	return geometries[index];
}

const Geometry* GeometryCollection::begin() const {
	return geometries;
}

const Geometry* GeometryCollection::end() const {
	return geometries + count;
}

Geometry* GeometryCollection::begin() {
	return geometries;
}

Geometry* GeometryCollection::end() {
	return geometries + count;
}

//------------------------------------------------------------------------------
// Geometry
//------------------------------------------------------------------------------
string Geometry::ToString() const {
	switch (type) {
	case GeometryType::POINT:
		return point.ToString();
	case GeometryType::LINESTRING:
		return linestring.ToString();
	case GeometryType::POLYGON:
		return polygon.ToString();
	case GeometryType::MULTIPOINT:
		return multipoint.ToString();
	case GeometryType::MULTILINESTRING:
		return multilinestring.ToString();
	case GeometryType::MULTIPOLYGON:
		return multipolygon.ToString();
	case GeometryType::GEOMETRYCOLLECTION:
		return geometrycollection.ToString();
	default:
		throw NotImplementedException("Geometry::ToString()");
	}
}

} // namespace core

} // namespace spatial