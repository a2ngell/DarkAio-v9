#include "Katarina.h"
#include <SDK/src/SDK.h>

namespace Katarina
{
	std::vector<std::string> comboBoxModes =
	{
	  xorstr_("Q-E"),
	  xorstr_("E-Q"),
	  xorstr_("AUTO")
	};
	std::vector<std::string> comboBoxEModes =
	{
	  xorstr_("Infront"),
	  xorstr_("Behind"),
	  xorstr_("Smart")
	};
	std::vector<std::string> comboBoxRModes =
	{
	  xorstr_("If Target Has x% Health"),
	  xorstr_("If Killable"),
	  xorstr_("If Count >="),
	  xorstr_("Auto(Killable And Count)")
	};
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Katarina"), xorstr_("DarkAio Katarina"));

		MenuTabPtr combogeneralTab = menu->createTab(xorstr_("combogeneral"), xorstr_("Combo"));
		MenuTabPtr harassgeneralTab = menu->createTab(xorstr_("harassgeneral"), xorstr_("Harass"));
		MenuTabPtr killstealgeneralTab = menu->createTab(xorstr_("killstealgeneral"), xorstr_("Killsteal"));
		MenuTabPtr miscgeneralTab = menu->createTab(xorstr_("miscgeneral"), xorstr_("Misc"));
		MenuTabPtr farmgeneralTab = menu->createTab(xorstr_("farmgeneral"), xorstr_("Farm"));
		MenuTabPtr drawgeneralTab = menu->createTab(xorstr_("drawgeneral"), xorstr_("Draw"));

		TabChildPtr comboMenu = combogeneralTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr combomode = comboMenu->addComboBox(xorstr_("Combo Mode"), xorstr_("Combo Mode"), comboBoxModes, comboBoxModes[2]);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboE = comboMenu->addCheckBox(xorstr_("Use E Combo"), xorstr_("Use E"), true);
		MenuElementPtr toverdivekey = comboMenu->addKeybind(xorstr_("toverdive"), xorstr_("Use E Under Tower"), Key::G);
		MenuElementPtr comboE_save = comboMenu->addCheckBox(xorstr_("esave"), xorstr_("Save E if no Dagger"), true);
		MenuElementPtr comboEmode = comboMenu->addComboBox(xorstr_("Combo E Mode"), xorstr_("Comb E Mode"), comboBoxEModes, comboBoxEModes[2]);
		MenuElementPtr comboR = comboMenu->addCheckBox(xorstr_("Use R Combo"), xorstr_("Use R"), true);
		MenuElementPtr comboRmode = comboMenu->addComboBox(xorstr_("Combo R Mode"), xorstr_("Comb R Mode"), comboBoxRModes, comboBoxRModes[3]);
		MenuElementPtr comboRMinHp = comboMenu->addSlider(xorstr_("Use R MinHp"), xorstr_("Min R Health"), 40, 0, 100);
		MenuElementPtr ComboRCount = comboMenu->addSlider(xorstr_("Use R Enemy Count"), xorstr_("^- Min R Enemies Count"), 2, 1, 5);
		MenuElementPtr ComboRCencle = comboMenu->addSlider(xorstr_("Use R Cencle"), xorstr_("Break R when killable enemy >="), 2, 1, 5);
		MenuElementPtr comboEbeforeR = comboMenu->addCheckBox(xorstr_("Use ER Combo"), xorstr_("Use E Before R"), true);

		TabChildPtr harassMenu = harassgeneralTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassQauto = harassMenu->addCheckBox(xorstr_("Use Q Auto Harass"), xorstr_("Use Auto Q"), true);
		MenuElementPtr HarassQautokey = harassMenu->addKeybind(xorstr_("qautokey"), xorstr_("Q Auto Key"), Key::H);

		TabChildPtr KillstealMenu = killstealgeneralTab->createTabChild(xorstr_("Killsteal Settings"), xorstr_("Killsteal Settings"), true);
		MenuElementPtr KillstealQ = KillstealMenu->addCheckBox(xorstr_("Use Q Killsteal"), xorstr_("Use Q"), true);
		MenuElementPtr KillstealE = KillstealMenu->addCheckBox(xorstr_("Use E Killsteal"), xorstr_("Use E"), true);
		MenuElementPtr KillstealDag = KillstealMenu->addCheckBox(xorstr_("Use Dagger"), xorstr_("Use Dagger"), true);
		MenuElementPtr KillstealEQ = KillstealMenu->addCheckBox(xorstr_("Use EQ Killsteal"), xorstr_("Use E Gapclose For Q"), true);

		TabChildPtr MiscMenu = miscgeneralTab->createTabChild(xorstr_("Misc Settings"), xorstr_("Misc Settings"), true);
		MenuElementPtr Magnet = MiscMenu->addCheckBox(xorstr_("Magnet"), xorstr_("Magnet"), true);
		MenuElementPtr ToverESave = MiscMenu->addCheckBox(xorstr_("ToverSave"), xorstr_("Auto Out Tower Range With E After Kill"), true);

		TabChildPtr FarmMenu = farmgeneralTab->createTabChild(xorstr_("Farm Settings"), xorstr_("Farm Settings"), true);
		MenuElementPtr clearQ = FarmMenu->addCheckBox(xorstr_("Use Q"), xorstr_("Use Q"), true);
		MenuElementPtr clearW = FarmMenu->addCheckBox(xorstr_("Use W"), xorstr_("Use W"), true);
		MenuElementPtr clearE = FarmMenu->addCheckBox(xorstr_("Use E"), xorstr_("Use E"), true);
		MenuElementPtr clearkey = FarmMenu->addKeybind(xorstr_("clearkey"), xorstr_("Farm Key"), Key::J);
		TabChildPtr drawingsMenu = drawgeneralTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 165, 0, 200, true);
		ColorCheckbox drawWRange = addColorCheckbox(drawingsMenu, xorstr_("W"), 255, 165, 0, 200, true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 0, 0, 200, true);
		ColorCheckbox drawRRange = addColorCheckbox(drawingsMenu, xorstr_("R"), 255, 165, 0, 200, true);
		ColorCheckbox drawDagRange = addColorCheckbox(drawingsMenu, xorstr_("Dagger"), 255, 0, 0, 200, true);
		ColorCheckbox drawdamage = addColorCheckbox(drawingsMenu, xorstr_("Damage"), 255, 0, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<TargetSpell> spellQ;
	std::unique_ptr<SelfSpellAoe> spellW;
	std::unique_ptr<PositionSpell> spellE;
	std::unique_ptr<PositionSpell> spellE2;
	std::unique_ptr<SelfSpellAoe> spellR;
	int spellqlevel[] = { 80, 110, 140, 170, 200 };
	int ElvlDmg[] = { 20, 35, 50, 65, 80 };
	double RlvlDmg[] = { 25, 37.5, 50 };
	int PDamages[] = { 68, 72, 77, 82, 89, 96, 103, 112, 121, 131, 142, 154, 166, 180, 194, 208, 224, 240 };
	
	bool haraskeyactive = false;
	bool toverdivekeyactive = false;
	bool farmkeyactive = false;

	bool toverattack = false;

	struct objectholder {
		IGameObject* object;
	};
	std::vector<IGameObject*> daggerholder;

	int countenemyinrange(Vector3 pos,int range)
	{
		auto count = 0;
		auto target1 = g_objectManager->players().alive().enemies().targetable().visible().inRange(pos, range);
		for (auto& target : target1)
		{
			count = count + 1;
		}
		return count;
	}


	int daggerdamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmg = 0;
			auto levelmulti = 0.0;
			if (g_localPlayer->level() < 6)
			{
				levelmulti = 0.7;
			}
			else if (g_localPlayer->level() >= 6 && g_localPlayer->level() < 11)
			{
				levelmulti = 0.8;
			}
			else if (g_localPlayer->level() >= 11 && g_localPlayer->level() < 16)
			{
				levelmulti = 0.9;
			}
			else if (g_localPlayer->level() >= 16)
			{
				levelmulti = 1;
			}
			if (g_localPlayer->level() <= 18)
			{
				dmg = dmg + PDamages[g_localPlayer->level()];
			}
			else
			{
				dmg = dmg + PDamages[18];
			}
			dmg = dmg + (g_localPlayer->stats()->totalAP() * levelmulti) + (g_localPlayer->stats()->bonusAD() * 0.6);
		    damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, dmg, 0, 0);
		}
		return damage;
	}

	int GetQDamage(IGameObject* target)
	{
		auto damage = 0;
		if (target)
		{
			auto dmg = 0;
			if (g_localPlayer->spell(SpellSlot::Q)->level() >= 1)
			{
				dmg = dmg + spellqlevel[g_localPlayer->spell(SpellSlot::Q)->level() - 1];
			}
			dmg = dmg + (g_localPlayer->stats()->totalAP() * 0.35);
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
			dmg = dmg + (g_localPlayer->stats()->totalAP() * 0.25) + (g_localPlayer->stats()->totalAD() * 0.4);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, dmg, 0, 0);
		}
		return damage;
	}

	int GetRDamage(IGameObject* target,int amount)
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
			dmgap = dmgap + (g_localPlayer->stats()->totalAP() * 0.19);
			dmgad = dmgad + (g_localPlayer->stats()->bonusAD() * (g_localPlayer->stats()->percentAttackSpeedMod() / 2)) +(g_localPlayer->stats()->bonusAD() * 0.16);
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, dmgap, dmgad, 0) * amount;
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
			if (spellW->isReady())
			{
				dmg = dmg + daggerdamage(target);
			}
			if (spellE->isReady())
			{
				dmg = dmg + GetEDamage(target);
			}
			if (spellR->isReady())
			{
				dmg = dmg + GetRDamage(target,9);
			}
			if (!daggerholder.empty()) {

				for (IGameObject* dagger : daggerholder) {
					if (dagger->position().distance(target->position()) < 450)
					{
						dmg = dmg + daggerdamage(target);
					}
				}
			}
		}
		return dmg;
	}
	int getkillableenemy()
	{
		auto count = 0;
		auto target1 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellE->range());
		for (auto& target : target1)
		{
			if (target->position().distance(g_localPlayer->position()) < spellE->range() && GetEDamage(target) > target->health())
			{
				count = count + 1;
				continue;
			}
			if (target->position().distance(g_localPlayer->position()) < spellQ->range() && GetQDamage(target) > target->health())
			{
				count = count + 1;
				continue;
			}
			if (target->position().distance(g_localPlayer->position()) < spellE->range())
			{
				if (!daggerholder.empty()) {

					for (IGameObject* dagger : daggerholder) {
						if (dagger->position().distance(target->position()) < 450 && daggerdamage(target) > target->health())
						{
							count = count + 1;
							break;
						}
					}
					continue;
				}
				
			}
		}
		return count;
	}
	bool castingr()
	{
		auto flag = false;
		auto buff = g_localPlayer->buff(BUFF_HASH("katarinarsound"));
		if (buff && buff->isValid())
			flag = true;
		return flag;
	}

	IGameObject* getclosesdagger()
	{
		IGameObject* closes = nullptr;
		auto distance = 9999;
		if (!daggerholder.empty()) {

			for (IGameObject* dagger : daggerholder) {
				if (dagger->position().distance(g_localPlayer->position()) < distance)
				{
					closes = dagger;
					distance = dagger->position().distance(g_localPlayer->position());
				}
			}
		}
		return closes;
	}

	IGameObject* closesobjecttopos(Vector3 pos,float closestotarget,float playertocloses)
	{
		IGameObject* closes = nullptr;
		auto distance = 9999;
		if (!daggerholder.empty()) {

			for (IGameObject* dagger : daggerholder) {
				if (dagger->position().distance(pos) < distance && dagger->position().distance(g_localPlayer->position()) < playertocloses)
				{
					closes = dagger;
					distance = dagger->position().distance(pos);
				}
			}
		}
		if (closes && distance < closestotarget)
		{
			return closes;
		}
		auto minions = g_objectManager->minions().alive().visible().inRange(g_localPlayer->position(), spellE->range());
		for (auto& minion : minions)
		{
			if (minion && minion->position().distance(pos) < distance && minion->position().distance(g_localPlayer->position()) < playertocloses)
			{
				closes = minion;
				distance = minion->position().distance(pos);
			}
		}
		if (closes && distance < closestotarget)
		{
			return closes;
		}
		auto heroes = g_objectManager->players().alive().visible().inRange(g_localPlayer->position(), spellE->range());
		for (auto& hero : heroes)
		{
			if (hero && hero->position().distance(pos) < distance && hero->position().distance(g_localPlayer->position()) < playertocloses)
			{
				closes = hero;
				distance = hero->position().distance(pos);
			}
		}
		if (closes && distance < closestotarget)
		{
			return closes;
		}
		return nullptr;
	}
	IGameObject* gettoveroutobject(Vector3 pos, float jumprange)
	{
		IGameObject* closes = nullptr;
		auto distance = 1;
		if (!daggerholder.empty()) {

			for (IGameObject* dagger : daggerholder) {
				if (dagger->position().distance(pos) > distance && dagger->position().distance(g_localPlayer->position()) < jumprange)
				{
					closes = dagger;
					distance = dagger->position().distance(pos);
				}
			}
		}
		if (closes && distance > g_localPlayer->position().distance(pos))
		{
			return closes;
		}
		auto minions = g_objectManager->minions().alive().visible().inRange(g_localPlayer->position(), spellE->range());
		for (auto& minion : minions)
		{
			if (minion && minion->position().distance(pos) > distance && minion->position().distance(g_localPlayer->position()) < jumprange)
			{
				closes = minion;
				distance = minion->position().distance(pos);
			}
		}
		if (closes && distance > g_localPlayer->position().distance(pos))
		{
			return closes;
		}
		auto heroes = g_objectManager->players().allies().alive().visible().inRange(g_localPlayer->position(), spellE->range());
		for (auto& hero : heroes)
		{
			if (hero && hero->position().distance(pos) > distance && hero->position().distance(g_localPlayer->position()) < jumprange)
			{
				closes = hero;
				distance = hero->position().distance(pos);
			}
		}
		if (closes && distance > g_localPlayer->position().distance(pos))
		{
			return closes;
		}
		return nullptr;
	}
	void ecast(IGameObject* target)
	{
		if (g_menu->comboEmode->getInt() == 0 && spellE->isReady())
		{
			if (spellQ->isReady() || spellW->isReady())
			{
				spellE->cast(target->position().extend(g_localPlayer->position(),50));
			}
		}
		if (g_menu->comboEmode->getInt() == 1 && spellE->isReady())
		{
			if (spellQ->isReady() || spellW->isReady())
			{
				spellE2->cast(target->position().extend(g_localPlayer->position(), -50));
			}
		}
		if (g_menu->comboEmode->getInt() == 2 && spellE->isReady())
		{
			if (!spellW->isReady())
			{
				if (spellQ->isReady() && g_menu->comboQ->getBool() && target->position().distance(g_localPlayer->position()) <= spellQ->range())
				{
					spellQ->cast(target);
				}
				if (spellE->isReady() && !g_menu->comboE_save->getBool())
				{
					spellE2->cast(target->position().extend(g_localPlayer->position(), -50));
				}
			}
			else if (!spellQ->isReady())
			{
				if (spellW->isReady() && spellE->isReady())
				{
					spellE2->cast(target->position().extend(g_localPlayer->position(), -50));
				}
			}
			else 
			{
				spellE->cast(target->position().extend(g_localPlayer->position(), -50));
			}
			if (!g_menu->comboE_save->getBool() && spellQ->isReady() && spellW->isReady())
			{
				if (spellE->isReady())
				{
					spellE2->cast(target->position().extend(g_localPlayer->position(), -50));
				}
			}
		}
	}
	void combo()
	{
		if (castingr()) return;

		auto target1 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellE->range() + 101);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target1, false, false);
		for (auto& target : selectedEnemies)
		{
			if (target && g_menu->comboE->getBool() && spellE->isReady()) {
				if (!toverdivekeyactive && target->position().isInEnemyTowerRange(20)) return;
				if (!daggerholder.empty()) {
					for (IGameObject* dagger : daggerholder) {
						if (spellE->isReady() && g_localPlayer->position().distance(target->position()) < spellE->range())
						{
							if (target->position().distance(dagger->position()) < 470 && dagger->position().extend(target->position(), 101).distance(g_localPlayer->position()) < spellE->range())
							{
								spellE->cast(dagger->position().extend(target->position(),200));
							}
						}
						if (spellE->isReady() && g_localPlayer->position().distance(target->position()) > spellE->range())
						{
							if (target->position().distance(dagger->position()) < 470 && dagger->position().extend(target->position(), 101).distance(g_localPlayer->position()) < spellE->range())
							{
								spellE->cast(dagger->position().extend(target->position(), 101));
							}
						}
					}
				}
			}
		}
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellE->range());
		auto selectedEnemies1 = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto& target : selectedEnemies1)
		{
			if (target)
			{
				if (g_menu->combomode->getInt() == 0)
				{
					if (g_menu->comboQ->getBool() && spellQ->isReady())
					{
						spellQ->cast(target);
					}
					if (g_menu->comboE->getBool() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						ecast(target);
					}
					if (g_menu->comboW->getBool() && spellW->isReady() && target->position().distance(g_localPlayer->position()) < 300)
					{
						spellW->cast();
					}
				}
				if (g_menu->combomode->getInt() == 1)
				{
					if (g_menu->comboE->getBool() && spellE->isReady())
					{
						ecast(target);
					}
					if (g_menu->comboW->getBool() && spellW->isReady() && target->position().distance(g_localPlayer->position()) < 300)
					{
						spellW->cast();
					}
					if (spellQ->isReady() && g_menu->comboQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						spellQ->cast(target);
					}
				}
				if (g_menu->combomode->getInt() == 2)
				{
					if (spellQ->isReady() && g_menu->comboQ->getBool())
					{
						spellQ->cast(target);
					}
					if (g_menu->comboE->getBool() && spellE->isReady())
					{
						if (!toverdivekeyactive && target->position().isInEnemyTowerRange(20)) return;
						ecast(target);
					}
					if (g_menu->comboW->getBool() && spellW->isReady() && target->position().distance(g_localPlayer->position()) < 300)
					{
						spellW->cast();
					}
					if (spellQ->isReady() && g_menu->comboQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ->range())
					{
						spellQ->cast(target);
					}
				}
			}
			if (g_menu->comboW->getBool() && spellW->isReady() && target->position().distance(g_localPlayer->position()) < 300 || countenemyinrange(g_localPlayer->position(), 300) > 0)
			{
				spellW->cast();
			}
			if (g_menu->comboE->getBool() && !g_menu->comboE_save->getBool() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < spellE->range())
			{
				spellE->cast(target->position().extend(g_localPlayer->position(), 50));
			}
			if (g_menu->comboR->getBool() && spellR->isReady())
			{
				if (g_menu->comboRmode->getInt() == 0)
				{
					if (target->position().distance(g_localPlayer->position()) < spellR->effectRange() - 100 && target->healthPercent() * 100 < g_menu->comboRMinHp->getInt())
					{
						if (g_menu->comboEbeforeR->getBool() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < spellE->range())
						{
							spellE->cast(target->position().extend(g_localPlayer->position(), 50));
						}
						spellR->cast();
					}
				}
				if (g_menu->comboRmode->getInt() == 1)
				{
					if (target->position().distance(g_localPlayer->position()) < spellR->effectRange() - 100 && target->health() < GetRDamage(target, 10))
					{
						if (g_menu->comboEbeforeR->getBool() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < spellE->range())
						{
							spellE->cast(target->position().extend(g_localPlayer->position(), 50));
						}
						spellR->cast();
					}
				}
				if (g_menu->comboRmode->getInt() == 2)
				{
					if (countenemyinrange(g_localPlayer->position(),spellR->effectRange() - 40) >= g_menu->ComboRCount->getInt())
					{
						spellR->cast();
					}
				}
				if (g_menu->comboRmode->getInt() == 3)
				{
					if (countenemyinrange(g_localPlayer->position(), spellR->effectRange() - 40) >= g_menu->ComboRCount->getInt())
					{
						spellR->cast();
					}
					if (spellR->isReady() && target->position().distance(g_localPlayer->position()) < spellR->effectRange() - 100 && target->health() < GetRDamage(target, 10))
					{
						if (g_menu->comboEbeforeR->getBool() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < spellE->range())
						{
							spellE->cast(target->position().extend(g_localPlayer->position(), 50));
						}
						spellR->cast();
					}
				}
			}
		}
	}
	void harass()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, spellQ->range());
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto& target : selectedEnemies)
		{
			if (target)
			{
				if (g_menu->harassQ->getBool() && spellQ->isReady() && target->position().distance(g_localPlayer->position()) < spellQ->range())
				{
					spellQ->cast(target);
				}
			}
		}
	}
	void active()
	{
		if (castingr() && g_menu->ComboRCencle->getInt() <= getkillableenemy())
		{
			g_moduleManager->orbwalker()->setBlockMove(false);
			g_moduleManager->orbwalker()->move(g_hud->mousePosition());
		}
		if (castingr()) return;
		if (toverattack && spellE->isReady() && g_menu->ToverESave->getBool())
		{
			auto enemiesInRange = countenemyinrange(g_localPlayer->position(), spellE->range() + 300);
			if (enemiesInRange == 0)
			{
				auto turrets = g_objectManager->turrets().enemies().visible().inRange(g_localPlayer, 1000).nearestTo(g_localPlayer);
				if (!turrets.empty())
				{
					auto tover = turrets[0];
					if (tover && tover->position().distance(g_localPlayer->position()) < 975)
					{
						auto farest = gettoveroutobject(tover->position(), spellE->range());
						if (spellE->isReady() && farest && farest->position().distance(tover->position()) > tover->position().distance(g_localPlayer->position()) + 100 && farest->position().distance(tover->position()) > 975)
						{
							spellE2->cast(farest->position().extend(g_localPlayer->position(), 20));
						}
					}
				}
			}
		}

		auto target1 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 5000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target1, false, false);
		for (auto& target : selectedEnemies)
		{
			if (target)
			{
				if (spellE->isReady() && g_menu->KillstealE->getBool() && target->position().distance(g_localPlayer->position()) < spellE->range() && target->health() < GetEDamage(target))
				{
					if (spellW->isReady())
					{
						spellW->cast();
					}
					spellE->cast(target->position().extend(g_localPlayer->position(), 20));
				}
				if (g_menu->KillstealDag->getBool() && spellE->isReady() && target->position().distance(g_localPlayer->position()) < spellE2->range())
				{
					if (!daggerholder.empty()) {

						for (IGameObject* dagger : daggerholder) {
							if (dagger->position().distance(target->position()) < 470 && daggerdamage(target) > target->health() && spellE->isReady())
							{
								if (spellW->isReady())
								{
									spellW->cast();
								}
								spellE2->cast(dagger->position().extend(target->position(), 200));
							}
						}
					}
				}
				if (spellQ->isReady() && g_menu->KillstealQ->getBool() && target->position().distance(g_localPlayer->position()) < spellQ->range() && target->health() < GetQDamage(target))
				{
					if (spellW->isReady())
					{
						spellW->cast();
					}
					spellQ->cast(target);
				}
				if (spellQ->isReady() && g_menu->harassQauto->getBool() && haraskeyactive && target->position().distance(g_localPlayer->position()) < spellQ->range())
				{
					spellQ->cast(target);
				}
				if (spellQ->isReady() && spellE->isReady() && g_menu->KillstealEQ->getBool() && target->health() < GetQDamage(target) && target->position().distance(g_localPlayer->position()) > spellE->range())
				{
					//auto dist1 = target->position().distance(g_localPlayer->position()) - spellE->range();
					auto closes = closesobjecttopos(target->position(), spellQ->range(),spellE->range());
					if (closes && closes->position().distance(target->position()) < spellE->range() && closes->position().distance(target->position()) < spellE->range() )
					{
						if (spellE->cast(closes->position()))
						{
							spellQ->cast(target);
						}
					}
				}
			}
		}
	}
	int countminioninrange(Vector3 pos,float range)
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
		if (farmkeyactive)
		{
			auto minions = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer, spellE->range());
			for (auto& minion : minions)
			{
				if (minion)
				{
					if (g_menu->clearQ->getBool() && spellQ->isReady())
					{
						spellQ->cast(minion);
					}
					if (g_menu->clearW->getBool() && spellW->isReady() && countminioninrange(g_localPlayer->position(), 300) >= 3)
					{
						spellW->cast();
					}
					if (g_menu->clearE->getBool() && spellE->isReady())
					{
						if (!daggerholder.empty())
						{
							for (IGameObject* dagger : daggerholder) {
								if (countminioninrange(dagger->position(), 300) >= 3 && spellE->isReady())
								{
									spellE->cast(dagger->position());
									break;
								}
							}
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
			if (g_menu->drawWRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::W)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellW->effectRange(), 2, g_menu->drawWRange.color->getColor());
			}
			if (g_menu->drawERange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::E)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellE->range(), 2, g_menu->drawERange.color->getColor());
			}
			if (g_menu->drawRRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::R)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellR->effectRange(), 2, g_menu->drawRRange.color->getColor());
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

			if (toverdivekeyactive)
			{
				g_drawings->drawText(Vector2(newpos.x - 55, newpos.y + 50), "Tover Dive:", 18, 0xdeffffe7);
				g_drawings->drawText(Vector2(newpos.x + 35, newpos.y + 50), "ON", 18, 0xff00ff00);
			}
			else if (!toverdivekeyactive)
			{
				g_drawings->drawText(Vector2(newpos.x - 55, newpos.y + 50), "Tover Dive:", 18, 0xdeffffe7);
				g_drawings->drawText(Vector2(newpos.x + 35, newpos.y + 50), "OFF", 18, 0xff0000ff);
			}
			if (g_menu->drawDagRange.checkbox->getBool())
			{
				if (!daggerholder.empty()) {
					for (IGameObject* dagger : daggerholder) {
						if (countenemyinrange(dagger->position(), 450) > 0)
						{
							g_drawings->drawWorldCircle(dagger->position(), 450, 2, 0xff00ff00);
						}
						if (countenemyinrange(dagger->position(), 450) == 0)
						{
							g_drawings->drawWorldCircle(dagger->position(), 450, 2, g_menu->drawDagRange.color->getColor());
						}
					}
				}
			}
		}
	}

	void onpresent(PresentEventArgs* args)
	{
		auto target1 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 30000);
		for (auto& target : target1)
		{
			if (target)
			{
				if (g_menu->drawdamage.checkbox->getBool())
				{
					g_moduleManager->damageDrawings()->drawDamage(target,getcombodamage(target));
					g_moduleManager->damageDrawings()->~IDamageDrawings();
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
		if (!toverdivekeyactive && g_menu->toverdivekey->isPressed() && !(toverdiveclicktime + 0.2 > g_game->gameTime()))
		{
			toverdivekeyactive = true;
			toverdiveclicktime = g_game->gameTime();
		}
		if (toverdivekeyactive && g_menu->toverdivekey->isPressed() && !(toverdiveclicktime + 0.2 > g_game->gameTime()))
		{
			toverdivekeyactive = false;
			toverdiveclicktime = g_game->gameTime();
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

	double toverdelay = 0;

	void ontovercheck()
	{
			auto tover1 = g_objectManager->turrets().enemies().visible().inRange(g_localPlayer, 1200);
			for (auto& tover : tover1)
			{
				if (tover)
				{
					if (tover->targetNetworkID() == g_localPlayer->networkID() && toverdelay + 0.1 < g_game->gameTime())
					{
						toverattack = true;
						toverdelay = g_game->gameTime();
					}
				}
			}
			if (toverdelay + 0.2 < g_game->gameTime())
			{
				toverattack = false;
			}
	}
	void magnet(OnOrbwalkerPreMoveEventArgs* args)
	{
		if (g_menu->Magnet->getBool() && args && g_moduleManager->orbwalker()->isComboMode())
		{
			if (castingr()) return;
			auto dagger = getclosesdagger();
			auto targets = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 700).nearestTo(g_localPlayer);
			if (!targets.empty() && dagger)
			{
				auto target = targets[0];
				if (target)
				{
					if (dagger->position().distance(g_localPlayer->position()) < 450 && dagger->position().distance(target->position()) < 450)
					{
						if (dagger->position().distance(g_localPlayer->position()) > 150)
						{
							args->position = dagger->position().extend(g_localPlayer->position(), 100); //g_moduleManager->orbwalker()->move();
						}
					}
				}
			}
		}
	}

	void onUpdate(GameUpdateEventArgs* args)
	{
		onkeyupdate();
		if (g_localPlayer->isAlive())
		{
			auto orb = g_moduleManager->orbwalker();
			if (castingr() && countenemyinrange(g_localPlayer->position(), spellR->effectRange() + 10) == 0)
			{
				g_moduleManager->orbwalker()->setBlockMove(false);
				g_moduleManager->orbwalker()->move(g_hud->mousePosition());
			}
			if (castingr())
			{
				orb->setBlockAttack(true);
				orb->setBlockMove(true);
			}
			else
			{
				orb->setBlockAttack(false);
				orb->setBlockMove(false);
			}
			ontovercheck();
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

	void onobjectcreate(OnObjectCreateEventArgs* args)
	{
		//Katarina_Base_W_Indicator_Ally
		if (args->object &&
			args->object->name().find("Katarina_") != std::string::npos &&
			args->object->name().find("W_Indicator_Ally") != std::string::npos)
		{
			daggerholder.push_back(args->object);
		}
	}
	void onobjectdelete(OnObjectDeleteEventArgs* args)
	{
		if (args->object &&
			args->object->name().find("Katarina_") != std::string::npos &&
			args->object->name().find("W_Indicator_Ally") != std::string::npos)
		{
			for (int i = 0; i < daggerholder.size(); i++) {

				if (daggerholder[i]->networkID() == args->object->networkID()) {
					daggerholder.erase(daggerholder.begin() + i);
				}

			}
		}
	}

	void load()
	{
		g_menu = new Menu();

		spellQ = std::make_unique<TargetSpell>(SpellSlot::Q);
		spellQ->setCastDelay(250);
		spellQ->setRange(625);
		spellQ->setCollisions({ Collisions::Windwall });

		spellW = std::make_unique<SelfSpellAoe>(SpellSlot::W);
		spellW->setEffectRange(400);

		spellE = std::make_unique<PositionSpell>(SpellSlot::E);
		spellE->setRange(725);
		spellE2 = std::make_unique<PositionSpell>(SpellSlot::E);
		spellE2->setRange(775);

		spellR = std::make_unique<SelfSpellAoe>(SpellSlot::R);
		spellR->setEffectRange(550);

		EventHandler<Events::OnDraw>::subscribe(onDraw);
		//EventHandler<Events::Present>::subscribe(onpresent);
		EventHandler<Events::OnOrbwalkerPreMove>::subscribe(magnet);
		EventHandler<Events::GameUpdate>::subscribe(onUpdate);
		EventHandler<Events::OnObjectCreate>::subscribe(onobjectcreate);
		EventHandler<Events::OnObjectDelete>::subscribe(onobjectdelete);
		//EventHandler<Events::OnGapcloser>::subscribe(onGapclose);
		//EventHandler<Events::OnInterruptibleSpell>::subscribe(onInterruptible);
	}

	void unload()
	{
		EventHandler<Events::OnDraw>::unsubscribe(onDraw);
		//EventHandler<Events::Present>::unsubscribe(onpresent);
		EventHandler<Events::OnOrbwalkerPreMove>::unsubscribe(magnet);
		EventHandler<Events::GameUpdate>::unsubscribe(onUpdate);
		EventHandler<Events::OnObjectCreate>::subscribe(onobjectcreate);
		EventHandler<Events::OnObjectDelete>::subscribe(onobjectdelete);
		//EventHandler<Events::OnGapcloser>::unsubscribe(onGapclose);
		//EventHandler<Events::OnInterruptibleSpell>::unsubscribe(onInterruptible);

		spellQ.reset();
		spellW.reset();
		spellE.reset();
		spellE2.reset();
		spellR.reset();

		g_mainMenu->removeMenu(g_menu->menu);
		delete g_menu;
	}
}