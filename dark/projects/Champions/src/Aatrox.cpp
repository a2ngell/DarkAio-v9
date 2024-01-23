#include "Aatrox.h"
#include <SDK/src/SDK.h>

namespace Aatrox
{
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Aatrox"), xorstr_("DarkAio Aatrox"));

		MenuTabPtr combogeneralTab = menu->createTab(xorstr_("combogeneral"), xorstr_("Combo"));
		MenuTabPtr harassgeneralTab = menu->createTab(xorstr_("harassgeneral"), xorstr_("Harass"));
		MenuTabPtr killstealgeneralTab = menu->createTab(xorstr_("killstealgeneral"), xorstr_("Killsteal"));
		MenuTabPtr miscgeneralTab = menu->createTab(xorstr_("miscgeneral"), xorstr_("Misc"));
		MenuTabPtr farmgeneralTab = menu->createTab(xorstr_("farmgeneral"), xorstr_("Farm"));
		MenuTabPtr drawgeneralTab = menu->createTab(xorstr_("drawgeneral"), xorstr_("Draw"));

		TabChildPtr comboMenu = combogeneralTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboE = comboMenu->addCheckBox(xorstr_("Use E Combo"), xorstr_("Use E"), true);
		MenuElementPtr comboR = comboMenu->addCheckBox(xorstr_("Use R Combo"), xorstr_("Use R"), true);
		MenuElementPtr ComboRCount = comboMenu->addSlider(xorstr_("Use R Enemy Count"), xorstr_("^- Min R Enemies Count"), 2, 1, 5);

		TabChildPtr harassMenu = harassgeneralTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), true);
		MenuElementPtr harassE = harassMenu->addCheckBox(xorstr_("Use E Harass"), xorstr_("Use E"), true);

		//TabChildPtr KillstealMenu = killstealgeneralTab->createTabChild(xorstr_("Killsteal Settings"), xorstr_("Killsteal Settings"), true);
		//MenuElementPtr KillstealQ = KillstealMenu->addCheckBox(xorstr_("Use Q Killsteal"), xorstr_("Use Q"), true);
		//MenuElementPtr KillstealW = KillstealMenu->addCheckBox(xorstr_("Use W Killsteal"), xorstr_("Use W"), true);
		//MenuElementPtr KillstealE = KillstealMenu->addCheckBox(xorstr_("Use E Killsteal"), xorstr_("Use E"), true);

		TabChildPtr MiscMenu = miscgeneralTab->createTabChild(xorstr_("Misc Settings"), xorstr_("Misc Settings"), true);

		TabChildPtr FarmMenu = farmgeneralTab->createTabChild(xorstr_("Farm Settings"), xorstr_("Farm Settings"), true);
		MenuElementPtr clearQ = FarmMenu->addCheckBox(xorstr_("Use Q"), xorstr_("Use Q"), true);

		TabChildPtr drawingsMenu = drawgeneralTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 165, 0, 200, true);
		ColorCheckbox drawWRange = addColorCheckbox(drawingsMenu, xorstr_("W"), 255, 165, 0, 200, true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 0, 0, 200, true);
		ColorCheckbox drawQERange = addColorCheckbox(drawingsMenu, xorstr_("QE"), 255, 165, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<PositionSpell> spellQ;
	std::unique_ptr<PositionSpell> spellQE;
	std::unique_ptr<PositionSpell> spellQ2;
	std::unique_ptr<PositionSpell> spellQ2E;
	std::unique_ptr<PositionSpell> spellQ3;
	std::unique_ptr<PositionSpell> spellQ3E;
	std::unique_ptr<PositionSpell> spellW;
	std::unique_ptr<PositionSpell> spellE;

	//for avoid range check.
	std::unique_ptr<PositionSpell> spellEGlobal;
	std::unique_ptr<PositionSpell> spellQGlobal;

	std::unique_ptr<SelfSpellAoe> spellR;
	int QlvlDmg[] = { 10, 25, 40, 55, 70 };
	int Q2lvlDmg[] = { 12, 31, 50, 68, 87 };
	int Q3lvlDmg[] = { 15, 37, 60, 82, 105 };
	int ElvlDmg[] = { 60, 100, 135, 170, 205 };
	double RlvlDmg[] = { 200, 300, 400 };

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
			dmg = dmg + (g_localPlayer->stats()->totalAP() * 0.85);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, dmg, 0, 0);
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
			dmg = dmg + (g_localPlayer->stats()->totalAP() * 0.50);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, dmg, 0, 0);
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
			dmgap = dmgap + (g_localPlayer->stats()->totalAP() * 0.80);
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

	void combo()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 1000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			//q1
			if (target && spellQ->isReady() && g_menu->comboQ->getBool() && g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ"))
			{
				//normalq
				if (target->position().distance(g_localPlayer->position()) < spellQ->range() && target->position().distance(g_localPlayer->position()) > spellQ->range() - 150)
				{
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(),target,400,2000);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//outsideq
				if (target->position().distance(g_localPlayer->position()) > spellQ->range() && target->position().distance(g_localPlayer->position()) < spellQ->range() + spellE->range()  - 120 && spellE->isReady() && g_menu->comboE->getBool())
				{
					auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 520;
					epos.y = g_navMesh->heightForPosition(epos);
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellEGlobal->cast(epos);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//inside
				if (target->position().distance(g_localPlayer->position()) < spellQ->range() && target->position().distance(g_localPlayer->position()) < spellQ->range() - 150 && spellE->isReady() && g_menu->comboE->getBool())
				{
					auto dist = spellQ->range() - target->position().distance(g_localPlayer->position());
					if (dist < 400)
					{
						auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 520;
						epos.y = g_navMesh->heightForPosition(epos);
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
						spellEGlobal->cast(epos);
					}
				}
				if (!spellE->isReady() || !g_menu->comboE->getBool())
				{
					if (spellQ->isReady() && g_menu->comboQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
					}
				}
			}
			//q2
			if (target && spellQ->isReady() && g_menu->comboQ->getBool() && g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ2"))
			{
				//normalq2
				if (target->position().distance(g_localPlayer->position()) < spellQ2->range() && target->position().distance(g_localPlayer->position()) > spellQ2->range() - 150)
				{
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//outsideq2
				if (target->position().distance(g_localPlayer->position()) > spellQ2->range() && target->position().distance(g_localPlayer->position()) < spellQ2->range() + spellE->range() - 150 && spellE->isReady() && g_menu->comboE->getBool())
				{
					auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 425;
					epos.y = g_navMesh->heightForPosition(epos);
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellEGlobal->cast(epos);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//inside2
				if (target->position().distance(g_localPlayer->position()) < spellQ2->range() && target->position().distance(g_localPlayer->position()) < spellQ2->range() - 150 && spellE->isReady() && g_menu->comboE->getBool())
				{
					auto dist = spellQ2->range() - target->position().distance(g_localPlayer->position());
					if (dist < 300)
					{
						auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 425;
						epos.y = g_navMesh->heightForPosition(epos);
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
						spellEGlobal->cast(epos);
					}
				}
				if (!spellE->isReady() || !g_menu->comboE->getBool())
				{
					if (spellQ->isReady() && g_menu->comboQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ2->range())
					{
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
					}
				}
			}
			//q3
			if (target && spellQ->isReady() && g_menu->comboQ->getBool() && g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ3"))
			{
				//normalq3
				if (target->position().distance(g_localPlayer->position()) < spellQ3->range() - 130)
				{
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//outsideq3
				if (target->position().distance(g_localPlayer->position()) > spellQ3->range() && target->position().distance(g_localPlayer->position()) < spellQ3->range() + spellE->range() - 139 && spellE->isReady() && g_menu->comboE->getBool())
				{
					auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 240;
					epos.y = g_navMesh->heightForPosition(epos);
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellQGlobal->cast(pred.predictedPosition);
					spellEGlobal->cast(epos);
				}
				//inside3
				if (spellQ->isReady() && spellE->isReady() && g_menu->comboE->getBool())
				{
					auto dist = spellQ3->range() - target->position().distance(g_localPlayer->position());
					if (dist < spellQ3->range() && dist > spellQ3->range() - 130)
					{
						auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 240;
						epos.y = g_navMesh->heightForPosition(epos);
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
						spellEGlobal->cast(epos);
					}
				}
				if (!spellE->isReady() || !g_menu->comboE->getBool())
				{
					if (spellQ->isReady() && g_menu->comboQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ2->range())
					{
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
					}
				}
			}
			if (target && spellW->isReady() && g_menu->comboW->getBool())
			{
				spellW->castPrediction(target, Hitchance::Medium);
			}
		}
		if (spellR->isReady() && countenemyinrange(g_localPlayer->position(), 600) >= g_menu->ComboRCount->getInt())
		{
			spellR->cast();
		}
	}
	void harass()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 1000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			//q1
			if (target && spellQ->isReady() && g_menu->harassQ->getBool() && g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ"))
			{
				//normalq
				if (target->position().distance(g_localPlayer->position()) < spellQ->range() && target->position().distance(g_localPlayer->position()) > spellQ->range() - 150)
				{
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//outsideq
				if (target->position().distance(g_localPlayer->position()) > spellQ->range() && target->position().distance(g_localPlayer->position()) < spellQ->range() + spellE->range() - 120 && spellE->isReady() && g_menu->harassE->getBool())
				{
					auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 520;
					epos.y = g_navMesh->heightForPosition(epos);
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellEGlobal->cast(epos);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//inside
				if (target->position().distance(g_localPlayer->position()) < spellQ->range() && target->position().distance(g_localPlayer->position()) < spellQ->range() - 150 && spellE->isReady() && g_menu->harassE->getBool())
				{
					auto dist = spellQ->range() - target->position().distance(g_localPlayer->position());
					if (dist < 400)
					{
						auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 520;
						epos.y = g_navMesh->heightForPosition(epos);
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
						spellEGlobal->cast(epos);
					}
				}
				if (!spellE->isReady() || !g_menu->harassE->getBool())
				{
					if (spellQ->isReady() && g_menu->harassQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
					}
				}
			}
			//q2
			if (target && spellQ->isReady() && g_menu->harassQ->getBool() && g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ2"))
			{
				//normalq2
				if (target->position().distance(g_localPlayer->position()) < spellQ2->range() && target->position().distance(g_localPlayer->position()) > spellQ2->range() - 150)
				{
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//outsideq2
				if (target->position().distance(g_localPlayer->position()) > spellQ2->range() && target->position().distance(g_localPlayer->position()) < spellQ2->range() + spellE->range() - 150 && spellE->isReady() && g_menu->harassE->getBool())
				{
					auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 425;
					epos.y = g_navMesh->heightForPosition(epos);
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellEGlobal->cast(epos);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//inside2
				if (target->position().distance(g_localPlayer->position()) < spellQ2->range() && target->position().distance(g_localPlayer->position()) < spellQ2->range() - 150 && spellE->isReady() && g_menu->harassE->getBool())
				{
					auto dist = spellQ2->range() - target->position().distance(g_localPlayer->position());
					if (dist < 300)
					{
						auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 425;
						epos.y = g_navMesh->heightForPosition(epos);
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
						spellEGlobal->cast(epos);
					}
				}
				if (!spellE->isReady() || !g_menu->harassE->getBool())
				{
					if (spellQ->isReady() && g_menu->harassQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ2->range())
					{
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
					}
				}
			}
			//q3
			if (target && spellQ->isReady() && g_menu->harassQ->getBool() && g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ3"))
			{
				//normalq3
				if (target->position().distance(g_localPlayer->position()) < spellQ3->range() - 130)
				{
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellQGlobal->cast(pred.predictedPosition);
				}
				//outsideq3
				if (target->position().distance(g_localPlayer->position()) > spellQ3->range() && target->position().distance(g_localPlayer->position()) < spellQ3->range() + spellE->range() - 139 && spellE->isReady() && g_menu->harassE->getBool())
				{
					auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 240;
					epos.y = g_navMesh->heightForPosition(epos);
					auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
					spellQGlobal->cast(pred.predictedPosition);
					spellEGlobal->cast(epos);
				}
				//inside3
				if (spellQ->isReady() && spellE->isReady() && g_menu->harassE->getBool())
				{
					auto dist = spellQ3->range() - target->position().distance(g_localPlayer->position());
					if (dist < spellQ3->range() && dist > spellQ3->range() - 130)
					{
						auto epos = target->position() + (g_localPlayer->position() - target->position()).normalized() * 240;
						epos.y = g_navMesh->heightForPosition(epos);
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
						spellEGlobal->cast(epos);
					}
				}
				if (!spellE->isReady() || !g_menu->harassE->getBool())
				{
					if (spellQ->isReady() && g_menu->harassQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ2->range())
					{
						auto pred = g_moduleManager->prediction()->getFastPrediction(g_localPlayer->position(), target, 400, 2000);
						spellQGlobal->cast(pred.predictedPosition);
					}
				}
			}
			if (target && spellW->isReady() && g_menu->harassW->getBool())
			{
				spellW->castPrediction(target, Hitchance::Medium);
			}
		}
	}
	void active()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 30000);
		for (auto target : target2)
		{
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
		auto minions = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer->position(), 600);
		for (auto& minion : minions)
		{
			if (minion)
			{
				if (spellQ->isReady() && g_menu->clearQ->getBool() && countminioninrange(minion->position(),300) >= 3)
				{
					if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ") && minion->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						spellQGlobal->cast(minion->position());
					}
					if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ2") && minion->position().distance(g_localPlayer->position()) < spellQ2->range())
					{
						spellQGlobal->cast(minion->position());
					}
					if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ3") && minion->position().distance(g_localPlayer->position()) < spellQ3->range())
					{
						spellQGlobal->cast(minion->position());
					}
				}
			}
		}
	}

	void onDraw(OnDrawEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			auto newpos = g_localPlayer->position().toScreen();
			g_drawings->drawText(Vector2(newpos.x - 30, newpos.y + 50), "DarkAio", 25, 0xff000000, false, false);
			if (g_menu->drawQRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::Q)->isLearned())
			{
				if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ"))
				{
					g_drawings->drawWorldCircle(g_localPlayer->position(), spellQ->range(), 2, g_menu->drawQRange.color->getColor());

				}
				else if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ2"))
				{
					g_drawings->drawWorldCircle(g_localPlayer->position(),spellQ2->range(), 2, g_menu->drawQRange.color->getColor());

				}
				else if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ3"))
				{
					g_drawings->drawWorldCircle(g_localPlayer->position(), spellQ3->range(), 2, g_menu->drawQRange.color->getColor());

				}
			}
			if (g_menu->drawWRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::W)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellW->range(), 2, g_menu->drawWRange.color->getColor());
			}
			if (g_menu->drawERange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::E)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellE->range(), 2, g_menu->drawERange.color->getColor());
			}
			if (g_menu->drawQERange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::E)->isLearned() && g_localPlayer->spell(SpellSlot::Q)->isLearned())
			{
				if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ"))
				{
					g_drawings->drawWorldCircle(g_localPlayer->position(), spellE->range() + spellQ->range() - 70, 2, 0xff0000ff);

				}
				else if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ2"))
				{
					g_drawings->drawWorldCircle(g_localPlayer->position(), spellE->range() + spellQ2->range() - 150, 2, 0xff0000ff);

				}
				else if (g_localPlayer->spell(SpellSlot::Q)->name() == xorstr_("AatroxQ3"))
				{
					g_drawings->drawWorldCircle(g_localPlayer->position(), spellE->range() + spellQ3->range() - 130, 2, 0xff0000ff);

				}
			}
		}
	}



	void onUpdate(GameUpdateEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			auto orb = g_moduleManager->orbwalker();
			//active();
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
		spellQ->setRange(625);
		spellQ->setSpeed(3000);

		spellQE = std::make_unique<PositionSpell>(SpellSlot::Q);
		spellQE->setCastDelay(250);
		spellQE->setRange(875);
		spellQE->setSpeed(3000);

		spellQ2 = std::make_unique<PositionSpell>(SpellSlot::Q);
		spellQ2->setCastDelay(250);
		spellQ2->setRange(500);
		spellQ2->setSpeed(3000);

		spellQ2E = std::make_unique<PositionSpell>(SpellSlot::Q);
		spellQ2E->setCastDelay(250);
		spellQ2E->setRange(750);
		spellQ2E->setSpeed(3000);

		spellQ3 = std::make_unique<PositionSpell>(SpellSlot::Q);
		spellQ3->setCastDelay(250);
		spellQ3->setRange(500);
		spellQ3->setSpeed(3000);

		spellQ3E = std::make_unique<PositionSpell>(SpellSlot::Q);
		spellQE->setCastDelay(250);
		spellQE->setRange(750);
		spellQE->setSpeed(3000);

		spellE = std::make_unique<PositionSpell>(SpellSlot::E);
		spellE->setRange(250);
		
		//for avoid range check.
		spellEGlobal = std::make_unique<PositionSpell>(SpellSlot::E);
		spellEGlobal->setRange(2000);

		spellQGlobal = std::make_unique<PositionSpell>(SpellSlot::Q);
		spellQGlobal->setCastDelay(250);
		spellQGlobal->setRange(1000);
		spellQGlobal->setSpeed(3000);
		spellQGlobal->setRadius(70);

		spellW = std::make_unique<PositionSpell>(SpellSlot::W);
		spellW->setCastDelay(250);
		spellW->setRange(825);
		spellW->setSpeed(1800);
		spellW->setRadius(100);
		spellW->setBoundingRadiusCollision(true);
		spellW->setCollisions({ Collisions::Windwall, Collisions::Heros, Collisions::Minions });
		spellW->setSkillshotType(SkillshotType::Line);

		spellR = std::make_unique<SelfSpellAoe>(SpellSlot::R);
		spellR->setEffectRange(600);

		EventHandler<Events::OnDraw>::subscribe(onDraw);
		EventHandler<Events::GameUpdate>::subscribe(onUpdate);
	}

	void unload()
	{
		EventHandler<Events::OnDraw>::unsubscribe(onDraw);
		EventHandler<Events::GameUpdate>::unsubscribe(onUpdate);

		spellQ.reset();
		spellW.reset();
		spellE.reset();
		spellR.reset();
		spellQE.reset();
		spellQ2.reset();
		spellQ2E.reset();
		spellQ3.reset();
		spellQ3E.reset();
		//for avoid range check.
		spellEGlobal.reset();
		spellQGlobal.reset();

		g_mainMenu->removeMenu(g_menu->menu);
		delete g_menu;
	}
}