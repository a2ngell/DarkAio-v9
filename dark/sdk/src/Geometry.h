#pragma once

#include "Vector2.h"
#include <vector>

#define CLIPPER_STATIC_LIB

#include "clipper.hpp"

#define PI 3.14159265358979323846
#define DEG_TO_RAD(degrees) ((degrees) * PI / 180.0)
#define RAD_TO_DEG(radians) ((radians) * 180.0 / PI)

#undef min
#undef max

namespace Geometry
{	
	struct BoundingRect
	{
		BoundingRect() = default;
		BoundingRect(const Vector2& min, const Vector2& max) : min(min), max(max) {}
		Vector2 min;
		Vector2 max;

		bool isInside(const Vector2& position) const
		{
			return position.x >= min.x && position.x <= max.x && position.y >= min.y && position.y <= max.y;
		}

		float width() const
		{
			return max.x - min.x;
		}

		float height() const
		{
			return max.y - min.y;
		}

		Vector2 topLeft() const
		{
			return Vector2(min.x, max.y);
		}

		Vector2 topRight() const
		{
			return max;
		}

		Vector2 bottomLeft() const
		{
			return min;
		}

		Vector2 bottomRight() const
		{
			return Vector2(max.x, min.y);
		}

		void draw(DWORD color, float width, float yPosition) const;

		float distance(const Vector2& point) const
		{
			if (isInside(point))
				return 0.0f;

			float dx = std::max(std::max(min.x - point.x, 0.0f), point.x - max.x);
			float dy = std::max(std::max(min.y - point.y, 0.0f), point.y - max.y);

			return std::sqrt(dx * dx + dy * dy);
		}
	};

	namespace Shapes
	{
		struct Intersection
		{
			bool intersect;
			std::vector<Vector2> points;
		};

		namespace Helper
		{
			Intersection circleIntersect(const Vector2& circleCenter, float radius, const Vector2& lineStart, const Vector2& lineEnd);
			bool lineIntersect(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, Vector2& intersection);
		}
		
		enum class ShapeType
		{
			Circle,
			Rectangle,
			Polygon,
			Sector,
			Ring,
			Group,
			RectangleEndCircle
		};


		class Polygon;
		class Shape
		{
		public:
			Shape() : m_offset(0) {}
			~Shape() = default;

		public:
			virtual ShapeType type() const = 0;
			virtual bool isInside(const Vector2& position) const = 0;
			bool isOutside(const Vector2& position) const;
			virtual void draw(DWORD color, float width, float yPosition) = 0;
			virtual Vector2 getClosestPoint(const Vector2& position) const = 0;
			virtual Intersection intersect(const Vector2& start, const Vector2& end) const = 0;
			virtual std::vector<Vector2> edgePoints(float step) const;

			float offset() const { return m_offset; }
			virtual void setOffset(float offsets) { m_offset = offsets; }

			virtual void toPolygon(Polygon* polygon) const = 0;

			virtual BoundingRect boundingRect() const = 0;

		protected:
			float m_offset;
		};

		class Circle : public Shape
		{
		public:
			Circle(const Vector2& center, float radius);
			~Circle() = default;

		public:
			ShapeType type() const override;

			bool isInside(const Vector2& position) const override;

			void setCenter(const Vector2& center);
			void setRadius(float radius);

			Vector2 center() const;
			float radius() const;

			void draw(DWORD color, float width, float yPosition) override;

			Vector2 getClosestPoint(const Vector2& position) const override;
			Intersection intersect(const Vector2& start, const Vector2& end) const override;

			void toPolygon(Polygon* polygon) const override;

			BoundingRect boundingRect() const override;

		private:
			Vector2 m_center;
			float m_radius;
		};

		class Rectangle : public Shape
		{
		public:
			Rectangle(const Vector2& start, const Vector2& end, float radius);
			~Rectangle() = default;

		public:
			ShapeType type() const override;

			bool isInside(const Vector2& position) const override;

			void setStart(const Vector2& start);
			void setEnd(const Vector2& end);
			void setRadius(float radius);

			Vector2 start() const;
			Vector2 end() const;
			float radius() const;

			void draw(DWORD color, float width, float yPosition) override;

			Vector2 getClosestPoint(const Vector2& position) const override;
			Intersection intersect(const Vector2& start, const Vector2& end) const override;

			void toPolygon(Polygon* polygon) const override;

			BoundingRect boundingRect() const override;

		private:
			Vector2 m_start;
			Vector2 m_end;
			float m_radius;
		};

		class Polygon : public Shape
		{
		public:
			Polygon();
			Polygon(const std::vector<Vector2>& points);
			~Polygon() = default;

		public:
			ShapeType type() const override;

			bool isInside(const Vector2& position) const override;

			void setPoints(const std::vector<Vector2>& points);

			std::vector<Vector2> points() const;

			void draw(DWORD color, float width, float yPosition) override;

			Vector2 getClosestPoint(const Vector2& position) const override;
			Intersection intersect(const Vector2& start, const Vector2& end) const override;

			void setOffset(float offset) override;

			void toPolygon(Polygon* polygon) const override;

			BoundingRect boundingRect() const override;

		private:
			std::vector<Vector2> m_points;
			std::vector<Vector2> m_pointsOffset;
		};

		class Sector : public Shape
		{
		public:
			Sector(const Vector2& center, const Vector2& direction, float radius, float angle);
			~Sector() = default;
			
		public:
			ShapeType type() const override;

			bool isInside(const Vector2& position) const override;

			void setCenter(const Vector2& center);
			void setDirection(const Vector2& direction);
			void setRadius(float radius);
			void setAngle(float angle);

			Vector2 center() const;
			Vector2 direction() const;
			float radius() const;
			float angle() const;

			void draw(DWORD color, float width, float yPosition) override;

			Vector2 getClosestPoint(const Vector2& position) const override;
			Intersection intersect(const Vector2& start, const Vector2& end) const override;

			void toPolygon(Polygon* polygon) const override;

			BoundingRect boundingRect() const override;

		private:
			Vector2 m_center;
			Vector2 m_direction;
			float m_radius;
			float m_angle;
		};

		class Ring : public Shape
		{
		public:
			Ring(const Vector2& center, float innerRadius, float outerRadius);
			~Ring() = default;

		public:
			ShapeType type() const override;

			bool isInside(const Vector2& position) const override;

			void setCenter(const Vector2& center);
			void setInnerRadius(float radius);
			void setOuterRadius(float radius);

			Vector2 center() const;
			float innerRadius() const;
			float outerRadius() const;
			
			void draw(DWORD color, float width, float yPosition) override;

			Vector2 getClosestPoint(const Vector2& position) const override;
			Intersection intersect(const Vector2& start, const Vector2& end) const override;

			void toPolygon(Polygon* polygon) const override;

			BoundingRect boundingRect() const override;

			std::vector<Vector2> edgePoints(float step) const override;

		private:
			Vector2 m_center;
			float m_innerRadius;
			float m_outerRadius;
		};

		class Group : public Shape
		{
		public:
			Group(const std::vector<Shape*>& shapes);
			~Group() = default;
			
		public:
			ShapeType type() const override;

			bool isInside(const Vector2& position) const override;

			void setShapes(const std::vector<Shape*>& shapes);

			std::vector<Shape*> shapes() const;

			void addShape(Shape* shape);

			void draw(DWORD color, float width, float yPosition) override;

			Vector2 getClosestPoint(const Vector2& position) const override;
			Intersection intersect(const Vector2& start, const Vector2& end) const override;

			void toPolygon(Polygon* polygon) const override;
			void toPolygonEvenOdd(Polygon* polygon) const;

			BoundingRect boundingRect() const override;

		private:
			std::vector<Shape*> m_shapes;
		};
	}
}