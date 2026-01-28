#pragma once

#include <ArrayClasses.h>
#include <GameModeOptionsClass.h>
#include <GeneralDefinitions.h>
#include <IPX.h>
#include <MessageListClass.h>
#include <MPGameModeClass.h>
#include <WinSock.h>

#include <Helpers/CompileTime.h>

namespace yrpp {

enum NetCommandType : int32_t
{
	NET_QUERY_GAME = 0u,                  ///< Hey, what games are out there?
	NET_ANSWER_GAME = 1u,                 ///< Yo, Here's my game's name!
	NET_QUERY_PLAYER = 2u,                ///< Hey, what players are in this game?
	NET_ANSWER_PLAYER = 3u,               ///< Yo, I'm in that game!
	NET_CHAT_ANNOUNCE = 4u,               ///< I'm at the chat screen
	NET_CHAT_REQUEST = 5u,                ///< Respond with a CHAT_ANNOUNCE, please.
	NET_QUERY_JOIN = 6u,                  ///< Hey guys, can I play too?
	NET_CONFIRM_JOIN = 7u,                ///< Well, OK, if you really want to.
	NET_REJECT_JOIN = 8u,                 ///< No, you can't join; sorry, dude.
	NET_GAME_OPTIONS = 9u,                ///< Hey, dudes, here's some new game options
	NET_SIGN_OFF = 10u,                   ///< Bogus, dudes, my boss is coming; I'm outta here!
	NET_GO = 11u,                         ///< OK, jump into the game loop!
	NET_MESSAGE = 12u,                    ///< Here's a message
	NET_PING = 13u,                       ///< I'm pinging you to take a time measurement
	NET_LOADGAME = 14u,                   ///< start a game by loading a saved game
	NET_REQ_SCENARIO = 1000u,             ///< Reqest that host sends the scenario file to the other players.
	NET_FILE_INFO = 1001u,                ///< Info about the file that is going to be transferred
	NET_FILE_CHUNK = 1002u,               ///< A chunk of scenario
	NET_READY_TO_GO = 1003u,              ///< Sent in response to a 'GO' command
	NET_NO_SCENARIO = 1004u,              ///< Scenario isnt available on remote machine so we cant play
};

#pragma pack(push, 1)
struct GlobalPacketType
{
	NetCommandType Command;
	wchar_t Name[20];
	char field_2C[411];
};
#pragma pack(pop)
static_assert(sizeof(GlobalPacketType) == 0x1C7);

struct MPlayerScoreType
{
	char Name[40];
	int Scheme;
	int NonGameOvers;
	int Lost[4];
	int Kills[4];
	int Built[4];
	int Score[4];
};

struct SessionOptionsClass
{
	int MPGameMode;
	int ScenIndex;
	int GameSpeed;
	int Credits;
	int UnitCount;
	bool ShortGame;
	bool SuperWeaponsAllowed;
	bool BuildOffAlly;
	bool MCVRepacks;
	bool CratesAppear;
	Vector3D<int> SlotData[8];
};

#pragma pack(push, 1)
struct NodeNameType {
	static constexpr constant_ptr<DynamicVectorClass<NodeNameType*>,0xA8DA74> const Array{};

	wchar_t Name[20];
	sockaddr_in Address;
	char Serial[19];
	int Country;
	int InitialCountry;
	int Color;
	int InitialColor;
	int StartPoint;
	int InitialStartPoint;
	int Team;
	int InitialTeam;
	DWORD SpectatorFlag; // 0xFFFFFFFF if Spectator
	int HouseIndex;
	int Time;
	DWORD unknown_int_77;
	int Clan;
	DWORD unknown_int_7F;
	BYTE unknown_byte_83;
	BYTE unknown_byte_84;
};
#pragma pack(pop)
static_assert(sizeof(NodeNameType) == 0x85);

#pragma pack(push, 4)
class SessionClass
{
public:
	static constexpr reference<SessionClass, 0xA8B238u> const Instance{};

	static bool IsCampaign()
	{
		return Instance->GameMode == GameMode::Campaign;
	}

	static bool IsSkirmish()
	{
		return Instance->GameMode == GameMode::Skirmish;
	}

	static bool IsSingleplayer()
	{
		return Instance->GameMode == GameMode::Campaign
			|| Instance->GameMode == GameMode::Skirmish;
	}

	static bool IsMultiplayer()
	{
		return Instance->GameMode == GameMode::LAN
			|| Instance->GameMode == GameMode::Internet;
	}

	// non-virtual
	void ReadScenarioDescriptions()
		{ JMP_THIS(0x699980) }

	bool CreateConnections()
		{ JMP_THIS(0x697B70) }

	void Resume()
		{ JMP_THIS(0x69BAB0) }

	GameMode GameMode;
	MPGameModeClass* MPGameMode;
	DWORD unknown_08;
	DWORD unknown_0C;
	DWORD unknown_10;
	DWORD unknown_14;
	GameModeOptionsClass Config;
	DWORD UniqueID;
	char Handle[20];
	int PlayerColor;
	DWORD unknown_160;
	DWORD unknown_164;
	DWORD unknown_168;
	DWORD unknown_16C;
	DWORD unknown_170;
	int idxSide;
	int idxSide2;
	int Color;
	int Color2;
	int Side;
	int Side2;
	SessionOptionsClass Skirmish;
	SessionOptionsClass LAN;
	SessionOptionsClass WOL;
	BOOL MultiplayerObserver;
	DWORD Unknown_304;
	bool WOLLimitResolution;
	int LastNickSlot;
	int MPlayerMax;
	int MPlayerCount;
	int MaxAhead;
	int FrameSendRate;
	int DesiredFrameRate;
	int ProcessTimer;
	int ProcessTicks;
	int ProcessFrames;
	int MaxMaxAhead;
	int PrecalcMaxAhead;
	int PrecalcDesiredFrameRate;
	struct
	{
		char Name[64];
		int MaxRoundTrip;
		int Resends;
		int Lost;
		int PercentLost;
		int MaxAvgRoundTrip;
		int FrameSyncStalls;
		int CommandCoundStalls;
		IPXAddressClass Address;
	} MPStats[8];
	bool EnableMultiplayerDebug;
	bool DrawMPDebugStats;
	char field_67E;
	char field_67F;
	int LoadGame;
	int SaveGame;
	char field_688;
	bool SawCompletion;
	bool OutOfSync;
	char field_68B;
	int GameVersion;
	DynamicVectorClass<class MultiMission*> MultiMission;
	char ScenarioFilename[0x202]; // 0x6A8
	char ScenarioDigest[34];
	int ScenarioFileLength;
	char ScenarioIsOfficial;
	int ScenarioMaxPlayers;
	char PlayersToSendScenario[8];
	char ScenarioSentCount;
	IPXAddressClass HostAddress[3];
	__declspec(align(4)) char array_908[32];
	char array_928[256];
	MessageListClass Messages;
	IPXAddressClass MessageAddress;
	char SomeMask[8];
	char LANTaunts;
	char WOLTaunts;
	wchar_t LastMessage[113];
	int Bitfield;
	char LANScrollText;
	char WOLScrollText;
	char field_1FC2;
	char field_1FC3;
	MPlayerScoreType Score[8];
	int GamesPlayed;
	int NumScores;
	int Winner;
	int CurGame;
	CCFileClass RecordFile;
	char Record;
	char Play;
	char Attract;
	int IsBridge;
	IPXAddressClass BridgeNet;
	char NetStealth;
	char NetProtect;
	char NetOpen;
	wchar_t GameName[20];
	GlobalPacketType GPacket;
	char field_25C7;
	int GPacketLen;
	IPXAddressClass GAddress;
	int16_t GProductID;
	char MetaPacket[558];
	int MetaSize;
	DynamicVectorClass<NodeNameType*> Games;
	DynamicVectorClass<NodeNameType*> Players;
	DynamicVectorClass<NodeNameType*> StartSpots;
	int field_2854;
	NodeNameType **name_pointer;
	char field_285C[264];
	int LatencyFudge;
	uint8_t gap2968[4];
	int a_connection_pointer;
	uint8_t gap2970[20];
	uint16_t PacketRouterPort;
	char field_2986[1690];
	wchar_t name[21];
	char field_304A[138];
	int TrapPrintCRC;
	int CurrentlyInGame; // at least used for deciding dialog backgrounds
};
#pragma pack(pop)

static_assert(sizeof(SessionClass) == 0x30DC);

} // namespace yrpp
