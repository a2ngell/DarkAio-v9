#include "Sivir.h"
#include <SDK/src/SDK.h>

namespace Sivir
{
	struct Menu
	{
		MenuPtr menu = g_mainMenu->createMenu(xorstr_("Sivir"), xorstr_("V9 Sivir"));

		MenuTabPtr generalTab = menu->createTab(xorstr_("General"), xorstr_("General"));
		MenuTabPtr farming = menu->createTab(xorstr_("Farming"), xorstr_("Farming"));

		TabChildPtr comboMenu = generalTab->createTabChild(xorstr_("Combo"), xorstr_("Combo Settings"), true);
		MenuElementPtr comboQ = comboMenu->addCheckBox(xorstr_("Use Q Combo"), xorstr_("Use Q"), true);
		MenuElementPtr comboW = comboMenu->addCheckBox(xorstr_("Use W Combo"), xorstr_("Use W"), true);
		MenuElementPtr comboR = comboMenu->addCheckBox(xorstr_("Use R Combo"), xorstr_("Use R"), true);

		TabChildPtr harassMenu = generalTab->createTabChild(xorstr_("Harass Settings"), xorstr_("Harass Settings"), true);
		MenuElementPtr harassQ = harassMenu->addCheckBox(xorstr_("Use Q Harass"), xorstr_("Use Q"), true);
		MenuElementPtr harassW = harassMenu->addCheckBox(xorstr_("Use W Harass"), xorstr_("Use W"), true);

		TabChildPtr targetSpellMenuE = generalTab->createTabChild(xorstr_("TargetSpellE"), xorstr_("TargetSpell E"), true);
		MenuElementPtr useETargetspell = targetSpellMenuE->addCheckBox(xorstr_("Use"), xorstr_("Use"), true);
		std::unique_ptr<ITargetspellMenu> targetSpellMenu = g_moduleManager->targetspell()->createTargetspellMenu(targetSpellMenuE, { TargetspellType::Invulnerable });

		TabChildPtr hitchanceMenu = generalTab->createTabChild(xorstr_("Hitchance Settings"), xorstr_("Hitchance Settings"), true);
		MenuElementPtr hitchanceQcombo = hitchanceMenu->addComboBox(xorstr_("Q Hitchance Combo"), xorstr_("Combo: Q"), g_hitchanceList, HITCHANCE_HIGH);
		MenuElementPtr hitchanceQharass = hitchanceMenu->addComboBox(xorstr_("Q Hitchance Harass"), xorstr_("Harass: Q"), g_hitchanceList, HITCHANCE_HIGH);

		TabChildPtr drawingsMenu = generalTab->createTabChild(xorstr_("Drawing Settings"), xorstr_("Drawing Settings"), true);
		ColorCheckbox drawQRange = addColorCheckbox(drawingsMenu, xorstr_("Q"), 255, 165, 0, 200, true);
	};

	Menu* g_menu = nullptr;

	std::unique_ptr<PositionSpell> g_q;
	std::unique_ptr<SelfSpell> g_w;
	std::unique_ptr<SelfSpell> g_e;

	FarmSpell* g_qFarm = nullptr;
	FarmSpell* g_wFarm = nullptr;

	void onDraw(OnDrawEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{
			if (g_menu->drawQRange.checkbox->getBool() && g_localPlayer->spell(SpellSlot::Q)->isLearned())
			{
				g_drawings->drawWorldCircle(g_localPlayer->position(), g_q->range(), 2, g_menu->drawQRange.color->getColor());
			}
		}
	}

	void fetchData()
	{
		float delay = 250;
		float bonusAttackSpeed = g_localPlayer->stats()->percentAttackSpeedMod() * 100;
		auto val = delay / (1 + bonusAttackSpeed / 100);
		if (val < 100)
			val = 100;

		g_q->setCastDelay(val);
	}

	void qCast(MenuElementPtr use, MenuElementPtr hitchance)
	{
		if (use->getBool() && g_q->isReady())
		{
			auto target = g_q->target();
			if (target)
			{
				if (g_localPlayer->isInAutoAttackRange(target) && !g_moduleManager->orbwalker()->isWindingDown())
					return;

				g_q->castPrediction(target, fromString(hitchance->getString()));
			}
		}
	}

	void onUpdate(GameUpdateEventArgs* args)
	{
		if (g_localPlayer->isAlive())
		{

			fetchData();

			auto orb = g_moduleManager->orbwalker();
			if (orb->isComboMode())
			{
				if (!orb->isWindingUp())
				{
					qCast(g_menu->comboQ, g_menu->hitchanceQcombo);
				}
			}
			else if (orb->isHarassMode())
			{
				if (!orb->isWindingUp())
				{
					qCast(g_menu->harassQ, g_menu->hitchanceQharass);
				}
			}
		}
	}

	void wCast(MenuElementPtr use)
	{
		if (use->getBool() && g_w->isReady())
		{
			g_w->cast();
		}
	}

	void onOrbwalkerCancel(OnOrbwalkerCancelEventArgs* args)
	{
		auto orb = g_moduleManager->orbwalker();
		if (orb->isComboMode())
		{
			if (!orb->isWindingUp())
			{
				wCast(g_menu->comboW);
			}
		}
		else if (orb->isHarassMode())
		{
			if (!orb->isWindingUp())
			{
				wCast(g_menu->harassW);
			}
		}
	}

	void onTargetSpell(OnTargetspellEventArgs* args)
	{
		if (g_menu->useETargetspell->getBool() && g_menu->targetSpellMenu->isSpellEnabled(args->spellHash))
		{
			if (args->target->isMe())
			{
				if (g_e->isReady())
				{
					g_e->cast();
				}
			}
		}
	}

	void load()
	{
		g_menu = new Menu();

		g_q = std::make_unique<PositionSpell>(SpellSlot::Q);
		g_q->setRange(1250);
		g_q->setSpeed(1450);
		g_q->setRadius(90);
		g_q->setBoundingRadiusCollision(true);
		g_q->setCollisions({ Collisions::Windwall });
		g_q->setSkillshotType(SkillshotType::Line);

		g_w = std::make_unique<SelfSpell>(SpellSlot::W);
		g_w->setCastDelay(0);

		g_e = std::make_unique<SelfSpell>(SpellSlot::E);
		g_e->setCastDelay(0);

		{
			FarmSpellInput input;
			input.parentTab = g_menu->farming;
			input.spell = g_q.get();
			input.isAoe = true;

			input.lastHit = false;

			input.laneClearFastPush = true;

			input.jungleClearFastPush = true;

			g_qFarm = g_moduleManager->spellFarming()->addSpell(input);
		}
		{
			FarmSpellInput input;
			input.parentTab = g_menu->farming;
			input.spell = g_w.get();
			input.onCancelSpell = true;

			input.lastHitMenu = false;

			input.laneClear = false;
			input.laneClearFastPush = true;

			input.jungleClearFastPush = true;

			g_wFarm = g_moduleManager->spellFarming()->addSpell(input);
		}

		EventHandler<Events::OnDraw>::subscribe(onDraw);
		EventHandler<Events::GameUpdate>::subscribe(onUpdate);
		EventHandler<Events::OnOrbwalkerCancelEvent>::subscribe(onOrbwalkerCancel);
		EventHandler<Events::OnTargetspell>::subscribe(onTargetSpell);
	}

	void unload()
	{
		EventHandler<Events::OnDraw>::unsubscribe(onDraw);
		EventHandler<Events::GameUpdate>::unsubscribe(onUpdate);
		EventHandler<Events::OnOrbwalkerCancelEvent>::unsubscribe(onOrbwalkerCancel);
		EventHandler<Events::OnTargetspell>::unsubscribe(onTargetSpell);

		g_moduleManager->spellFarming()->removeSpell(g_qFarm);
		g_moduleManager->spellFarming()->removeSpell(g_wFarm);

		g_q.reset();
		g_w.reset();
		g_e.reset();

		g_mainMenu->removeMenu(g_menu->menu);

		delete g_menu;
	}
}