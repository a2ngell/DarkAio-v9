#pragma once

#include "XorStr.h"

#include <vector>
#include <Windows.h>

enum class MinionType
{
	None,
	Melee,
	Caster,
	Siege,
	Super,
	Jungle,
};

enum class TurretType
{
	None,
	T1,
	T2,
	T3,
	Nexus,
};

enum class PluginType
{
	Modules,
	Champions,
	Misc
};

enum class ModuleType
{
	Evade,
	SpellFarming,
	Tracker,
	Collision,
	Prediction,
	InterruptibleSpell,
	DamageDrawings,
	Gapclose,
	Targetspell,
	TargetSelector,
	PermaShow,
	MinionHealthPrediction,
	HealthPrediction,
	DamageLib,
	Orbwalker,
	Max,
};

enum class Events : unsigned int
{
	GameUpdate,
	Present,
	ResizeBuffers,
	OnObjectCreate,
	OnObjectDelete,
	OnNewPath,
	OnDraw,
	OnProcessSpell,
	OnStopCast,
	OnGapcloser,
	OnCastDashSpell,
	OnSpellImpact,
	OnFinishCast,
	OnTargetspell,
	OnOrbwalkerPreAttack,
	OnInterruptibleSpell,
	OnOrbwalkerPostAttack,
	OnOrbwalkerPreMove,
	OnVisibilityChanged,
	OnRenderMouseOvers,
	OnOrbwalkerCancelEvent,
	OnPlayerMove,
	OnPlayerAttack,
	OnPlayerAttackMove,
	OnTriggerSpell,
	OnWndProc,
	OnIssueClick,
	OnGetSpellPositionMouse,
	OnScreenPointToTargetResolver
};

enum class EngineType : unsigned char
{
	DX9,
	DX11 = 3,
	Invalid
};

enum class ObjectType
{
	Unknown = 0,
	NeutralMinionCamp,
	Hero,
	Minion,
	Turret,
	Troy,
	Missile,
	DrawFX,
	Inhibitor,
	Barracks,
	SpawnPoint,
	GrassObject,
	HQ,
	InfoPoint,
	LevelPropGameObject,
	LevelPropSpawnerPoint,
	Shop,
	MaxType,
};

enum class ObjectTeam
{
	Unknown = 0,
	Blue = 100,
	Red = 200,
	Neutral = 300,
};

enum class ResourceType : unsigned char
{
	Mana,
	Energy,
	None,
	Shield,
	BattleFury,
	DragonFury,
	Rage,
	Heat,
	GnarFury,
	Ferocity,
	BloodWell,
	Wind,
	Health,
	Other,
};

enum class PathType
{
	Move,
	Dash,
	Blink
};

enum class CombatType
{
	Unknown,
	Melee,
	Ranged,
};

enum class BuffType
{
	Internal = 0,
	Aura = 1,
	CombatEnchancer = 2,
	CombatDehancer = 3,
	SpellShield = 4,
	Stun = 5,
	Invisibility = 6,
	Silence = 7,
	Taunt = 8,
	Berserk = 9,
	Polymorph = 10,
	Slow = 11,
	Snare = 12,
	Damage = 13,
	Heal = 14,
	Haste = 15,
	SpellImmunity = 16,
	PhysicalImmunity = 17,
	Invulnerability = 18,
	AttackSpeedSlow = 19,
	NearSight = 20,
	Fear = 22,
	Charm = 23,
	Poison = 24,
	Suppression = 25,
	Blind = 26,
	Counter = 27,
	Currency = 21,
	Shred = 28,
	Flee = 29,
	Knockup = 30,
	Knockback = 31,
	Disarm = 32,
	Grounded = 33,
	Drowsy = 34,
	Asleep = 35,
	Obscured = 36,
	ClickProofToEnemies = 37,
	Unkillable = 38
};


enum class SpellSlot : int
{
	Q = 0,
	W = 1,
	E = 2,
	R = 3,
	SummonerSpell1,
	SummonerSpell2,
	Inventory1,
	Inventory2,
	Inventory3,
	Inventory4,
	Inventory5,
	Inventory6,
	Ward,
	Recall,
	Max,
	SpecialAttack = 45,
	ApheliosE = 47,
	LucianAttack = 54,
	BasicAttack = 64,
	BasicAttack2 = 65,
	JinxFishBone = 70,
	Unknown,
};

enum class NeutralCampID : int
{
	BlueOrder = 1,
	WolvesOrder,
	RaptorsOrder,
	RedOrder,
	KrugsOrder,
	Dragon,
	BlueChaos,
	WolvesChaos,
	RaptorsChaos,
	RedChaos,
	KrugsChaos,
	Baron,
	GrompOrder,
	GrompChaos,
	CrabBottom,
	CrabTop,
	Herald,
	MaxCamps
};

enum class SpellState
{
	Ready = 0x0000,
	NotAvailable = 0x0004,
	Suppressed = 0x0008,
	NotLearned = 0x000C,
	Cooldown = 0x0020,
	NoMana = 0x0040,
	InvalidSpell = 0x0080,
	NotAlive = 0x0100,
};

enum class SpellType
{
	Base,
	Self,
	SelfAoe,
	Ranged,
	Dash,
	Position,
	DoublePosition,
	Target,
	Chargeable
};

enum class DashType
{
	Normal,
	Blink
};

enum class ItemID : int
{
	Unknown,

	// Starter
	Cull = 1083,
	DarkSeal = 1082,
	DoransBlade = 1055,
	DoransRing = 1056,
	DoransShield = 1054,
	RelicShield = 3858,
	SpectralSickle = 3862,
	SpellthiefsEdge = 3850,
	SteelShoulderguards = 3854,
	TearOfTheGoddess = 3070,

	// Potions and consumables
	CorruptingPotion = 2033,
	RefillablePotion = 2031,
	HealthPotion = 2003,
	ElixirOfIron = 2138,
	ElixirOfSorcery = 2139,
	ElixirOfWrathedit = 2140,

	// Distributed
	PerfectlyTimedStopwatch = 2423,
	EyeOfTheHerald = 3513,
	MinionDematerializer = 2403,
	TotalBiscuitOfEverlastingWill = 2010,
	YourCut = 3400,

	// Boots
	Boots = 1001,
	SlightlyMagicalBoots = 2422,
	BerserkersGreaves = 3006,
	BootsOfSwiftness = 3009,
	IonianBootsOfLucidity = 3158,
	MercurysTreads = 3111,
	MobilityBoots = 3117,
	PlatedSteelcaps = 3047,
	SorcerersShoes = 3020,

	// Basic
	AmplifyingTome = 1052,
	BFSword = 1038,
	BlastingWand = 1026,
	Stopwatch = 2420,
	BrokenStopwatch = 2421,
	CloakOfAgility = 1018,
	ClothArmor = 1029,
	Dagger = 1042,
	FaerieCharm = 1004,
	LongSword = 1036,
	NeedlesslyLargeRod = 1058,
	NullMagicMantle = 1033,
	Pickaxe = 1037,
	RejuvenationBead = 1006,
	RubyCrystal = 1028,
	SapphireCrystal = 1027,
	Sheen = 3057,

	// Epic
	AegisOfTheLegion = 3105,
	AetherWisp = 3113,
	BamisCinder = 6660,
	BandleglassMirror = 4642,
	BlightingJewel = 4630,
	BrambleVest = 3076,
	CatalystOfAeons = 3803,
	CaulfieldsWarhammer = 3133,
	ChainVest = 1031,
	CrystallineBracer = 3801,
	ExecutionersCalling = 3123,
	FiendishCodex = 3108,
	ForbiddenIdol = 3114,
	Frostfang = 3851,
	GiantsBelt = 1011,
	GlacialBuckler = 3024,
	HarrowingCrescent = 3863,
	HearthboundAxe = 3051,
	Hexdrinker = 3155,
	HextechAlternator = 3145,
	IronspikeWhip = 6029,
	Kindlegem = 3067,
	KircheisShard = 2015,
	LastWhisper = 3035,
	LeechingLeer = 4635,
	LostChapter = 3802,
	NegatronCloak = 1057,
	Noonquiver = 6670,
	OblivionOrb = 3916,
	Phage = 3044,
	QuicksilverSash = 3140,
	Rageknife = 6677,
	RecurveBow = 1043,
	RunesteelSpaulders = 3855,
	SeekersArmguard = 3191,
	SerratedDirk = 3134,
	SpectresCowl = 3211,
	TargonsBuckler = 3859,
	Tiamat = 3077,
	VampiricScepter = 1053,
	VerdantBarrier = 4632,
	WardensMail = 3082,
	WatchfulWardstone = 4638,
	WingedMoonplate = 3066,
	Zeal = 3086,

	// Legendary
	AbyssalMask = 8020,
	AnathemasChains = 8001,
	ArchangelsStaff = 3003,
	ArdentCenser = 3504,
	AxiomArc = 6696,
	BansheesVeil = 3102,
	BlackCleaver = 3071,
	BlackMistScythe = 3864,
	BladeOfTheRuinedKing = 3153,
	Bloodthirster = 3124,
	BulwarkOfTheMountain = 3860,
	ChempunkChainsword = 6609,
	ChemtechPutrifier = 3011,
	CosmicDrive = 4629,
	DeadMansPlate = 3742,
	DeathsDance = 6333,
	DemonicEmbrace = 4637,
	EdgeOfNight = 3814,
	EssenceReaver = 3508,
	Fimbulwinter = 3121,
	ForceOfNature = 4401,
	FrozenHeart = 3110,
	GargoyleStoneplate = 3193,
	GuardianAngel = 3026,
	GuinsoosRageblade = 3124,
	HorizonFocus = 4628,
	Hullbreaker = 3181,
	InfinityEdge = 3031,
	KnightsVow = 3109,
	LichBane = 3100,
	LordDominiksRegards = 3036,
	Manamune = 3004,
	MawOfMalmortius = 3156,
	MejaisSoulstealer = 3041,
	MercurialScimitar = 3139,
	MikaelsBlessing = 3222,
	Morellonomicon = 3165,
	MortalReminder = 3033,
	Muramana = 3042,
	NashorsTooth = 3115,
	NavoriQuickblades = 6675,
	PauldronsOfWhiterock = 3857,
	PhantomDancer = 3046,
	RabadonsDeathcap = 3089,
	RanduinsOmen = 3143,
	RapidFirecannon = 3094,
	RavenousHydra = 3074,
	Redemption = 3107,
	RunaansHurricane = 3085,
	RylaisCrystalScepter = 3116,
	SeraphsEmbrace = 3040,
	SerpentsFang = 6695,
	SeryldasGrudge = 6694,
	Shadowflame = 4645,
	ShardOfTrueIce = 3853,
	SilvermereDawn = 6035,
	SpearOfShojin = 3161,
	SpiritVisage = 3065,
	StaffOfFlowingWater = 6616,
	StatikkShiv = 3087,
	SteraksGage = 3053,
	Stormrazor = 3095,
	SunfireAegis = 3068,
	TheCollector = 6676,
	Thornmail = 3075,
	TitanicHydra = 3748,
	TurboChemtank = 6664,
	UmbralGlaive = 3179,
	VigilantWardstone = 4643,
	VoidStaff = 3135,
	WarmogsArmor = 3083,
	WintersApproach = 3119,
	WitsEnd = 3091,
	YoumuusGhostblade = 3142,
	ZekesConvergence = 3050,
	ZhonyasHourglass = 3157,

	// Mystic
	CrownOfTheShatteredQueen = 4644,
	DivineSunderer = 6632,
	DuskbladeOfDraktharr = 6691,
	Eclipse = 6692,
	Evenshroud = 3001,
	Everfrost = 6656,
	Galeforce = 6671,
	Goredrinker = 6630,
	Heartsteel = 3084,
	HextechRocketbelt = 3152,
	IcebornGauntlet = 6662,
	ImmortalShieldbow = 6673,
	ImperialMandate = 4005,
	JakShoTheProtean = 6665,
	KrakenSlayer = 6672,
	LiandrysAnguish = 6653,
	LocketOfTheIronSolari = 3190,
	LudensTempest = 6655,
	MoonstoneRenewer = 6617,
	NightHarvester = 4636,
	ProwlersClaw = 6693,
	RadiantVirtue = 6667,
	Riftmaker = 4633,
	RodOfAges = 6657,
	ShurelyasBattlesong = 2065,
	Stridebreaker = 6631,
	TrinityForce = 3078,

	// Ornn items
	Bloodward = 7008,
	Caesura = 7024,
	CeaselessHunger = 7015,
	Deicide = 7017,
	DraktharrsShadowcarver = 7002,
	Dreamshatter = 7016,
	Equinox = 7023,
	EternalWinter = 7014,
	EyeOfLuden = 7013,
	FrozenFist = 7005,
	IcathiasCurse = 7009,
	InfiniteConvergence = 7028,
	InfinityForce = 7018,
	Leviathan = 7025,
	LiandrysLament = 7012,
	PrimordialDawn = 7027,
	ReliquaryOfTheGoldenDawn = 7019,
	SandshrikesClaw = 7000,
	SeatOfCommand = 7022,
	ShurelyasRequiem = 7020,
	Starcaster = 7021,
	Syzygy = 7001,
	TheUnspokenParasite = 7026,
	Typhoon = 7006,
	UpgradedAeropack = 7011,
	Vespertide = 7010,
	WyrmfallenSacrifice = 7007,

	// Vision
	FarsightAlteration = 3363,
	OracleLense = 3364,
	StealthWard = 3340,
	ControlWard = 2055,

	// Smites
	GustwalkerHatchling = 1102,
	MosstomperSeedlin = 1103,
	ScorchclawPup = 1101,

	// Aram
	GuardiansBlade = 3177,
	GuardiansHammer = 3184,
	GuardiansHorn = 2051,
	GuardiansOrb = 3112,
	PoroSnax = 2052,
};

enum class ChampionID : int
{
	Aatrox = 266,
	Ahri = 103,
	Akali = 84,
	Alistar = 12,
	Amumu = 32,
	Anivia = 34,
	Annie = 1,
	Aphelios = 523,
	Ashe = 22,
	AurelionSol = 136,
	Azir = 268,
	Bard = 432,
	Blitzcrank = 53,
	Brand = 63,
	Braum = 201,
	Caitlyn = 51,
	Camille = 164,
	Cassiopeia = 69,
	Chogath = 31,
	Corki = 42,
	Darius = 122,
	Diana = 131,
	DrMundo = 36,
	Draven = 119,
	Ekko = 245,
	Elise = 60,
	Evelynn = 28,
	Ezreal = 81,
	FiddleSticks = 9,
	Fiora = 114,
	Fizz = 105,
	Galio = 3,
	Gangplank = 41,
	Garen = 86,
	Gnar = 150,
	Gragas = 79,
	Graves = 104,
	Hecarim = 120,
	Heimerdinger = 74,
	Hwei = 910,
	Illaoi = 420,
	Irelia = 39,
	Ivern = 427,
	Janna = 40,
	JarvanIV = 59,
	Jax = 24,
	Jayce = 126,
	Jhin = 202,
	Jinx = 222,
	Kaisa = 145,
	Kalista = 429,
	Karma = 43,
	Karthus = 30,
	Kassadin = 38,
	Katarina = 55,
	Kayle = 10,
	Kayn = 141,
	Kennen = 85,
	Khazix = 121,
	Kindred = 203,
	Kled = 240,
	KogMaw = 96,
	Leblanc = 7,
	LeeSin = 64,
	Leona = 89,
	Lillia = 876,
	Lissandra = 127,
	Lucian = 236,
	Lulu = 117,
	Lux = 99,
	Malphite = 54,
	Malzahar = 90,
	Maokai = 57,
	MasterYi = 11,
	MissFortune = 21,
	Mordekaiser = 82,
	Morgana = 25,
	Nami = 267,
	Nasus = 75,
	Nautilus = 111,
	Neeko = 518,
	Nidalee = 76,
	Nocturne = 56,
	Nunu = 20,
	Olaf = 2,
	Orianna = 61,
	Ornn = 516,
	Pantheon = 80,
	Poppy = 78,
	Pyke = 555,
	Qiyana = 246,
	Quinn = 133,
	Rakan = 497,
	Rammus = 33,
	RekSai = 421,
	Rell = 526,
	Renekton = 58,
	Rengar = 107,
	Riven = 92,
	Rumble = 68,
	Ryze = 13,
	Samira = 360,
	Sejuani = 113,
	Senna = 235,
	Seraphine = 147,
	Sett = 875,
	Shaco = 35,
	Shen = 98,
	Shyvana = 102,
	Singed = 27,
	Sion = 14,
	Sivir = 15,
	Skarner = 72,
	Sona = 37,
	Soraka = 16,
	Swain = 50,
	Sylas = 517,
	Syndra = 134,
	TahmKench = 223,
	Taliyah = 163,
	Talon = 91,
	Taric = 44,
	Teemo = 17,
	Thresh = 412,
	Tristana = 18,
	Trundle = 48,
	Tryndamere = 23,
	TwistedFate = 4,
	Twitch = 29,
	Udyr = 77,
	Urgot = 6,
	Varus = 110,
	Vayne = 67,
	Veigar = 45,
	VelKoz = 161,
	Vi = 254,
	Viego = 234,
	Viktor = 112,
	Vladimir = 8,
	Volibear = 106,
	Warwick = 19,
	MonkeyKing = 62,
	Xayah = 498,
	Xerath = 101,
	XinZhao = 5,
	Yasuo = 157,
	Yone = 777,
	Yorick = 83,
	Yuumi = 350,
	Zac = 154,
	Zed = 238,
	Ziggs = 115,
	Zilean = 26,
	Zoe = 142,
	Zyra = 143,
	Gwen = 887,
	Akshan = 166,
	Vex = 711,
	Zeri = 221,
	Renata = 888,
	Belveth = 200,
	Nilah = 895,
	KSante = 897,
	Milio = 902,
	Naafiri = 950,
	Briar = 233,
	Unknown = 5000,
	TFTChampion,
	SG_Skarner,
	SG_VelKoz,
	SG_RekSai,
	SG_KogMaw,
	SG_KhaZix,
	SG_ChoGath,
	All,
};

enum class DangerLevel
{
	Low,
	Medium,
	High,
	VeryHigh,
};

enum class TargetspellType
{
	TargetBlink,
	Invulnerable,
	DamageReduction,
	Windwall,
};

enum class WardType
{
	Unknown,
	VisionWard,
	ControlWard,
	BlueTrinket,
	ZombieWard,
	FiddleWard,
	TeemoShroom,
	SightWard,
	Poro,
	MaokaiSappling,
	ShacoBox,
};

enum class CollisionFlags : int
{
	None = 0,
	Grass = 1,
	Wall = 2,
	Building = 64,
	Tower = 70,
	Prop = 128,
	GlobalVision = 256
};

enum class DamageType
{
	Physical,
	Magical,
	True,
	Mixed,
};

enum class ActionState
{
	CanAttack = 1 << 0,
	CanMove = 1 << 1,
	CanCast = 1 << 2,
	IsImmune = 1 << 13,
};

enum class Collisions
{
	Minions,
	Heros,
	Tower,
	Inhib,
	Wall,
	Windwall,
};

enum class Hitchance
{
	Impossible,
	Collision,
	Instant,
	Low,
	Medium,
	High,
	VeryHigh
};

enum class SkillshotType
{
	Unknown,
	Line,
	Circle,
	Cone,
	Ring,
	Polygon,
	LineCircle,
};

enum class GameState
{
	LoadingScreen = 0,
	Connecting = 1,
	Running = 2,
	Paused = 3,
	Finished = 4,
	Exiting = 5
};

enum class Keystone : int
{
	PressTheAttack = 8008,
	LethalTempo = 8005,
	FleetFootwork = 8021,
	Conqueror = 8010,

	Electrocute = 8112,
	Predator = 8124,
	DarkHarvest = 8128,
	HailOfBlades = 9923,

	SummonAery = 8214,
	ArcaneComet = 8229,
	PhaseRush = 8230,

	GraspOfTheUndying = 8437,
	Aftershock = 8439,
	Guardian = 8465,

	GlacialAugment = 8351,
	UnsealedSpellbook = 8360,
	FirstStrike = 8369,
};

enum class Key : int
{
	Unknown = 0x00,
	LeftMouse = 0x01,
	RightMouse = 0x02,
	MiddleMouse = 0x04,
	X1Mouse = 0x05,
	X2Mouse = 0x06,
	Backspace = 0x08,
	Tab = 0x09,
	Clear = 0x0C,
	Enter = 0x0D,
	Shift = 0x10,
	Control = 0x11,
	Alt = 0x12,
	Pause = 0x13,
	CapsLock = 0x14,
	Escape = 0x1B,
	Space = 0x20,
	PageUp = 0x21,
	PageDown = 0x22,
	End = 0x23,
	Home = 0x24,
	ArrowLeft = 0x25,
	ArrowUp = 0x26,
	ArrowRight = 0x27,
	ArrowDown = 0x28,
	Select = 0x29,
	Print = 0x2A,
	Execute = 0x2B,
	Insert = 0x2D,
	Delete = 0x2E,
	Zero = 0x30,
	One = 0x31,
	Two = 0x32,
	Three = 0x33,
	Four = 0x34,
	Five = 0x35,
	Six = 0x36,
	Seven = 0x37,
	Eight = 0x38,
	Nine = 0x39,
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,	
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	LeftWindows = 0x5B,
	RightWindows = 0x5C,
	Applications = 0x5D,
	NumpadZero = 0x60,
	NumpadOne = 0x61,
	NumpadTwo = 0x62,
	NumpadThree = 0x63,
	NumpadFour = 0x64,
	NumpadFive = 0x65,
	NumpadSix = 0x66,
	NumpadSeven = 0x67,
	NumpadEight = 0x68,
	NumpadNine = 0x69,
	Multiply = 0x6A,
	Add = 0x6B,
	Separator = 0x6C,
	Subtract = 0x6D,
	Decimal = 0x6E,
	Divide = 0x6F,
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
	NumLock = 0x90,
	LeftShift = 0xA0,
	RightShift = 0xA1,
	LeftControl = 0xA2,
	RightControl = 0xA3,
	LeftAlt = 0xA4,
	RightAlt = 0xA5,
};

inline bool isKeySupported(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return true;
	default:
		return false;
	}
}
inline Key toKey(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		return Key::LeftMouse;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		return Key::RightMouse;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		return Key::MiddleMouse;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		switch (GET_XBUTTON_WPARAM(wParam))
		{
		case XBUTTON1:
			return Key::X1Mouse;
		case XBUTTON2:
			return Key::X2Mouse;
		default:
			return Key::Unknown;
		}
	case WM_MOUSEMOVE:
		return Key::Unknown;
	case WM_MOUSEWHEEL:
		return Key::Unknown;
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return static_cast<Key>(wParam);
	default:
		return Key::Unknown;
	}
}
inline bool isKeyDown(Key key, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (wParam == static_cast<WPARAM>(key))
			return true;
		break;
	case WM_LBUTTONDOWN:
		return key == Key::LeftMouse;
		break;
	case WM_RBUTTONDOWN:
		return key == Key::RightMouse;
		break;
	case WM_MBUTTONDOWN:
		return key == Key::MiddleMouse;
		break;
	case WM_XBUTTONDOWN:
		UINT xButton = GET_XBUTTON_WPARAM(wParam);
		if ((xButton == XBUTTON1 && key == Key::X1Mouse) || (xButton == XBUTTON2 && key == Key::X2Mouse))
			return true;
		break;
	}
	return false;
}
inline bool isKeyUp(Key key, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if (wParam == static_cast<WPARAM>(key))
			return true;
		break;
	case WM_LBUTTONUP:
		return key == Key::LeftMouse;
		break;
	case WM_RBUTTONUP:
		return key == Key::RightMouse;
		break;
	case WM_MBUTTONUP:
		return key == Key::MiddleMouse;
		break;
	case WM_XBUTTONUP:
		UINT xButton = GET_XBUTTON_WPARAM(wParam);
		if ((xButton == XBUTTON1 && key == Key::X1Mouse) || (xButton == XBUTTON2 && key == Key::X2Mouse))
			return true;
		break;
	}
	return false;
}

inline std::string toString(SpellSlot slot)
{
	switch (slot)
	{
	case SpellSlot::Q:
		return xorstr_("Q");
	case SpellSlot::W:
		return xorstr_("W");
	case SpellSlot::E:
		return xorstr_("E");
	case SpellSlot::R:
		return xorstr_("R");
	case SpellSlot::SummonerSpell1:
		return xorstr_("Summoner 1");
	case SpellSlot::SummonerSpell2:
		return xorstr_("Summoner 2");
	case SpellSlot::Inventory1:
		return xorstr_("Item1");
	case SpellSlot::Inventory2:
		return xorstr_("Item2");
	case SpellSlot::Inventory3:
		return xorstr_("Item3");
	case SpellSlot::Inventory4:
		return xorstr_("Item4");
	case SpellSlot::Inventory5:
		return xorstr_("Item5");
	case SpellSlot::Inventory6:
		return xorstr_("Item6");
	case SpellSlot::Ward:
		return xorstr_("Ward");
	case SpellSlot::Recall:
		return xorstr_("Recall");
	case SpellSlot::Unknown:
		return xorstr_("Unknown");
	default:
		return xorstr_("Unknown");
	}
}

#define HITCHANCE_INSTANT xorstr_("Instant")
#define HITCHANCE_LOW xorstr_("Low")
#define HITCHANCE_MEDIUM xorstr_("Medium")
#define HITCHANCE_HIGH xorstr_("High")
#define HITCHANCE_VERYHIGH xorstr_("Very High")

inline std::vector<std::string> g_hitchanceList = { HITCHANCE_INSTANT, HITCHANCE_LOW, HITCHANCE_MEDIUM, HITCHANCE_HIGH, HITCHANCE_VERYHIGH };

inline Hitchance fromString(const std::string& str)
{
	if (str == HITCHANCE_INSTANT)
		return Hitchance::Instant;
	if (str == HITCHANCE_LOW)
		return Hitchance::Low;
	if (str == HITCHANCE_MEDIUM)
		return Hitchance::Medium;
	if (str == HITCHANCE_HIGH)
		return Hitchance::High;
	if (str == HITCHANCE_VERYHIGH)
		return Hitchance::VeryHigh;
	return Hitchance::Medium;
}

inline std::string toString(Hitchance hitchance)
{
	switch (hitchance)
	{
	case Hitchance::Impossible:
		return xorstr_("Impossible");
	case Hitchance::Collision:
		return xorstr_("Collision");
	case Hitchance::Instant:
		return HITCHANCE_INSTANT;
	case Hitchance::Low:
		return HITCHANCE_LOW;
	case Hitchance::Medium:
		return HITCHANCE_MEDIUM;
	case Hitchance::High:
		return HITCHANCE_HIGH;
	case Hitchance::VeryHigh:
		return HITCHANCE_VERYHIGH;
	default:
		return HITCHANCE_MEDIUM;
	}
}

inline DangerLevel dangerLevelFromString(const std::string& str)
{
	if (str == xorstr_("Low"))
		return DangerLevel::Low;
	if (str == xorstr_("Medium"))
		return DangerLevel::Medium;
	if (str == xorstr_("High"))
		return DangerLevel::High;
	if (str == xorstr_("Very High"))
		return DangerLevel::VeryHigh;
	return DangerLevel::Medium;
}

inline std::string toString(DangerLevel dangerLevel)
{
	switch (dangerLevel)
	{
	case DangerLevel::Low:
		return xorstr_("Low");
	case DangerLevel::Medium:
		return xorstr_("Medium");
	case DangerLevel::High:
		return xorstr_("High");
	case DangerLevel::VeryHigh:
		return xorstr_("Very High");
	default:
		return xorstr_("Medium");
	}
}

#define DANGERLEVEL_LOW xorstr_("Low")
#define DANGERLEVEL_MEDIUM xorstr_("Medium")
#define DANGERLEVEL_HIGH xorstr_("High")
#define DANGERLEVEL_VERYHIGH xorstr_("Very High")

inline std::vector<std::string> g_dangerLevelList = { DANGERLEVEL_LOW, DANGERLEVEL_MEDIUM, DANGERLEVEL_HIGH, DANGERLEVEL_VERYHIGH };

inline std::string toString(Key key)
{
	switch (key)
	{
	case Key::LeftMouse: return xorstr_("Left Mouse");
	case Key::RightMouse: return xorstr_("Right Mouse");
	case Key::MiddleMouse: return xorstr_("Middle Mouse");
	case Key::X1Mouse: return xorstr_("X1 Mouse");
	case Key::X2Mouse: return xorstr_("X2 Mouse");
	case Key::Backspace: return xorstr_("Backspace");
	case Key::Tab: return xorstr_("Tab");
	case Key::Clear: return xorstr_("Clear");
	case Key::Enter: return xorstr_("Enter");
	case Key::Shift: return xorstr_("Shift");
	case Key::Control: return xorstr_("Control");
	case Key::Alt: return xorstr_("Alt");
	case Key::Pause: return xorstr_("Pause");
	case Key::CapsLock: return xorstr_("Caps Lock");
	case Key::Escape: return xorstr_("Escape");
	case Key::Space: return xorstr_("Space");
	case Key::PageUp: return xorstr_("Page Up");
	case Key::PageDown: return xorstr_("Page Down");
	case Key::End: return xorstr_("End");
	case Key::Home: return xorstr_("Home");
	case Key::ArrowLeft: return xorstr_("Arrow Left");  
	case Key::ArrowUp: return xorstr_("Arrow Up");
	case Key::ArrowRight: return xorstr_("Arrow Right");
	case Key::ArrowDown: return xorstr_("Arrow Down");
	case Key::Select: return xorstr_("Select");
	case Key::Print: return xorstr_("Print");
	case Key::Execute: return xorstr_("Execute");
	case Key::Insert: return xorstr_("Insert");
	case Key::Delete: return xorstr_("Delete");
	case Key::Zero: return xorstr_("0");
	case Key::One: return xorstr_("1");
	case Key::Two: return xorstr_("2");
	case Key::Three: return xorstr_("3");
	case Key::Four: return xorstr_("4");
	case Key::Five: return xorstr_("5");
	case Key::Six: return xorstr_("6");
	case Key::Seven: return xorstr_("7");
	case Key::Eight: return xorstr_("8");
	case Key::Nine: return xorstr_("9");
	case Key::A: return xorstr_("A");
	case Key::B: return xorstr_("B");
	case Key::C: return xorstr_("C");
	case Key::D: return xorstr_("D");
	case Key::E: return xorstr_("E");
	case Key::F: return xorstr_("F");
	case Key::G: return xorstr_("G");
	case Key::H: return xorstr_("H");
	case Key::I: return xorstr_("I");
	case Key::J: return xorstr_("J");
	case Key::K: return xorstr_("K");
	case Key::L: return xorstr_("L");
	case Key::M: return xorstr_("M");
	case Key::N: return xorstr_("N");
	case Key::O: return xorstr_("O");
	case Key::P: return xorstr_("P");
	case Key::Q: return xorstr_("Q");
	case Key::R: return xorstr_("R");
	case Key::S: return xorstr_("S");
	case Key::T: return xorstr_("T");
	case Key::U: return xorstr_("U");
	case Key::V: return xorstr_("V");
	case Key::W: return xorstr_("W");
	case Key::X: return xorstr_("X");
	case Key::Y: return xorstr_("Y");
	case Key::Z: return xorstr_("Z");
	case Key::LeftWindows: return xorstr_("Left Windows");
	case Key::RightWindows: return xorstr_("Right Windows");
	case Key::Applications: return xorstr_("Applications");
	case Key::NumpadZero: return xorstr_("Numpad 0");
	case Key::NumpadOne: return xorstr_("Numpad 1");
	case Key::NumpadTwo: return xorstr_("Numpad 2");
	case Key::NumpadThree: return xorstr_("Numpad 3");
	case Key::NumpadFour: return xorstr_("Numpad 4");
	case Key::NumpadFive: return xorstr_("Numpad 5");
	case Key::NumpadSix: return xorstr_("Numpad 6");
	case Key::NumpadSeven: return xorstr_("Numpad 7");
	case Key::NumpadEight: return xorstr_("Numpad 8");
	case Key::NumpadNine: return xorstr_("Numpad 9");
	case Key::Multiply: return xorstr_("Multiply");
	case Key::Add: return xorstr_("Add");
	case Key::Separator: return xorstr_("Separator");
	case Key::Subtract: return xorstr_("Subtract");
	case Key::Decimal: return xorstr_("Decimal");
	case Key::Divide: return xorstr_("Divide");
	case Key::F1: return xorstr_("F1");
	case Key::F2: return xorstr_("F2");
	case Key::F3: return xorstr_("F3");
	case Key::F4: return xorstr_("F4");
	case Key::F5: return xorstr_("F5");
	case Key::F6: return xorstr_("F6");
	case Key::F7: return xorstr_("F7");
	case Key::F8: return xorstr_("F8");
	case Key::F9: return xorstr_("F9");
	case Key::F10: return xorstr_("F10");
	case Key::F11: return xorstr_("F11");
	case Key::F12: return xorstr_("F12");
	case Key::NumLock: return xorstr_("Num Lock");
	case Key::LeftShift: return xorstr_("Left Shift"); 
	case Key::RightShift: return xorstr_("Right Shift");
	case Key::LeftControl: return xorstr_("Left Control");
	case Key::RightControl: return xorstr_("Right Control");
	case Key::LeftAlt: return xorstr_("Left Alt");
	case Key::RightAlt: return xorstr_("Right Alt");
	default: return xorstr_("Unknown");
	}
}

inline std::string toString(ModuleType type)
{
	switch (type)
	{
	case ModuleType::Evade:
		return xorstr_("Evade");
		break;
	case ModuleType::SpellFarming:
		return xorstr_("Spell Farming");
		break;
	case ModuleType::Tracker:
		return xorstr_("Tracker");
		break;
	case ModuleType::Collision:
		return xorstr_("Collision");
		break;
	case ModuleType::Prediction:
		return xorstr_("Prediction");
		break;
	case ModuleType::InterruptibleSpell:
		return xorstr_("Interruptible Spell");
		break;
	case ModuleType::DamageDrawings:
		return xorstr_("Damage Drawings");
		break;
	case ModuleType::Gapclose:
		return xorstr_("Gapclose");
		break;
	case ModuleType::Targetspell:
		return xorstr_("Target Spell");
		break;
	case ModuleType::TargetSelector:
		return xorstr_("Target Selector");
		break;
	case ModuleType::PermaShow:
		return xorstr_("Perma Show");
		break;
	case ModuleType::MinionHealthPrediction:
		return xorstr_("Minion Health Prediction");
		break;
	case ModuleType::HealthPrediction:
		return xorstr_("Health Prediction");
		break;
	case ModuleType::DamageLib:
		return xorstr_("Damage Library");
		break;
	case ModuleType::Orbwalker:
		return xorstr_("Orbwalker");
		break;
	default:
		break;
	}
}

inline std::string toString(PluginType type)
{
	switch (type)
	{
	case PluginType::Modules:
		return xorstr_("Modules");
		break;
	case PluginType::Champions:
		return xorstr_("Champions");
		break;
	case PluginType::Misc:
		return xorstr_("Misc");
		break;
	default:

		break;
	}
}

inline std::string toString(ChampionID id)
{
	switch (id)
	{
	case ChampionID::Aatrox: return xorstr_("Aatrox");
	case ChampionID::Ahri: return xorstr_("Ahri");
	case ChampionID::Akali: return xorstr_("Akali");
	case ChampionID::Alistar: return xorstr_("Alistar");
	case ChampionID::Amumu: return xorstr_("Amumu");
	case ChampionID::Anivia: return xorstr_("Anivia");
	case ChampionID::Annie: return xorstr_("Annie");
	case ChampionID::Aphelios: return xorstr_("Aphelios");
	case ChampionID::Ashe: return xorstr_("Ashe");
	case ChampionID::AurelionSol: return xorstr_("Aurelion Sol");
	case ChampionID::Azir: return xorstr_("Azir");
	case ChampionID::Bard: return xorstr_("Bard");
	case ChampionID::Blitzcrank: return xorstr_("Blitzcrank");
	case ChampionID::Brand: return xorstr_("Brand");
	case ChampionID::Braum: return xorstr_("Braum");
	case ChampionID::Caitlyn: return xorstr_("Caitlyn");
	case ChampionID::Camille: return xorstr_("Camille");
	case ChampionID::Cassiopeia: return xorstr_("Cassiopeia");
	case ChampionID::Chogath: return xorstr_("Cho'Gath");
	case ChampionID::Corki: return xorstr_("Corki");
	case ChampionID::Darius: return xorstr_("Darius");
	case ChampionID::Diana: return xorstr_("Diana");
	case ChampionID::DrMundo: return xorstr_("Dr. Mundo");
	case ChampionID::Draven: return xorstr_("Draven");
	case ChampionID::Ekko: return xorstr_("Ekko");
	case ChampionID::Elise: return xorstr_("Elise");
	case ChampionID::Evelynn: return xorstr_("Evelynn");
	case ChampionID::Ezreal: return xorstr_("Ezreal");
	case ChampionID::FiddleSticks: return xorstr_("Fiddlesticks");
	case ChampionID::Fiora: return xorstr_("Fiora");
	case ChampionID::Fizz: return xorstr_("Fizz");
	case ChampionID::Galio: return xorstr_("Galio");
	case ChampionID::Gangplank: return xorstr_("Gangplank");
	case ChampionID::Garen: return xorstr_("Garen");
	case ChampionID::Gnar: return xorstr_("Gnar");
	case ChampionID::Gragas: return xorstr_("Gragas");
	case ChampionID::Graves: return xorstr_("Graves");
	case ChampionID::Hecarim: return xorstr_("Hecarim");
	case ChampionID::Heimerdinger: return xorstr_("Heimerdinger");
	case ChampionID::Illaoi: return xorstr_("Illaoi");
	case ChampionID::Irelia: return xorstr_("Irelia");
	case ChampionID::Ivern: return xorstr_("Ivern");
	case ChampionID::Janna: return xorstr_("Janna");
	case ChampionID::JarvanIV: return xorstr_("Jarvan IV");
	case ChampionID::Jax: return xorstr_("Jax");
	case ChampionID::Jayce: return xorstr_("Jayce");
	case ChampionID::Jhin: return xorstr_("Jhin");
	case ChampionID::Jinx: return xorstr_("Jinx");
	case ChampionID::Kaisa: return xorstr_("Kai'Sa");
	case ChampionID::Kalista: return xorstr_("Kalista");
	case ChampionID::Karma: return xorstr_("Karma");
	case ChampionID::Karthus: return xorstr_("Karthus");
	case ChampionID::Kassadin: return xorstr_("Kassadin");
	case ChampionID::Katarina: return xorstr_("Katarina");
	case ChampionID::Kayle: return xorstr_("Kayle");
	case ChampionID::Kayn: return xorstr_("Kayn");
	case ChampionID::Kennen: return xorstr_("Kennen");
	case ChampionID::Khazix: return xorstr_("Kha'Zix");
	case ChampionID::Kindred: return xorstr_("Kindred");
	case ChampionID::Kled: return xorstr_("Kled");
	case ChampionID::KogMaw: return xorstr_("Kog'Maw");
	case ChampionID::Leblanc: return xorstr_("LeBlanc");
	case ChampionID::LeeSin: return xorstr_("Lee Sin");
	case ChampionID::Leona: return xorstr_("Leona");
	case ChampionID::Lillia: return xorstr_("Lillia");
	case ChampionID::Lissandra: return xorstr_("Lissandra");
	case ChampionID::Lucian: return xorstr_("Lucian");
	case ChampionID::Lulu: return xorstr_("Lulu");
	case ChampionID::Lux: return xorstr_("Lux");
	case ChampionID::Malphite: return xorstr_("Malphite");
	case ChampionID::Malzahar: return xorstr_("Malzahar");
	case ChampionID::Maokai: return xorstr_("Maokai");
	case ChampionID::MasterYi: return xorstr_("Master Yi");
	case ChampionID::MissFortune: return xorstr_("Miss Fortune");
	case ChampionID::Mordekaiser: return xorstr_("Mordekaiser");
	case ChampionID::Morgana: return xorstr_("Morgana");
	case ChampionID::Nami: return xorstr_("Nami");
	case ChampionID::Nasus: return xorstr_("Nasus");
	case ChampionID::Nautilus: return xorstr_("Nautilus");
	case ChampionID::Neeko: return xorstr_("Neeko");
	case ChampionID::Nidalee: return xorstr_("Nidalee");
	case ChampionID::Nocturne: return xorstr_("Nocturne");
	case ChampionID::Nunu: return xorstr_("Nunu");
	case ChampionID::Olaf: return xorstr_("Olaf");
	case ChampionID::Orianna: return xorstr_("Orianna");
	case ChampionID::Ornn: return xorstr_("Ornn");
	case ChampionID::Pantheon: return xorstr_("Pantheon");
	case ChampionID::Poppy: return xorstr_("Poppy");
	case ChampionID::Pyke: return xorstr_("Pyke");
	case ChampionID::Qiyana: return xorstr_("Qiyana");
	case ChampionID::Quinn: return xorstr_("Quinn");
	case ChampionID::Rakan: return xorstr_("Rakan");
	case ChampionID::Rammus: return xorstr_("Rammus");
	case ChampionID::RekSai: return xorstr_("Rek'Sai");
	case ChampionID::Rell: return xorstr_("Rell");
	case ChampionID::Renekton: return xorstr_("Renekton");
	case ChampionID::Rengar: return xorstr_("Rengar");
	case ChampionID::Riven: return xorstr_("Riven");
	case ChampionID::Rumble: return xorstr_("Rumble");
	case ChampionID::Ryze: return xorstr_("Ryze");
	case ChampionID::Samira: return xorstr_("Samira");
	case ChampionID::Sejuani: return xorstr_("Sejuani");
	case ChampionID::Senna: return xorstr_("Senna");
	case ChampionID::Seraphine: return xorstr_("Seraphine");
	case ChampionID::Sett: return xorstr_("Sett");
	case ChampionID::Shaco: return xorstr_("Shaco");
	case ChampionID::Shen: return xorstr_("Shen");
	case ChampionID::Shyvana: return xorstr_("Shyvana");
	case ChampionID::Singed: return xorstr_("Singed");
	case ChampionID::Sion: return xorstr_("Sion");
	case ChampionID::Sivir: return xorstr_("Sivir");
	case ChampionID::Skarner: return xorstr_("Skarner");
	case ChampionID::Sona: return xorstr_("Sona");
	case ChampionID::Soraka: return xorstr_("Soraka");
	case ChampionID::Swain: return xorstr_("Swain");
	case ChampionID::Sylas: return xorstr_("Sylas");
	case ChampionID::Syndra: return xorstr_("Syndra");
	case ChampionID::TahmKench: return xorstr_("Tahm Kench");
	case ChampionID::Taliyah: return xorstr_("Taliyah");
	case ChampionID::Talon: return xorstr_("Talon");
	case ChampionID::Taric: return xorstr_("Taric");
	case ChampionID::Teemo: return xorstr_("Teemo");
	case ChampionID::Thresh: return xorstr_("Thresh");
	case ChampionID::Tristana: return xorstr_("Tristana");
	case ChampionID::Trundle: return xorstr_("Trundle");
	case ChampionID::Tryndamere: return xorstr_("Tryndamere");
	case ChampionID::TwistedFate: return xorstr_("Twisted Fate");
	case ChampionID::Twitch: return xorstr_("Twitch");
	case ChampionID::Udyr: return xorstr_("Udyr");
	case ChampionID::Urgot: return xorstr_("Urgot");
	case ChampionID::Varus: return xorstr_("Varus");
	case ChampionID::Vayne: return xorstr_("Vayne");
	case ChampionID::Veigar: return xorstr_("Veigar");
	case ChampionID::VelKoz: return xorstr_("Vel'Koz");
	case ChampionID::Vi: return xorstr_("Vi");
	case ChampionID::Viego: return xorstr_("Viego");
	case ChampionID::Viktor: return xorstr_("Viktor");
	case ChampionID::Vladimir: return xorstr_("Vladimir");
	case ChampionID::Volibear: return xorstr_("Volibear");
	case ChampionID::Warwick: return xorstr_("Warwick");
	case ChampionID::MonkeyKing: return xorstr_("Wukong");
	case ChampionID::Xayah: return xorstr_("Xayah");
	case ChampionID::Xerath: return xorstr_("Xerath");
	case ChampionID::XinZhao: return xorstr_("Xin Zhao");
	case ChampionID::Yasuo: return xorstr_("Yasuo");
	case ChampionID::Yone: return xorstr_("Yone");
	case ChampionID::Yorick: return xorstr_("Yorick");
	case ChampionID::Yuumi: return xorstr_("Yuumi");
	case ChampionID::Zac: return xorstr_("Zac");
	case ChampionID::Zed: return xorstr_("Zed");
	case ChampionID::Ziggs: return xorstr_("Ziggs");
	case ChampionID::Zilean: return xorstr_("Zilean");
	case ChampionID::Zoe: return xorstr_("Zoe");
	case ChampionID::Zyra: return xorstr_("Zyra");
	case ChampionID::Gwen: return xorstr_("Gwen");
	case ChampionID::Akshan: return xorstr_("Akshan");
	case ChampionID::Vex: return xorstr_("Vex");
	case ChampionID::Zeri: return xorstr_("Zeri");
	case ChampionID::Renata: return xorstr_("Renata");
	case ChampionID::Belveth: return xorstr_("Belveth");
	case ChampionID::Nilah: return xorstr_("Nilah");
	case ChampionID::KSante: return xorstr_("KSante");
	case ChampionID::Milio: return xorstr_("Milio");
	case ChampionID::Naafiri: return xorstr_("Naafiri");
	case ChampionID::Briar: return xorstr_("Briar");
	case ChampionID::Unknown: return xorstr_("Unknown");
	case ChampionID::TFTChampion: return xorstr_("TFT Champion");
	case ChampionID::SG_Skarner: return xorstr_("SG Skarner");
	case ChampionID::SG_VelKoz: return xorstr_("SG Vel'Koz");
	case ChampionID::SG_RekSai: return xorstr_("SG Rek'Sai");
	case ChampionID::SG_KogMaw: return xorstr_("SG Kog'Maw");
	case ChampionID::SG_KhaZix: return xorstr_("SG Kha'Zix");
	case ChampionID::SG_ChoGath: return xorstr_("SG Cho'Gath");
	case ChampionID::All: return xorstr_("All");
	default: return xorstr_("Unknown");
	}
}
