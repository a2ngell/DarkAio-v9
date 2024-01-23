#include "Katarina.h"
#include <SDK/src/SDK.h>

namespace Amumu
{
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Amumu"), xorstr_("DarkAio Amumu"));

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

		TabChildPtr hitchanceMenu = combogeneralTab->createTabChild(xorstr_("Hitchance Settings"), xorstr_("Hitchance Settings"), true);
		MenuElementPtr hitchanceQcombo = hitchanceMenu->addComboBox(xorstr_("Q Hitchance Combo"), xorstr_("Combo: Q"), g_hitchanceList, HITCHANCE_HIGH);
		MenuElementPtr hitchanceQharass = hitchanceMenu->addComboBox(xorstr_("Q Hitchance Harass"), xorstr_("Harass: Q"), g_hitchanceList, HITCHANCE_MEDIUM);

		TabChildPtr harassMenu = harassgeneralTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), true);
		MenuElementPtr harassE = harassMenu->addCheckBox(xorstr_("Use E Harass"), xorstr_("Use E"), true);

		TabChildPtr KillstealMenu = killstealgeneralTab->createTabChild(xorstr_("Killsteal Settings"), xorstr_("Killsteal Settings"), true);
		MenuElementPtr KillstealQ = KillstealMenu->addCheckBox(xorstr_("Use Q Killsteal"), xorstr_("Use Q"), true);
		MenuElementPtr KillstealE = KillstealMenu->addCheckBox(xorstr_("Use E Killsteal"), xorstr_("Use E"), true);

		TabChildPtr MiscMenu = miscgeneralTab->createTabChild(xorstr_("Misc Settings"), xorstr_("Misc Settings"), true);

		TabChildPtr FarmMenu = farmgeneralTab->createTabChild(xorstr_("Farm Settings"), xorstr_("Farm Settings"), true);
		MenuElementPtr clearQ = FarmMenu->addCheckBox(xorstr_("Use Q"), xorstr_("Use Q"), false);
		MenuElementPtr clearQStack = FarmMenu->addCheckBox(xorstr_("Use Q1"), xorstr_("Q Always Save Stack"), false);
		MenuElementPtr clearW = FarmMenu->addCheckBox(xorstr_("Use W"), xorstr_("Use W"), false);
		MenuElementPtr clearE = FarmMenu->addCheckBox(xorstr_("Use E"), xorstr_("Use E"), false);

		TabChildPtr drawingsMenu = drawgeneralTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 165, 0, 200, true);
		ColorCheckbox drawWRange = addColorCheckbox(drawingsMenu, xorstr_("W"), 255, 165, 0, 200, true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 0, 0, 200, true);
		ColorCheckbox drawRRange = addColorCheckbox(drawingsMenu, xorstr_("R"), 255, 165, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<PositionSpell> spellQ;
	std::unique_ptr<SelfSpellAoe> spellW;
	std::unique_ptr<SelfSpellAoe> spellE;
	std::unique_ptr<SelfSpellAoe> spellR;
	int QlvlDmg[] = { 70, 95, 120, 145, 170 };
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
	bool castingw()
	{
		auto flag = false;
		auto buff = g_localPlayer->buff(BUFF_HASH("AuraofDespair"));
		if (buff && buff->isValid())
			flag = true;
		return flag;
		spellW;
	}

	void combo()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (target && spellQ->isReady() && g_menu->comboQ->getBool())
			{
				spellQ->castPrediction(target, fromString(g_menu->hitchanceQcombo->getString()));
			}
		}
		if (spellW->isReady() && g_menu->comboW->getBool() &&  countenemyinrange(g_localPlayer->position(),spellW->effectRange()) > 0 && !castingw())
		{
			spellW->cast();
		}
		if (spellW->isReady() && g_menu->comboW->getBool() && countenemyinrange(g_localPlayer->position(), spellW->effectRange()) == 0 && castingw())
		{
			spellW->cast();
		}
		if (spellE->isReady() && g_menu->comboE->getBool() && countenemyinrange(g_localPlayer->position(), spellE->effectRange()) > 0)
		{
			spellE->cast();
		}
		if (spellR->isReady() && g_menu->comboR->getBool() && countenemyinrange(g_localPlayer->position(), spellR->effectRange()) >= g_menu->ComboRCount->getInt())
		{
			spellR->cast();
		}
	}
	void harass()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (target && spellQ->isReady() && g_menu->harassQ->getBool())
			{
				spellQ->castPrediction(target, fromString(g_menu->hitchanceQharass->getString()));
			}
		}
		if (spellW->isReady() && g_menu->harassW->getBool() && countenemyinrange(g_localPlayer->position(), spellW->effectRange()) > 0 && !castingw())
		{
			spellW->cast();
		}
		if (spellW->isReady() && g_menu->harassW->getBool() && countenemyinrange(g_localPlayer->position(), spellW->effectRange()) == 0 && castingw())
		{
			spellW->cast();
		}
		if (spellE->isReady() && g_menu->harassE->getBool() && countenemyinrange(g_localPlayer->position(), spellE->effectRange()) > 0)
		{
			spellE->cast();
		}
	}
	void active()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 30000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (target && spellQ->isReady() && g_menu->KillstealQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ->range() && GetQDamage(target) > target->health())
			{
				spellQ->castPrediction(target, Hitchance::Medium);
			}
			if (spellE->isReady() && g_menu->KillstealE->getBool() && target->position().distance(g_localPlayer->position()) < spellE->effectRange() && GetEDamage(target) > target->health())
			{
				spellE->cast();
			}
		}
	}

	int countlaneminioninrange(Vector3 pos, float range)
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
		auto countminioninrange = countlaneminioninrange(g_localPlayer->position(), 350);
		if (spellW->isReady() && g_menu->clearW->getBool() && countminioninrange > 0 && !castingw())
		{
			spellW->cast();
		}
		if (spellW->isReady() && g_menu->clearW->getBool() && countminioninrange == 0 && castingw())
		{
			spellW->cast();
		}
		if (spellE->isReady() && g_menu->clearE->getBool() && countminioninrange > 0 )
		{
			spellE->cast();
		}
		auto minions = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer->position(), spellQ->range() - 50);
		for (auto& minion : minions)
		{
			if (minion && minion->isBigJunglerMoster())
			{
				if (spellQ->isReady() && g_menu->clearQ->getBool())
				{
					if (g_menu->clearQStack->getBool() && g_localPlayer->spell(SpellSlot::Q)->charges() < 2)
					{

					}
					else
					{
						spellQ->cast(minion->position());
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
			if (g_menu->drawWRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::W)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellW->effectRange(), 2, g_menu->drawWRange.color->getColor());
			}
			if (g_menu->drawERange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::E)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellE->effectRange(), 2, g_menu->drawERange.color->getColor());
			}
			if (g_menu->drawRRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::R)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellR->effectRange(), 2, g_menu->drawRRange.color->getColor());
			}
			auto newpos = g_localPlayer->position().toScreen();
			g_drawings->drawText(Vector2(newpos.x - 30, newpos.y + 50), "DarkAio", 25, 0xff000000, false, false);
		}
	}


	void onUpdate(GameUpdateEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
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
		spellQ->setCastDelay(350);
		spellQ->setRange(1100);
		spellQ->setCollisions({ Collisions::Windwall, Collisions::Heros, Collisions::Minions });
		spellQ->setBoundingRadiusCollision(true);
		spellQ->setSpeed(2000);
		spellQ->setRadius(100);

		spellW = std::make_unique<SelfSpellAoe>(SpellSlot::W);
		spellW->setEffectRange(350);

		spellE = std::make_unique<SelfSpellAoe>(SpellSlot::E);
		spellE->setEffectRange(350);

		spellR = std::make_unique<SelfSpellAoe>(SpellSlot::R);
		spellR->setEffectRange(550);

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

		g_mainMenu->removeMenu(g_menu->menu);
		delete g_menu;
	}
}