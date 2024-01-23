#include "Varus.h"
#include <SDK/src/SDK.h>

namespace Varus
{
	std::vector<std::string> comboBoxModes =
	{
	  xorstr_("Q-E"),
	  xorstr_("E-Q"),
	};
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Varus"), xorstr_("DarkAio Varus"));

		MenuTabPtr combogeneralTab = menu->createTab(xorstr_("combogeneral"), xorstr_("Combo"));
		MenuTabPtr harassgeneralTab = menu->createTab(xorstr_("harassgeneral"), xorstr_("Harass"));
		MenuTabPtr killstealgeneralTab = menu->createTab(xorstr_("killstealgeneral"), xorstr_("Killsteal"));
		MenuTabPtr miscgeneralTab = menu->createTab(xorstr_("miscgeneral"), xorstr_("Misc"));
		MenuTabPtr farmgeneralTab = menu->createTab(xorstr_("farmgeneral"), xorstr_("Farm"));
		MenuTabPtr drawgeneralTab = menu->createTab(xorstr_("drawgeneral"), xorstr_("Draw"));

		TabChildPtr comboMenu = combogeneralTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr combomode = comboMenu->addComboBox(xorstr_("Combo Mode"), xorstr_("Combo Order"), comboBoxModes, comboBoxModes[0]);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr ComboQPassiveCount = comboMenu->addSlider(xorstr_("comboqpasivecount"), xorstr_("Q If Min Passive Count >="), 0, 0, 3);
		MenuElementPtr ComboQExtrarange = comboMenu->addSlider(xorstr_("comboqextrarange"), xorstr_("Q Always Give Extra Range"), 200, 0, 300);
		MenuElementPtr comboQMax = comboMenu->addCheckBox(xorstr_("Use Q Max"), xorstr_("Use Q Only Max Range"), true);
		MenuElementPtr comboQignorepred = comboMenu->addCheckBox(xorstr_("Use Q predignore"), xorstr_("Ignore Q Pred If Q About The End"), true);
		MenuElementPtr combodisablepred = comboMenu->addCheckBox(xorstr_("Use DarkAio1 Pred"), xorstr_("Use DarkAio Pred(Beta)"), true);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboE = comboMenu->addCheckBox(xorstr_("Use E Combo"), xorstr_("Use E"), true);
		MenuElementPtr ComboEPassiveCount = comboMenu->addSlider(xorstr_("comboepasivecount"), xorstr_("E If Min Passive Count >="), 0, 0, 3);
		MenuElementPtr comboR = comboMenu->addCheckBox(xorstr_("Use R Combo"), xorstr_("Use R"), true);
		MenuElementPtr ComboRCount = comboMenu->addSlider(xorstr_("Use R Enemy Count"), xorstr_("Use R If Count Enemy In Range >="), 3, 1, 5);

		TabChildPtr hitchanceMenu = combogeneralTab->createTabChild(xorstr_("Hitchance Settings"), xorstr_("Hitchance Settings"), true);
		MenuElementPtr hitchanceqcombo = hitchanceMenu->addComboBox(xorstr_("Q Hitchance Combo"), xorstr_("Q Hitchance"), g_hitchanceList, HITCHANCE_LOW);
		MenuElementPtr hitchanceecombo = hitchanceMenu->addComboBox(xorstr_("E Hitchance Combo"), xorstr_("E Hitchance"), g_hitchanceList, HITCHANCE_LOW);
		MenuElementPtr hitchanceRcombo = hitchanceMenu->addComboBox(xorstr_("R Hitchance Combo"), xorstr_("Combo: R"), g_hitchanceList, HITCHANCE_HIGH);
		//MenuElementPtr delayq = hitchanceMenu->addSlider(xorstr_("delayq"), xorstr_("Q/W Delay"), 100, 0, 500);

		TabChildPtr harassMenu = harassgeneralTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassQMax = harassMenu->addCheckBox(xorstr_("Use Q Harassmax"), xorstr_("Use Q Only Max Range"), true);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), true);
		MenuElementPtr harassE = harassMenu->addCheckBox(xorstr_("Use E Harass"), xorstr_("Use E"), true);

		TabChildPtr KillstealMenu = killstealgeneralTab->createTabChild(xorstr_("Killsteal Settings"), xorstr_("Killsteal Settings"), true);
		MenuElementPtr KillstealQ = KillstealMenu->addCheckBox(xorstr_("Use Q Killsteal"), xorstr_("Use Q"), true);
		MenuElementPtr KillstealE = KillstealMenu->addCheckBox(xorstr_("Use E Killsteal"), xorstr_("Use E"), true);

		TabChildPtr MiscMenu = miscgeneralTab->createTabChild(xorstr_("Misc Settings"), xorstr_("Misc Settings"), true);
		MenuElementPtr antigapR = MiscMenu->addCheckBox(xorstr_("Use R Antigap"), xorstr_("Use R Antigap"), true);

		TabChildPtr FarmMenu = farmgeneralTab->createTabChild(xorstr_("Farm Settings"), xorstr_("Farm Settings"), true);
		MenuElementPtr clearQ = FarmMenu->addCheckBox(xorstr_("Use Q"), xorstr_("Use Q"), false);
		MenuElementPtr clearQMax = FarmMenu->addCheckBox(xorstr_("Use Q clear max"), xorstr_("Use Q Max Range"), false);
		MenuElementPtr clearE = FarmMenu->addCheckBox(xorstr_("Use E"), xorstr_("Use E"), false);
		MenuElementPtr clearMana = FarmMenu->addSlider(xorstr_("clearmana"), xorstr_("Min Mana Save"), 40, 0, 100);

		TabChildPtr drawingsMenu = drawgeneralTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 165, 0, 200, true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 165, 0, 200, true);
		ColorCheckbox drawRRange = addColorCheckbox(drawingsMenu, xorstr_("R"), 255, 165, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<PositionSpell> spellQ;
	std::unique_ptr<ChargeableSpell> spellQ2;
	std::unique_ptr<SelfSpellAoe> spellW;
	std::unique_ptr<PositionSpell> spellE;
	std::unique_ptr<PositionSpell> spellR;
	int QlvlDmg[] = { 10, 46, 83, 120, 156 };
	int ElvlDmg[] = { 60, 100, 140, 180, 220 };
	double RlvlDmg[] = { 150, 250, 350 };


	double lastqcasttime = 0;
	double lastq2casttime = 0;

	struct objectholder {
		IGameObject* object;
	};
	std::vector<IGameObject*> daggerholder;
	struct PredictionOutput
	{
		Vector3 position;
		float hitChance = 100.0f;
	};

	int countenemyinrange(Vector3 pos, int range)
	{
		auto count = 0;
		auto target1 = g_objectManager->players().alive().enemies().targetable().visible().inRange(pos, range);
		for (auto& target : target1)
		{
			count = count + 1;
		}
		return count;
	}

	int GetQDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmg = 0;
			if (g_localPlayer->spell(SpellSlot::Q)->level() >= 1)
			{
				dmg = dmg + QlvlDmg[g_localPlayer->spell(SpellSlot::Q)->level() - 1];
			}
			dmg = dmg + (g_localPlayer->stats()->totalAD() * 0.85);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, 0, dmg, 0);
		}
		return damage;
	}

	int GetEDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmg = 0;
			if (g_localPlayer->spell(SpellSlot::E)->level() >= 1)
			{
				dmg = dmg + ElvlDmg[g_localPlayer->spell(SpellSlot::E)->level() - 1];
			}
			dmg = dmg + (g_localPlayer->stats()->bonusAD() * 0.9);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, 0, dmg, 0);
		}
		return damage;
	}

	int GetRDamage(IGameObject* target, int amount)
	{
		auto damage = 0;
		if (target)
		{
			auto dmgap = 0;
			auto dmgad = 0;
			if (g_localPlayer->spell(SpellSlot::R)->level() >= 1)
			{
				dmgap = dmgap + RlvlDmg[g_localPlayer->spell(SpellSlot::R)->level() - 1];
			}
			dmgap = dmgap + (g_localPlayer->stats()->totalAP());
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, dmgap, 0, 0);
		}
		return damage;
	}

	int getcombodamage(IGameObject* target)
	{
		auto dmg = 0;
		if (target)
		{
			dmg = dmg + g_moduleManager->damageLib()->calculateAutoAttackDamage(g_localPlayer, target);
			if (spellQ->isReady())
			{
				dmg = dmg + GetQDamage(target);
			}
			if (spellE->isReady())
			{
				dmg = dmg + GetEDamage(target);
			}
			if (spellR->isReady())
			{
				dmg = dmg + GetRDamage(target, 9);
			}
		}
		return dmg;
	}

	bool varushaveqmissle()
	{
		if (!daggerholder.empty()) {

			for (IGameObject* dagger : daggerholder) {
				if (dagger)
				{
					return true;
				}
			}
		}
		return false;

	}
	bool castingq()
	{
		auto flag = false;
		auto buff = g_localPlayer->buff(BUFF_HASH("VarusQ"));
		if (buff && buff->isValid())
			flag = true;
		return flag;
	}

	bool castingw()
	{
		auto flag = false;
		auto buff = g_localPlayer->buff(BUFF_HASH("varuswempowered"));
		if (buff && buff->isValid())
			flag = true;
		return flag;
	}

	bool varuswbuff(IGameObject* target)
	{
		auto flag = false;
		auto buff = target->buff(BUFF_HASH("VarusWDebuff"));
		if (buff && buff->isValid())
			flag = true;
		return flag;
	}

	int varuswbuffcount(IGameObject* target)
	{
		auto count = 0;
		auto buff = target->buff(BUFF_HASH("VarusWDebuff"));
		if (buff && buff->isValid())
			count = buff->count();
		return count;
	}


	bool stillcastingq()
	{
		if (castingq() && lastqcasttime > lastq2casttime)
		{
			auto newtime = g_game->gameTime() - lastqcasttime;
			if (newtime > 3.5)
			{
				return true;
			}
		}
		return false;
	}
	
	double getqrange()
	{
		auto range = 895;
		auto gametime = g_game->gameTime();
		if (lastqcasttime + 0.25 < gametime)
		{
			range = 1035;
		}
		if (lastqcasttime + 0.5 < gametime)
		{
			range = 1175;
		}
		if (lastqcasttime + 0.75 < gametime)
		{
			range = 1315;
		}
		if (lastqcasttime + 1 < gametime)
		{
			range = 1455;
		}
		if (lastqcasttime + 1.25 < gametime)
		{
			range = 1595;
		}
		return range;
	}
	bool isplant(IGameObject* minion)
	{
		if (minion && minion->isVisionPlant() || minion->isJumpPlant() || minion->isHealthPlant() || minion->isWard() || minion->name().find("Ward") != std::string::npos || minion->name().find("JammerDevice") != std::string::npos)
		{
			return true;
		}
		return false;

	}
	bool IsSpecificObjectInWay(Vector3 sourcePos, Vector3 targetPos, IGameObject* collisionObject, float projectileRadius)
	{
		auto sourceToTarget = targetPos - sourcePos;
		sourceToTarget.y = 0.0f;
		auto distance = sourceToTarget.length();

		auto objPos = collisionObject->position();
		auto sourceToObj = objPos - sourcePos;
		sourceToObj.y = 0.0f;
		if (sourceToObj.length() > distance) return false;

		float dot1 = sourceToObj.dot(sourceToTarget);
		float dot2 = sourceToTarget.dot(sourceToTarget);

		if (dot1 < 0.0f) return false;

		float t = dot1 / dot2;

		Vector3 projection = sourcePos + (sourceToTarget * t);
		projection.y = 0.0;

		Vector3 distVector = objPos - projection;
		distVector.y = 0.0;

		if (distVector.length() <= projectileRadius + collisionObject->boundingRadius())
			return true;

		return false;
	}

	bool IsAnyObjectInWay(Vector3 sourcePos, Vector3 targetPos, IGameObject* sourceObject, IGameObject* targetObject, float projectileRadius)
	{
		auto objectInWay = [&](auto objectManager) {
			auto sourceToTarget = targetPos - sourcePos;
			sourceToTarget.y = 0.0f;
			auto distance = sourceToTarget.length();

			for (auto obj : objectManager)
			{
				if (obj == targetObject || obj == sourceObject) continue;
				if (!obj->isValid()) continue;
				if (isplant(obj)) continue;

				if (IsSpecificObjectInWay(sourcePos, targetPos, obj, projectileRadius))
					return true;
			}
			return false;
		};
		return objectInWay(g_objectManager->minions().alive().enemies().targetable()) || objectInWay(g_objectManager->players().alive().enemies().targetable());
	}

	bool CheckCollision(Vector3 sourcePos, Vector3 targetPos, IGameObject* sourceObject, IGameObject* targetObject, PositionSpell skillshot)
	{
	/*	for (const auto& collision : skillshot.collisions()) {
			if (collision == Collisions::Minions || collision == Collisions::Heros)
			{
				if (IsAnyObjectInWay(sourcePos, targetPos, sourceObject, targetObject, skillshot.radius()))
					return false;
			}
		}
		return true;*/
		CollisionInput collisionInput;
		collisionInput.source = sourceObject;
		collisionInput.target = targetObject;
		collisionInput.from = sourcePos;
		collisionInput.to = targetPos;
		collisionInput.radius = skillshot.radius();
		collisionInput.collisions = skillshot.collisions();
		auto wallcoals = g_moduleManager->collision()->collisionCheck(collisionInput);
		if (wallcoals.isCollision)
		{
			return false;
		}
		return true;
	}

	Vector3 GetObjectPositionAfterTime(IGameObject* obj, float time, float distanceBuffer)
	{
		const auto aiManager = obj->pathController();

		float speed = obj->stats()->moveSpeed();
		if (aiManager->isDashing())
		{
			speed = aiManager->dashSpeed();
		}
		//DLOG("time");
		//DLOG(time);
		std::vector<Vector3> waypoints = { obj->serverPosition() };
		auto futureWaypoints = aiManager->currentPath();
		for (auto waypoint : futureWaypoints)
			waypoints.push_back(waypoint);

		const int waypointsSize = (int)waypoints.size();

		if (!waypointsSize || !time || !aiManager->isMoving())
			return obj->serverPosition();

		float distance = (speed * time) - distanceBuffer;
		//DLOG("waypointsize");
		//DLOG(waypointsSize);

		for (int i = 1; i < waypointsSize; i++)
		{
			//DLOG("i");
			//DLOG(i);
			if (i > 1)
			{
				if (waypointsSize == 1)
					return waypoints.front();
				const float waydistance = waypoints[i - 1].distance(waypoints[i]);
				//DLOG("waydistance");
				//DLOG(waydistance);
				//DLOG("distance");
				//DLOG(distance);
				if (waydistance >= distance)
				{
					return waypoints[i - 1].extend(waypoints[i], distance);
				}
				distance = distance - waydistance;
				if (i == waypointsSize - 1)
					return waypoints[i];
				distance = distance - waydistance;
			}
		}

		return waypoints.front();
	}

	float CalculateHitchance(float distance) {
		const float maxDistance = 400.0f;

		if (distance > maxDistance) {
			return 0.0f;
		}

		float hitchance = 100.0f - (distance / maxDistance) * 100.0f;

		return std::max(0.0f, std::min(100.0f, hitchance));
	}

	bool GetPrediction1(IGameObject* sourceObj, IGameObject* target, PositionSpell spell, PredictionOutput& out)
	{
		out.hitChance = 100.0f;
		const auto sourcePos = sourceObj->serverPosition();
		const auto targetAiManager = target->pathController();
		const float spellRadius = spell.radius();

		float distance = sourcePos.distance(target->serverPosition());
		float distanceBuffer = spell.skillshotType() == SkillshotType::Circle ? std::max(spellRadius - 20.0f, 0.0f) : 0.0f;

		if (distance > spell.range())
			return false;

		if (!spell.speed())
		{
			out.position = GetObjectPositionAfterTime(target, (spell.castDelay() / 1000), distanceBuffer);
			return CheckCollision(sourcePos, out.position, sourceObj, target, spell);
		}
		auto waypoints = targetAiManager->currentPath();
		const int waypointsSize = waypoints.size();

		if (!waypointsSize || !targetAiManager->isMoving())
		{
			out.position = target->serverPosition();
			out.hitChance = 100.0f;	
			return CheckCollision(sourcePos, out.position, sourceObj, target, spell);
		}
		if (waypoints.size() > 0 && targetAiManager->isDashing())
		{
			out.position = waypoints.back();
			out.hitChance = 100.0f;
			return CheckCollision(sourcePos, out.position, sourceObj, target, spell);
		}
		float travelTime = (distance / spell.speed()) + (spell.castDelay() / 1000);

		auto predictedPos = GetObjectPositionAfterTime(target, travelTime, distanceBuffer);
		distance = predictedPos.distance(sourcePos);
		float missileTime = (distance / spell.speed()) + (spell.castDelay() / 1000);

		travelTime = missileTime;
		predictedPos = GetObjectPositionAfterTime(target, travelTime, distanceBuffer);

		distance = predictedPos.distance(sourcePos);
		if (distance > spell.range())
		{
			return false;
		}

		missileTime = (distance / spell.speed()) + (spell.castDelay() / 1000);
		/*}*/
		//out.hitChance = CalculateHitchance(predictedPos.distance(target->position()));
		out.position = predictedPos;
		return CheckCollision(sourcePos, out.position, sourceObj, target, spell);;
	}

	bool GetPrediction(IGameObject* target, PositionSpell spell, PredictionOutput& out)
	{
		if (!target) return false;

		return GetPrediction1(g_localPlayer, target, spell, out);
	}

	void castq2(IGameObject* target)
	{
		if (g_menu->combodisablepred->getBool())
		{
			PredictionOutput qpred;
			auto newspell = PositionSpell(SpellSlot::Q);
			newspell.setCastDelay(400);
			newspell.setRange(getqrange() - g_menu->ComboQExtrarange->getInt());
			newspell.setCollisions({ Collisions::Windwall });
			newspell.setBoundingRadiusCollision(false);
			newspell.setSpeed(1900);
			newspell.setRadius(140);
			newspell.setSkillshotType(SkillshotType::Line);
			auto pred = GetPrediction(target, newspell, qpred);
			if (pred)
			{
				//spellQ->cast(qpred.position);
				g_localPlayer->castSpell(SpellSlot::Q, qpred.position);
			}
		}
		else if (!g_menu->combodisablepred->getBool())
		{
			PredictionInput input;
			input.caster = g_localPlayer;
			input.target = target;
			input.rangeCheckFrom = g_localPlayer->position();
			input.range = getqrange() - g_menu->ComboQExtrarange->getInt();
			input.collisions = spellQ->collisions();
			input.useBoundingRadius = false;
			input.delay = 350;
			input.missileSpeed = spellQ->speed();
			input.radius = spellQ->radius();
			input.type = SkillshotType::Line;
			auto pred = g_moduleManager->prediction()->getPrediction(input);
			if (pred.hitchance >= Hitchance::Instant)
			{
				spellQ->castPrediction(target, fromString(g_menu->hitchanceqcombo->getString()));
			}
		}
	}

	void caste(IGameObject* target)
	{
		PredictionInput input;
		input.caster = g_localPlayer;
		input.target = target;
		input.rangeCheckFrom = g_localPlayer->position();
		input.range = spellE->range();
		input.collisions = spellE->collisions();
		input.useBoundingRadius = false;
		input.delay = spellE->castDelay();
		input.missileSpeed = spellE->speed();
		input.radius = spellE->radius();
		input.type = SkillshotType::Circle;
		auto pred = g_moduleManager->prediction()->getPrediction(input);
		if (pred.hitchance >= Hitchance::Instant)
		{
			spellE->castPrediction(target, fromString(g_menu->hitchanceecombo->getString()));
		}
	}

	void castr(IGameObject* target)
	{
		PredictionInput input;
		input.caster = g_localPlayer;
		input.target = target;
		input.rangeCheckFrom = g_localPlayer->position();
		input.range = spellR->range();
		input.collisions = spellR->collisions();
		input.useBoundingRadius = false;
		input.delay = spellR->castDelay();
		input.missileSpeed = spellR->speed();
		input.radius = spellR->radius();
		input.type = SkillshotType::Line;
		auto pred = g_moduleManager->prediction()->getPrediction(input);
		if (pred.hitchance >= Hitchance::Instant)
		{
			spellE->castPrediction(target, fromString(g_menu->hitchanceRcombo->getString()));
		}
	}
	IGameObject* getnewtarget(float range)
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, range);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			return target;
		}
		return nullptr;
	}

	void combo()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 3000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		if (g_menu->combomode->getInt() == 0)
		{
			for (auto target : selectedEnemies)
			{
				if (g_menu->comboR->getBool() && spellR->isReady() && !castingq())
				{
					if (countenemyinrange(target->position(), 600) >= g_menu->ComboRCount->getInt())
					{
						castr(target);
					}
				}
				if (g_menu->comboQ->getBool() && spellQ->isReady())
				{
					if (!castingq() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						if (g_menu->ComboQPassiveCount->getInt() == 0)
						{
							if (g_menu->comboW->getBool() && spellW->isReady() && !castingw())
							{
								spellW->cast();
							}
							spellQ2->startChargeing(g_hud->mousePosition());
						}
						else
						{
							if (varuswbuff(target) && varuswbuffcount(target) >= g_menu->ComboQPassiveCount->getInt())
							{
								if (g_menu->comboW->getBool() && spellW->isReady() && !castingw())
								{
									spellW->cast();
								}
								spellQ2->startChargeing(g_hud->mousePosition());
							}
						}
					}
				}
			}
			if (g_menu->comboQ->getBool() && spellQ->isReady())
			{
				auto target = getnewtarget(spellQ->range());
				if (castingq() && target)
				{
					if (g_menu->comboQMax->getBool() && getqrange() == 1595)
					{
						castq2(target);
					}
					else if (!g_menu->comboQMax->getBool())
					{
						castq2(target);
					}
					if (stillcastingq() && g_menu->comboQignorepred->getBool())
					{
						if (target->position().distance(g_localPlayer->position()) < getqrange())
						{
							auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 250, spellQ->speed());
							spellQ2->cast(pred.predictedPosition);
						}
					}
				}
			}
			if (g_menu->comboE->getBool() && spellE->isReady() && !castingq() && !varushaveqmissle())
			{
				auto target = getnewtarget(spellE->range());
				if (target)
				{
					if (g_menu->ComboEPassiveCount->getInt() == 0)
					{
						caste(target);
					}
					else
					{
						if (varuswbuff(target) && varuswbuffcount(target) >= g_menu->ComboEPassiveCount->getInt())
						{
							caste(target);
						}
					}
				}
			}
		}
		if (g_menu->combomode->getInt() == 1)
		{
			if (g_menu->comboE->getBool() && spellE->isReady() && !castingq() && !varushaveqmissle())
			{
				auto target = getnewtarget(spellE->range());
				if (target)
				{
					if (g_menu->ComboEPassiveCount->getInt() == 0)
					{
						caste(target);
					}
					else
					{
						if (varuswbuff(target) && varuswbuffcount(target) >= g_menu->ComboEPassiveCount->getInt())
						{
							caste(target);
						}
					}
				}
			}
			for (auto target : selectedEnemies)
			{
				if (g_menu->comboR->getBool() && spellR->isReady() && !castingq())
				{
					if (countenemyinrange(target->position(), 600) >= g_menu->ComboRCount->getInt())
					{
						castr(target);
					}
				}
				if (g_menu->comboQ->getBool() && spellQ->isReady())
				{
					if (!castingq() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						if (g_menu->ComboQPassiveCount->getInt() == 0)
						{
							if (g_menu->comboW->getBool() && spellW->isReady() && !castingw())
							{
								spellW->cast();
							}
							spellQ2->startChargeing(g_hud->mousePosition());
						}
						else
						{
							if (varuswbuff(target) && varuswbuffcount(target) >= g_menu->ComboQPassiveCount->getInt())
							{
								if (g_menu->comboW->getBool() && spellW->isReady() && !castingw())
								{
									spellW->cast();
								}
								spellQ2->startChargeing(g_hud->mousePosition());
							}
						}
					}
				}
			}
			if (g_menu->comboQ->getBool() && spellQ->isReady())
			{
				auto target = getnewtarget(spellQ->range());
				if (castingq() && target)
				{
					if (g_menu->comboQMax->getBool() && getqrange() == 1595)
					{
						castq2(target);
					}
					else if (!g_menu->comboQMax->getBool())
					{
						castq2(target);
					}
					if (stillcastingq() && g_menu->comboQignorepred->getBool())
					{
						if (target->position().distance(g_localPlayer->position()) < getqrange())
						{
							auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 250, spellQ->speed());
							spellQ2->cast(pred.predictedPosition);
						}
					}
				}
			}
		}
	}

	void harass()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 3000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		if (g_menu->combomode->getInt() == 0)
		{
			for (auto target : selectedEnemies)
			{
				if (g_menu->harassQ->getBool() && spellQ->isReady())
				{
					if (!castingq() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						if (g_menu->ComboQPassiveCount->getInt() == 0)
						{
							if (g_menu->harassW->getBool() && spellW->isReady() && !castingw())
							{
								spellW->cast();
							}
							spellQ2->startChargeing(g_hud->mousePosition());
						}
						else
						{
							if (varuswbuff(target) && varuswbuffcount(target) >= g_menu->ComboQPassiveCount->getInt())
							{
								if (g_menu->harassW->getBool() && spellW->isReady() && !castingw())
								{
									spellW->cast();
								}
								spellQ2->startChargeing(g_hud->mousePosition());
							}
						}
					}
				}
			}
			if (g_menu->harassQ->getBool() && spellQ->isReady())
			{
				auto target = getnewtarget(spellQ->range());
				if (castingq() && target)
				{
					if (g_menu->harassQMax->getBool() && getqrange() == 1595)
					{
						castq2(target);
					}
					else if (!g_menu->harassQMax->getBool())
					{
						castq2(target);
					}
					if (stillcastingq() && g_menu->comboQignorepred->getBool())
					{
						if (target->position().distance(g_localPlayer->position()) < getqrange())
						{
							auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 250, spellQ->speed());
							spellQ2->cast(pred.predictedPosition);
						}
					}
				}
			}
			if (g_menu->harassE->getBool() && spellE->isReady() && !castingq() && !varushaveqmissle())
			{
				auto target = getnewtarget(spellE->range());
				if (target)
				{
					if (g_menu->ComboEPassiveCount->getInt() == 0)
					{
						caste(target);
					}
					else
					{
						if (varuswbuff(target) && varuswbuffcount(target) >= g_menu->ComboEPassiveCount->getInt())
						{
							caste(target);
						}
					}
				}
			}
		}
		if (g_menu->combomode->getInt() == 1)
		{
			if (g_menu->harassE->getBool() && spellE->isReady() && !castingq() && !varushaveqmissle())
			{
				auto target = getnewtarget(spellE->range());
				if (target)
				{
					if (g_menu->ComboEPassiveCount->getInt() == 0)
					{
						caste(target);
					}
					else
					{
						if (varuswbuff(target) && varuswbuffcount(target) >= g_menu->ComboEPassiveCount->getInt())
						{
							caste(target);
						}
					}
				}
			}
			for (auto target : selectedEnemies)
			{
				if (g_menu->harassQ->getBool() && spellQ->isReady())
				{
					if (!castingq() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						if (g_menu->ComboQPassiveCount->getInt() == 0)
						{
							if (g_menu->harassW->getBool() && spellW->isReady() && !castingw())
							{
								spellW->cast();
							}
							spellQ2->startChargeing(g_hud->mousePosition());
						}
						else
						{
							if (varuswbuff(target) && varuswbuffcount(target) >= g_menu->ComboQPassiveCount->getInt())
							{
								if (g_menu->harassW->getBool() && spellW->isReady() && !castingw())
								{
									spellW->cast();
								}
								spellQ2->startChargeing(g_hud->mousePosition());
							}
						}
					}
				}
			}
			if (g_menu->harassQ->getBool() && spellQ->isReady())
			{
				auto target = getnewtarget(spellQ->range());
				if (castingq() && target)
				{
					if (g_menu->harassQMax->getBool() && getqrange() == 1595)
					{
						castq2(target);
					}
					else if (!g_menu->harassQMax->getBool())
					{
						castq2(target);
					}
					if (stillcastingq() && g_menu->comboQignorepred->getBool())
					{
						if (target->position().distance(g_localPlayer->position()) < getqrange())
						{
							auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 250, spellQ->speed());
							spellQ2->cast(pred.predictedPosition);
						}
					}
				}
			}
		}
	}

	void active()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 3000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (g_menu->KillstealE->getBool() && GetEDamage(target) > target->health() && spellE->isReady() && !castingq() && !varushaveqmissle())
			{
				spellE->castPrediction(target, Hitchance::Medium);
			}
			if (g_menu->KillstealQ->getBool() && spellQ->isReady())
			{
				if (!castingq())
				{
					if (GetQDamage(target) > target->health())
					{
						spellQ2->startChargeing(g_hud->mousePosition());
					}
					if (spellW->isReady() && !castingw() && GetQDamage(target) < target->health() && GetQDamage(target) * 2 > target->health())
					{
						spellW->cast();
						spellQ2->startChargeing(g_hud->mousePosition());
					}
				}
				if (castingq())
				{
					if (GetQDamage(target) > target->health())
					{
						castq2(target);
					}
					else if (GetQDamage(target) < target->health() && GetQDamage(target) * 2 > target->health())
					{
						castq2(target);
					}
				}
			}
		}
	}

	int countminioninrange(Vector3 pos, float range)
	{
		auto count = 0;
		auto minions = g_objectManager->minions().alive().enemies().targetable().visible().inRange(pos, range);
		for (auto& minion : minions)
		{
			if (minion)
			{
				count++;
			}
		}
		return count;
	}

	auto lastfarm = 0;
	void laneclear()
	{
		if ((g_localPlayer->maxResource() / 100) * g_menu->clearMana->getInt() < g_localPlayer->resource())
		{
			auto target2 = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
			for (auto target : target2)
			{
				if (g_menu->clearQ->getBool() && spellQ->isReady() && target->position().distance(g_localPlayer->position()) < spellQ->range())
				{
					if (!castingq() && countminioninrange(target->position(), 300) >= 3)
					{
						spellQ2->startChargeing(g_hud->mousePosition());
						//lastfarm = target->networkID();
					}
					if (castingq() && countminioninrange(target->position(), 300) >= 3)
					{
						if (g_menu->clearQMax->getBool() && getqrange() == 1595)
						{
							castq2(target);
						}
						else if (!g_menu->clearQMax->getBool())
						{
							castq2(target);
						}
					}
					if (stillcastingq())
					{
						if (target->position().distance(g_localPlayer->position()) < getqrange())
						{
							spellQ2->cast(target->position());
						}
					}
				}
				if (g_menu->clearE->getBool() && spellE->isReady() && !castingq() && !varushaveqmissle() && target->position().distance(g_localPlayer->position()) < spellE->range() && countminioninrange(target->position(), 300) >= 3)
				{
					caste(target);
				}
			}
		}
		
	}

	void onDraw(OnDrawEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			if (g_menu->drawQRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::Q)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellQ->range(), 2, g_menu->drawQRange.color->getColor());
			}
			if (g_menu->drawERange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::E)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellE->range() - 75, 2, g_menu->drawERange.color->getColor());
			}
			if (g_menu->drawRRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::R)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellR->range(), 2, g_menu->drawRRange.color->getColor());
			}
			auto newpos = g_localPlayer->position().toScreen();
			g_drawings->drawText(Vector2(newpos.x - 30, newpos.y + 50), "DarkAio", 25, 0xff000000, false, false);
		}
	}

	void antigap1()
	{
		if (g_menu->antigapR->getBool() && spellR->isReady())
		{
			auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
			for (auto target : target2)
			{
				if (target)
				{
					std::vector<Vector3> path = target->pathController()->currentPath();
					if (path.size() > 0) {
						auto endPos = path.back();
						if (target->pathController()->isDashing() == true &&
							endPos.distance(g_localPlayer->position()) < 400 &&
							endPos.distance(g_localPlayer->position()) < target->position().distance(g_localPlayer->position())) {
							spellR->castPrediction(target, Hitchance::High);
						}
					}
				}
			}

		}
	}
	bool lastqcheck = false;

	void onUpdate(GameUpdateEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			auto activeSpell = g_localPlayer->activeSpell();
			if (activeSpell)
			{
				if (activeSpell->info()->name() == xorstr_("VarusQ"))
				{
					lastqcasttime = activeSpell->startTime();
				}
			}
			antigap1();
			auto orb = g_moduleManager->orbwalker();
			active();
			if (orb->isComboMode())
			{
				combo();
			}
			else if (orb->isHarassMode())
			{
				harass();
			}
			else if (orb->isLaneClearMode())
			{
				laneclear();
			}
		}
	}

	void finishspell(OnStopCastEventArgs* args)
	{
	}

	void onobjectcreate(OnObjectCreateEventArgs* args)
	{
		if (args->object && args->object->name().find("VarusQMissile") != std::string::npos)
		{
			lastq2casttime = g_game->gameTime();
			daggerholder.push_back(args->object);
		}
	}
	void onobjectdelete(OnObjectDeleteEventArgs* args)
	{
		if (args->object &&
			args->object->name().find("VarusQMissile") != std::string::npos)
			{
			for (int i = 0; i < daggerholder.size(); i++) {

				if (daggerholder[i]->networkID() == args->object->networkID()) {
					daggerholder.erase(daggerholder.begin() + i);
				}
			}
		}
	}

	void preattack1(OnOrbwalkerPreAttackEventArgs* args)
	{
		if (castingq())
		{
			args->process = false;
		}
	}

	void load()
	{
		g_menu = new Menu();

		spellQ = std::make_unique<PositionSpell>(SpellSlot::Q);
		spellQ->setCastDelay(150);
		spellQ->setRange(1595);
		spellQ->setCollisions({ Collisions::Windwall });
		spellQ->setBoundingRadiusCollision(false);
		spellQ->setSpeed(1900);
		spellQ->setRadius(140);
		spellQ->setSkillshotType(SkillshotType::Line);

		spellQ2 = std::make_unique<ChargeableSpell>(SpellSlot::Q);
		spellQ2->setCastDelay(150);
		spellQ2->setRange(1595);
		spellQ2->setCollisions({ Collisions::Windwall });
		spellQ2->setBoundingRadiusCollision(false);
		spellQ2->setSpeed(1900);
		spellQ2->setRadius(140);
		spellQ2->setSkillshotType(SkillshotType::Line);

		spellW = std::make_unique<SelfSpellAoe>(SpellSlot::W);
		spellW->setEffectRange(325);

		spellE = std::make_unique<PositionSpell>(SpellSlot::E);
		spellE->setCastDelay(400);
		spellE->setRange(1000);
		spellE->setCollisions({ Collisions::Windwall });
		spellE->setBoundingRadiusCollision(false);
		spellE->setSpeed(2000);
		spellE->setRadius(300);
		spellE->setSkillshotType(SkillshotType::Circle);

		spellR = std::make_unique<PositionSpell>(SpellSlot::R);
		spellR->setCastDelay(150);
		spellR->setRange(1370);
		spellR->setCollisions({ Collisions::Windwall });
		spellR->setBoundingRadiusCollision(false);
		spellR->setSpeed(1900);
		spellR->setRadius(140);
		spellR->setSkillshotType(SkillshotType::Line);

		EventHandler<Events::OnDraw>::subscribe(onDraw);
		//EventHandler<Events::OnStopCast>::subscribe(finishspell);
		EventHandler<Events::OnOrbwalkerPreAttack>::subscribe(preattack1);
		EventHandler<Events::GameUpdate>::subscribe(onUpdate);
		EventHandler<Events::OnObjectCreate>::subscribe(onobjectcreate);
		EventHandler<Events::OnObjectDelete>::subscribe(onobjectdelete);
	}

	void unload()
	{
		EventHandler<Events::OnDraw>::unsubscribe(onDraw);
		//EventHandler<Events::OnStopCast>::unsubscribe(finishspell);
		EventHandler<Events::OnOrbwalkerPreAttack>::unsubscribe(preattack1);
		EventHandler<Events::GameUpdate>::unsubscribe(onUpdate);
		EventHandler<Events::OnObjectCreate>::subscribe(onobjectcreate);
		EventHandler<Events::OnObjectDelete>::subscribe(onobjectdelete);

		spellQ.reset();
		spellQ2.reset();
		spellW.reset();
		spellE.reset();
		spellR.reset();

		g_mainMenu->removeMenu(g_menu->menu);
		delete g_menu;
	}
}