#pragma once

#include "Vector2.h"
#include "Vector3.h"

#include <string>
#include <filesystem>

class IDrawings
{
public:
	virtual ~IDrawings() = default;

public:
	virtual void drawText(const Vector2& position, const std::string& text, int size, DWORD color, bool center = false, bool outlined = true) = 0;
	virtual void drawLine(const Vector2& start, const Vector2& end, float width, DWORD color) = 0;
	virtual void drawPolyline(const std::vector<Vector2>& points, float width, DWORD color) = 0;
	virtual void drawRect(const Vector2& position, const Vector2& size, float width, DWORD color, float rounding = 0) = 0;
	virtual void drawFilledRect(const Vector2& position, const Vector2& size, DWORD color, float rounding = 0) = 0;
	virtual void drawCircle(const Vector2& center, float radius, float width, DWORD color) = 0;
	virtual void drawFilledCircle(const Vector2& center, float radius, DWORD color) = 0;
	virtual void drawPolygon(const std::vector<Vector2>& points, DWORD color, float width = 2) = 0;
	virtual void drawImage(uint32_t hash, const Vector2& pos, const Vector2& size, bool centered = false, float rounding = 0) = 0;
	virtual void drawImageColor(uint32_t hash, const Vector2& pos, const Vector2& size, DWORD color, bool centered = false, float rounding = 0) = 0;
	virtual void drawLineArrowWorld(const Vector3& start, const Vector3& end, float width, float arrowLength, DWORD color) = 0;

	virtual Vector2 textSize(const std::string& text, int size) = 0;

	virtual void drawWorldCircle(const Vector3& position, float radius, float width, DWORD color) = 0;
	virtual void drawWorldCircleLeague(const Vector3& position, float radius, DWORD color, const std::string& textureName = "") = 0;
	virtual void drawWorldCircleFilled(const Vector3& position, float radius, DWORD color) = 0;
	virtual void drawMinimapCircle(const Vector3& position, float radius, float width, DWORD color) = 0;
	virtual void drawMinimapCircle(const Vector2& position, float radius, float width, DWORD color) = 0;
	virtual void drawLeagueImage(const std::string& imageName, const Vector2& pos, const Vector2& size, bool centered = false, float rounding = 0) = 0;

	virtual bool loadImage(uint32_t hash, const std::filesystem::path& path) = 0;
	virtual bool loadImageFromMemory(uint32_t hash, const unsigned char* data, size_t size) = 0;
	virtual void* getImage(uint32_t hash) = 0;
};