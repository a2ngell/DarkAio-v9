#pragma once
#include <SDK/src/SDK.h>

enum ESpellCastType
{
	Cone = 1,
	Line = 2,
	MissileLine = 3
};


namespace Predection
{
	void load();
	void unload();

	struct PredictionInput
	{
		Vector3 from = g_localPlayer->position();
		float delay = 0;
		float radius = 1.f;
		float range = FLT_MAX;
		float speed = FLT_MAX;
		ESpellCastType castType;
		IGameObject* target;
	};

	class PredictionOutput
	{
	public:
		PredictionOutput(PredictionInput input) {
			this->input = input;
			this->castPosition = g_localPlayer->position();
		}

		PredictionInput input;
		Vector3 castPosition;
		Vector3 predictedPosition;
	};

	class Prediction
	{
	public:
		static PredictionOutput GetPositionOnPath(PredictionInput input);
		static std::tuple<float, Vector2> VectorMovementCollision(Vector2 startPoint1, Vector2 endPoint1, float v1, Vector2 startPoint2, float v2, float delay);

		static Vector3 BasicPrediction(IGameObject* target, float spellRadius, float spellRange, float missileSpeed, float castDelay);
	};

}