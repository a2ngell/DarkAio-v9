#include "Geometry.h"
#include "SDK.h"

#undef max
#undef min

namespace Geometry
{
	void BoundingRect::draw(DWORD color, float width, float yPosition) const
	{
		g_drawings->drawWorldCircle(g_navMesh->toWorldVector(min),10, width, color);
		g_drawings->drawWorldCircle(g_navMesh->toWorldVector(max), 10, width, color);

		Vector2 topLeft = this->topLeft();
		Vector2 topRight = this->topRight();
		Vector2 bottomLeft = this->bottomLeft();
		Vector2 bottomRight = this->bottomRight();

		Vector2 topLeftScreen = g_navMesh->toWorldVector(topLeft).toScreen();
		Vector2 topRightScreen = g_navMesh->toWorldVector(topRight).toScreen();
		Vector2 bottomLeftScreen = g_navMesh->toWorldVector(bottomLeft).toScreen();
		Vector2 bottomRightScreen = g_navMesh->toWorldVector(bottomRight).toScreen();

		g_drawings->drawLine(topLeftScreen, topRightScreen, width, color);
		g_drawings->drawLine(topRightScreen, bottomRightScreen, width, color);
		g_drawings->drawLine(bottomRightScreen, bottomLeftScreen, width, color);
		g_drawings->drawLine(bottomLeftScreen, topLeftScreen, width, color);
	}
}

namespace Geometry::Shapes
{
	bool Shape::isOutside(const Vector2& position) const
	{
		return !isInside(position);
	}

	std::vector<Vector2> Shape::edgePoints(float step) const
	{
		Polygon polygon;
		toPolygon(&polygon);

		std::vector<Vector2> points = polygon.points();
		std::vector<Vector2> result;

		for (size_t i = 0; i < points.size(); ++i)
		{
			Vector2 start = points[i];
			Vector2 end = points[(i + 1) % points.size()]; 

			Vector2 segment = end - start;
			int pointCount = static_cast<int>(segment.magnitude() / step);

			for (int j = 0; j < pointCount; ++j)
			{
				Vector2 pointOnEdge = start + segment.normalized() * step * j;
				result.push_back(pointOnEdge);
			}
		}

		return result;
	}

	Circle::Circle(const Vector2& center, float radius)
		: m_center(center), m_radius(radius)
	{
	}

	ShapeType Circle::type() const
	{
		return ShapeType::Circle;
	}

	bool Circle::isInside(const Vector2& position) const
	{
		return m_center.distance(position) <= m_radius + m_offset;
	}

	void Circle::setCenter(const Vector2& center)
	{
		m_center = center;
	}

	void Circle::setRadius(float radius)
	{
		m_radius = radius;
	}

	Vector2 Circle::center() const
	{
		return m_center;
	}

	float Circle::radius() const
	{
		return m_radius;
	}

	void Circle::draw(DWORD color, float width, float yPosition)
	{
		g_drawings->drawWorldCircleFilled({ m_center.x, yPosition, m_center.y }, m_radius + m_offset, color);
	}

	Vector2 Circle::getClosestPoint(const Vector2& position) const
	{
		Vector2 direction = position - m_center;
		
		direction = direction.normalized();
		
		Vector2 closestPoint = m_center + direction * (m_radius + m_offset);

		return closestPoint;
	}


	Intersection Circle::intersect(const Vector2& start, const Vector2& end) const
	{
		Intersection result;

		Vector2 d = end - start;
		Vector2 f = start - m_center;

		float a = d.dotProduct(d);
		float b = 2 * f.dotProduct(d);
		float c = f.dotProduct(f) - (m_radius + m_offset) * (m_radius + m_offset);

		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0)
		{
		}
		else if (discriminant == 0)
		{
			float t = -b / (2 * a);
			if (t >= 0.0f && t <= 1.0f)
			{
				Vector2 intersectionPoint = start + d * t;
				result.points.push_back(intersectionPoint);
			}
		}
		else
		{
			float t1 = (-b - sqrt(discriminant)) / (2 * a);
			float t2 = (-b + sqrt(discriminant)) / (2 * a);

			if (t1 >= 0.0f && t1 <= 1.0f)
			{
				Vector2 intersectionPoint1 = start + d * t1;
				result.points.push_back(intersectionPoint1);
			}

			if (t2 >= 0.0f && t2 <= 1.0f)
			{
				Vector2 intersectionPoint2 = start + d * t2;
				result.points.push_back(intersectionPoint2);
			}
		}

		result.intersect = !result.points.empty();

		std::sort(result.points.begin(), result.points.end(),
			[&start](const Vector2& a, const Vector2& b)
			{
				return start.distanceSquared(a) < start.distanceSquared(b);
			});
		return result;
	}


	void Circle::toPolygon(Polygon* polygon) const
	{
		if (!polygon)
			return;
		
		std::vector<Vector2> points;
		float angle = 2 * PI / 30;

		for (int i = 0; i < 30; i++)
		{
			float x = m_center.x + (m_radius + m_offset) * cos(angle * i);
			float y = m_center.y + (m_radius + m_offset) * sin(angle * i);

			points.push_back({ x, y });
		}
		
		polygon->setPoints(points);
	}

	BoundingRect Circle::boundingRect() const
	{
		float radius = m_radius + m_offset;
		Vector2 min = m_center - Vector2(radius, radius);
		Vector2 max = m_center + Vector2(radius, radius);
		return BoundingRect(min, max);
	}
	
	Rectangle::Rectangle(const Vector2& start, const Vector2& end, float radius)
		: m_start(start), m_end(end), m_radius(radius)
	{
	}

	ShapeType Rectangle::type() const
	{
		return ShapeType::Rectangle;
	}

	bool Rectangle::isInside(const Vector2& position) const
	{
		Vector2 diagonal = m_end - m_start;
		float angle = atan2(diagonal.y, diagonal.x);
		Vector2 rotatedPosition = position.rotate(-angle, m_start);
		Vector2 rotatedEnd = m_end.rotate(-angle, m_start);

		return rotatedPosition.x >= m_start.x &&
			rotatedPosition.x <= rotatedEnd.x &&
			rotatedPosition.y >= m_start.y - (m_radius + m_offset) &&
			rotatedPosition.y <= m_start.y + (m_radius + m_offset);
	}

	void Rectangle::setStart(const Vector2& start)
	{
		m_start = start;
	}
	
	void Rectangle::setEnd(const Vector2& end)
	{
		m_end = end;
	}
	
	void Rectangle::setRadius(float radius)
	{
		m_radius = radius;
	}
	
	Vector2 Rectangle::start() const
	{
		return m_start;
	}
	
	Vector2 Rectangle::end() const
	{
		return m_end;
	}
	
	float Rectangle::radius() const
	{
		return m_radius;
	}

	void Rectangle::draw(DWORD color, float width, float yPosition)
	{
		auto dir = (m_end - m_start).normalized();
		auto perp = dir.perpendicular();

		auto vecRadius = perp * (m_radius + m_offset);

		Vector2 pos1 = m_start + vecRadius;
		Vector2 pos2 = m_start - vecRadius;
		Vector2 pos3 = m_end - vecRadius;
		Vector2 pos4 = m_end + vecRadius;

		Vector3 worldPos1(pos1.x, yPosition, pos1.y);
		Vector3 worldPos2(pos2.x, yPosition, pos2.y);
		Vector3 worldPos3(pos3.x, yPosition, pos3.y);
		Vector3 worldPos4(pos4.x, yPosition, pos4.y);
		
		std::vector<Vector2> screenPoints = { worldPos1.toScreen(), worldPos2.toScreen(), worldPos3.toScreen(), worldPos4.toScreen() };
		g_drawings->drawPolygon(screenPoints, color);
	}
	
	Vector2 Rectangle::getClosestPoint(const Vector2& position) const
	{
		float radius = m_radius + m_offset;

		Vector2 direction = (m_end - m_start).normalized();
		Vector2 orthogonal = Vector2(-direction.y, direction.x);  

		Vector2 upLeft = m_start - orthogonal * radius;
		Vector2 upRight = m_start + orthogonal * radius;
		Vector2 downRight = m_end + orthogonal * radius;
		Vector2 downLeft = m_end - orthogonal * radius;

		std::vector<Vector2> rectPoints = { upLeft, upRight, downRight, downLeft };

		Vector2 closestPoint = rectPoints[0];
		float closestDistance = position.distance(rectPoints[0]);

		for (int i = 0; i < 4; ++i)
		{
			Vector2 lineStart = rectPoints[i];
			Vector2 lineEnd = rectPoints[(i + 1) % 4];

			Vector2 difference = lineEnd - lineStart;
			float lengthSquared = difference.magnitude() * difference.magnitude();

			Vector2 lineDir = difference / sqrt(lengthSquared);

			Vector2 vectorToPoint = position - lineStart;

			float t = lineDir.dotProduct(vectorToPoint);

			if (t < 0)
			{
				continue; 
			}
			else if (t * t > lengthSquared)
			{
				lineStart = lineEnd; 
			}
			else
			{
				lineStart = lineStart + lineDir * t; 
			}

			float distance = position.distance(lineStart);
			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestPoint = lineStart;
			}
		}

		return closestPoint;
	}

	Intersection Rectangle::intersect(const Vector2& start, const Vector2& end) const
	{
		float radius = m_radius + m_offset;
		Intersection result;

		Vector2 direction = (m_end - m_start).normalized();
		Vector2 orthogonal = Vector2(-direction.y, direction.x);  

		Vector2 upLeft = m_start - orthogonal * radius;
		Vector2 upRight = m_start + orthogonal * radius;
		Vector2 downRight = m_end + orthogonal * radius;
		Vector2 downLeft = m_end - orthogonal * radius;

		std::vector<Vector2> lines[] = { {upLeft, upRight}, {upRight, downRight}, {downRight, downLeft}, {downLeft, upLeft} };
		for (const auto& line : lines)
		{
			if (line.size() != 2)
				continue;
			Vector2 intersectionPoint;
			if (Helper::lineIntersect(start, end, line[0], line[1], intersectionPoint))
			{
				result.points.push_back(intersectionPoint);
			}
		}
		result.intersect = !result.points.empty();
		std::sort(result.points.begin(), result.points.end(),
			[&start](const Vector2& a, const Vector2& b)
			{
				return start.distanceSquared(a) < start.distanceSquared(b);
			});
		return result;
	}
	
	void Rectangle::toPolygon(Polygon* polygon) const
	{
		float radius = m_radius + m_offset;

		Vector2 direction = (m_end - m_start).normalized();
		Vector2 orthogonal = Vector2(-direction.y, direction.x);

		Vector2 upLeft = m_start - orthogonal * radius;
		Vector2 upRight = m_start + orthogonal * radius;
		Vector2 downRight = m_end + orthogonal * radius;
		Vector2 downLeft = m_end - orthogonal * radius;

		std::vector<Vector2> rectPoints = { upLeft, upRight, downRight, downLeft };
		polygon->setPoints(rectPoints);
	}

	BoundingRect Rectangle::boundingRect() const
	{
		float radius = m_radius + m_offset;

		Vector2 direction = (m_end - m_start).normalized();
		Vector2 orthogonal = Vector2(-direction.y, direction.x);

		Vector2 upLeft = m_start - orthogonal * radius;
		Vector2 upRight = m_start + orthogonal * radius;
		Vector2 downRight = m_end + orthogonal * radius;
		Vector2 downLeft = m_end - orthogonal * radius;

		float minX = std::min({ upLeft.x, upRight.x, downRight.x, downLeft.x, m_start.x, m_end.x });
		float maxX = std::max({ upLeft.x, upRight.x, downRight.x, downLeft.x, m_start.x, m_end.x });
		float minY = std::min({ upLeft.y, upRight.y, downRight.y, downLeft.y, m_start.y, m_end.y });
		float maxY = std::max({ upLeft.y, upRight.y, downRight.y, downLeft.y, m_start.y, m_end.y });

		return BoundingRect(Vector2(minX, minY), Vector2(maxX, maxY));
	}


	Polygon::Polygon()
	{
		
	}

	Polygon::Polygon(const std::vector<Vector2>& points)
		: m_points(points), m_pointsOffset(points)
	{
	}
	
	ShapeType Polygon::type() const
	{
		return ShapeType::Polygon;
	}

	bool Polygon::isInside(const Vector2& position) const
	{
		ClipperLib::Path path(m_pointsOffset.size());
		for (int i = 0; i < m_pointsOffset.size(); i++)
		{
			path[i] = ClipperLib::IntPoint(m_pointsOffset[i].x, m_pointsOffset[i].y);
		}
		return ClipperLib::PointInPolygon(ClipperLib::IntPoint(position.x, position.y), path) != 0;
	}
	
	void Polygon::setPoints(const std::vector<Vector2>& points)
	{
		m_points = points;
		setOffset(m_offset);
	}
	
	std::vector<Vector2> Polygon::points() const
	{
		return m_pointsOffset;
	}

	void Polygon::draw(DWORD color, float width, float yPosition)
	{
		std::vector<Vector2> screenPolygon;
		for (const auto& point : m_pointsOffset)
		{
			screenPolygon.push_back(Vector3(point.x, yPosition, point.y).toScreen());
		}
		g_drawings->drawPolygon(screenPolygon, color, width);
	}

	Vector2 Polygon::getClosestPoint(const Vector2& position) const
	{
		float minDistance = std::numeric_limits<float>::max();
		Vector2 closestPoint;

		for (int i = 0; i < m_pointsOffset.size(); i++)
		{
			Vector2 currentPoint = m_pointsOffset[i];
			Vector2 nextPoint = m_pointsOffset[(i + 1) % m_pointsOffset.size()];

			Vector2 edge = nextPoint - currentPoint;
			Vector2 toPosition = position - currentPoint;

			float t = std::max(0.0f, std::min(1.0f, toPosition.dot(edge) / edge.dot(edge)));

			Vector2 projection = currentPoint + edge * t;

			float distance = projection.distance(position);
			if (distance < minDistance)
			{
				minDistance = distance;
				closestPoint = projection;
			}
		}

		return closestPoint;
	}

	Intersection Polygon::intersect(const Vector2& start, const Vector2& end) const
	{
		Intersection intersection;
		intersection.intersect = false;

		Vector2 intersectionPoint;
		for (int i = 0; i < m_pointsOffset.size(); i++)
		{
			Vector2 currentPoint = m_pointsOffset[i];
			Vector2 nextPoint = m_pointsOffset[(i + 1) % m_pointsOffset.size()];

			if (Helper::lineIntersect(start, end, currentPoint, nextPoint, intersectionPoint))
			{
				intersection.intersect = true;
				intersection.points.push_back(intersectionPoint);
			}
		}

		std::sort(intersection.points.begin(), intersection.points.end(),
			[&start](const Vector2& a, const Vector2& b) {
				return a.distance(start) < b.distance(start);
			});

		return intersection;
	}

	void Polygon::setOffset(float offset)
	{
		if (m_points.size() == 0)
			return;
		if (offset == 0)
		{
			m_pointsOffset = m_points;
			return;
		}
		m_offset = offset;
		ClipperLib::Path path(m_points.size());
		for (int i = 0; i < m_points.size(); i++)
		{
			path[i] = ClipperLib::IntPoint(m_points[i].x, m_points[i].y);
		}
		ClipperLib::ClipperOffset co;
		co.AddPath(path, ClipperLib::jtMiter, ClipperLib::etClosedPolygon);
		ClipperLib::Paths newPolygon;
		co.Execute(newPolygon, m_offset); 

		if (newPolygon.size() == 0)
			return;

		m_pointsOffset.clear();
		for (int i = 0; i < newPolygon[0].size(); i++)
		{
			m_pointsOffset.push_back(Vector2(newPolygon[0][i].X, newPolygon[0][i].Y));
		}
	}

	void Polygon::toPolygon(Polygon* polygon) const
	{
		polygon->setPoints(m_points);
		polygon->setOffset(m_offset);
	}

	BoundingRect Polygon::boundingRect() const
	{
		if (m_pointsOffset.empty())
			return BoundingRect(); 

		float minX = m_pointsOffset[0].x;
		float maxX = m_pointsOffset[0].x;
		float minY = m_pointsOffset[0].y;
		float maxY = m_pointsOffset[0].y;

		for (const Vector2& point : m_pointsOffset)
		{
			if (point.x < minX)
				minX = point.x;
			if (point.x > maxX)
				maxX = point.x;
			if (point.y < minY)
				minY = point.y;
			if (point.y > maxY)
				maxY = point.y;
		}

		return BoundingRect(Vector2(minX, minY), Vector2(maxX, maxY));
	}

	
	Sector::Sector(const Vector2& center, const Vector2& direction, float radius, float angle)
		: m_center(center), m_direction(direction), m_radius(radius), m_angle(angle)
	{
	}
	
	ShapeType Sector::type() const
	{
		return ShapeType::Sector;
	}

	bool Sector::isInside(const Vector2& position) const
	{
		float new_angle = m_angle + 2 * atan(m_offset / m_radius);
		Vector2 diff = position - m_center;
		Vector2 normalizedDiff = diff.normalized();
		Vector2 normalizedDirection = m_direction.normalized();

		float dot = normalizedDirection.x * normalizedDiff.x + normalizedDirection.y * normalizedDiff.y;
		float det = normalizedDirection.x * normalizedDiff.y - normalizedDirection.y * normalizedDiff.x;
		float angleToPosition = atan2(det, dot);

		return abs(angleToPosition) <= new_angle / 2 && diff.magnitude() <= (m_radius + m_offset);
	}
	
	void Sector::setCenter(const Vector2& center)
	{
		m_center = center;
	}
	
	void Sector::setDirection(const Vector2& direction)
	{
		m_direction = direction;
	}
	
	void Sector::setRadius(float radius)
	{
		m_radius = radius;
	}
	
	void Sector::setAngle(float angle)
	{
		m_angle = angle;
	}
	
	Vector2 Sector::center() const
	{
		return m_center;
	}
	
	Vector2 Sector::direction() const
	{
		return m_direction;
	}
	
	float Sector::radius() const
	{
		return m_radius;
	}
	
	float Sector::angle() const
	{
		return m_angle;
	}

	void Sector::draw(DWORD color, float width, float yPosition)
	{
		Polygon polygon;
		toPolygon(&polygon);
		polygon.draw(color, width, yPosition);
	}

	Vector2 Sector::getClosestPoint(const Vector2& position) const
	{
		auto getClosestPointOnLine = [] (const Vector2& lineStart, const Vector2& lineEnd, const Vector2& point)
		{
			Vector2 lineDirection = (lineEnd - lineStart).normalized();
			Vector2 pointDirection = point - lineStart;
			float t = lineDirection.dotProduct(pointDirection);

			if (t <= 0)
				return lineStart;

			float lineLength = (lineEnd - lineStart).magnitude();
			if (t >= lineLength)
				return lineEnd;

			return lineStart + lineDirection * t;
		};

		float new_angle = m_angle + 2 * atan(m_offset / m_radius);

		Vector2 diff = position - m_center;
		Vector2 normalizedDiff = diff.normalized();
		Vector2 normalizedDirection = m_direction.normalized();
		float dot = normalizedDirection.x * normalizedDiff.x + normalizedDirection.y * normalizedDiff.y;
		float det = normalizedDirection.x * normalizedDiff.y - normalizedDirection.y * normalizedDiff.x;
		float angleToPosition = atan2(det, dot);

		if (abs(angleToPosition) <= new_angle / 2) {
			return m_center + normalizedDiff * (m_radius + m_offset);
		}
		else {
			Vector2 line1Dir = m_direction.rotated(-new_angle / 2).normalized();
			Vector2 line2Dir = m_direction.rotated(new_angle / 2).normalized();
			Vector2 pointOnLine1 = m_center + line1Dir * (m_radius + m_offset);
			Vector2 pointOnLine2 = m_center + line2Dir * (m_radius + m_offset);

			auto dirPerp = m_direction.perpendicular();
			Vector2 start1 = m_center - dirPerp * m_offset;
			Vector2 start2 = m_center + dirPerp * m_offset;

			Vector2 closestPointOnLine1 = getClosestPointOnLine(start1, pointOnLine1, position);
			Vector2 closestPointOnLine2 = getClosestPointOnLine(start2, pointOnLine2, position);


			float distanceToLine1 = (position - closestPointOnLine1).magnitude();
			float distanceToLine2 = (position - closestPointOnLine2).magnitude();

			if (m_offset != 0)
			{
				Vector2 closestPointOnLine3 = getClosestPointOnLine(start1, start2, position);
				float distanceToLine3 = (position - closestPointOnLine3).magnitude();
				if (distanceToLine3 < distanceToLine1 && distanceToLine3 < distanceToLine2)
					return closestPointOnLine3;
			}

			if (distanceToLine1 < distanceToLine2)
				return closestPointOnLine1;
			else
				return closestPointOnLine2;
		}
	}

	Intersection Sector::intersect(const Vector2& start, const Vector2& end) const
	{
		float new_angle = m_angle + 2 * atan(m_offset / m_radius);
		Intersection result;
		Intersection arcResult = Helper::circleIntersect(m_center, m_radius + m_offset, start, end);
		for (const Vector2& point : arcResult.points)
		{
			Vector2 diff = point - m_center;
			Vector2 normalizedDiff = diff.normalized();
			Vector2 normalizedDirection = m_direction.normalized();
			float dot = normalizedDirection.x * normalizedDiff.x + normalizedDirection.y * normalizedDiff.y;
			float det = normalizedDirection.x * normalizedDiff.y - normalizedDirection.y * normalizedDiff.x;
			float angleToPosition = atan2(det, dot);
			
			if (abs(angleToPosition) <= new_angle / 2)
			{
				result.points.push_back(point);
			}
		}

		auto dirPerp = m_direction.perpendicular();
		Vector2 start1 = m_center - dirPerp * m_offset;
		Vector2 start2 = m_center + dirPerp * m_offset;

		Vector2 line1Start = start1;
		Vector2 line1End = m_center + m_direction.rotated(-new_angle / 2).normalized() * (m_radius + m_offset);
		Vector2 line2Start = start2;
		Vector2 line2End = m_center + m_direction.rotated(new_angle / 2).normalized() * (m_radius + m_offset);

		Vector2 line1Intersection;
		if (Helper::lineIntersect(start, end, line1Start, line1End, line1Intersection))
			result.points.push_back(line1Intersection);

		Vector2 line2Intersection;
		if (Helper::lineIntersect(start, end, line2Start, line2End, line2Intersection))
			result.points.push_back(line2Intersection);
		
		if (m_offset != 0)
		{
			Vector2 line3Start = start1;
			Vector2 line3End = start2;
			Vector2 line3Intersection;
			if (Helper::lineIntersect(start, end, line3Start, line3End, line3Intersection))
				result.points.push_back(line3Intersection);
		}

		result.intersect = !result.points.empty();

		std::sort(result.points.begin(), result.points.end(),
			[&start](const Vector2& a, const Vector2& b) {
				return start.distanceSquared(a) < start.distanceSquared(b);
			});

		return result;
	}

	void Sector::toPolygon(Polygon* polygon) const
	{
		std::vector<Vector2> points;

		float new_angle = m_angle + 2 * atan(m_offset / m_radius);
		Vector2 start = m_center + m_direction.rotated(-new_angle / 2).normalized() * (m_radius + m_offset);
		Vector2 end = m_center + m_direction.rotated(new_angle / 2).normalized() * (m_radius + m_offset);

		auto dirPerp = m_direction.perpendicular();
		Vector2 start1 = m_center - dirPerp * m_offset;
		Vector2 start2 = m_center + dirPerp * m_offset;

		points.push_back(start1);
		points.push_back(start);

		const int numSegments = 25;
		for (int i = 0; i <= numSegments - 1; ++i) {
			float angle1 = -new_angle / 2 + new_angle * i / numSegments;
			float angle2 = -new_angle / 2 + new_angle * (i + 1) / numSegments;

			Vector2 point1 = m_center + m_direction.rotated(angle1).normalized() * (m_radius + m_offset);
			Vector2 point2 = m_center + m_direction.rotated(angle2).normalized() * (m_radius + m_offset);

			points.push_back(point1);
			points.push_back(point2);
		}

		points.push_back(end);
		points.push_back(start2);
		polygon->setPoints(points);
	}

	BoundingRect Sector::boundingRect() const
	{
		Polygon polygon;
		toPolygon(&polygon);
		return polygon.boundingRect();
	}


	Ring::Ring(const Vector2& center, float innerRadius, float outerRadius)
		: m_center(center), m_innerRadius(innerRadius), m_outerRadius(outerRadius)
	{
	}
	
	ShapeType Ring::type() const
	{
		return ShapeType::Ring;
	}

	bool Ring::isInside(const Vector2& position) const
	{
		Vector2 diff = position - m_center;
		float dist = diff.magnitude();

		return dist >= m_innerRadius && dist <= m_outerRadius;
	}
	
	void Ring::setCenter(const Vector2& center)
	{
		m_center = center;
	}
	
	void Ring::setInnerRadius(float radius)
	{
		m_innerRadius = radius;
	}
	
	void Ring::setOuterRadius(float radius)
	{
		m_outerRadius = radius;
	}
	
	Vector2 Ring::center() const
	{
		return m_center;
	}
	
	float Ring::innerRadius() const
	{
		return m_innerRadius;
	}
	
	float Ring::outerRadius() const
	{
		return m_outerRadius;
	}

	void Ring::draw(DWORD color, float width, float yPosition)
	{
		g_drawings->drawWorldCircle({ m_center.x, yPosition, m_center.y }, m_innerRadius - m_offset, width, color);
		g_drawings->drawWorldCircle({ m_center.x, yPosition, m_center.y }, m_outerRadius + m_offset, width, color);
	}

	Vector2 Ring::getClosestPoint(const Vector2& position) const
	{
		Vector2 diff = position - m_center;
		float distance = diff.magnitude();

		if (distance < (m_innerRadius - m_offset)) {
			return m_center + diff.normalized() * (m_innerRadius - m_offset);
		}
		else if (distance > (m_outerRadius + m_offset)) {
			return m_center + diff.normalized() * (m_outerRadius + m_offset);
		}
		else {
			return position;
		}
	}

	Intersection Ring::intersect(const Vector2& start, const Vector2& end) const
	{
		Intersection intersection;
		
		Intersection innerIntersection = Circle(m_center, m_innerRadius - m_offset).intersect(start, end);
		if (innerIntersection.intersect)
		{
			intersection.intersect = true;
			intersection.points.insert(intersection.points.end(),
				innerIntersection.points.begin(),
				innerIntersection.points.end());
		}
		
		Intersection outerIntersection = Circle(m_center, m_outerRadius + m_offset).intersect(start, end);
		if (outerIntersection.intersect)
		{
			intersection.intersect = true;
			intersection.points.insert(intersection.points.end(),
				outerIntersection.points.begin(),
				outerIntersection.points.end());
		}
		
		std::sort(intersection.points.begin(), intersection.points.end(),
			[start](Vector2 a, Vector2 b) { return (a - start).magnitude() < (b - start).magnitude(); });

		return intersection;
	}

	void Ring::toPolygon(Polygon* polygon) const
	{
		
	}

	BoundingRect Ring::boundingRect() const
	{
		Vector2 minPoint = m_center - Vector2(m_outerRadius + m_offset, m_outerRadius + m_offset);
		Vector2 maxPoint = m_center + Vector2(m_outerRadius + m_offset, m_outerRadius + m_offset);

		return BoundingRect(minPoint, maxPoint);
	}

	std::vector<Vector2> Ring::edgePoints(float step) const
	{
		float angleStepOuter = step / m_outerRadius;

		std::vector<Vector2> points;

		float angle = 0;
		while (angle < 2 * PI)
		{
			Vector2 outerPoint = m_center + Vector2(cos(angle), sin(angle)) * (m_outerRadius + m_offset);
			Vector2 innerPoint = m_center + Vector2(cos(angle), sin(angle)) * (m_innerRadius - m_offset);

			points.push_back(outerPoint);
			points.push_back(innerPoint);

			angle += angleStepOuter;
		}

		return points;
	}



	Group::Group(const std::vector<Shape*>& shapes)
		: m_shapes(shapes)
	{
	}
	
	ShapeType Group::type() const
	{
		return ShapeType::Group;
	}

	bool Group::isInside(const Vector2& position) const
	{
		for (auto& p : m_shapes)
			if (p->isInside(position))
				return true;
		return false;
	}
	
	void Group::setShapes(const std::vector<Shape*>& shapes)
	{
		m_shapes = shapes;
	}
	
	std::vector<Shape*> Group::shapes() const
	{
		return m_shapes;
	}
	
	void Group::addShape(Shape* shape)
	{
		m_shapes.push_back(shape);
	}
	
	void Group::draw(DWORD color, float width, float yPosition)
	{
		for (auto& shape : m_shapes)
			shape->draw(color, width, yPosition);
	}

	Vector2 Group::getClosestPoint(const Vector2& position) const
	{
		Vector2 closestPoint;
		float closestDistance = std::numeric_limits<float>::max();

		for (auto& shape : m_shapes)
		{
			Vector2 point = shape->getClosestPoint(position);
			float distance = (point - position).magnitude();

			if (distance < closestDistance)
			{
				closestPoint = point;
				closestDistance = distance;
			}
		}

		return closestPoint;
	}

	Intersection Group::intersect(const Vector2& start, const Vector2& end) const
	{
		Intersection intersection;

		for (auto& shape : m_shapes)
		{
			Intersection shapeIntersection = shape->intersect(start, end);

			if (shapeIntersection.intersect)
			{
				intersection.intersect = true;
				intersection.points.insert(intersection.points.end(),
					shapeIntersection.points.begin(),
					shapeIntersection.points.end());
			}
		}

		std::sort(intersection.points.begin(), intersection.points.end(),
			[start](Vector2 a, Vector2 b) { return (a - start).magnitude() < (b - start).magnitude(); });

		return intersection;
	}

	void Group::toPolygon(Polygon* inputPolygon) const
	{
		ClipperLib::Clipper clipper;

		std::vector<std::vector<ClipperLib::IntPoint>> subj(m_shapes.size());
		std::vector<std::vector<ClipperLib::IntPoint>> clip(m_shapes.size());

		for (auto& shape : m_shapes)
		{
			Polygon polygon;
			shape->toPolygon(&polygon);

			ClipperLib::Path path;
			for (auto& point : polygon.points())
				path.push_back(ClipperLib::IntPoint(point.x, point.y));

			subj.push_back(path);
			clip.push_back(path);
		}
		
		ClipperLib::Paths solution;
		clipper.AddPaths(subj, ClipperLib::ptSubject, true);
		clipper.AddPaths(clip, ClipperLib::ptClip, true);
		clipper.Execute(ClipperLib::ctUnion, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);
		
		if (solution.size() > 0)
		{
			std::vector<Vector2> points;
			for (auto& point : solution[0])
				points.push_back(Vector2(point.X, point.Y));
			inputPolygon->setPoints(points);
		}
	}

	void Group::toPolygonEvenOdd(Polygon* polygon) const
	{
		ClipperLib::Clipper clipper;

		std::vector<std::vector<ClipperLib::IntPoint>> subj(m_shapes.size());
		std::vector<std::vector<ClipperLib::IntPoint>> clip(m_shapes.size());

		for (auto& shape : m_shapes)
		{
			Polygon polygon;
			shape->toPolygon(&polygon);

			ClipperLib::Path path;
			for (auto& point : polygon.points())
				path.push_back(ClipperLib::IntPoint(point.x, point.y));

			subj.push_back(path);
			clip.push_back(path);
		}

		ClipperLib::Paths solution;
		clipper.AddPaths(subj, ClipperLib::ptSubject, true);
		clipper.AddPaths(clip, ClipperLib::ptClip, true);
		clipper.Execute(ClipperLib::ctUnion, solution, ClipperLib::pftEvenOdd, ClipperLib::pftEvenOdd);

		if (solution.size() > 0)
		{
			std::vector<Vector2> points;
			for (auto& point : solution[0])
				points.push_back(Vector2(point.X, point.Y));
			polygon->setPoints(points);
		}
	}

	BoundingRect Group::boundingRect() const
	{
		Vector2 minPoint(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
		Vector2 maxPoint(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());

		for (auto& shape : m_shapes)
		{
			BoundingRect rect = shape->boundingRect();
			minPoint.x = std::min(minPoint.x, rect.min.x);
			minPoint.y = std::min(minPoint.y, rect.min.y);
			maxPoint.x = std::max(maxPoint.x, rect.max.x);
			maxPoint.y = std::max(maxPoint.y, rect.max.y);
		}

		return BoundingRect(minPoint, maxPoint);
	}

}

namespace Geometry::Shapes::Helper
{
	bool lineIntersect(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, Vector2& intersection)
	{
		float s1_x, s1_y, s2_x, s2_y;
		s1_x = p1.x - p0.x;
		s1_y = p1.y - p0.y;
		s2_x = p3.x - p2.x;
		s2_y = p3.y - p2.y;
		
		float s, t;
		float denominator = (-s2_x * s1_y + s1_x * s2_y);
		if (fabs(denominator) < 1e-9) {
			return false;
		}
		s = (-s1_y * (p0.x - p2.x) + s1_x * (p0.y - p2.y)) / denominator;
		t = (s2_x * (p0.y - p2.y) - s2_y * (p0.x - p2.x)) / denominator;

		
		if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		{
			intersection.x = p0.x + (t * s1_x);
			intersection.y = p0.y + (t * s1_y);
			return true;
		}

		return false; 
	}

	Intersection circleIntersect(const Vector2& circleCenter, float radius, const Vector2& lineStart, const Vector2& lineEnd)
	{
		Intersection result;

		Vector2 d = lineEnd - lineStart;
		Vector2 f = lineStart - circleCenter;

		float a = d.dotProduct(d);
		float b = 2 * f.dotProduct(d);
		float c = f.dotProduct(f) - radius * radius;

		float discriminant = b * b - 4 * a * c;
		if (discriminant < 0)
		{
			
		}
		else
		{
			discriminant = sqrt(discriminant);

			float t1 = (-b - discriminant) / (2 * a);
			float t2 = (-b + discriminant) / (2 * a);

			if (t1 >= 0 && t1 <= 1)
			{
				Vector2 point = lineStart + d * t1;
				result.points.push_back(point);
			}
			
			if (t2 >= 0 && t2 <= 1)
			{
				Vector2 point = lineStart + d * t2;
				result.points.push_back(point);
			}

			result.intersect = !result.points.empty();
		}

		return result;
	}
}