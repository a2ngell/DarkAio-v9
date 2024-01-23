#include "Riven.h"
#include <SDK/src/SDK.h>

namespace Riven
{
	std::vector<std::string> comboBoxModes =
	{
	  xorstr_("After Attack"),
	  xorstr_("Allways"),
	};
	std::vector<std::string> comboBoxRModes =
	{
	  xorstr_("If Killable"),
	  xorstr_("If Target Has x% Health"),
	};
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Darkaioriven"), xorstr_("DarkAio Riven"));

		MenuTabPtr combogeneralTab = menu->createTab(xorstr_("combogeneral"), xorstr_("Combo"));
		MenuTabPtr harassgeneralTab = menu->createTab(xorstr_("harassgeneral"), xorstr_("Harass"));
		MenuTabPtr killstealgeneralTab = menu->createTab(xorstr_("killstealgeneral"), xorstr_("Killsteal"));
		MenuTabPtr miscgeneralTab = menu->createTab(xorstr_("miscgeneral"), xorstr_("Misc"));
		MenuTabPtr farmgeneralTab = menu->createTab(xorstr_("farmgeneral"), xorstr_("Farm"));
		MenuTabPtr drawgeneralTab = menu->createTab(xorstr_("drawgeneral"), xorstr_("Draw"));

		TabChildPtr comboMenu = combogeneralTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr comboQmode = comboMenu->addComboBox(xorstr_("Combo Q Mode"), xorstr_("Combo Q Mode"), comboBoxModes, comboBoxModes[0]);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboE = comboMenu->addCheckBox(xorstr_("Use E Combo"), xorstr_("Use E"), true);
		MenuElementPtr comboR = comboMenu->addCheckBox(xorstr_("Use R Combo"), xorstr_("Use R"), true);
		MenuElementPtr comboR2end = comboMenu->addCheckBox(xorstr_("Use R2 If About The End "), xorstr_("Use R2 If About The End"), true);
		MenuElementPtr comboRmode = comboMenu->addComboBox(xorstr_("Combo R Mode"), xorstr_("Comb R Mode"), comboBoxRModes, comboBoxRModes[0]);
		MenuElementPtr comboRMinHp = comboMenu->addSlider(xorstr_("Use R MinHp"), xorstr_("Min R Health"), 40, 0, 100);
		MenuElementPtr ComboR2Count = comboMenu->addSlider(xorstr_("Use R2 Enemy Count"), xorstr_("^- Min R2 Enemies Count"), 2, 1, 5);

		TabChildPtr harassMenu = harassgeneralTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), true);
		MenuElementPtr harassE = harassMenu->addCheckBox(xorstr_("Use E Harass"), xorstr_("Use E"), false);

		TabChildPtr KillstealMenu = killstealgeneralTab->createTabChild(xorstr_("Killsteal Settings"), xorstr_("Killsteal Settings"), true);
		MenuElementPtr KillstealQ = KillstealMenu->addCheckBox(xorstr_("Use Q Killsteal"), xorstr_("Use Q"), true);
		MenuElementPtr KillstealW = KillstealMenu->addCheckBox(xorstr_("Use W Killsteal"), xorstr_("Use W"), true);
		MenuElementPtr KillstealE = KillstealMenu->addCheckBox(xorstr_("Use EQ Killsteal"), xorstr_("Use E-Q E-W"), true);
		MenuElementPtr KillstealR = KillstealMenu->addCheckBox(xorstr_("Use R Killsteal"), xorstr_("Use R"), true);
		//TabChildPtr MiscMenu = miscgeneralTab->createTabChild(xorstr_("Misc Settings"), xorstr_("Misc Settings"), true);

		TabChildPtr FarmMenu = farmgeneralTab->createTabChild(xorstr_("Farm Settings"), xorstr_("Farm Settings"), true);
		MenuElementPtr clearQ = FarmMenu->addCheckBox(xorstr_("Use Q"), xorstr_("Use Q"), true);
		MenuElementPtr clearW = FarmMenu->addCheckBox(xorstr_("Use W"), xorstr_("Use W"), true);
		MenuElementPtr clearE = FarmMenu->addCheckBox(xorstr_("Use E"), xorstr_("Use E"), true);

		TabChildPtr drawingsMenu = drawgeneralTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 165, 0, 200, true);
		ColorCheckbox drawWRange = addColorCheckbox(drawingsMenu, xorstr_("W"), 255, 165, 0, 200, true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 0, 0, 200, true);
		ColorCheckbox drawRRange = addColorCheckbox(drawingsMenu, xorstr_("R"), 255, 165, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<TargetSpell> spellQ;
	std::unique_ptr<SelfSpellAoe> spellW;
	std::unique_ptr<PositionSpell> spellE;
	std::unique_ptr<PositionSpell> spellR;
	std::unique_ptr<SelfSpell> spellR1;

	int QlvlDmg[] = { 15, 35, 55, 75, 95 };
	int WlvlDmg[] = { 65, 95, 125, 155, 185 };
	//int ElvlDmg[] = { 20, 35, 50, 65, 80 };
	int RlvlDmg[] = { 100, 150, 200 };

	double lastqgametime = 0;
	bool castedq = false;

	int countenemyinrange(Vector3 pos, int range)
	{
		auto count = 0;
		auto allies = g_objectManager->players().alive().enemies().targetable().visible().inRange(pos, range);
		for (auto& a : allies)
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
			auto spelleevel = g_localPlayer->spell(SpellSlot::Q)->level();
			auto totalad = g_localPlayer->stats()->totalAD();
			if (spelleevel == 1)
			{
				dmg = dmg + QlvlDmg[spelleevel-1] + (totalad * 0.5);
			}
			if (spelleevel == 2)
			{
				dmg = dmg + QlvlDmg[spelleevel-1] + (totalad * 0.55);
			}
			if (spelleevel == 3)
			{
				dmg = dmg + QlvlDmg[spelleevel-1] + (totalad * 0.6);
			}
			if (spelleevel == 4)
			{
				dmg = dmg + QlvlDmg[spelleevel-1] + (totalad * 0.65);
			}
			if (spelleevel == 5)
			{
				dmg = dmg + QlvlDmg[spelleevel-1] + (totalad * 0.7);
			}
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, 0, dmg, 0);
		}
		return damage;
	}

	int GetWDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmg = 0;
			auto spelleevel = g_localPlayer->spell(SpellSlot::W)->level();
			auto bonusad = g_localPlayer->stats()->bonusAD();
			if (spelleevel >= 1)
			{
				dmg = dmg + WlvlDmg[spelleevel-1] + bonusad;
			}
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, 0, dmg, 0);
		}
		return damage;
	}

	int GetRDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmg = 0;
			auto spelleevel = g_localPlayer->spell(SpellSlot::R)->level();
			auto bonusad = g_localPlayer->stats()->bonusAD();
			if (spelleevel >= 1)
			{
				dmg = dmg + RlvlDmg[spelleevel-1] + (bonusad * 0.6);
			}
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, 0, dmg, 0);
		}
		return damage;
	}


	int GetComboDamage(IGameObject* target)
	{
		auto dmg = 0;
		if (target)
		{
			dmg = dmg + g_moduleManager->damageLib()->calculateAutoAttackDamage(g_localPlayer, target);
			if (spellQ->isReady())
			{
				dmg = dmg + GetQDamage(target);
			}
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
				g_drawings->drawWorldCircle(g_localPlayer->position(), 310, 2, g_menu->drawERange.color->getColor());
			}
			if (g_menu->drawRRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::R)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellR->range(), 2, g_menu->drawRRange.color->getColor());
			}
		}
	}

	bool havershot()
	{
		auto flag = false;
		for (auto&& buff : g_localPlayer->buffs()) {
			if (buff.get()->name() == "rivenwindslashready")
			{
				flag = true;
			}
		}
		return flag;
	}

	double getrendtime()
	{
		auto flag = false;
		for (auto&& buff : g_localPlayer->buffs()) {
			if (buff.get()->name() == "rivenwindslashready" && buff->endTime() - 1 < g_game->gameTime())
			{
				flag = true;
			}
		}
		return flag;
	}

	void combo()
	{
		if (spellE->isReady() && g_menu->comboE->getBool())
		{
			auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 520);
			for (auto& target : enemy)
			{
				if (target)
				{
					spellE->cast(target->position());
				}
			}
		}
		if (spellR->isReady() && g_menu->comboR->getBool() && g_localPlayer->spell(SpellSlot::R)->name() == "RivenFengShuiEngine")
		{
			auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
			for (auto& target : enemy)
			{
				if (target)
				{
					if (GetComboDamage(target) >= target->health())
					{
						spellR1->cast();
					}
					if (g_menu->comboRmode->getInt() == 1 && target->health() <= (target->maxHealth() / 100) * g_menu->comboRMinHp->getInt())
					{
						spellR1->cast();
					}
				}
			}
		}
		if (spellR->isReady() && g_menu->comboR->getBool() && g_localPlayer->spell(SpellSlot::R)->name() == "RivenIzunaBlade" && havershot())
		{
			auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellR->range());
			for (auto& target : enemy)
			{
				if (target)
				{
					if (getrendtime() and g_menu->comboR2end->getBool())
					{
						spellR->castPrediction(target, Hitchance::High);
					}
					if (countenemyinrange(target->position(),400) >= g_menu->ComboR2Count->getInt())
					{
						spellR->castPrediction(target,Hitchance::High);
					}
				}
			}
		}
		if (spellQ->isReady() && g_menu->comboQ->getBool())
		{
			if (g_menu->comboQmode->getInt() == 1)
			{
				auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
				for (auto& target : enemy)
				{
					if (target)
					{
						spellQ->cast(target);
					}
				}
			}
		}
		if (spellW->isReady() && g_menu->comboW->getBool())
		{
			if (g_menu->comboW->getBool())
			{
				//countenemyinrange(player.position(),spellW->range()) >= 1
				auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellW->effectRange());
				for (auto& target : enemy)
				{
					if (target)
					{
						spellW->cast();
					}
				}
			}
		}
	}

	void harass()
	{
		if (spellE->isReady() && g_menu->harassE->getBool())
		{
			auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 520);
			for (auto& target : enemy)
			{
				if (target)
				{
					spellE->cast(target->position());
				}
			}
		}
		if (spellQ->isReady() && g_menu->harassQ->getBool())
		{
			if (g_menu->comboQmode->getInt() == 1)
			{
				auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
				for (auto& target : enemy)
				{
					if (target)
					{
						spellQ->cast(target);
					}
				}
			}
		}
		if (spellW->isReady() && g_menu->harassW->getBool())
		{
			if (g_menu->comboW->getBool())
			{
				//countenemyinrange(player.position(),spellW->range()) >= 1
				auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellW->effectRange());
				for (auto& target : enemy)
				{
					if (target)
					{
						spellW->cast();
					}
				}
			}
		}
	}
	void active()
	{
		if (spellQ->isReady() && g_menu->KillstealQ->getBool())
		{
			auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
			for (auto& target : enemy)
			{
				if (target && GetQDamage(target) > target->health())
				{
					spellQ->cast(target);
				}
			}
		}
		if (spellW->isReady() && g_menu->KillstealW->getBool())
		{
				auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellW->effectRange());
				for (auto& target : enemy)
				{
					if (target && GetWDamage(target) > target->health())
					{
						spellW->cast();
					}
				}
		}
		if (spellE->isReady() && g_menu->KillstealE->getBool())
		{
			auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 520);
			for (auto& target : enemy)
			{
				if (target && GetWDamage(target) > target->health() || GetQDamage(target) > target->health())
				{
					spellE->cast(target->position());
				}
			}
		}
		if (spellR->isReady() && g_menu->KillstealR->getBool() && g_localPlayer->spell(SpellSlot::R)->name() == "RivenIzunaBlade" && havershot())
		{
			auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellR->range());
			for (auto& target : enemy)
			{
				if (target)
				{
					if (GetRDamage(target) > target->health())
					{
						spellR->castPrediction(target, Hitchance::High);
					}
				}
			}
		}

	}
	void laneclear()
	{
		if (g_menu->comboQmode->getInt() == 1 && spellQ->isReady() && g_menu->clearQ->getBool())
		{
			auto minions = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
			for (auto& minion : minions)
			{
				if (minion)
				{
					spellQ->cast(minion);
				}
			}
		}
	}

	void onUpdate(GameUpdateEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			active();
			auto orb = g_moduleManager->orbwalker();

			//if (castedq && lastqgametime + 0.02 < g_game->gameTime())
			//{
			//	DLOG(lastqgametime);
			//	DLOG(g_game->gameTime());
			//	orb->resetAA();
			//	castedq = false;
			//}
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
	void afterattack(OnOrbwalkerCancelEventArgs* args)
	{
		if (g_menu->comboQmode->getInt() == 0 && spellQ->isReady() && g_menu->comboQ->getBool())
		{
			auto orb = g_moduleManager->orbwalker();
			if (orb->isComboMode() || orb->isHarassMode())
			{
				auto enemy = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
				for (auto& target : enemy)
				{
					if (target)
					{
						if (spellQ->cast(target))
						{
							lastqgametime = g_game->gameTime();
							castedq = true;
							orb->resetAA();
						}
					}
				}

			}
		}
		if (g_menu->comboQmode->getInt() == 0 && spellQ->isReady() && g_menu->clearQ->getBool())
		{
			auto orb = g_moduleManager->orbwalker();
			if (orb->isLaneClearMode())
			{
				auto minions = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
				for (auto& minion : minions)
				{
					if (minion)
					{
						if (spellQ->cast(minion))
						{
							lastqgametime = g_game->gameTime();
							castedq = true;
							orb->resetAA();
						}
					}
				}
			}
		}

	}
	auto globalindex = 0;
	void preattack1(OnOrbwalkerPreAttackEventArgs* args)
	{
		DLOG("index:");
		DLOG(globalindex);
		DLOG("time:");
		DLOG(g_game->gameTime());
		DLOG("process:");
		DLOG(args->process);
		DLOG("qname:");
		auto qactive = g_localPlayer->activeSpell()->info()->name();
		//DLOG(qactive);
		globalindex++;
	}
	void load()
	{
		g_menu = new Menu();

		spellQ = std::make_unique<TargetSpell>(SpellSlot::Q);
		spellQ->setCastDelay(250);
		spellQ->setRange(325);
		spellQ->setCollisions({ Collisions::Windwall });

		spellW = std::make_unique<SelfSpellAoe>(SpellSlot::W);
		spellW->setEffectRange(260);

		spellE = std::make_unique<PositionSpell>(SpellSlot::E);
		spellE->setRange(520);

		spellR1 = std::make_unique<SelfSpell>(SpellSlot::R);

		spellR = std::make_unique<PositionSpell>(SpellSlot::R);
		spellR->setRange(1100);
		spellR->setSpeed(2000);
		spellR->setRadius(200);
		spellR->setBoundingRadiusCollision(true);
		spellR->setCollisions({ Collisions::Windwall });
		spellR->setSkillshotType(SkillshotType::Line);

		EventHandler<Events::OnDraw>::subscribe(onDraw);
		EventHandler<Events::OnOrbwalkerPreAttack>::subscribe(preattack1);
		EventHandler<Events::GameUpdate>::subscribe(onUpdate);
		EventHandler<Events::OnOrbwalkerCancelEvent>::subscribe(afterattack);

	}

	void unload()
	{
		EventHandler<Events::OnDraw>::unsubscribe(onDraw);
		EventHandler<Events::OnOrbwalkerPreAttack>::unsubscribe(preattack1);
		EventHandler<Events::GameUpdate>::unsubscribe(onUpdate);
		EventHandler<Events::OnOrbwalkerCancelEvent>::subscribe(afterattack);


		spellQ.reset();
		spellW.reset();
		spellE.reset();
		spellR.reset();

		g_mainMenu->removeMenu(g_menu->menu);
		delete g_menu;
	}
}