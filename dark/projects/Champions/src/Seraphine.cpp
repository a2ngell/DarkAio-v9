#include "Seraphine.h"
#include <SDK/src/SDK.h>

namespace Seraphine
{
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Seraphine"), xorstr_("V9 Seraphine"));

		MenuTabPtr generalTab = menu->createTab(xorstr_("General"), xorstr_("General"));
		MenuTabPtr farming = menu->createTab(xorstr_("Farming"), xorstr_("Farming"));

		TabChildPtr comboMenu = generalTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboE = comboMenu->addCheckBox(xorstr_("Use E Combo"), xorstr_("Use E"), true);
		MenuElementPtr useComboRAuto = comboMenu->addCheckBox(xorstr_("Use R Auto Combo"), xorstr_("Use R"), true);
		MenuElementPtr useComboRAutoSize = comboMenu->addSlider(xorstr_("Use R Auto Size Combo"), xorstr_("^- Min Enemies"), 3, 1, 5);
		MenuElementPtr useComboRKey = comboMenu->addKeybind(xorstr_("Use R Key Combo"), xorstr_("R Cast Key"), Key::T);

		TabChildPtr harassMenu = generalTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), true);
		MenuElementPtr harassE = harassMenu->addCheckBox(xorstr_("Use E Harass"), xorstr_("Use E"), true);

		TabChildPtr gapcloseMenuE = generalTab->createTabChild(xorstr_("Anti Gapcloser E"), xorstr_("Anti Gapcloser E"), true);
		MenuElementPtr useEAntiCloser = gapcloseMenuE->addCheckBox(xorstr_("Use"), xorstr_("Use"), true);
		std::unique_ptr<IGapcloseMenu> gapcloseMenuSpells = g_moduleManager->gapclose()->createGapcloseMenu(gapcloseMenuE);

		TabChildPtr interrupterMenuR = generalTab->createTabChild(xorstr_("Interrupter R"), xorstr_("Interrupter R"), true);
		MenuElementPtr useRInterrupter = interrupterMenuR->addCheckBox(xorstr_("Use"), xorstr_("Use"), true);
		std::unique_ptr<IInterruptibleSpellMenu> interrupterMenuSpells = g_moduleManager->interruptibleSpell()->createInterruptibleSpellMenu(interrupterMenuR);

		TabChildPtr hitchanceMenu = generalTab->createTabChild(xorstr_("Hitchance Settings"), xorstr_("Hitchance Settings"), true);
		MenuElementPtr hitchanceQcombo = hitchanceMenu->addComboBox(xorstr_("Q Hitchance Combo"), xorstr_("Combo: Q"), g_hitchanceList, HITCHANCE_MEDIUM);
		MenuElementPtr hitchanceEcombo = hitchanceMenu->addComboBox(xorstr_("E Hitchance Combo"), xorstr_("Combo: E"), g_hitchanceList, HITCHANCE_HIGH);
		MenuElementPtr hitchanceRcombo = hitchanceMenu->addComboBox(xorstr_("R Hitchance Combo"), xorstr_("R Cast"), g_hitchanceList, HITCHANCE_HIGH);
		MenuElementPtr hitchanceQharass = hitchanceMenu->addComboBox(xorstr_("Q Hitchance Harass"), xorstr_("Harass: Q"), g_hitchanceList, HITCHANCE_MEDIUM);
		MenuElementPtr hitchanceEharass = hitchanceMenu->addComboBox(xorstr_("E Hitchance Harass"), xorstr_("Harass: E"), g_hitchanceList, HITCHANCE_HIGH);

		TabChildPtr drawingsMenu = generalTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 165, 0, 200, true);
		ColorCheckbox drawWRange = addColorCheckbox(drawingsMenu, xorstr_("W"), 255, 165, 0, 200, true);
		ColorCheckbox drawERange = addColorCheckbox(drawingsMenu, xorstr_("E"), 255, 165, 0, 200, true);
		ColorCheckbox drawRRange = addColorCheckbox(drawingsMenu, xorstr_("R"), 255, 165, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<PositionSpell> g_q;
	std::unique_ptr<SelfSpellAoe> g_w;
	std::unique_ptr<PositionSpell> g_e;
	std::unique_ptr<PositionSpell> g_r;

	FarmSpell* g_qFarm = nullptr;
	FarmSpell* g_eFarm = nullptr;

	void onDraw(OnDrawEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			if (g_menu->drawQRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::Q)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_q->range(), 2, g_menu->drawQRange.color->getColor());
			}
			if (g_menu->drawWRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::W)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_w->effectRange(), 2, g_menu->drawWRange.color->getColor());
			}
			if (g_menu->drawERange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::E)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_e->range(), 2, g_menu->drawERange.color->getColor());
			}
			if (g_menu->drawRRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::R)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_r->range(), 2, g_menu->drawRRange.color->getColor());
			}
		}
	}


	void qCast(MenuElementPtr use, MenuElementPtr hitchance)
	{
		if (use->getBool() && g_q->isReady())
		{
			auto target = g_q->target();
			if (target)
			{
				g_q->castPrediction(target, fromString(hitchance->getString()));
			}
		}
	}

	void eCast(MenuElementPtr use, MenuElementPtr hitchance)
	{
		if (use->getBool() && g_e->isReady())
		{
			auto target = g_e->target();
			if (target)
			{
				g_e->castPrediction(target, fromString(hitchance->getString()));
			}
		}
	}

	void rMulti(MenuElementPtr use)
	{
		if (use->getBool() && g_r->isReady())
		{
			auto enemies = g_objectManager->players().enemies().alive().visible().targetable().inRange(g_localPlayer, g_r->range());
			if (enemies.size() >= g_menu->useComboRAutoSize->getInt())
			{
				g_r->castMultiPrediction(g_menu->useComboRAutoSize->getInt());
			}
		}
	}

	void rSingle(MenuElementPtr hitchance)
	{
		if (g_r->isReady())
		{
			auto target = g_r->target();
			if (target)
			{
				g_r->castPrediction(target, fromString(hitchance->getString()));
			}
		}
	}

	void wCast(MenuElementPtr use)
	{
		if (use->getBool() && g_w->isReady())
		{
			auto allies = g_objectManager->players().alive().allies().targetable().visible().inRange(g_localPlayer, g_w->effectRange());
			for (auto& a : allies)
			{
				if (a->healthPercent() < 0.6f && g_moduleManager->healthPrediction()->hasIncomingDamage(a, 1000))
				{
					if (g_w->cast())
						return;
				}
			}
		}
	}

	void onUpdate(GameUpdateEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			if (g_menu->useComboRKey->isPressed())
			{
				rSingle(g_menu->hitchanceRcombo);
			}

			auto orb = g_moduleManager->orbwalker();
			if (orb->isComboMode())
			{
				rMulti(g_menu->useComboRAuto);
				eCast(g_menu->comboE, g_menu->hitchanceEcombo);
				qCast(g_menu->comboQ, g_menu->hitchanceQcombo);
				wCast(g_menu->comboW);
			}
			else if (orb->isHarassMode())
			{
				eCast(g_menu->harassE, g_menu->hitchanceEharass);
				qCast(g_menu->harassQ, g_menu->hitchanceQharass);
				wCast(g_menu->harassW);
			}
		}
	}

	void onGapclose(OnGapcloserEventArgs* args)
	{
		if (g_menu->useEAntiCloser->getBool() && args->toLocalPlayer && g_menu->gapcloseMenuSpells->isSpellEnabled(args->spellHash))
		{
			if (args->caster->hasBuff(BuffType::Slow) || g_localPlayer->hasItem(ItemID::RylaisCrystalScepter))
			{
				if (g_e->isReady())
				{
					g_e->castPrediction(args->caster);
				}
			}
		}
	}

	void onInterruptible(OnInterruptibleSpellEventArgs* args)
	{
		if (g_menu->useRInterrupter->getBool() && g_menu->interrupterMenuSpells->isSpellEnabled(args->caster->championID(), args->slot))
		{
			if (g_r->isReady())
			{
				g_r->castPrediction(args->caster);
			}
		}
	}

	void load()
	{
		g_menu = new Menu();

		g_moduleManager->permaShow()->addToggle(xorstr_("Seraphine: R Cast Key"), g_menu->useComboRKey);

		g_q = std::make_unique<PositionSpell>(SpellSlot::Q);
		g_q->setCastDelay(250);
		g_q->setRange(900);
		g_q->setSpeed(1200);
		g_q->setRadius(350);
		g_q->setBoundingRadiusCollision(false);
		g_q->setCollisions({ Collisions::Windwall });
		g_q->setSkillshotType(SkillshotType::Circle);

		g_w = std::make_unique<SelfSpellAoe>(SpellSlot::W);
		g_w->setCastDelay(250);
		g_w->setEffectRange(800);

		g_e = std::make_unique<PositionSpell>(SpellSlot::E);
		g_e->setCastDelay(250);
		g_e->setRange(1300);
		g_e->setSpeed(1200);
		g_e->setRadius(70);
		g_e->setBoundingRadiusCollision(false);
		g_e->setCollisions({ Collisions::Windwall });
		g_e->setSkillshotType(SkillshotType::Line);

		g_r = std::make_unique<PositionSpell>(SpellSlot::R);
		g_r->setCastDelay(500);
		g_r->setRange(1200);
		g_r->setSpeed(1600);
		g_r->setRadius(160);
		g_r->setBoundingRadiusCollision(false);
		g_r->setCollisions({ Collisions::Windwall });
		g_r->setSkillshotType(SkillshotType::Line);

		{
			FarmSpellInput input;
			input.parentTab = g_menu->farming;
			input.spell = g_q.get();
			input.isAoe = true;

			input.lastHitMenu = false;

			input.laneClear = false;
			input.laneClearMinHits = 3;
			input.laneClearFastPush = true;

			input.jungleClear = false;
			input.jungleClearFastPush = true;

			g_qFarm = g_moduleManager->spellFarming()->addSpell(input);
		}
		{
			FarmSpellInput input;
			input.parentTab = g_menu->farming;
			input.spell = g_e.get();
			input.isAoe = true;

			input.lastHitMenu = false;

			input.laneClear = false;
			input.laneClearMinHits = 3;
			input.laneClearFastPush = true;

			input.jungleClear = false;
			input.jungleClearFastPush = true;

			g_eFarm = g_moduleManager->spellFarming()->addSpell(input);
		}

		EventHandler<Events::OnDraw>::subscribe(onDraw);
		EventHandler<Events::GameUpdate>::subscribe(onUpdate);
		EventHandler<Events::OnGapcloser>::subscribe(onGapclose);
		EventHandler<Events::OnInterruptibleSpell>::subscribe(onInterruptible);
	}

	void unload()
	{
		EventHandler<Events::OnDraw>::unsubscribe(onDraw);
		EventHandler<Events::GameUpdate>::unsubscribe(onUpdate);
		EventHandler<Events::OnGapcloser>::unsubscribe(onGapclose);
		EventHandler<Events::OnInterruptibleSpell>::unsubscribe(onInterruptible);

		g_moduleManager->spellFarming()->removeSpell(g_qFarm);
		g_moduleManager->spellFarming()->removeSpell(g_eFarm);

		g_moduleManager->permaShow()->removeToggle(xorstr_("Seraphine: R Cast Key"));

		g_q.reset();
		g_w.reset();
		g_e.reset();
		g_r.reset();

		g_mainMenu->removeMenu(g_menu->menu);
		delete g_menu;
	}
}