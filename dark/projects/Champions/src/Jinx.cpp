#include "Jinx.h"
#include <SDK/src/SDK.h>

namespace Jinx
{
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Jinx"), xorstr_("DarkAio Jinx"));
		MenuTabPtr combogeneralTab = menu->createTab(xorstr_("combogeneral"), xorstr_("Combo"));
		MenuTabPtr harassgeneralTab = menu->createTab(xorstr_("harassgeneral"), xorstr_("Harass"));
		MenuTabPtr killstealgeneralTab = menu->createTab(xorstr_("killstealgeneral"), xorstr_("Killsteal"));
		MenuTabPtr miscgeneralTab = menu->createTab(xorstr_("miscgeneral"), xorstr_("Misc"));
		MenuTabPtr farmgeneralTab = menu->createTab(xorstr_("farmgeneral"), xorstr_("Farm"));
		MenuTabPtr drawgeneralTab = menu->createTab(xorstr_("drawgeneral"), xorstr_("Draw"));

		TabChildPtr comboMenu = combogeneralTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboWa = comboMenu->addCheckBox(xorstr_("Use Waa Combo"), xorstr_("Use W Only out of AA range"), false);
		MenuElementPtr comboE = comboMenu->addCheckBox(xorstr_("Use E Combo"), xorstr_("Use E"), true);
		MenuElementPtr comboEalways = comboMenu->addCheckBox(xorstr_("Use Ealways Combo"), xorstr_("Use E Always"), false);
		MenuElementPtr combodisablepred = comboMenu->addCheckBox(xorstr_("Use DarkAio1 Pred(Beta)"), xorstr_("Use DarkAio Pred(Beta)"), true);

		TabChildPtr hitchanceMenu = combogeneralTab->createTabChild(xorstr_("Hitchance Settings"), xorstr_("Hitchance Settings"), true);
		MenuElementPtr hitchancewcombo = hitchanceMenu->addComboBox(xorstr_("W Hitchance Combo"), xorstr_("W Hitchance"), g_hitchanceList, HITCHANCE_LOW);
		MenuElementPtr hitchancercombo = hitchanceMenu->addComboBox(xorstr_("R Hitchance Combo"), xorstr_("R Hitchance"), g_hitchanceList, HITCHANCE_LOW);

		TabChildPtr harassMenu = harassgeneralTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), true);

		TabChildPtr KillstealMenu = killstealgeneralTab->createTabChild(xorstr_("Killsteal Settings"), xorstr_("Killsteal Settings"), true);
		MenuElementPtr KillstealW = KillstealMenu->addCheckBox(xorstr_("Use W Killsteal"), xorstr_("Use W"), true);
		MenuElementPtr KillstealR = KillstealMenu->addCheckBox(xorstr_("Use R Killsteal"), xorstr_("Use R"), true);
		MenuElementPtr killsteal_r_maxdist = KillstealMenu->addSlider(xorstr_("krmax"), xorstr_("max R dist (you can see in draw)"), 3000, 0, 25000);
		MenuElementPtr killsteal_r_mindist = KillstealMenu->addSlider(xorstr_("krmin"), xorstr_("min R dist (you can see in draw)"), 1000, 0, 5000);

		TabChildPtr MiscMenu = miscgeneralTab->createTabChild(xorstr_("Misc Settings"), xorstr_("Misc Settings"), true);
		MenuElementPtr antigapE = MiscMenu->addCheckBox(xorstr_("Use eantigap "), xorstr_("Use E Anti Gap"), true);
		std::unique_ptr<IGapcloseMenu> gapcloseMenuSpells = g_moduleManager->gapclose()->createGapcloseMenu(MiscMenu);

		TabChildPtr FarmMenu = farmgeneralTab->createTabChild(xorstr_("Farm Settings"), xorstr_("Farm Settings"), true);
		MenuElementPtr clearQ = FarmMenu->addCheckBox(xorstr_("Use Q"), xorstr_("Use Q"), true);
		MenuElementPtr clearMana = FarmMenu->addSlider(xorstr_("clearmana"), xorstr_("Min Mana Save"), 40, 0, 100);

		TabChildPtr drawingsMenu = drawgeneralTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 0, 0, 200, true);
		ColorCheckbox drawWRange = addColorCheckbox(drawingsMenu, xorstr_("W"), 255, 0, 0, 200, true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 165, 0, 200, false);
		ColorCheckbox drawRKillable = addColorCheckbox(drawingsMenu, xorstr_("R Killable"), 255, 0, 0, 200, true);
		ColorCheckbox drawRmaxmin = addColorCheckbox(drawingsMenu, xorstr_("Draw R min/max dist (min blue) (max red)"), 255, 165, 0, 200, true);
	};
	Menu* g_menu = nullptr;

	std::unique_ptr<SelfSpellAoe> spellQ;
	std::unique_ptr<PositionSpell> spellW;
	std::unique_ptr<PositionSpell> spellE;
	std::unique_ptr<PositionSpell> spellR;
	double WlvlDmg[] = { 10,60,110,160,210 };
	double RlvlDmg[] = { 325 , 475  , 625 };

	auto minigun = true;

	float getqrange()
	{
		auto range = 0;
		range = range + g_localPlayer->stats()->attackRange() + g_localPlayer->boundingRadius();
		if (g_localPlayer->spell(SpellSlot::Q)->level() == 1)
		{
			return range + 80;
		}
		else if (g_localPlayer->spell(SpellSlot::Q)->level() == 2)
		{
			return range + 110;
		}
		else if (g_localPlayer->spell(SpellSlot::Q)->level() == 3)
		{
			return range + 140;
		}
		else if (g_localPlayer->spell(SpellSlot::Q)->level() == 4)
		{
			return range + 170;
		}
		else if (g_localPlayer->spell(SpellSlot::Q)->level() == 5)
		{
			return range + 200;
		}
		return range;
	}

	float actualrange()
	{
		auto range = 0;
		range = range + g_localPlayer->stats()->attackRange() + g_localPlayer->boundingRadius();
		if (!minigun)
		{
			if (g_localPlayer->spell(SpellSlot::Q)->level() == 1)
			{
				return range - 80;
			}
			else if (g_localPlayer->spell(SpellSlot::Q)->level() == 2)
			{
				return range - 110;
			}
			else if (g_localPlayer->spell(SpellSlot::Q)->level() == 3)
			{
				return range - 140;
			}
			else if (g_localPlayer->spell(SpellSlot::Q)->level() == 4)
			{
				return range - 170;
			}
			else if (g_localPlayer->spell(SpellSlot::Q)->level() == 5)
			{
				return range - 200;
			}
		}
		return range;
	}

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

	int GetRDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmgad = 0;
			auto xvalue = 0;
			if (g_localPlayer->spell(SpellSlot::R)->level() >= 1)
			{
				dmgad = dmgad + RlvlDmg[g_localPlayer->spell(SpellSlot::R)->level() - 1];
				xvalue = g_localPlayer->spell(SpellSlot::R)->level();
			}

			auto distance = std::abs(g_localPlayer->position().distance(target->position()));

			double additionalDistanceDamage;
			if (distance < 1500) {
				additionalDistanceDamage = 0.10 + (std::floor(distance / 100) * 0.06);
			}
			else {
				additionalDistanceDamage = 1.0;
			}

			dmgad = dmgad + (g_localPlayer->stats()->bonusAD() * 1.65);
			auto remainprecent = (100 - target->healthPercent());
			auto newdmg = remainprecent * (target->maxHealth() / 100);
			if (xvalue == 1) dmgad = dmgad + (newdmg * 0.25);
			else if (xvalue == 2) dmgad = dmgad + (newdmg * 0.30);
			else if (xvalue == 3) dmgad = dmgad + (newdmg * 0.35);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, 0, dmgad, 0);
			damage = damage * additionalDistanceDamage;
		}
		return damage;
	}

	int GetWDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmgad = 0;
			if (g_localPlayer->spell(SpellSlot::R)->level() >= 1)
			{
				dmgad = dmgad + RlvlDmg[g_localPlayer->spell(SpellSlot::R)->level() - 1];
			}
			dmgad = dmgad + (g_localPlayer->stats()->bonusAD() * 1.6);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, 0, dmgad, 0);
		}
		return damage;
	}

	int getcombodamage(IGameObject* target)
	{
		auto dmg = 0;
		if (target)
		{
			dmg = dmg + g_moduleManager->damageLib()->calculateAutoAttackDamage(g_localPlayer, target) * 3;
			if (spellW->isReady())
			{
				dmg = dmg + GetWDamage(target);
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
	Vector3 Extend(Vector3 p1, Vector3 p2, float dist)
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

	PredictionOutput PredGetPrediction(Vector3 startpos, PositionSpell spell, IGameObject* target)
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
				output.hitPorblty = Hitchance::Medium;
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
		PredictionOutput output = PredGetPrediction(g_localPlayer->position(), spell, target);
		out.position = output.position;
		out.hitPorblty = output.hitPorblty;
		if (output.hitPorblty > Hitchance::Low)
		{
			if (output.hitPorblty == Hitchance::Medium && target->position().distance(g_localPlayer->position()) > spellW->range() - 30) return false;
			return CheckCollision(g_localPlayer->position(), out.position, g_localPlayer, target, spell);
		}
		return false;
	}

	void castw(IGameObject* target)
	{
		if (g_menu->combodisablepred->getBool())
		{
			PredictionOutput wpred;
			auto newspell = PositionSpell(SpellSlot::W);
			newspell.setCastDelay(600);
			newspell.setRange(1500);
			newspell.setCollisions({ Collisions::Windwall, Collisions::Minions });
			newspell.setBoundingRadiusCollision(false);
			newspell.setSpeed(3300);
			newspell.setRadius(120);
			newspell.setSkillshotType(SkillshotType::Line);
			auto pred = GetPrediction4(target, newspell, wpred);
			if (pred)
			{
				spellW->cast(wpred.position);
			}
		}
		else if (!g_menu->combodisablepred->getBool())
		{
			PredictionInput input;
			input.caster = g_localPlayer;
			input.target = target;
			input.rangeCheckFrom = g_localPlayer->position();
			input.range = spellW->range();
			input.collisions = spellW->collisions();
			input.useBoundingRadius = false;
			input.delay = 600;
			input.missileSpeed = spellW->speed();
			input.radius = spellW->radius();
			input.type = SkillshotType::Line;
			auto pred = g_moduleManager->prediction()->getPrediction(input);
			if (pred.hitchance >= Hitchance::Instant)
			{
				spellW->castPrediction(target, fromString(g_menu->hitchancewcombo->getString()));
			}
		}
	}

	void caste(IGameObject* target)
	{
		PredictionOutput epred;
		auto newspell = PositionSpell(SpellSlot::E);
		newspell.setCastDelay(10);
		newspell.setRange(925);
		newspell.setCollisions({ Collisions::Windwall });
		newspell.setBoundingRadiusCollision(false);
		newspell.setSpeed(3000);
		newspell.setRadius(225);
		newspell.setSkillshotType(SkillshotType::Line);
		auto pred = GetPrediction4(target, newspell, epred);
		if (pred)
		{
			if (epred.hitPorblty >= Hitchance::High)
			{
				spellE->cast(epred.position);
			}
			else if (epred.hitPorblty >= Hitchance::Medium)
			{
				if (g_menu->comboEalways->getBool())
				{
					std::vector<Vector3> path = target->pathController()->currentPath();
					if (path.size() > 0) {
						auto endPos = path.back();
						if (endPos.distance(g_localPlayer->position()) < target->position().distance(g_localPlayer->position()))
						{
							spellE->cast(target->position().extend(g_localPlayer->position(), 250));
						}
						else if (endPos.distance(g_localPlayer->position()) > target->position().distance(g_localPlayer->position()))
						{
							spellE->cast(target->position().extend(endPos, 200));
						}
					}
				}
			}
		}
	}

	auto lastezrealrtime = 0;
	bool rcheck()
	{
		auto spell = g_localPlayer->activeSpell();
		if (spell)
		{
			if (spell->info()->name() == "JinxR")
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

	IGameObject* getnewtarget(float range)
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, getqrange());
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			return target;
		}
		return nullptr;
	}

	void castq()
	{
		auto target = getnewtarget(getqrange());
		if (target)
		{
			if ((target->position().distance(g_localPlayer->position()) > actualrange() || countenemyinrange(target->position(), 250) > 1 )&& minigun)
			{
				if (target->position().distance(g_localPlayer->position()) < getqrange())
				{
					spellQ->cast();
				}
			}
			if (!minigun && countenemyinrange(target->position(), 250) < 2 && target->position().distance(g_localPlayer->position()) < actualrange())
			{
				spellQ->cast();
			}
		}
	}

	void combo()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 3000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (g_menu->comboQ->getBool() && spellQ->isReady())
			{
				castq();
			}
			if (g_menu->comboW->getBool() && spellW->isReady())
			{
				if (g_menu->comboWa->getBool() && target->position().distance(g_localPlayer->position()) > actualrange())
				{
					castw(target);
				}
				else if (!g_menu->comboWa->getBool())
				{
					castw(target);
				}
			}
			if (g_menu->comboE->getBool() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < spellE->range())
			{
				caste(target);
			}
		}
	}
	void harass()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 3000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (g_menu->harassQ->getBool() && spellQ->isReady())
			{
				castq();
			}
			if (g_menu->harassW->getBool() && spellW->isReady())
			{
				castw(target);
			}
		}
	}

	void active()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 30000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (g_menu->KillstealW->getBool() && spellW->isReady() && GetWDamage(target) > target->health())
			{
				castw(target);
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
		if (g_menu->clearQ->getBool())
		{
			if ((g_localPlayer->maxResource() / 100) * g_menu->clearMana->getInt() < g_localPlayer->resource())
			{
				if (spellQ->isReady())
				{
					auto minion = g_moduleManager->orbwalker()->getTarget();
					if (minion)
					{
						if (!isplant(minion))
						{
							if (countminioninrange(minion->position(), 250) > 2 && minigun)
							{
								spellQ->cast();
							}
							if (!minigun && countminioninrange(minion->position(), 250) < 3)
							{
								spellQ->cast();
							}
						}
					}
				}
			}
			else
			{
				if (!minigun)
				{
					if (spellQ->isReady())
					{
						spellQ->cast();
					}
				}
			}
		}
	}

	void onDraw(OnDrawEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			if (g_menu->drawQRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::Q)->isLearned() && minigun)
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), getqrange(), 2, g_menu->drawQRange.color->getColor());
			}
			if (g_menu->drawWRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::W)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellW->range(), 2, g_menu->drawWRange.color->getColor());
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
			g_drawings->drawText(Vector2(newpos.x - 30, newpos.y + 50), "DarkAio", 25, 0xff000000, false, false);
		}
	}

	void onGapclose(OnGapcloserEventArgs* args)
	{
		if (g_menu->antigapE->getBool() && spellE->isReady() && args->toLocalPlayer && g_menu->gapcloseMenuSpells->isSpellEnabled(args->spellHash))
		{
			std::vector<Vector3> path = args->caster->pathController()->currentPath();
			if (path.size() > 0) {
				auto endPos = args->endPosition;
				if (endPos.distance(g_localPlayer->position()) < spellE->range())
				{
					spellE->cast(endPos);
				}
			}
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
	void updatebuff()
	{
		auto buff = g_localPlayer->buff(BUFF_HASH("JinxQ"));
		if (buff && buff->isValid())
			minigun = false;
		else minigun = true;
	}
	void onUpdate(GameUpdateEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			updatebuff();
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
		spellQ = std::make_unique<SelfSpellAoe>(SpellSlot::Q);
		spellQ->setEffectRange(550);

		spellW = std::make_unique<PositionSpell>(SpellSlot::W);
		spellW->setCastDelay(600);
		spellW->setRange(1500);
		spellW->setCollisions({ Collisions::Windwall, Collisions::Minions });
		spellW->setBoundingRadiusCollision(false);
		spellW->setSpeed(3300);
		spellW->setRadius(120);
		spellW->setSkillshotType(SkillshotType::Line);

		spellE = std::make_unique<PositionSpell>(SpellSlot::E);
		spellE->setCastDelay(100);
		spellE->setRange(975);
		spellE->setCollisions({ Collisions::Windwall });
		spellE->setBoundingRadiusCollision(false);
		spellE->setSpeed(3000);
		spellE->setRadius(225);
		spellE->setSkillshotType(SkillshotType::Line);

		spellR = std::make_unique<PositionSpell>(SpellSlot::R);
		spellR->setCastDelay(600);
		spellR->setRange(99999);
		spellR->setCollisions({ Collisions::Windwall, Collisions::Heros });
		spellR->setBoundingRadiusCollision(false);
		spellR->setSpeed(2200);
		spellR->setRadius(280);
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