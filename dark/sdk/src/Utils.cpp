#include "Utils.h"
#include <vector>
#include "SDK.h"

#define _USE_MATH_DEFINES
#include <math.h>

#undef min
#undef max

namespace Utils
{
	std::string randomString(size_t length)
	{
		auto randchar = []() -> char
			{
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t maxIndex = (sizeof(charset) - 1);
			return charset[rand() % maxIndex];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}

    std::string ptrToHex(uintptr_t ptr)
    {
        std::stringstream ss;
        ss << std::hex << ptr;
        return ss.str();
    }

    std::vector<std::string> split(const std::string& s, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::string toLower(std::string_view string)
    {
        std::string strLower;
        strLower.resize(string.size());

        std::transform(string.begin(),
            string.end(),
            strLower.begin(),
            ::tolower);

        return strLower;
    }
    
	VectorMovementCollisionResult vectorMovementCollision(const Vector2& startPoint1, const Vector2& endPoint, float v1, const Vector2& startPoint2, float v2, float delay)
	{
		auto sP1x = startPoint1.x;
		auto sP1y = startPoint1.y;
		auto eP1x = endPoint.x;
		auto eP1y = endPoint.y;
		auto sP2x = startPoint2.x;
		auto sP2y = startPoint2.y;

		float d = eP1x - sP1x, e = eP1y - sP1y;
		float dist = (float)sqrt(d * d + e * e), t1 = std::numeric_limits<float>::quiet_NaN();
		float S = abs(dist) > std::numeric_limits<float>::epsilon() ? v1 * d / dist : 0,
			K = (abs(dist) > std::numeric_limits<float>::epsilon()) ? v1 * e / dist : 0.f;

		float r = sP2x - sP1x, j = sP2y - sP1y;
		auto c = r * r + j * j;

		if (dist > 0.f)
		{
			if (abs(v1 - std::numeric_limits<float>::max()) < std::numeric_limits<float>::epsilon())
			{
				auto t = dist / v1;
				t1 = v2 * t >= 0.f ? t : std::numeric_limits<float>::quiet_NaN();
			}
			else if (abs(v2 - std::numeric_limits<float>::max()) < std::numeric_limits<float>::epsilon())
			{
				t1 = 0.f;
			}
			else
			{
				float a = S * S + K * K - v2 * v2, b = -r * S - j * K;

				if (abs(a) < std::numeric_limits<float>::epsilon())
				{
					if (abs(b) < std::numeric_limits<float>::epsilon())
					{
						t1 = (abs(c) < std::numeric_limits<float>::epsilon()) ? 0.f : std::numeric_limits<float>::quiet_NaN();
					}
					else
					{
						auto t = -c / (2 * b);
						t1 = (v2 * t >= 0.f) ? t : std::numeric_limits<float>::quiet_NaN();
					}
				}
				else
				{
					auto sqr = b * b - a * c;
					if (sqr >= 0)
					{
						auto nom = (float)sqrt(sqr);
						auto t = (-nom - b) / a;
						t1 = v2 * t >= 0.f ? t : std::numeric_limits<float>::quiet_NaN();
						t = (nom - b) / a;
						auto t2 = (v2 * t >= 0.f) ? t : std::numeric_limits<float>::quiet_NaN();

						if (!isnan(t2) && !isnan(t1))
						{
							if (t1 >= delay && t2 >= delay)
							{
								t1 = std::min(t1, t2);
							}
							else if (t2 >= delay)
							{
								t1 = t2;
							}
						}
					}
				}
			}
		}
		else if (abs(dist) < std::numeric_limits<float>::epsilon())
		{
			t1 = 0.f;
		}

		return VectorMovementCollisionResult{ t1, !isnan(t1), (!isnan(t1)) ? Vector2(sP1x + S * t1, sP1y + K * t1) : Vector2() };
	}
	std::vector<Vector3> circlePoints(const Vector3& from, float radius, int points, bool isWallValid)
	{
		std::vector<Vector3> p;
		float step = M_PI * 2.0 / points;
		
		for (float a = 0; a < M_PI * 2; a += step)
		{
			float rX1 = radius * cos(a) + from.x;
			float rZ1 = radius * sinf(a) + from.z;
		
			auto pos = Vector3{ rX1, from.y, rZ1 };
		
			if (!isWallValid && g_navMesh->isWall(pos))
				continue;
		
			p.push_back(Vector3{ rX1, from.y, rZ1 });
		}
		return p;
	}
}