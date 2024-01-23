#include "Ezreal.h"
#include <SDK/src/SDK.h>

namespace Ezreal
{
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Ezreal"), xorstr_("DarkAio Ezreal"));

		MenuTabPtr combogeneralTab = menu->createTab(xorstr_("combogeneral"), xorstr_("Combo"));
		MenuTabPtr harassgeneralTab = menu->createTab(xorstr_("harassgeneral"), xorstr_("Harass"));
		MenuTabPtr killstealgeneralTab = menu->createTab(xorstr_("killstealgeneral"), xorstr_("Killsteal"));
		MenuTabPtr miscgeneralTab = menu->createTab(xorstr_("miscgeneral"), xorstr_("Misc"));
		MenuTabPtr farmgeneralTab = menu->createTab(xorstr_("farmgeneral"), xorstr_("Farm"));
		MenuTabPtr drawgeneralTab = menu->createTab(xorstr_("drawgeneral"), xorstr_("Draw"));

		TabChildPtr comboMenu = combogeneralTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr settarget = comboMenu->addCheckBox(xorstr_("setw"), xorstr_("Change Q Target To One Who Has W Buff"), true);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboE = comboMenu->addCheckBox(xorstr_("Use E Combo"), xorstr_("Use E (i don't suggest to open better with hand)"), true);
		MenuElementPtr comboR = comboMenu->addCheckBox(xorstr_("Use R Combo"), xorstr_("Use R"), true);
		MenuElementPtr combodisablepred = comboMenu->addCheckBox(xorstr_("Use DarkAio1 Pred(Beta)"), xorstr_("Use DarkAio Pred(Beta)"), true);

		TabChildPtr hitchanceMenu = combogeneralTab->createTabChild(xorstr_("Hitchance Settings"), xorstr_("Hitchance Settings"), true);
		//MenuElementPtr darkpredhitchance = hitchanceMenu->addSlider(xorstr_("darkpredhitcha"), xorstr_("DarkAio Pred HitChance"), 30, 0, 100);
		MenuElementPtr comboQrange = hitchanceMenu->addSlider(xorstr_("qranng"), xorstr_("Q/W Max Range %"), 90, 0, 100);
		MenuElementPtr hitchanceqcombo = hitchanceMenu->addComboBox(xorstr_("Q Hitchance Combo"), xorstr_("Q Hitchance"), g_hitchanceList, HITCHANCE_LOW);
		MenuElementPtr hitchancewcombo = hitchanceMenu->addComboBox(xorstr_("W Hitchance Combo"), xorstr_("W Hitchance"), g_hitchanceList, HITCHANCE_LOW);
		MenuElementPtr hitchancercombo = hitchanceMenu->addComboBox(xorstr_("R Hitchance Combo"), xorstr_("R Hitchance"), g_hitchanceList, HITCHANCE_LOW);
		//MenuElementPtr delayq = hitchanceMenu->addSlider(xorstr_("delayq"), xorstr_("Q/W Delay"), 100, 0, 500);

		TabChildPtr harassMenu = harassgeneralTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassQfarm = harassMenu->addCheckBox(xorstr_("useqfarm"), xorstr_("Use Q last hit farm"), true);
		MenuElementPtr clearManaharas = harassMenu->addSlider(xorstr_("clearmanaharas"), xorstr_("Min Mana Save farm q"), 40, 0, 100);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), false);
		MenuElementPtr autoq = harassMenu->addCheckBox(xorstr_("autqthinks"), xorstr_("Use Auto Q"), true);
		MenuElementPtr HarassQautokey = harassMenu->addKeybind(xorstr_("qautokey"), xorstr_("Q Auto Key"), Key::H);

		TabChildPtr KillstealMenu = killstealgeneralTab->createTabChild(xorstr_("Killsteal Settings"), xorstr_("Killsteal Settings"), true);
		MenuElementPtr KillstealQ = KillstealMenu->addCheckBox(xorstr_("Use Q Killsteal"), xorstr_("Use Q"), true);
		MenuElementPtr KillstealE = KillstealMenu->addCheckBox(xorstr_("Use E Killsteal"), xorstr_("Use E"), false);
		MenuElementPtr KillstealR = KillstealMenu->addCheckBox(xorstr_("Use R Killsteal"), xorstr_("Use R"), true);
		MenuElementPtr killsteal_r_maxdist = KillstealMenu->addSlider(xorstr_("krmax"), xorstr_("max R dist (you can see in draw)"), 3000, 0, 25000);
		MenuElementPtr killsteal_r_mindist = KillstealMenu->addSlider(xorstr_("krmin"), xorstr_("min R dist (you can see in draw)"), 1000, 0, 5000);

		TabChildPtr MiscMenu = miscgeneralTab->createTabChild(xorstr_("Misc Settings"), xorstr_("Misc Settings"), true);
		//MenuElementPtr usewtover = MiscMenu->addCheckBox(xorstr_("Use w tover"), xorstr_("Use W To Tover"), true);
		MenuElementPtr antigapE = MiscMenu->addCheckBox(xorstr_("Use eantigap "), xorstr_("Use E Anti Gap(Mouse Pos)"), true);
		std::unique_ptr<IGapcloseMenu> gapcloseMenuSpells = g_moduleManager->gapclose()->createGapcloseMenu(MiscMenu);

		TabChildPtr FarmMenu = farmgeneralTab->createTabChild(xorstr_("Farm Settings"), xorstr_("Farm Settings"), true);
		MenuElementPtr clearQ = FarmMenu->addCheckBox(xorstr_("Use Q"), xorstr_("Use Q"), true);
		MenuElementPtr clearQ_aa = FarmMenu->addCheckBox(xorstr_("Use Q clear max"), xorstr_("Use Q out of aa range"), false);
		MenuElementPtr clearQ_killable = FarmMenu->addCheckBox(xorstr_("qonlykill"), xorstr_("Use Q only killable"), true);
		MenuElementPtr clearMana = FarmMenu->addSlider(xorstr_("clearmana"), xorstr_("Min Mana Save"), 40, 0, 100);
		MenuElementPtr clearkey = FarmMenu->addKeybind(xorstr_("clearkey"), xorstr_("Farm Key"), Key::G);

		TabChildPtr drawingsMenu = drawgeneralTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 0, 0, 200, true);
		ColorCheckbox drawQdamage = addColorCheckbox(drawingsMenu, xorstr_("Q Damage"), 255, 165, 0, 200, true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 165, 0, 200, false);
		ColorCheckbox drawRKillable = addColorCheckbox(drawingsMenu, xorstr_("R Killable"), 255, 0, 0, 200, true);
		ColorCheckbox drawRmaxmin = addColorCheckbox(drawingsMenu, xorstr_("Draw R min/max dist (min blue) (max red)"), 255, 165, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<PositionSpell> spellQ;
	std::unique_ptr<PositionSpell> spellW;
	std::unique_ptr<PositionSpell> spellE;
	std::unique_ptr<PositionSpell> spellR;
	int QlvlDmg[] = { 20, 45, 70, 95, 120 };
	int ElvlDmg[] = { 80, 130, 180, 230, 280 };
	double RlvlDmg[] = { 350, 500 , 650 };

	bool haraskeyactive = false;
	bool farmkeyactive = false;

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
		Hitchance hitPorblty = Hitchance::Medium;
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

	enum CollidableObjects
	{
		Objects,
		Walls
	};

	int GetQDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmg = 0;
			auto magicdmg = 0;
			if (g_localPlayer->spell(SpellSlot::Q)->level() >= 1)
			{
				dmg = dmg + QlvlDmg[g_localPlayer->spell(SpellSlot::Q)->level() - 1];
			}
			dmg = dmg + (g_localPlayer->stats()->totalAD() * 1.3);
			magicdmg = magicdmg + (g_localPlayer->stats()->totalAP() * 0.15);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, magicdmg, dmg, 0);
		}
		return damage;
	}

	int GetEDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmg = 0;
			auto addamage = 0;
			if (g_localPlayer->spell(SpellSlot::E)->level() >= 1)
			{
				dmg = dmg + ElvlDmg[g_localPlayer->spell(SpellSlot::E)->level() - 1];
			}
			addamage = addamage + (g_localPlayer->stats()->bonusAD() * 0.5);
			dmg = dmg + (g_localPlayer->stats()->totalAP() * 0.75);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, dmg, addamage, 0);
		}
		return damage;
	}

	int GetRDamage(IGameObject* target)
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
			dmgap = dmgap + (g_localPlayer->stats()->totalAP() * 0.9);
			dmgad = dmgad + (g_localPlayer->stats()->bonusAD());
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, dmgap, dmgad, 0);
		}
		return damage;
	}
	float qwrange()
	{
		auto range = 0.0f;
		range = range + spellQ->range() * (g_menu->comboQrange->getInt() / 100.0f);
		return range;
	}

	bool ezrealwbuff(IGameObject* target)
	{
		auto flag = false;
		auto buff = target->buff(BUFF_HASH("ezrealwattach"));
		if (buff && buff->isValid())
			flag = true;
		return flag;
	}

	int getcombodamage(IGameObject* target)
	{
		auto dmg = 0;
		if (target)
		{
			dmg = dmg + g_moduleManager->damageLib()->calculateAutoAttackDamage(g_localPlayer, target) * 2;
			if (spellQ->isReady())
			{
				dmg = dmg + GetQDamage(target);
			}
			if (spellW->isReady())
			{
				dmg = dmg + GetQDamage(target);
			}
			if (spellE->isReady())
			{
				dmg = dmg + GetEDamage(target);
			}
			if (spellR->isReady())
			{
				dmg = dmg + GetRDamage(target);
			}
		}
		return dmg;
	}
	bool isplant(IGameObject* minion)
	{
	//	DLOG(minion->name());
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
		//CollisionInput collisionInput;
		//collisionInput.source = sourceObject;
		//collisionInput.target = targetObject;
		//collisionInput.from = sourcePos;
		//collisionInput.to = targetPos;
		//collisionInput.radius = skillshot.radius();
		//collisionInput.collisions = { Collisions::Windwall };
		//auto wallcoals = g_moduleManager->collision()->collisionCheck(collisionInput);
		//for (const auto& collision : skillshot.collisions()) {
		//	if (collision == Collisions::Minions || collision == Collisions::Heros || collision == Collisions::Windwall)
		//	{
		//		if (IsAnyObjectInWay(sourcePos, targetPos, sourceObject, targetObject, skillshot.radius()))
		//			return false;
		//	}
		//	if (collision == Collisions::Windwall)
		//	{
		//		if (wallcoals.isCollision)
		//		{
		//			return false;
		//		}
		//	}
		//}
		//return true;
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

	float Distance(Vector3 p1, Vector3 p2)
	{
		return p1.distance(p2);
	}
	Vector3 Extend(Vector3 p1, Vector3 p2,float dist)
	{
		return p1.extend(p2, dist);
	}
	bool checkstun(IGameObject* target)
	{
		for (const auto& buff : target->allBuffs())
		{
			// BuffType kontrolü burada düzeltilmiþtir.
			if (buff->type() == BuffType::Stun ||
				buff->type() == BuffType::Knockup ||
				buff->type() == BuffType::Knockback ||
				buff->type() == BuffType::Charm ||
				buff->type() == BuffType::Flee ||
				buff->type() == BuffType::Snare ||
				buff->type() == BuffType::Fear ||
				buff->type() == BuffType::Taunt ||
				buff->type() == BuffType::Polymorph)
			{
				return true;
			}
		}
		return false;
	}

	PredictionOutput PredGetPrediction(Vector3 startpos, PositionSpell spell,IGameObject* target)
	{
		PredictionOutput output;
		if (target != nullptr) {
			output.hitPorblty = Hitchance::Impossible;
			auto navigation = target->pathController();
			std::vector<Vector3> waypoint = target->pathController()->currentPath();
			Vector3 RangeCheckFrom = startpos;

			if (waypoint.size() == 1 || !navigation->isMoving())
			{
				output.position = waypoint[0];
				output.hitPorblty = Hitchance::High;
			}
			float speed = target->stats()->moveSpeed();
			if (navigation->isDashing())
			{
				speed = navigation->dashSpeed();

			}
			float realspelldelay = spell.castDelay() / 1000;
			float time = 0.f;
			for (int i = 1; i < waypoint.size(); i = i + 1)
			{
				float distance = Distance(waypoint[i - 1], waypoint[i]);
				for (float j = 0; j <= distance; j = j + 5)
				{
					Vector3 Position = Extend(waypoint[i - 1], waypoint[i], j);
					//time = Vector3(Position - RangeCheckFrom).Length() / spellspeed;
					//time += realspelldelay;
					float spelldistance = Distance(RangeCheckFrom, Position);
					float targettime = time + j / speed;
					float spelltime = realspelldelay + spelldistance / spell.speed();
					if (abs(targettime - spelltime) < 10 / target->stats()->moveSpeed())
					{
						output.position = Position;
						output.hitPorblty = Hitchance::Medium;
						goto ABC;
					}
				}
				time = time + distance / target->stats()->moveSpeed();
			}
		ABC:
			if (output.hitPorblty > Hitchance::Impossible)
			{
				if (Distance(target->position(), RangeCheckFrom) <= 300)
					output.hitPorblty = Hitchance::VeryHigh;

				if (navigation->isDashing())
					output.hitPorblty = Hitchance::High;

				else if (waypoint.size() == 1 && (checkstun(target)))
					output.hitPorblty = Hitchance::VeryHigh;

				if (Distance(output.position, RangeCheckFrom) > spell.range() && spell.range() != 0)
				{
					output.hitPorblty = Hitchance::Low;
				}
				if (!CheckCollision(g_localPlayer->position(), output.position, g_localPlayer, target, spell))
				{
					output.hitPorblty = Hitchance::Collision;
				}
				return output;
			}
			output.position = waypoint.back();
			return output;
		}
	}

	bool GetPrediction4(IGameObject* target, PositionSpell spell, PredictionOutput& out)
	{
		if (!target) return false;
		PredictionOutput output = PredGetPrediction(g_localPlayer->position(), spell,target);
		out.position = output.position;
		if (output.hitPorblty > Hitchance::Low)
		{
			if (output.hitPorblty == Hitchance::Medium && target->position().distance(g_localPlayer->position()) > spellQ->range()) return false;
			return CheckCollision(g_localPlayer->position(), out.position, g_localPlayer, target, spell);
		}
		return false;
	}

	void castq(IGameObject* target)
	{
		if (g_menu->combodisablepred->getBool())
		{
			PredictionOutput qpred;
			auto newspell = PositionSpell(SpellSlot::Q);
			newspell.setCastDelay(400);
			newspell.setRange(1200);
			newspell.setCollisions({ Collisions::Windwall,Collisions::Minions });
			newspell.setBoundingRadiusCollision(true);
			newspell.setSpeed(2000);
			newspell.setRadius(80);
			newspell.setSkillshotType(SkillshotType::Line);
			auto pred = GetPrediction4(target, newspell, qpred);
			if (pred)
			{
				//if (qpred.hitChance >= g_menu->darkpredhitchance->getInt())
				//{
					if (qpred.position.distance(g_localPlayer->position()) < qwrange())
					{
						spellQ->cast(qpred.position);
					}
				//}
			}
			/*auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 250, spellQ->speed());
			if (!IsAnyObjectInWay(g_localPlayer->position(), pred.predictedPosition, g_localPlayer, target, spellQ->radius()))
			{
				spellQ->cast(pred.predictedPosition);
			}*/
		}
		else if (!g_menu->combodisablepred->getBool())
		{
			PredictionInput input;
			input.caster = g_localPlayer;
			input.target = target;
			input.rangeCheckFrom = g_localPlayer->position();
			input.range = qwrange();
			input.collisions = spellQ->collisions();
			input.useBoundingRadius = true;
			input.delay = 250;
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
	void castw(IGameObject* target)
	{
		if (g_menu->combodisablepred->getBool())
		{
			PredictionOutput wpred;
			auto newspell = PositionSpell(SpellSlot::W);
			newspell.setCastDelay(400);
			newspell.setRange(1200);
			newspell.setCollisions({ Collisions::Windwall });
			newspell.setBoundingRadiusCollision(false);
			newspell.setSpeed(1600);
			newspell.setRadius(100);
			newspell.setSkillshotType(SkillshotType::Line);
			auto pred = GetPrediction4(target, newspell, wpred);
			if (pred)
			{
				//if (wpred.hitChance >= g_menu->darkpredhitchance->getInt())
				//{
					if (wpred.position.distance(g_localPlayer->position()) < qwrange())
					{
						spellW->cast(wpred.position);
					}
				//}
			}
			/*auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 250, spellW->speed());
			spellW->cast(pred.predictedPosition);*/
		}
		else if (!g_menu->combodisablepred->getBool())
		{
			PredictionInput input;
			input.caster = g_localPlayer;
			input.target = target;
			input.rangeCheckFrom = g_localPlayer->position();
			input.range = qwrange();
			input.collisions = spellW->collisions();
			input.useBoundingRadius = false;
			input.delay = 250;
			input.missileSpeed = spellW->speed();
			input.radius = spellW->radius();
			input.type = SkillshotType::Line;
			auto pred = g_moduleManager->prediction()->getPrediction(input);
			if (pred.hitchance >= Hitchance::Instant)
			{
				spellQ->castPrediction(target, fromString(g_menu->hitchancewcombo->getString()));
			}
		}
	}
	//isSafePath(const std::vector<Vector3>& path, float delay, float speed) 
	auto lastezrealrtime = 0;
	bool rcheck()
	{
		auto spell = g_localPlayer->activeSpell();
		if (spell)
		{
			if (spell->info()->name() == "EzrealR")
			{
				lastezrealrtime = g_game->gameTime();
				return true;
			}
		}
		if (lastezrealrtime + 1 < g_game->gameTime())
		{
			return false;
		}
		return true;
	}

	void combo()
	{
		if (g_menu->settarget->getBool())
		{
			auto target3 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 3000);
			auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target3, false, false);
			for (auto target : selectedEnemies)
			{
				if (g_menu->comboQ->getBool() && spellQ->isReady())
				{
					if (ezrealwbuff(target))
					{
						castq(target);
					}
				}
			}
		}

		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 3000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (g_menu->comboW->getBool() && spellW->isReady())
			{
				if (spellQ->isReady() && !IsAnyObjectInWay(g_localPlayer->position(), target->position(), g_localPlayer, target, spellQ->radius()))
				{
					castw(target);
				}
				else if (target->position().distance(g_localPlayer->position())  < g_localPlayer->stats()->attackRange())
				{
					castw(target);
				}
			}
			if (g_menu->comboQ->getBool() && spellQ->isReady())
			{
				castq(target);
			}
			if (g_menu->comboE->getBool() && spellQ->isReady() && spellW->isReady() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < spellE->range() + spellQ->range() - 100)
			{
				if (getcombodamage(target) > target->health())
				{
					auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * spellE->range();
					spellE->cast(epos);
				}
			}
		}
	}
	void harass()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (g_menu->harassW->getBool() && spellQ->isReady() && spellW->isReady())
			{
				if (spellQ->isReady() && !IsAnyObjectInWay(g_localPlayer->position(), target->position(), g_localPlayer, target, spellQ->radius()))
				{
					castw(target);
				}
				else if (target->position().distance(g_localPlayer->position()) < g_localPlayer->stats()->attackRange())
				{
					castw(target);
				}
			}
			if (g_menu->harassQ->getBool() && spellQ->isReady())
			{
				castq(target);
			}
		}
		if ((g_localPlayer->maxResource() / 100) * g_menu->clearManaharas->getInt() < g_localPlayer->resource())
		{
			auto minion2 = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer->position(), spellQ->range());
			for (auto minion : minion2)
			{
				if (g_menu->harassQfarm->getBool() && spellQ->isReady() && GetQDamage(minion) > minion->health())
				{
					if (!isplant(minion))
					{
						castq(minion);
					}
				}
			}
		}

	}

	void active()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 30000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (g_menu->KillstealQ->getBool() && spellQ->isReady() && GetQDamage(target) > target->health())
			{
				castq(target);
			}
			if (g_menu->KillstealE->getBool() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < 725 && GetEDamage(target) > target->health())
			{
				auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * spellE->range() - 50;
				spellE->cast(epos);
			}
			if (spellQ->isReady() && g_menu->autoq->getBool() && haraskeyactive)
			{
				castq(target);
			}
			if (g_menu->KillstealR->getBool() && spellR->isReady() && target->position().distance(g_localPlayer->position()) < spellR->range() && !target->isZombie())
			{
				auto maxdist = g_menu->killsteal_r_maxdist->getInt();
				auto mindist = g_menu->killsteal_r_mindist->getInt();
				if (target->position().distance(g_localPlayer->position()) < maxdist && !rcheck() && target->position().distance(g_localPlayer->position()) > mindist && GetRDamage(target) > target->health())
				{
					spellR->castPrediction(target, fromString(g_menu->hitchancercombo->getString()));
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
	void laneclear()
	{
		/*if (g_menu->usewtover->getBool())
		{
			auto target3 = g_moduleManager->orbwalker()->getTarget();
			if (target3 && target3->turretType() != TurretType::None)
			{
				if (target3->position().distance(g_localPlayer->position()) < spellW->range())
				{
					spellW->cast(target3->position());
				}
			}
		}*/
		if ((g_localPlayer->maxResource() / 100) * g_menu->clearMana->getInt() < g_localPlayer->resource() && farmkeyactive)
		{
			auto target2 = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer->position(), spellQ->range());
			for (auto minion : target2)
			{
				if (!isplant(minion))
				{
					if (g_menu->clearQ_aa->getBool() && minion->position().distance(g_localPlayer->position()) > g_localPlayer->stats()->attackRange())
					{
						if (g_menu->clearQ_killable->getBool() && GetQDamage(minion) > minion->health())
						{
							castq(minion);
						}
						else if (!g_menu->clearQ_killable->getBool())
						{
							castq(minion);
						}
					}
					else if (!g_menu->clearQ_aa->getBool())
					{
						if (g_menu->clearQ_killable->getBool() && GetQDamage(minion) > minion->health())
						{
							castq(minion);
						}
						else if (!g_menu->clearQ_killable->getBool())
						{
							castq(minion);
						}
					}
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
			if (g_menu->drawRmaxmin.checkbox->getBool() && g_localPlayer->spell(SpellSlot::R)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_menu->killsteal_r_maxdist->getInt(), 1, 0xff0000ff);
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_menu->killsteal_r_mindist->getInt(), 1, 0xffff0000);
			}
			auto newpos = g_localPlayer->position().toScreen();
			if (haraskeyactive)
			{
				g_drawings->drawText(Vector2(newpos.x - 30, newpos.y + 30), "Auto Q:", 18, 0xdeffffe7);
				g_drawings->drawText(Vector2(newpos.x + 35, newpos.y + 30), "ON", 20, 0xff00ff00);
			}
			else if (!haraskeyactive)
			{
				g_drawings->drawText(Vector2(newpos.x - 30, newpos.y + 30), "Auto Q:", 18, 0xdeffffe7);
				g_drawings->drawText(Vector2(newpos.x + 35, newpos.y + 30), "OFF", 18, 0xff0000ff);
			}

			if (farmkeyactive)
			{
				g_drawings->drawText(Vector2(newpos.x - 20, newpos.y + 10), "Farm:", 18, 0xdeffffe7);
				g_drawings->drawText(Vector2(newpos.x + 35, newpos.y + 11), "ON", 18, 0xff00ff00);
			}
			else if (!farmkeyactive)
			{
				g_drawings->drawText(Vector2(newpos.x - 20, newpos.y + 10), "Farm:", 18, 0xdeffffe7);
				g_drawings->drawText(Vector2(newpos.x + 35, newpos.y + 11), "OFF", 18, 0xff0000ff);
			}
			if (g_menu->drawRKillable.checkbox->getBool() && g_localPlayer->spell(SpellSlot::R)->isLearned() && spellR->isReady())
			{
				auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 30000);
				for (auto target : target2)
				{
					if (GetRDamage(target) > target->health())
					{
						g_drawings->drawText(target->position().toScreen(), "Killable With R", 18, g_menu->drawRKillable.color->getColor());
					}
				}
			}
			g_drawings->drawText(Vector2(newpos.x - 30, newpos.y + 50), "DarkAio", 25, 0xff000000,false,false);
		/*	auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 6000);
			for (auto target : target2)
			{
				std::vector<Vector3> waypoints = { target->serverPosition() };
				auto futureWaypoints = target->pathController()->currentPath();
				for (auto waypoint : futureWaypoints)
					waypoints.push_back(waypoint);

				const int waypointsSize = (int)waypoints.size();
				for (int i = 1; i < waypointsSize; i++)
				{
					std::string text = std::to_string(i);
					g_drawings->drawText(waypoints[i].toScreen(), text.c_str(), 40, 0xff0000ff);
					g_drawings->drawWorldCircle(waypoints[i], 70, 1, 0xff0000ff);
				}
			}*/
		}
	}


	void antigap1()
	{
		if (g_menu->antigapE->getBool() && spellE->isReady())
		{
			auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 1000);
			for (auto target : target2)
			{
				if (target)
				{
					std::vector<Vector3> path = target->pathController()->currentPath();
					if (path.size() > 0) {
						auto endPos = path.back();
						//auto pos = g_localPlayer->position().extend(g_hud->mousePosition(), spellE->range());
						if (target->pathController()->isDashing() == true &&
							endPos.distance(g_localPlayer->position()) < 400 &&
							endPos.distance(g_localPlayer->position()) < target->position().distance(g_localPlayer->position())) {
							spellE->cast(g_localPlayer->position().extend(g_hud->mousePosition(), spellE->range()));
						}
					}
				}
			}

		}
	}

	void onGapclose(OnGapcloserEventArgs* args)
	{
		if (g_menu->antigapE->getBool() && spellE->isReady() && args->toLocalPlayer && g_menu->gapcloseMenuSpells->isSpellEnabled(args->spellHash))
		{
			std::vector<Vector3> path = args->caster->pathController()->currentPath();
			if (path.size() > 0) {
				auto endPos = args->endPosition;
				//auto pos = g_localPlayer->position().extend(g_hud->mousePosition(), spellE->range());
				/*if (args->caster->pathController()->isDashing() == true &&
					endPos.distance(g_localPlayer->position()) < 400 &&
					endPos.distance(g_localPlayer->position()) < target->position().distance(g_localPlayer->position())) {
					spellE->cast(g_localPlayer->position().extend(g_hud->mousePosition(), spellE->range()));
				}*/
				auto castpos = g_localPlayer->position().extend(g_hud->mousePosition(), spellE->range());
				if (countenemyinrange(castpos,400) == 0 && g_moduleManager->evade()->isSafeToBlink(castpos,0.25) )
				{
					spellE->cast(castpos);
				}
				else
				{
					castpos = endPos.extend(g_localPlayer->position(), spellE->range() + endPos.distance(g_localPlayer->position()));
					spellE->cast(castpos);
				}
			}
		}
	}

	double haraslastclicktime = 0;
	double toverdiveclicktime = 0;
	double farmlastclicktime = 0;
	void onkeyupdate()
	{
		if (!haraskeyactive && g_menu->HarassQautokey->isPressed() && !(haraslastclicktime + 0.2 > g_game->gameTime()))
		{
			haraskeyactive = true;
			haraslastclicktime = g_game->gameTime();
		}
		if (haraskeyactive && g_menu->HarassQautokey->isPressed() && !(haraslastclicktime + 0.2 > g_game->gameTime()))
		{
			haraskeyactive = false;
			haraslastclicktime = g_game->gameTime();
		}
		if (!farmkeyactive && g_menu->clearkey->isPressed() && !(farmlastclicktime + 0.2 > g_game->gameTime()))
		{
			farmkeyactive = true;
			farmlastclicktime = g_game->gameTime();
		}
		if (farmkeyactive && g_menu->clearkey->isPressed() && !(farmlastclicktime + 0.2 > g_game->gameTime()))
		{
			farmkeyactive = false;
			farmlastclicktime = g_game->gameTime();
		}
	}
	void onpresent(PresentEventArgs* args)
	{
		//auto target1 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 30000);
		//for (auto& target : target1)
		//{
		//	if (target)
		//	{
		//		g_moduleManager->damageDrawings()->drawDamage(target, getcombodamage(target));
		//	}
		//}
		//auto minions = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer->position(), 3000);
		//for (auto& minion : minions)
		//{
		//	if (minion)
		//	{
		//		if (g_menu->drawQdamage.checkbox->getBool())
		//		{
		//			g_moduleManager->damageDrawings()->drawDamage(minion, GetQDamage(minion));
		//		}
		//	}
		//}
	}
	void onUpdate(GameUpdateEventArgs* args)
	{
		onkeyupdate();
		if (g_localPlayer->isAlive())
		{
			//antigap1();
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

	void load()
	{
		g_menu = new Menu();

		spellQ = std::make_unique<PositionSpell>(SpellSlot::Q);
		spellQ->setCastDelay(250);
		spellQ->setRange(1200);
		spellQ->setCollisions({ Collisions::Windwall,Collisions::Minions});
		spellQ->setBoundingRadiusCollision(true);
		spellQ->setSpeed(2000);
		spellQ->setRadius(80);
		spellQ->setSkillshotType(SkillshotType::Line);

		spellW = std::make_unique<PositionSpell>(SpellSlot::W);
		spellW->setCastDelay(250);
		spellW->setRange(1200);
		spellW->setCollisions({ Collisions::Windwall });
		spellW->setBoundingRadiusCollision(false);
		spellW->setSpeed(1600);
		spellW->setRadius(100);
		spellW->setSkillshotType(SkillshotType::Line);

		spellE = std::make_unique<PositionSpell>(SpellSlot::E);
		spellE->setCastDelay(250);
		spellE->setRange(475);
		spellE->setBoundingRadiusCollision(false);
		spellE->setSpeed(2000);
		spellE->setRadius(750);
		spellE->setSkillshotType(SkillshotType::Line);

		spellR = std::make_unique<PositionSpell>(SpellSlot::R);
		spellR->setCastDelay(1000);
		spellR->setRange(99999);
		spellR->setCollisions({ Collisions::Windwall });
		spellR->setBoundingRadiusCollision(false);
		spellR->setSpeed(2000);
		spellR->setRadius(320);
		spellR->setSkillshotType(SkillshotType::Line);

		//EventHandler<Events::Present>::subscribe(onpresent);
		EventHandler<Events::OnDraw>::subscribe(onDraw);
		EventHandler<Events::OnGapcloser>::subscribe(onGapclose);
		EventHandler<Events::GameUpdate>::subscribe(onUpdate);
	}

	void unload()
	{
		//EventHandler<Events::Present>::unsubscribe(onpresent);
		EventHandler<Events::OnDraw>::unsubscribe(onDraw);
		EventHandler<Events::OnGapcloser>::unsubscribe(onGapclose);
		EventHandler<Events::GameUpdate>::unsubscribe(onUpdate);

		spellQ.reset();
		spellW.reset();
		spellE.reset();
		spellR.reset();

		g_mainMenu->removeMenu(g_menu->menu);
		delete g_menu;
	}
}