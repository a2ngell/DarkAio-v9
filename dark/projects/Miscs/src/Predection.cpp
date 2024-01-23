#include "Predection.h"

namespace Predection
{
	IGameObject* me = g_localPlayer;
	PredictionOutput Prediction::GetPositionOnPath(PredictionInput input)
	{
		IGameObject* player = me;
		auto navigation = input.target->pathController();
		if (!navigation) input.target->position();
		auto pathManager = navigation->currentPath();

		float speed = input.target->stats()->moveSpeed();

		if (input.target->position().distance(me->position()) <= 250)
			speed /= 1.5f;

		if (pathManager.size() <= 1 || (input.target->activeSpell() && input.target->activeSpell()->isBasicAttack() && !navigation->isDashing()))
		{
			PredictionOutput result = PredictionOutput(input);
			result.predictedPosition = input.target->position();
			return result;
		}


		//Skillshots with only a delay
		auto pat1 = pathManager.back();
		auto pat2 = pathManager[pathManager.size() - 1];
		float pathLength = pat1.distance(pat2);
		if (pathLength >= input.delay * speed - input.radius && std::abs(input.speed - FLT_MAX) < FLT_EPSILON)
		{
			float tDistance = input.delay * speed - input.radius;

			for (int i = 0; i < pathManager.size(); i++)
			{
				Vector3 a = pathManager[i];
				Vector3 b = pathManager[i + 1];
				float d = a.distance(b);

				if (d >= tDistance)
				{
					Vector3 direction = (b - a).normalized();

					Vector3 cp = a + direction * tDistance;
					Vector3 p = a + direction * ((i == pathManager.size() - 2) ? std::min(tDistance + input.radius, d) : (tDistance + input.radius));

					PredictionOutput result = PredictionOutput(input);
					result.castPosition = result.castPosition = cp;
					result.predictedPosition = p;
					return result;
				}

				tDistance -= d;
			}
		}

		PredictionOutput result = PredictionOutput(input);
		result.predictedPosition = Vector3(0, 0, 0);
		return result;

	}

	std::tuple<float, Vector2> Prediction::VectorMovementCollision(Vector2 startPoint1, Vector2 endPoint1, float v1, Vector2 startPoint2, float v2, float delay)
	{
		float sP1x = startPoint1.x,
			sP1y = startPoint1.y,
			eP1x = endPoint1.x,
			eP1y = endPoint1.y,
			sP2x = startPoint2.x,
			sP2y = startPoint2.y;

		float FLOAT_EPSILON = 1.401298E-45f;
		float FLOAT_NAN = std::numeric_limits<float>::quiet_NaN();
		float FLOAT_MAX_VALUE = std::numeric_limits<float>::max();

		float	d = eP1x - sP1x, e = eP1y - sP1y;
		float	dist = (float)std::sqrt(d * d + e * e), t1 = FLOAT_NAN;
		float	S = std::abs(dist) > FLOAT_EPSILON ? v1 * d / dist : 0,
			K = (std::abs(dist) > FLOAT_EPSILON) ? v1 * e / dist : 0;

		float r = sP2x - sP1x, j = sP2y - sP1y;
		auto c = r * r + j * j;

		if (dist > 0)
		{
			if (std::abs(v1 - FLOAT_MAX_VALUE) < FLOAT_EPSILON)
			{
				auto t = dist / v1;
				t1 = v2 * t >= 0 ? t : FLOAT_NAN;
			}
			else if (std::abs(v2 - FLOAT_MAX_VALUE) < FLOAT_EPSILON)
			{
				t1 = 0;
			}
			else
			{
				float a = S * S + K * K - v2 * v2, b = -r * S - j * K;

				if (std::abs(a) < FLOAT_EPSILON)
				{
					if (std::abs(b) < FLOAT_EPSILON)
					{
						t1 = (std::abs(c) < FLOAT_EPSILON) ? 0 : FLOAT_NAN;
					}
					else
					{
						auto t = -c / (2 * b);
						t1 = (v2 * t >= 0) ? t : FLOAT_NAN;
					}
				}
				else
				{
					auto sqr = b * b - a * c;
					if (sqr >= 0)
					{
						auto nom = (float)std::sqrt(sqr);
						auto t = (-nom - b) / a;
						t1 = v2 * t >= 0 ? t : FLOAT_NAN;
						t = (nom - b) / a;
						auto t2 = (v2 * t >= 0) ? t : FLOAT_NAN;

						if (!std::isnan(t2) && !std::isnan(t1))
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
		else if (std::abs(dist) < FLOAT_EPSILON)
		{
			t1 = 0;
		}

		return std::make_tuple(t1, std::isnan(t1) == false ? Vector2(sP1x + S * t1, sP1y + K * t1) : Vector2());
	}

	Vector3 Prediction::BasicPrediction(IGameObject* target, float spellRadius, float spellRange, float missileSpeed, float castDelay)
	{
		IGameObject* player = me;
		auto navigation = target->pathController();
		if (!navigation) target->position();
		auto pathManager = navigation->currentPath();

		if (!navigation->isMoving())
			return target->position();

		/*
		int ping = 40;
		float flyTimeMax = spellRange / missileSpeed;
		float t_min = castDelay + ping / 1000.f;
		float t_max = flyTimeMax + castDelay + ping / 1000.f;
		*/

		int ping = g_game->getPing();
		DLOG(ping);
		float flytime_max = (missileSpeed != 0) ? spellRange / missileSpeed : 0.f;
		float t_min = castDelay + ping / 1000.f;
		float t_max = flytime_max + castDelay + ping / 1000.f;
		float path_time = 0.f;


		int path_bounds_index[2] = { -1, -1 };

		int pathSize = pathManager.size();
		for (int i = 0; i < pathSize; ++i)
		{
			Vector3 cur = pathManager[i].to2D();			//skills hit calculating in 2d space
			Vector3 next = pathManager[i + 1].to2D();		//because height is not neccessary but when calculating the distance in 3d
			float t = next.distance(cur);								//that causes a little difference in calculating so it will likely miss the target

			if (path_time <= t_min && path_time + t >= t_min)
				path_bounds_index[0] = i;
			if (path_time <= t_max && path_time + t >= t_max)
				path_bounds_index[1] = i;
			if (path_bounds_index[0] >= 0 && path_bounds_index[1] >= 0)
				break;

			path_time += t;
		}

		//if skill will hit to the target within the boundaries
		if (path_bounds_index[0] >= 0 && path_bounds_index[1] >= 0)
		{
			int curr_path_index = path_bounds_index[0];
			while (true)
			{
				Vector3 cur = pathManager[curr_path_index].to2D();
				Vector3 next = pathManager[curr_path_index + 1].to2D();

				Vector3 direction = (next - cur).normalized();

				float extender = target->boundingRadius();
				float distance = spellRadius;

				int steps = (int)floor(cur.distance(next) / distance);

				if (steps > 0 && steps < 1000)
				{
					for (int i = 1; i < steps - 1; i++)
					{
						Vector3 center = cur + direction * distance * i;
						Vector3 pt_a = center - direction * extender;
						Vector3 pt_b = center + direction * extender;

						float flytime = (missileSpeed != 0) ? player->position().distance(target->position()) / missileSpeed : 0.f;
						float t = flytime + castDelay + ping / 1000.f;

						float arrive_time_a = target->position().distance(pt_a) / target->stats()->moveSpeed();
						float arrive_time_b = target->position().distance(pt_b) / target->stats()->moveSpeed();

						Vector3 predicted_pos = center;
						if (std::min(arrive_time_a, arrive_time_b) <= t && std::max(arrive_time_a, arrive_time_b) >= t)
						{
							return center;
						}
					}
				}

				if (curr_path_index == path_bounds_index[1])
					break;

				++curr_path_index;
			}
		}

		return Vector3(0, 0, 0);
	}
}