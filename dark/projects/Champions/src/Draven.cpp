#include "Draven.h"
#include <SDK/src/SDK.h>

namespace Draven
{
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Draven"), xorstr_("DarkAio Draven"));

		MenuTabPtr combogeneralTab = menu->createTab(xorstr_("combogeneral"), xorstr_("Combo"));
		MenuTabPtr harassgeneralTab = menu->createTab(xorstr_("harassgeneral"), xorstr_("Harass"));
		MenuTabPtr killstealgeneralTab = menu->createTab(xorstr_("killstealgeneral"), xorstr_("Killsteal"));
		MenuTabPtr miscgeneralTab = menu->createTab(xorstr_("miscgeneral"), xorstr_("Misc"));
		MenuTabPtr farmgeneralTab = menu->createTab(xorstr_("farmgeneral"), xorstr_("Farm"));
		MenuTabPtr drawgeneralTab = menu->createTab(xorstr_("drawgeneral"), xorstr_("Draw"));

		TabChildPtr hitchanceMenu = combogeneralTab->createTabChild(xorstr_("Hitchance Settings"), xorstr_("Hitchance Settings"), true);
		MenuElementPtr hitchanceEcombo = hitchanceMenu->addComboBox(xorstr_("E Hitchance Combo"), xorstr_("E Hitchance"), g_hitchanceList, HITCHANCE_HIGH);

		TabChildPtr comboMenu = combogeneralTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboWrace = comboMenu->addCheckBox(xorstr_("Use Wrace Combo"), xorstr_("Dont Use W If Already Have"), true);
		MenuElementPtr comobWmana = comboMenu->addSlider(xorstr_("combowmana"), xorstr_("Min W Save Mana For Q"), 20, 0, 101);
		MenuElementPtr comboE = comboMenu->addCheckBox(xorstr_("Use E Combo"), xorstr_("Use E"), false);
		MenuElementPtr comboEgap = comboMenu->addCheckBox(xorstr_("Use Egap Combo"), xorstr_("Use E AntiGap"), true);
		MenuElementPtr comboR = comboMenu->addCheckBox(xorstr_("Use R Combo"), xorstr_("Use R"), true);
		MenuElementPtr comboRCount = comboMenu->addSlider(xorstr_("comborcount"), xorstr_("R Hit Count"), 3, 0, 5);

		TabChildPtr harassMenu = harassgeneralTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);;
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), true);
		MenuElementPtr harassE = harassMenu->addCheckBox(xorstr_("Use E Harass"), xorstr_("Use E"), false);

		TabChildPtr KillstealMenu = killstealgeneralTab->createTabChild(xorstr_("Killsteal Settings"), xorstr_("Killsteal Settings"), true);
		MenuElementPtr KillstealE = KillstealMenu->addCheckBox(xorstr_("Use E Killsteal"), xorstr_("Use E"), true);
		MenuElementPtr KillstealR = KillstealMenu->addCheckBox(xorstr_("Use R Killsteal"), xorstr_("Use R"), true);
		MenuElementPtr killsteal_r_maxdist = KillstealMenu->addSlider(xorstr_("krmax"), xorstr_("max R dist (you can see in draw)"), 3000, 0, 25000);
		MenuElementPtr killsteal_r_mindist = KillstealMenu->addSlider(xorstr_("krmin"), xorstr_("min R dist (you can see in draw)"), 1000, 0, 5000);

		TabChildPtr MiscMenu = miscgeneralTab->createTabChild(xorstr_("Misc Settings"), xorstr_("Misc Settings"), true);
		MenuElementPtr axecatch = MiscMenu->addCheckBox(xorstr_("Useaxecatch"), xorstr_("Use Axe Magnet"), true);
		MenuElementPtr axecatchrange = MiscMenu->addSlider(xorstr_("axecatchrange"), xorstr_("Min Axe Catch Range"), 1000, 0, 2000);

		TabChildPtr FarmMenu = farmgeneralTab->createTabChild(xorstr_("Farm Settings"), xorstr_("Farm Settings"), true);
		MenuElementPtr clearQ = FarmMenu->addCheckBox(xorstr_("Use Q"), xorstr_("Use Q"), true);
		MenuElementPtr clearW = FarmMenu->addCheckBox(xorstr_("Usew"), xorstr_("Use W"), false);
		MenuElementPtr clearMana = FarmMenu->addSlider(xorstr_("clearmana"), xorstr_("Min Mana Save"), 40, 0, 100);
		MenuElementPtr clearkey = FarmMenu->addKeybind(xorstr_("clearkey"), xorstr_("Farm Key"), Key::G);

		TabChildPtr drawingsMenu = drawgeneralTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 165, 0, 200, false);
		ColorCheckbox drawcatchrange = addColorCheckbox(drawingsMenu, xorstr_("Draw Catch Range"), 255, 0, 0, 200, true);
		ColorCheckbox drawRKillable = addColorCheckbox(drawingsMenu, xorstr_("R Killable"), 255, 0, 0, 200, true);
		ColorCheckbox drawRmaxmin = addColorCheckbox(drawingsMenu, xorstr_("Draw R min/max dist (min blue) (max red)"), 255, 165, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<SelfSpellAoe> spellQ;
	std::unique_ptr<SelfSpellAoe> spellW;
	std::unique_ptr<PositionSpell> spellE;
	std::unique_ptr<PositionSpell> spellR;
	int ElvlDmg[] = { 75 , 110 , 145 , 180 , 215 };
	double RlvlDmg[] = { 175 , 275  , 375 };

	bool farmkeyactive = false;

	struct objectholder {
		IGameObject* object;
	};
	std::vector<IGameObject*> daggerholder;


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
			dmg = dmg + (g_localPlayer->stats()->bonusAD() * 0.5);
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
			if (g_localPlayer->spell(SpellSlot::R)->level() >= 1)
			{
				dmg = dmg + RlvlDmg[g_localPlayer->spell(SpellSlot::R)->level() - 1];
				if (g_localPlayer->spell(SpellSlot::R)->level() == 1)
				{
					dmg = dmg + (g_localPlayer->stats()->totalAD() * 1.1);
				}
				if (g_localPlayer->spell(SpellSlot::R)->level() == 2)
				{
					dmg = dmg + (g_localPlayer->stats()->totalAD() * 1.3);
				}
				if (g_localPlayer->spell(SpellSlot::R)->level() == 3)
				{
					dmg = dmg + (g_localPlayer->stats()->totalAD() * 1.5);
				}
			}
			damage = g_moduleManager->damageLib()->calculateSpellDamage(g_localPlayer, target, 0, dmg, 0) * 2;
		}
		return damage;
	}

	int getaxecount()
	{
		int count = 0;
		auto buff = g_localPlayer->buff(BUFF_HASH("DravenSpinningAttack"));
		if (buff && buff->isValid())
			count = count + buff->count();
		if (!daggerholder.empty()) {
			for (IGameObject* dagger : daggerholder) {
				count = count + 1;
			}
		}
		return count;
	}

	bool havewbuff()
	{
		auto flag = false;
		auto buff = g_localPlayer->buff(BUFF_HASH("DravenFury"));
		if (buff && buff->isValid())
			flag = true;
		return flag;
	}

	bool havewattackbuff()
	{
		auto flag = false;
		auto buff = g_localPlayer->buff(BUFF_HASH("dravenfurybuff"));
		if (buff && buff->isValid())
			flag = true;
		return flag;
	}

	IGameObject* getclosesaxe()
	{
		IGameObject* closes = nullptr;
		auto dist = 5000;
		if (!daggerholder.empty()) {
			for (IGameObject* dagger : daggerholder) {
				if (dagger->position().distance(g_localPlayer->position()) < dist)
				{
					dist = dagger->position().distance(g_localPlayer->position());
					closes = dagger;
				}
			}
		}
		return closes;
	}

	int getcombodamage(IGameObject* target)
	{
		auto dmg = 0;
		if (target)
		{
			dmg = dmg + g_moduleManager->damageLib()->calculateAutoAttackDamage(g_localPlayer, target) * 3;
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
		if (minion && minion->isVisionPlant() || minion->isJumpPlant() || minion->isHealthPlant() || minion->isWard())
		{
			return true;
		}
		return false;

	}

	auto lastdravenrtime = 0;
	bool rcheck()
	{
		auto spell = g_localPlayer->activeSpell();
		if (spell)
		{
			//DLOG(spell->info()->name());
			if (spell->info()->name() == "DravenRCast")
			{
				lastdravenrtime = g_game->gameTime();
				return false;
			}
		}
		if (lastdravenrtime + 5 < g_game->gameTime())
		{
			return false;
		}
		return true;
	}


	void combo()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 5000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (spellQ->isReady() && g_menu->comboQ->getBool() && target->position().distance(g_localPlayer->position()) < g_localPlayer->stats()->attackRange() + 65)
			{
				if (getaxecount() < 4)
				{
					spellQ->cast();
				}
			}
			if (spellW->isReady() && g_menu->comboW->getBool() && target->position().distance(g_localPlayer->position()) < g_localPlayer->stats()->attackRange() + 65)
			{
				if (g_menu->comboWrace->getBool() && havewbuff())
				{
				}
				else if (!g_menu->comboWrace->getBool() || !havewbuff())
				{
					if (g_localPlayer->resource() > (g_localPlayer->maxResource() / 100) * g_menu->comobWmana->getInt())
					{
						spellW->cast();
					}
				}
			}
			if (spellE->isReady() && g_menu->comboE->getBool())
			{
				spellE->castPrediction(target, fromString(g_menu->hitchanceEcombo->getString()));
			}
			if (spellR->isReady() && g_menu->comboR->getBool() && !rcheck() && countenemyinrange(target->position(), 300) >= g_menu->comboRCount->getInt())
			{
				spellR->castPrediction(target, Hitchance::Medium);
			}
		}
	}
	void harass()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 3000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (spellQ->isReady() && g_menu->harassQ->getBool() && target->position().distance(g_localPlayer->position()) < g_localPlayer->stats()->attackRange() + 65)
			{
				if (getaxecount() < 4)
				{
					spellQ->cast();
				}
			}
			if (spellW->isReady() && g_menu->harassW->getBool() && target->position().distance(g_localPlayer->position()) < g_localPlayer->stats()->attackRange() + 65)
			{
				if (g_menu->comboWrace->getBool() && havewbuff())
				{
				}
				else if (!g_menu->comboWrace->getBool() || !havewbuff())
				{
					if (g_localPlayer->resource() > (g_localPlayer->maxResource() / 100) * g_menu->comobWmana->getInt())
					{
						spellW->cast();
					}
				}
			}
			if (spellE->isReady() && g_menu->harassE->getBool())
			{
				spellE->castPrediction(target, fromString(g_menu->hitchanceEcombo->getString()));
			}
		}
	}

	void active()
	{
		auto target2 = g_objectManager->players().alive().enemies().targetable().visible().inRange(g_localPlayer, 30000);
		auto selectedEnemies = g_moduleManager->targetSelector()->getTargetsSorted(target2, false, false);
		for (auto target : selectedEnemies)
		{
			if (g_menu->KillstealR->getBool() && spellR->isReady())
			{
				auto maxdist = g_menu->killsteal_r_maxdist->getInt();
				auto mindist = g_menu->killsteal_r_mindist->getInt();
				if (target->position().distance(g_localPlayer->position()) < maxdist && target->position().distance(g_localPlayer->position()) > mindist && GetRDamage(target) > target->health() && !rcheck())
				{
					spellR->castPrediction(target, Hitchance::Instant);
				}
			}
			if (spellE->isReady() && g_menu->KillstealE->getBool() && GetEDamage(target) > target->health())
			{
				spellE->castPrediction(target, Hitchance::Medium);
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
		if ((g_localPlayer->maxResource() / 100) * g_menu->clearMana->getInt() < g_localPlayer->resource() && farmkeyactive)
		{
			auto target2 = g_objectManager->minions().alive().enemies().targetable().visible().inRange(g_localPlayer->position(), 1000);
			for (auto minion : target2)
			{
				if (!isplant(minion))
				{
					if (spellQ->isReady() && g_menu->clearQ->getBool() && minion->position().distance(g_localPlayer->position()) < g_localPlayer->stats()->attackRange() + 65)
					{
						if (getaxecount() < 2)
						{
							spellQ->cast();
						}
					}
					if (spellW->isReady() && g_menu->clearW->getBool() && minion->position().distance(g_localPlayer->position()) < g_localPlayer->stats()->attackRange() + 65 && !havewattackbuff())
					{
						spellW->cast();
					}
				}
			}
		}

	}

	void onDraw(OnDrawEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			if (g_menu->drawERange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::E)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), spellE->range() - 75, 2, g_menu->drawERange.color->getColor());
			}
			if (g_menu->drawRmaxmin.checkbox->getBool() && g_localPlayer->spell(SpellSlot::R)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_menu->killsteal_r_maxdist->getInt(), 1, 0xff0000ff);
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_menu->killsteal_r_mindist->getInt(), 1, 0xffff0000);
			}
			if (g_menu->drawcatchrange.checkbox->getBool())
			{
				g_drawings->drawWorldCircle(g_hud->mousePosition(), g_menu->axecatchrange->getInt(), 2, g_menu->drawcatchrange.color->getColor());
			}
			auto newpos = g_localPlayer->position().toScreen();
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
			g_drawings->drawText(Vector2(newpos.x - 30, newpos.y + 50), "DarkAio", 25, 0xff000000, false, false);
			if (!daggerholder.empty()) {
				for (IGameObject* dagger : daggerholder) {
					if (dagger->position().distance(g_localPlayer->position()) > 150)
					{
						g_drawings->drawWorldCircle(dagger->position(), 150, 2, 0xff0000ff);
					}
					if (dagger->position().distance(g_localPlayer->position()) < 150)
					{
						g_drawings->drawWorldCircle(dagger->position(), 150, 2, 0xff00ff00);
					}
				}
			}
		}
	}


	void antigap1()
	{
		if (g_menu->comboEgap->getBool() && spellE->isReady())
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
							spellE->cast(endPos);
						}
					}
				}
			}

		}
	}

	double farmlastclicktime = 0;
	void onkeyupdate()
	{
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

	void magnet(OnOrbwalkerPreMoveEventArgs* args)
	{
		if (g_menu->axecatch->getBool() && args)
		{
			if (g_moduleManager->orbwalker()->isComboMode() || g_moduleManager->orbwalker()->isHarassMode() || g_moduleManager->orbwalker()->isLaneClearMode())
			{
				auto catchaxe = getclosesaxe();
				if (catchaxe)
				{
					if (catchaxe->position().distance(g_hud->mousePosition()) < g_menu->axecatchrange->getInt())
					{
						if (catchaxe->position().distance(g_localPlayer->position()) > 130 - g_localPlayer->boundingRadius())
						{
							args->position = catchaxe->position();
						}
					}
				}
			}
		}
	}

	void onobjectcreate(OnObjectCreateEventArgs* args)
	{
		//Katarina_Base_W_Indicator_Ally
		if (args->object &&
			args->object->name().find("Draven_") != std::string::npos &&
			args->object->name().find("_Q_reticle_self") != std::string::npos)
		{
			daggerholder.push_back(args->object);
		}
	}
	void onobjectdelete(OnObjectDeleteEventArgs* args)
	{
		if (args->object &&
			args->object->name().find("Draven_") != std::string::npos &&
			args->object->name().find("_Q_reticle_self") != std::string::npos)
		{
			for (int i = 0; i < daggerholder.size(); i++) {

				if (daggerholder[i]->networkID() == args->object->networkID()) {
					daggerholder.erase(daggerholder.begin() + i);
				}

			}
		}
	}


	void onUpdate(GameUpdateEventArgs* args)
	{
		onkeyupdate();
		if (g_localPlayer->isAlive())
		{
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

	void load()
	{
		g_menu = new Menu();

		spellQ = std::make_unique<SelfSpellAoe>(SpellSlot::Q);
		spellQ->setEffectRange(600);

		spellW = std::make_unique<SelfSpellAoe>(SpellSlot::W);
		spellW->setEffectRange(400);

		spellE = std::make_unique<PositionSpell>(SpellSlot::E);
		spellE->setCastDelay(250);
		spellE->setRange(1100);
		spellE->setBoundingRadiusCollision(false);
		spellE->setCollisions({ Collisions::Windwall });
		spellE->setSpeed(1400);
		spellE->setRadius(260);
		spellE->setSkillshotType(SkillshotType::Line);

		spellR = std::make_unique<PositionSpell>(SpellSlot::R);
		spellR->setCastDelay(600);
		spellR->setRange(99999);
		spellR->setCollisions({ Collisions::Windwall });
		spellR->setBoundingRadiusCollision(false);
		spellR->setSpeed(2000);
		spellR->setRadius(320);
		spellR->setSkillshotType(SkillshotType::Line);

		//EventHandler<Events::Present>::subscribe(onpresent);
		EventHandler<Events::OnOrbwalkerPreMove>::subscribe(magnet);
		EventHandler<Events::OnObjectCreate>::subscribe(onobjectcreate);
		EventHandler<Events::OnObjectDelete>::subscribe(onobjectdelete);
		EventHandler<Events::OnDraw>::subscribe(onDraw);
		EventHandler<Events::GameUpdate>::subscribe(onUpdate);
	}

	void unload()
	{
		//EventHandler<Events::Present>::unsubscribe(onpresent);
		EventHandler<Events::OnOrbwalkerPreMove>::unsubscribe(magnet);
		EventHandler<Events::OnObjectCreate>::subscribe(onobjectcreate);
		EventHandler<Events::OnObjectDelete>::subscribe(onobjectdelete);
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