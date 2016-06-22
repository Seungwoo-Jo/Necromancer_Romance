#include <thread>

// ..\framework
#include "..\framework\CBitmap.h"
#include "..\framework\CTextureShader.h"
#include "..\framework\CInput.h"
#include "..\framework\common.h"
#include "..\framework\CFont.h"
#include "..\framework\CTime.h"
#include "..\framework\CSound.h"

// ..\managers
#include "..\managers\CObjectManager.h"
#include "..\managers\CSceneManager.h"
#include "..\managers\CBattleManager.h"
#include "..\managers\CCardManager.h"
#include "..\managers\CMonsterManager.h"
#include "..\managers\CScriptManager.h"
#include "..\managers\CNero.h"

// ..\objects
#include "..\objects\CObject_Background.h"
#include "..\objects\CObject_Chain.h"
#include "..\objects\CObject_Monstergauge.h"
#include "..\objects\CObject_Skillselect.h"
#include "..\objects\CObject_PartySlot.h"
#include "..\objects\CObject_MemberChange.h"
#include "..\objects\CObject_Target.h"
#include "..\objects\CObject_ExploreBar.h"
#include "..\objects\CObject_ExploreButton.h"
#include "..\objects\CObject_TalkWindow.h"
#include "..\objects\CCard.h"
#include "..\objects\CMonster.h"

// ..\scenes
#include "CScene_Field.h"

CScene_Field::CScene_Field()
{
	m_stage1Walk		= NULL;
	m_stage1BossWalk	= NULL;
	m_stage2Walk		= NULL;
	m_stage2BossWalk	= NULL;
	m_walkShader		= NULL;
	m_stage1Bg			= NULL;
	m_stage1BossBg		= NULL;
	m_stage2Bg			= NULL;
	m_stage2BossBg		= NULL;
	m_chain				= NULL;
	m_Text				= NULL;
	m_fadeTimer			= NULL;
	m_monsterGauge		= NULL;
	m_exploreBar		= NULL;
	m_exploreBtn		= NULL;
	m_talkWindow		= NULL;
	m_resultTimer		= NULL;
	m_battleTimer		= NULL;
	m_walkTimer			= NULL;
	m_sound_Move		= NULL;
	m_bgm_stage1		= NULL;
	m_bgm_stage1_boss	= NULL;
	m_bFadeIn			= true;
	m_bTalkOn			= false;
	m_bScriptReset		= true;
	m_bExplore			= true;
	m_bBattle			= false;
	m_bTresure			= false;
	m_bTrap				= false;
	m_bWalk				= false;
	m_bBossClear		= false;
	m_skillNum			= 0;
	m_scriptNum			= 0;
}

CScene_Field::CScene_Field(const CScene_Field& scene)
{
}

CScene_Field::~CScene_Field()
{
}

void CScene_Field::Initialize()
{
	m_stage1Walk = new CBitmap();
	m_stage1Walk->Initialize(L"res/background/field_stage1_back.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_stage2Walk = new CBitmap();
	m_stage2Walk->Initialize(L"res/background/field_stage2_back.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_stage1BossWalk = new CBitmap();
	m_stage1BossWalk->Initialize(L"res/background/field_stage1_boss_back.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_stage2BossWalk = new CBitmap();
	m_stage2BossWalk->Initialize(L"res/background/field_stage2_boss_back.png", 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	m_walkShader = new CTextureShader();
	m_walkShader->Initialize(NULL, L"shader/WalkShader.ps");

	m_stage1Bg = new CObject_Background();
	m_stage1Bg->Initalize(0, 0, 95, L"res/background/field_stage1_back.png");
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_stage1Bg));

	m_stage1BossBg = new CObject_Background();
	m_stage1BossBg->Initalize(0, 0, 100, L"res/background/field_stage1_boss_back.png");
	m_stage1BossBg->setOpacity(0.0f);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_stage1BossBg));

	m_stage2Bg = new CObject_Background();
	m_stage2Bg->Initalize(0, 0, 95, L"res/background/field_stage2_back.png");
	m_stage2Bg->setOpacity(0.0f);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_stage2Bg));

	m_stage2BossBg = new CObject_Background();
	m_stage2BossBg->Initalize(0, 0, 100, L"res/background/field_stage2_boss_back.png");
	m_stage2BossBg->setOpacity(0.0f);
	CObjectManager::getObjectManager()->AddObject(static_cast<CObject*>(m_stage2BossBg));

	m_chain = new CObject_Chain();
	m_chain->Initialize();

	CMonster* tempMonster = CMonsterManager::getMonsterManager()->getMonsterWithNum(0);
	CBattleManager::getBattleManager()->SetMonster(tempMonster);

	m_monsterGauge = new CObject_Monstergauge();
	m_monsterGauge->Initalize(tempMonster);

	m_partySlot = new CObject_PartySlot();
	m_partySlot->Initalize();

	m_skillButton = new CObject_Skillselect();
	m_skillButton->Initalize();

	m_memberChange = new CObject_MemberChange();
	m_memberChange->Initalize(SCENE::FIELD);
	m_memberChange->SetActivate(false);

	m_targetMark = new CObject_Target();
	m_targetMark->Initalize(0, 0, 10);

	m_exploreBar = new CObject_ExploreBar();
	m_exploreBar->Initalize();

	m_exploreBtn = new CObject_ExploreButton();
	m_exploreBtn->Initialize();

	m_talkWindow = new CObject_TalkWindow();
	m_talkWindow->Initalize();

	CScriptManager::getSkillManager()->AddScript(0, L"�� �ñ��� �� �ִµ�, �츱 ��Ƴ��� �� �༮�� �̷� ������ ��� ���°ž�?");
	CScriptManager::getSkillManager()->AddScript(1, L"�ʵ� �˴ٽ��� �� ���ڴ� ����� �Ҹ��� �־�.\n��� ������ ���ƴٴϸ� �絵���� ��ġ�ϰ� �ִٴ±�.");
	CScriptManager::getSkillManager()->AddScript(2, L"ȥ�ڼ� �絵�� ��ġ�Ѵٰ�?\n����, ���� �����ִ� ���̿� �̷� ���װ� ������ �� �ų�?\n�絵�� ���� ���� ���������ݾ�.\n�ΰ� ȥ�ڼ� �������.");
	CScriptManager::getSkillManager()->AddScript(3, L"��� �� ������ ������ ��¥����.\n�Ѿư��� ���� �絵�� �������� �𸣰ڴµ�.");
	/*
	CScriptManager::getSkillManager()->AddScript(10, L"�� �� ������ �� �� ���� �ų�? ��ġ�� �ʹ� �����ݾ�.");
	CScriptManager::getSkillManager()->AddScript(11, L"���� �� ���� ��ü�̸� �����ϴ� �ų�?\n�� ������ ����� �����븦 �����.");
	CScriptManager::getSkillManager()->AddScript(12, L"���� �ͼ� ���ϴ� ������ �� �𸣸�Ʈ���� ���̾�.\n���� ����Ÿ�� �߰����� ��,\n�� �������� �׳ฦ �츱 �� �ִ��� ������ �ؾ� ����.");
	CScriptManager::getSkillManager()->AddScript(13, L"����Ÿ�� �׻� ã�ƿ��� ����...\n�ű⿡ ����� ������ �ǻ���� �� �ʾ�, ��.\n�̸��� ���� ���� �̸� �״�ΰ�.");
	CScriptManager::getSkillManager()->AddScript(14, L"�������� �� ����, �� �ٸ� ����� ã�� ����.\n���� �ڿ������ϴ� �������� ������ �ٴϴ� �ž�.\n�䰪 �� �ض�.");
	CScriptManager::getSkillManager()->AddScript(15, L"(�ռ����� �׷��� ������� ������ ������.)");

	CScriptManager::getSkillManager()->AddScript(100, L"���� �ȿ� �� ���ƺ��� å�� ����ִµ�.");
	CScriptManager::getSkillManager()->AddScript(101, L"��� ���...");
	CScriptManager::getSkillManager()->AddScript(102, L"<��� ����>\n���� �̻�");
	CScriptManager::getSkillManager()->AddScript(103, L"    �� �� �����ڶ� ��Ī�ϴ� ��������\n������Ģ�� �Ž����� ���� �ڵ��� ���������.\n������ �׵��� �ڴ�� ��Ȱ ������ ������� ��.\n�ű⿡ ���� ���� ������.");
	CScriptManager::getSkillManager()->AddScript(104, L"�ݱ⸦ ��Ʈ���� �ΰ��鿡�� �г��� ����\n������ ������ �η��� �л������� �����ڸ� ��� �׿�\nȸ���� ��Ȱ ���� ������ ���� ���´�.");
	CScriptManager::getSkillManager()->AddScript(105, L"�� �� Ư�� �����鿡�� ���� �����־�\n�ڽ��� �絵�� ��� �η��� �����ϵ��� �Ͽ���.");
	CScriptManager::getSkillManager()->AddScript(106, L"�̰���, ���� �ƴ� ��� ������ �����̴�.\n\n�η����� ������ ���̶� �����ߴ� ���ϱ�...");

	CScriptManager::getSkillManager()->AddScript(200, L"�̷� ���� ��... �Ʊ���� ��� ���븸 �����ݾ�!\n�� ���� �Ǻ� ������ ���� �ų�?\n��ŭ�� ���µ� �����϶��!");
	CScriptManager::getSkillManager()->AddScript(201, L"���� ���� �� ���� �����ڵ��� �����ϴ� �޾縲�̾���.\n�Ű� ������� �� �ִ� ��Ҷ� ����.");
	CScriptManager::getSkillManager()->AddScript(202, L"���� ���� �׿� ���� ������ �������� ������� ��Ÿ����\n���� ���� �߸� �𵮵� ���ſ� ���� ������ ����ٴ� �ҹ��̾�.");
	*/
	CScriptManager::getSkillManager()->AddScript(800, L"�� ���ڴ� ���� �������� �� ����.");
	CScriptManager::getSkillManager()->AddScript(801, L"������ ���������� �̰� ó���ϴ� �� �ۿ� ���ڴµ���");
	CScriptManager::getSkillManager()->AddScript(802, L"�� �� �� �Ⱥ���?! �� �׾�� �ִµ� ���� ������ ��� �������?");
	CScriptManager::getSkillManager()->AddScript(803, L"���� �ǹ��� ó�� ����.");
	CScriptManager::getSkillManager()->AddScript(804, L"��¥ ���� �����̳�!!\n�� �� ��¦���� ���� �ž�?? ��ü ���������� �Ƴİ�! ");
	CScriptManager::getSkillManager()->AddScript(805, L"�ο� �غ� ��. �´�.");
	CScriptManager::getSkillManager()->AddScript(806, L"�絵�� �����ؿԴ�.");

	CScriptManager::getSkillManager()->AddScript(900, L"���� �絵�� �ϳ� �׾���.\n���� �� ���� ������ ���� �� �ְ���. ");
	CScriptManager::getSkillManager()->AddScript(901, L"�¾� �¾�, ������ �˰� ����. ");
	CScriptManager::getSkillManager()->AddScript(902, L"���� ����������. ���ڸ� �Ѿƾ� ��.");

	CScriptManager::getSkillManager()->AddScript(1000, L"���� ����? �׷�.");
	CScriptManager::getSkillManager()->AddScript(1001, L"���� ���� �������� ��ġ���ִ� �����̴�.\n������ �������� �ұ�������.");
	CScriptManager::getSkillManager()->AddScript(1002, L"���� �ͼ��� �����ε��� \n�絵 ���� ���� ���� �ִ� �� �Ƴ�?");
	CScriptManager::getSkillManager()->AddScript(1003, L"��Ȯ���� ����.\n���⿡ ���ͼ� ��Ƴ��� ����� ���ٰ� �ϴϱ�.");
	CScriptManager::getSkillManager()->AddScript(1004, L"��. ���� ������ �ҹ��̱�.\n�̹� ��ü�� ���� ��¿ �ųİ�.");

	CScriptManager::getSkillManager()->AddScript(1100, L"�����..");
	CScriptManager::getSkillManager()->AddScript(1101, L"�������̾� ����!\n�̹��� �� �� �ִ� �� �ƴ϶��? ");
	CScriptManager::getSkillManager()->AddScript(1102, L"������ �ִ�.\n�װ� �׷��� �� �ǰ�? ���� ���� �ΰ��ΰ�?\n����غ���, ���.");
	CScriptManager::getSkillManager()->AddScript(1103, L"����硯���? �׷�, ������ �� �׷��� �θ��� �� ������.\n��¥ ����� ���̾�, ����̶� ���ӵ���..");
	CScriptManager::getSkillManager()->AddScript(1104, L"�ʡ� ��ũ�θǼ��α�.\n���� ������ ��ƿ��� ��, ���� �� �𸣳�?");
	CScriptManager::getSkillManager()->AddScript(1105, L"�𸥴�.\n�系 ��� ������ ��������� �ʰ�, �׷��ٰ� ���� ���迡�� �� ��Ƽ�ϱ�.");
	CScriptManager::getSkillManager()->AddScript(1106, L"��õ�� ��.. ���� ���.\n���� �ڵ��� �ǻ츮�� ���ַ� Ī�� �޴� �庻��!\n���� ����� ���� �� ���� �ڰ����� ���� ���̴�!");
	CScriptManager::getSkillManager()->AddScript(1107, L"�� �ڽ� ���� �Ҹ� �ϴ� �ž�? ");
	CScriptManager::getSkillManager()->AddScript(1108, L"�׷��� ���� ��..\n������ �ο��� ���� ��ó�� �ϳ��� ����.");
	CScriptManager::getSkillManager()->AddScript(1109, L"�����?\n��� ��ó�� ��������?\n�и��� ���� �������� �ܾ���µ�?");
	CScriptManager::getSkillManager()->AddScript(1110, L"������ �� ��Ȱ������ ������, ȸ�������� ����� �� �ִ�.\n�ΰ� �߿� ��������.");
	CScriptManager::getSkillManager()->AddScript(1111, L"�׷� ��¥��? �� �ΰ��� ��¥ �� ��ƶ��?\nå������ ���� ���ִ��̶��??");
	CScriptManager::getSkillManager()->AddScript(1112, L"������ ������ �ſ��� �й��� ���ִ� ����� �����..\n�׸��� �׸� ������ ��ũ�θǼ��鵵.");
	CScriptManager::getSkillManager()->AddScript(1113, L"�� �ƴ±�.\n������ �����ϴ� ������ �׵�ۿ� �����ϱ�, �����ϰ� ���� ������.");
	CScriptManager::getSkillManager()->AddScript(1114, L"�̰� ���� ����̶��..\nȮ����, ���� ���� ���� �ΰ��̴�. ��� ���δ�.");
	CScriptManager::getSkillManager()->AddScript(1115, L"���� ������� �߶��ϰ� �� �š� ���δ�.\n���� ������ �絵�鵵 ������ ���� �״�!");
	CScriptManager::getSkillManager()->AddScript(1116, L"�� �������� ����!!");

	CScriptManager::getSkillManager()->AddScript(1200, L"�̰�١� ���� ���� ���� �ΰ��� ��ȥ�� �� �տ���");
	CScriptManager::getSkillManager()->AddScript(1201, L"Ū�� ������ �� �׾���.\n�ƹ��͵� �𸣴� ��û�� ��ũ�θǼ�...");
	CScriptManager::getSkillManager()->AddScript(1202, L"��ٷ� ����Ÿ. ���� �Ρ�");
	CScriptManager::getSkillManager()->AddScript(1203, L"��, ���ߡ� �׳� �� ���� ǰ�� �־���?\n�׷�, �ʵ� �ᱹ ������ ���� �־��� �ӡ�");
	CScriptManager::getSkillManager()->AddScript(1204, L"�� ������.. ���� ���� ����� ������ �ļա�\n�� ���⵵ ���� �� ���Ͼ� �Ӹ�ī���� ���� �� �� ������! ");
	CScriptManager::getSkillManager()->AddScript(1205, L"�� ���ڽ�, ���� ���� ����!");
	CScriptManager::getSkillManager()->AddScript(1206, L"���� �׿���.\n���� �絵�� ���δٰ� �����߳�? űű�� ��û�ѡ�..");
	CScriptManager::getSkillManager()->AddScript(1207, L"�׾��. ");
	CScriptManager::getSkillManager()->AddScript(1208, L"����");
	CScriptManager::getSkillManager()->AddScript(1209, L"��ȥ�� ������ �ƴϾ��, ������ �׿��� �� ���̾���.");
	CScriptManager::getSkillManager()->AddScript(1210, L"�ġ� ���塦 ��·�� �̰ɷ� ��ȥ�� �տ� �־��١�\n���ư��� �ǽ��� �����ϰھ�.");
	CScriptManager::getSkillManager()->AddScript(1211, L"����");

	CScriptManager::getSkillManager()->AddScript(1400, L"�� ���ÿ� �̷� ���� �־�����");
	CScriptManager::getSkillManager()->AddScript(1401, L"�¾�, ���� ��ﳵ��. ���� ���� ���� ������ �����ϴ� ��.");
	CScriptManager::getSkillManager()->AddScript(1402, L"��, �λ��� �׷�. �Ŵ��̽ô�.");
	CScriptManager::getSkillManager()->AddScript(1403, L"��ü��");
	CScriptManager::getSkillManager()->AddScript(1404, L"��! ���� ���� �Ȱ��ơ� ���� ����. ");
	CScriptManager::getSkillManager()->AddScript(1405, L"�̰� �� �� �ٸ� �𸣰ڳ�! �׷���? �� ��ȥ.");
	CScriptManager::getSkillManager()->AddScript(1406, L"���ܵ״� ���� ��ü���� �� ����� �ʹ� �����ż� �ٽ� �� ���ø� �� �˾ҰŴá�");
	CScriptManager::getSkillManager()->AddScript(1407, L"���, �̰� �� ���� �Ҹ���?");
	CScriptManager::getSkillManager()->AddScript(1408, L"�׷��ϱ�, ��� �� ������ ���� ��ü����~ �� �����̾�.");
	CScriptManager::getSkillManager()->AddScript(1409, L"���̶�� ��Ī�ϴ� �� �༮��, ���� ��뿡 ��� �ΰ��̾��ٰ�.\n���� �����̶� ���� ���� �� ȭ��������.");
	CScriptManager::getSkillManager()->AddScript(1410, L"������ ������ ���� ���¡� �ҷκһ簡 �Ǳ� ���� ��ü�� ���� ������ ��ü�� �Ǿ���. ");
	CScriptManager::getSkillManager()->AddScript(1411, L"�� �� ���� ��ü�� ���� ���� ������ ��⡦ �װ� �����͡��̴�. ");
	CScriptManager::getSkillManager()->AddScript(1412, L"���Ŷ�� ���� �����. �� �̸��� ��� ���������ݾ�?\n���� �����ִ� �� �ű��� �����̾�!");
	CScriptManager::getSkillManager()->AddScript(1413, L"Ȯ���� �� �̸��� �׸��� ������ ��١�");
	CScriptManager::getSkillManager()->AddScript(1414, L"������ �� �Ǵ±���\n����Ÿ�� ���� �� ���̰ھ�. ");
	CScriptManager::getSkillManager()->AddScript(1415, L"���� ���� ������, ������ �޶�.\n�� ���� �� Ÿ�ο��� ��̰� �����ŵ硦!");
	CScriptManager::getSkillManager()->AddScript(1416, L"�������\n���� �� ��ü�� �����Դ� �ϴ��� �ΰ��� �ΰ�. ");
	CScriptManager::getSkillManager()->AddScript(1417, L"���� ���� ������ ���� ����.");

	CScriptManager::getSkillManager()->AddScript(1500, L"����Ÿ!!!!");
	CScriptManager::getSkillManager()->AddScript(1501, L"�׷Ρ����� ����ҡ�?");
	CScriptManager::getSkillManager()->AddScript(1502, L"�̺�, ��. �ƴϡ� ��.\n�� �׾�� ���翡 �� �� ���� �غ����.");
	CScriptManager::getSkillManager()->AddScript(1503, L"�� ���� �Ӹ�ī������ �׳��ǡ� �ļ��ΰ�����");
	CScriptManager::getSkillManager()->AddScript(1504, L"�׷�. ��Ư�ϰԵ� ������,\n���� �� �������� ���� ã�ƿԴ� ����̾�.");
	CScriptManager::getSkillManager()->AddScript(1505, L"�� ������ᱸ����\n�� ���� �ð� ���ȡ�");
	CScriptManager::getSkillManager()->AddScript(1506, L"�����߱�.");
	CScriptManager::getSkillManager()->AddScript(1507, L"��, �и� �ݹ��� ���ڿ��� ��ȴµ���");
	CScriptManager::getSkillManager()->AddScript(1508, L"�����ơ� �ƹ� ���� ��������");
	CScriptManager::getSkillManager()->AddScript(1509, L"�׷Ρ�");
	CScriptManager::getSkillManager()->AddScript(1510, L"���� ���� �Բ� �������� ��Ȱ�� ���ư���.");
	CScriptManager::getSkillManager()->AddScript(1511, L"����Ÿ�� ��Ƴ����� �� ���� �� ������ ������ ���� ä��.");
	CScriptManager::getSkillManager()->AddScript(1512, L"���� �� �׳��� �̼Ҹ� ���� �� �����ε�, ���¡�");
	CScriptManager::getSkillManager()->AddScript(1513, L"Necromancer Romance FIN.");



	m_sound_Move = new CSound();
	m_sound_Move->Initialize("res/sound/se/move.wav");
	m_sound_Move->Loop(false);

	m_bgm_stage1 = new CSound();
	m_bgm_stage1->Initialize("res/sound/bgm/1Stage_Forest.mp3");
	m_bgm_stage1->Loop(true);

	m_bgm_stage1_boss = new CSound();
	m_bgm_stage1_boss->Initialize("res/sound/bgm/VS_lupus.mp3");
	m_bgm_stage1_boss->Loop(true);

	m_bgm_stage2 = new CSound();
	m_bgm_stage2->Initialize("res/sound/bgm/2Stage_Estate.mp3");
	m_bgm_stage2->Loop(true);

	m_bgm_stage2_boss = new CSound();
	m_bgm_stage2_boss->Initialize("res/sound/bgm/VS_Succubus.mp3");
	m_bgm_stage2_boss->Loop(true);

	m_Text = new CFont();
	m_Text->Initialize(L"10X10");

	m_fadeTimer = new CTime();
	m_fadeTimer->SetTimer(0.75f, false);

	m_resultTimer = new CTime();
	m_battleTimer = new CTime();
	m_rotateDelay = new CTime();
	m_walkTimer	= new CTime();

	m_monsterDamage = 0;
	m_cardDamage = 0;
	m_bTalkOn			= false;
	m_bScriptReset		= true;
	m_scriptNum			= 0;
}

void CScene_Field::Shutdown()
{	
	if(m_stage1Walk != NULL)
	{
		m_stage1Walk->Shutdown();
		SAFE_DELETE(m_stage1Walk);
	}
	if(m_stage1BossWalk != NULL)
	{
		m_stage1BossWalk->Shutdown();
		SAFE_DELETE(m_stage1BossWalk);
	}
	if(m_stage2Walk != NULL)
	{
		m_stage2Walk->Shutdown();
		SAFE_DELETE(m_stage2Walk);
	}
	if(m_stage2BossWalk != NULL)
	{
		m_stage2BossWalk->Shutdown();
		SAFE_DELETE(m_stage2BossWalk);
	}
	if(m_chain != NULL)
	{
		m_chain->Shutdown();
		SAFE_DELETE(m_chain);
	}
	if(m_walkShader != NULL)
	{
		m_walkShader->Shutdown();
		SAFE_DELETE(m_walkShader);
	}
	if(m_monsterGauge != NULL)
	{
		m_monsterGauge->Shutdown();
		SAFE_DELETE(m_monsterGauge);
	}
	if(m_skillButton != NULL)
	{
		m_skillButton->Shutdown();
		SAFE_DELETE(m_skillButton);
	}
	if(m_memberChange != NULL)
	{
		m_memberChange->Shutdown();
		SAFE_DELETE(m_memberChange);
	}
	if(m_targetMark != NULL)
	{
		m_targetMark->Shutdown();
		SAFE_DELETE(m_targetMark);
	}
	if(m_exploreBar != NULL)
	{
		m_exploreBar->Shutdown();
		SAFE_DELETE(m_exploreBar);
	}
	if(m_exploreBtn != NULL)
	{
		m_exploreBtn->Shutdown();
		SAFE_DELETE(m_exploreBtn);
	}
	if(m_talkWindow != NULL)
	{
		m_talkWindow->Shutdown();
		SAFE_DELETE(m_talkWindow);
	}
	if(m_Text != NULL)
	{
		m_Text->Shutdown();
		SAFE_DELETE(m_Text);
	}
	if(m_fadeTimer != NULL)
	{
		m_fadeTimer->StopTimer();
		SAFE_DELETE(m_fadeTimer);
	}
	if(m_resultTimer != NULL)
	{
		m_resultTimer->StopTimer();
		SAFE_DELETE(m_resultTimer);
	}
	if(m_battleTimer != NULL)
	{
		m_battleTimer->StopTimer();
		SAFE_DELETE(m_battleTimer);
	}
	if(m_rotateDelay != NULL)
	{
		m_rotateDelay->StopTimer();
		SAFE_DELETE(m_rotateDelay);
	}
	if(m_walkTimer != NULL)
	{
		m_walkTimer->StopTimer();
		SAFE_DELETE(m_walkTimer);
	}
	if(m_sound_Move != NULL)
	{
		m_sound_Move->Release();
		SAFE_DELETE(m_sound_Move);
	}
	if(m_bgm_stage1 != NULL)
	{
		m_bgm_stage1->Release();
		SAFE_DELETE(m_bgm_stage1);
	}
	if(m_bgm_stage1_boss != NULL)
	{
		m_bgm_stage1_boss->Release();
		SAFE_DELETE(m_bgm_stage1_boss);
	}
	if(m_bgm_stage2 != NULL)
	{
		m_bgm_stage2->Release();
		SAFE_DELETE(m_bgm_stage2);
	}
	if(m_bgm_stage2_boss != NULL)
	{
		m_bgm_stage2_boss->Release();
		SAFE_DELETE(m_bgm_stage2_boss);
	}

	m_bFadeIn = true;
	m_bTalkOn			= false;
	m_bScriptReset		= true;
	m_scriptNum			= 0;
	CScriptManager::getSkillManager()->ClearMap();
	CObjectManager::getObjectManager()->RemoveAllObjects();
}

void CScene_Field::Update(CInput* input)
{
	m_input = input;
	CObjectManager::getObjectManager()->UpdateAllObjects(input);
	
	bool bDefeat = false;

	m_exploreBar->Update(input);

	if(m_bExplore)
	{
		// ���丮 03
		if(CNero::getNero()->GetStoryProgress(STORY::STORY03))
		{
			int NumberOfLines = 4;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 0;
					switch(scriptNum)
					{
					case 0:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 2:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 3: m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					default:												break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY03);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}
		/*
		// ���丮 04
		if(CNero::getNero()->GetStoryProgress(STORY::STORY04))
		{
			int NumberOfLines = 6;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 10;
					switch(scriptNum)
					{
					case 10:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 11:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 12:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 13:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 14:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 15:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY04);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}
		*/
		/*
		// ���丮 06
		if(CNero::getNero()->GetStoryProgress(STORY::STORY06))
		{
			int NumberOfLines = 7;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 100;
					switch(scriptNum)
					{
					case 100:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 101:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 102:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					case 103:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					case 104:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					case 105:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					case 106:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY06);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}
		*/
		/*
		// ���丮 07
		if(CNero::getNero()->GetStoryProgress(STORY::STORY07))
		{
			int NumberOfLines = 3;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 200;
					switch(scriptNum)
					{
					case 200:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 201:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 202:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY07);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}
		*/
		// ���丮 08
		if(CNero::getNero()->GetStoryProgress(STORY::STORY08))
		{
			int NumberOfLines = 6;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 800;
					switch(scriptNum)
					{
					case 800:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 801:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 802:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 803:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 804:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 805:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY08);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}

		// ���丮 10
		if(CNero::getNero()->GetStoryProgress(STORY::STORY10))
		{
			int NumberOfLines = 5;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 1000;
					switch(scriptNum)
					{
					case 1000:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1001:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1002:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1003:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1004:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY10);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}

		// ���丮 11
		if(CNero::getNero()->GetStoryProgress(STORY::STORY11))
		{
			int NumberOfLines = 17;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 1100;
					switch(scriptNum)
					{
					case 1100:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1101:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1102:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1103:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1104:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1105:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1106:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1107:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1108:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1109:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1110:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1111:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1112:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1113:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1114:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1115:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1116:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY11);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}
		// ���丮 12
		if(CNero::getNero()->GetStoryProgress(STORY::STORY12))
		{
			int NumberOfLines = 12;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 1200;
					switch(scriptNum)
					{
					case 1200:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1201:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1202:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1203:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1204:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1205:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1206:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1207:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1208:	m_talkWindow->Reset(scriptNum, CARD::ILL_SHOA);	break;
					case 1209:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1210:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1211:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY12);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}

		// ���丮 14
		if(CNero::getNero()->GetStoryProgress(STORY::STORY14))
		{
			int NumberOfLines = 18;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 1400;
					switch(scriptNum)
					{
					case 1400:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1401:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1402:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1403:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					case 1404:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1405:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1406:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					case 1407:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1408:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1409:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1410:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					case 1411:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					case 1412:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1413:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					case 1414:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1415:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1416:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					case 1417:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY14);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}

		// ���丮 15
		if(CNero::getNero()->GetStoryProgress(STORY::STORY15))
		{
			int NumberOfLines = 14;
			if(m_scriptNum < NumberOfLines && m_scriptNum >= 0)
			{
				m_bTalkOn = true;
				if(m_bScriptReset)
				{
					int scriptNum = m_scriptNum + 1500;
					switch(scriptNum)
					{
					case 1500:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1501:	m_talkWindow->Reset(scriptNum, CARD::DAY);		break;
					case 1502:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1503:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					case 1504:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1505:	m_talkWindow->Reset(scriptNum, CARD::HILDE);	break;
					case 1506:	m_talkWindow->Reset(scriptNum, CARD::JOHN);		break;
					case 1507:	m_talkWindow->Reset(scriptNum, CARD::DAY);		break;
					case 1508:	m_talkWindow->Reset(scriptNum, CARD::NERO);		break;
					case 1509:	m_talkWindow->Reset(scriptNum, CARD::DAY);		break;
					case 1510:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					case 1511:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					case 1512:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					case 1513:	m_talkWindow->Reset(scriptNum, CARD::NOCARD);	break;
					default:													break;
					}
					m_bScriptReset = false;
				}
			}

			if(input->IsLButtonUp()) {
				m_scriptNum++;
				m_bScriptReset = true;
			}
			if(m_scriptNum >= NumberOfLines)
			{
				CNero::getNero()->OffStoryProgress(STORY::STORY15);
				m_scriptNum = 0;
				m_bTalkOn = false;
			}
		}

		if(!m_bTalkOn)
		{
			m_exploreBar->Show(true);
		
			m_memberChange->SetActivate(false);
			m_memberChange->Update(input);

		

			m_exploreBtn->Update(input);

			int select = m_exploreBtn->getSelect();

			if(select != -1)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::LUPUS || CNero::getNero()->GetBossProgress() == BOSS::SUCCUBUS) {
					select = RESULT::BATTLE;
				}
			}

			if(select == 100)
			{
				if(m_fadeTimer->GetTimer())
				{
					m_sound_Move->Reset();
					m_sound_Move->Play();
					m_fadeTimer->SetTimer(1.0f, false);
					m_bFadeIn = false;
				}
				m_bBattle	= false;
				m_bTresure	= false;
				m_bTrap		= false;
			}
			else if(select == RESULT::BATTLE)
			{
				m_bBattle	= true;
				m_bTresure	= false;
				m_bTrap		= false;
				m_bWalk		= true;
				m_battleTimer->SetTimer(2.8f, false);
				m_walkTimer->SetTimer(1.0f, false);
				CNero::getNero()->m_numBattle++;
			}
			else if(select == RESULT::TREASURE)
			{
				m_bBattle	= false;
				m_bTresure	= true;
				m_bTrap		= false;
				m_bWalk		= true;
				m_walkTimer->SetTimer(1.0f, false);
			}
			else if(select == RESULT::TRAP)
			{
				m_bBattle	= false;
				m_bTresure	= false;
				m_bTrap		= true;
				m_bWalk		= true;
				m_walkTimer->SetTimer(1.0f, false);
			}
			else
			{
				if(!m_bWalk) {
					m_exploreBtn->Show(true);

					if(CNero::getNero()->m_numExplore == 6) {
						CNero::getNero()->SetStoryProgress(STORY::STORY07);
						CNero::getNero()->m_numExplore++;
					}
				}
			}
		}

		
	}

	// ��Ʋ! ��Ʋ!! ��Ʋ!!!
	if(m_bBattle && m_battleTimer->GetTimer())
	{
		// ���� �غ�!!
		if(!CNero::getNero()->IsBattle())
		{
			CNero::getNero()->SetBattle(true);

			while(true)
			{
				if(CBattleManager::getBattleManager()->GetTurnCard() != NULL) {
					CBattleManager::getBattleManager()->TurnCardDequeue();
				}
				else {
					break;
				}
			}

			for(int i=0; i<4; i++) {
				CCard* tempCard = CNero::getNero()->GetPartyCardWithSlot(i);
				if(tempCard != NULL) {
					tempCard->setTurnTimer();
				}
			}
			if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::LUPUS) {
					CBattleManager::getBattleManager()->SetMonster(CMonsterManager::getMonsterManager()->getMonsterWithNum(2));
				}
				else {
					CBattleManager::getBattleManager()->SetMonster(CMonsterManager::getMonsterManager()->getMonsterWithNum(rand()%2));
				}
			}
			else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::SUCCUBUS) {
					CBattleManager::getBattleManager()->SetMonster(CMonsterManager::getMonsterManager()->getMonsterWithNum(12));
				}
				else if(CNero::getNero()->GetBossProgress() == BOSS::SHOA) {
					CBattleManager::getBattleManager()->SetMonster(CMonsterManager::getMonsterManager()->getMonsterWithNum(101));
				}
				else if(CNero::getNero()->GetBossProgress() == BOSS::GOD) {
					CBattleManager::getBattleManager()->SetMonster(CMonsterManager::getMonsterManager()->getMonsterWithNum(1000));
				}
				else {
					CBattleManager::getBattleManager()->SetMonster(CMonsterManager::getMonsterManager()->getMonsterWithNum(10+(rand()%2)));
				}
			}
			CBattleManager::getBattleManager()->GetMonster()->setTurnTimer(7.5f);
			CBattleManager::getBattleManager()->GetMonster()->UseSkill(m_skillNum);
			m_monsterGauge->setMonster(CBattleManager::getBattleManager()->GetMonster());
				
			m_targetMark->setMark();
			m_memberChange->SetActivate(false);
			m_chain->Reset();

		} // ���� �غ� ��!

		m_exploreBar->Show(false);
		m_exploreBtn->Show(false);

		m_skillButton->Update(input);

		m_memberChange->SetActivate(false);
		m_memberChange->Update(input);

		m_targetMark->Update(input);
		m_chain->Update(input);
	
		CMonster* tempMonster = CBattleManager::getBattleManager()->GetMonster();

		

		tempMonster->UseSkill(m_skillNum);

		if(tempMonster->getMyTurn())
		{
			m_skillNum = rand()%2;
		}

		m_targetMark->setMark();

		if(tempMonster->getStat().m_ap >= 100) {
			tempMonster->setAp(0);
			tempMonster->setTurnTimer(15.0f);
		}

		for(int i=0; i<4; i++)
		{
			CCard* tempCard = CNero::getNero()->GetPartyCardWithSlot(i);
			if(tempCard != NULL)
			{
				if(tempCard != CBattleManager::getBattleManager()->GetTurnCard())
				{
					if(tempCard->getRemainToTurn() == 1.0f) {
						CBattleManager::getBattleManager()->TurnCardEnqueue(tempCard);
					}
				}
			}
		}
		if(input->IsWheelDown())
		{
			if(CNero::getNero()->GetRotate() > 0)
			{
				CNero::getNero()->SetRotate(CNero::getNero()->GetRotate()-1);
				CBattleManager::getBattleManager()->RotateSlot();
				m_chain->Move();
			}
		}

		CBattleManager::getBattleManager()->EffectUpdate();
		CBattleManager::getBattleManager()->EffectAutoRemove();

		// ���� ����� ��
		if(tempMonster->getStat().m_hp <= 0 && m_resultTimer->GetTimer())
		{
			m_resultTimer->SetTimer(3.0f, false);
			m_exploreBtn->setBattleResult(RESULT::WON);

			CNero::getNero()->SetBattle(false);
			if(tempMonster->getIdNum() == 2)
			{
				m_bBossClear = true;
				CNero::getNero()->SetSoul(CNero::getNero()->GetSoul()+1);
				CNero::getNero()->SetGameProgress(PROGRESS::STAGE2);
				CNero::getNero()->SetBossProgress(BOSS::NONE);
			}
			else if(tempMonster->getIdNum() == 101)
			{
				CNero::getNero()->m_bShoa = false;
				CNero::getNero()->SetBossProgress(BOSS::NONE);
			}
			CNero::getNero()->SetGold(CNero::getNero()->GetGold()+100);
			CNero::getNero()->SetSoul(CNero::getNero()->GetSoul()+1);
			for(int i=0; i<4; i++)
			{
				CCard* tempCard = CNero::getNero()->GetPartyCardWithSlot(i);
				if(tempCard != NULL) {
					tempCard->stopTimer();
				}
			}

			CBattleManager::getBattleManager()->GetMonster()->Restore();

			if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
			{
				if(CNero::getNero()->m_numBattle == 1) {
					CNero::getNero()->SetStoryProgress(STORY::STORY04);
				}
			}

			m_bExplore = true;
			m_bBattle = false;

			//CBattleManager::getBattleManager()->EffectClear();
		}
		
		if(CNero::getNero()->GetCardNero()->getStat().m_hp <= 0 && m_resultTimer->GetTimer())
		{
			m_resultTimer->SetTimer(3.0f, false);
			m_exploreBtn->setBattleResult(RESULT::LOST);
			
			CNero::getNero()->SetBattle(false);

			m_bExplore = true;
			m_bBattle = false;

			if(m_fadeTimer->GetTimer())
			{
				m_fadeTimer->SetTimer(5.0f, false);
				m_bFadeIn = false;
			}
		}
	}

	CNero::getNero()->deathProcess();

	if(m_fadeTimer->GetTimer() && !m_bFadeIn)
	{
		CNero::getNero()->AllRestore();
		if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1) {
			CNero::getNero()->SetExploreNero(0.0f);
		}
		else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2) {
			CNero::getNero()->SetExploreNero(101.0f);
		}
		
		m_memberChange->SetActivate(false);

		CBattleManager::getBattleManager()->EffectClear();

		CSceneManager::getSceneManager()->SetScene(SCENE::TOWN);
	}
	if(m_walkTimer->GetTimer()) {
		m_bWalk = false;
	}
	
	if(CNero::getNero()->GetBossProgress() == BOSS::NONE)
	{
		if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
		{
			m_bgm_stage1->Play();
			m_bgm_stage1_boss->Stop();
			m_bgm_stage2->Stop();
			m_bgm_stage2_boss->Stop();
		}
		else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
		{
			m_bgm_stage1->Stop();
			m_bgm_stage1_boss->Stop();
			m_bgm_stage2->Play();
			m_bgm_stage2_boss->Stop();
		}
	}
	else if(CNero::getNero()->GetBossProgress() == BOSS::LUPUS)
	{
		m_bgm_stage1->Stop();
		m_bgm_stage1_boss->Play();
		m_bgm_stage2->Play();
		m_bgm_stage2_boss->Stop();
	}
	else if(CNero::getNero()->GetBossProgress() == BOSS::SUCCUBUS)
	{
		m_bgm_stage1->Stop();
		m_bgm_stage1_boss->Stop();
		m_bgm_stage2->Stop();
		m_bgm_stage2_boss->Play();
	}

	if(m_input->IsKeyDown(VK_NUMPAD0))
	{
		if(!CNero::getNero()->GetStoryProgress(STORY::STORY10)) {
			CNero::getNero()->SetStoryProgress(STORY::STORY10);
			m_input->KeyUp(VK_NUMPAD0);
		}
	}
	else if(m_input->IsKeyDown(VK_NUMPAD1))
	{
		if(!CNero::getNero()->GetStoryProgress(STORY::STORY11)) {
			CNero::getNero()->SetStoryProgress(STORY::STORY11);
			m_input->KeyUp(VK_NUMPAD1);
		}
	}
	else if(m_input->IsKeyDown(VK_NUMPAD2))
	{
		if(!CNero::getNero()->GetStoryProgress(STORY::STORY12)) {
			CNero::getNero()->SetStoryProgress(STORY::STORY12);
			m_input->KeyUp(VK_NUMPAD2);
		}
	}
	else if(m_input->IsKeyDown(VK_NUMPAD3))
	{
		if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1) {
			CNero::getNero()->SetGameProgress(PROGRESS::STAGE2);
			CNero::getNero()->SetExploreNero(BOSS1_PLACE + 100.0f);
			m_input->KeyUp(VK_NUMPAD3);
		}
	}
	else if(m_input->IsKeyDown(VK_NUMPAD4))
	{
		if(!CNero::getNero()->GetStoryProgress(STORY::STORY14)) {
			CNero::getNero()->SetStoryProgress(STORY::STORY14);
			m_input->KeyUp(VK_NUMPAD4);
		}
	}
	else if(m_input->IsKeyDown(VK_NUMPAD5))
	{
		if(!CNero::getNero()->GetStoryProgress(STORY::STORY15)) {
			CNero::getNero()->SetStoryProgress(STORY::STORY15);
			m_input->KeyUp(VK_NUMPAD5);
		}
	}
}

void CScene_Field::Render()
{
	float opacity = 0.0f;
	if(m_bFadeIn) {
		opacity = 1.0f - (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
		m_bgm_stage1->Volume(opacity);
	}
	else {
		opacity = (m_fadeTimer->RemainTime()/m_fadeTimer->GetSetTime());
		m_bgm_stage1->Volume(opacity);
	}


	if(m_bExplore)
	{
		if(opacity == 1.0f)
		{
			if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::LUPUS)
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(1.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
				else
				{
					m_stage1Bg->setOpacity(1.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
			}
			else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::SUCCUBUS)
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(1.0f);
				}
				else
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(1.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
			}

			CObjectManager::getObjectManager()->RenderAllObjects();

			if(m_bTalkOn)
			{
				m_talkWindow->Update(m_input);
				m_talkWindow->Render();
			}
			else
			{
				if(m_bWalk)
				{
					if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
					{
						m_stage1Walk->Render(0, 0, 0);
						m_walkShader->Render(m_stage1Walk->GetTexture(), m_walkTimer->RemainTime());
					}
					else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
					{
						m_stage2Walk->Render(0, 0, 0);
						m_walkShader->Render(m_stage2Walk->GetTexture(), m_walkTimer->RemainTime());
					}
					/*
					if(m_stage1BossBg->getOpacity() == 1.0f)
					{
						m_stage1BossWalk->Render(0, 0, 0);
						m_walkShader->Render(m_stage1BossWalk->GetTexture(), m_walkTimer->RemainTime());
					}
					else
					{
						m_stage1Walk->Render(0, 0, 0);
						m_walkShader->Render(m_stage1Walk->GetTexture(), m_walkTimer->RemainTime());
					}
					*/
				}
				m_exploreBar->Render();
				m_partySlot->Render();

				CBattleManager::getBattleManager()->EffectRender();

				m_exploreBtn->Render();

				m_memberChange->acceptSceneOpacity(opacity);
				m_memberChange->Render();
			}
		}
		else
		{
			if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::LUPUS)
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(opacity);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
				else
				{
					m_stage1Bg->setOpacity(opacity);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
			}
			else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::SUCCUBUS)
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(opacity);
				}
				else
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(opacity);
					m_stage2BossBg->setOpacity(0.0f);
				}
			}
			m_stage1Bg->Render();
			m_stage1BossBg->Render();
			m_stage2Bg->Render();
			m_stage2BossBg->Render();

			if(!m_bTalkOn)
			{
				m_exploreBar->setOpacity(opacity);
				m_exploreBar->Render();

				m_partySlot->setOpacity(opacity);
				m_partySlot->Render();

				m_exploreBtn->setOpacity(opacity);
				m_exploreBtn->Render();

				m_memberChange->setOpacity(opacity);
				m_memberChange->acceptSceneOpacity(opacity);
				m_memberChange->Render();
				
			}
		}
	}

	if(m_bBattle && m_battleTimer->GetTimer())
	{
		
		if(opacity == 1.0f)
		{
			if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::LUPUS)
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(1.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
				else
				{
					m_stage1Bg->setOpacity(1.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
			}
			else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::SUCCUBUS)
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(1.0f);
				}
				else
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(1.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
			}

			CObjectManager::getObjectManager()->RenderAllObjects();

			if(!m_bTalkOn)
			{

				CBattleManager::getBattleManager()->GetMonster()->MonsterRender(400, 50, 1.0f, 1.0f, opacity);
			
				m_monsterGauge->Render();
				m_targetMark->Render();

				if(m_bWalk)
				{
					if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
					{
						if(CNero::getNero()->GetBossProgress() == BOSS::LUPUS)
						{
							m_stage1BossWalk->Render(0, 0, 0);
							m_walkShader->Render(m_stage1BossWalk->GetTexture(), m_walkTimer->RemainTime());
						}
						else
						{
							m_stage1Walk->Render(0, 0, 0);
							m_walkShader->Render(m_stage1Walk->GetTexture(), m_walkTimer->RemainTime());
						}
					}
					else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
					{
						if(CNero::getNero()->GetBossProgress() == BOSS::SUCCUBUS)
						{
							m_stage2BossWalk->Render(0, 0, 0);
							m_walkShader->Render(m_stage1BossWalk->GetTexture(), m_walkTimer->RemainTime());
						}
						else
						{
							m_stage2Walk->Render(0, 0, 0);
							m_walkShader->Render(m_stage1Walk->GetTexture(), m_walkTimer->RemainTime());
						}
					}
				}
				else {
					m_chain->Render();
				}
			
			
				m_partySlot->Render();
				m_memberChange->Render();
			
				CBattleManager::getBattleManager()->EffectRender();
				m_skillButton->Render();
			}
		}
		else
		{
			if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE1)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::LUPUS)
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(opacity);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
				else
				{
					m_stage1Bg->setOpacity(opacity);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(0.0f);
				}
			}
			else if(CNero::getNero()->GetGameProgress() == PROGRESS::STAGE2)
			{
				if(CNero::getNero()->GetBossProgress() == BOSS::SUCCUBUS)
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(0.0f);
					m_stage2BossBg->setOpacity(opacity);
				}
				else
				{
					m_stage1Bg->setOpacity(0.0f);
					m_stage1BossBg->setOpacity(0.0f);
					m_stage2Bg->setOpacity(opacity);
					m_stage2BossBg->setOpacity(0.0f);
				}
			}
			m_stage1Bg->Render();
			m_stage1BossBg->Render();
			m_stage2Bg->Render();
			m_stage2BossBg->Render();

			m_chain->setOpacity(opacity);
			m_chain->Render();

			CBattleManager::getBattleManager()->GetMonster()->MonsterRender(400, 50, 1.0f, 1.0f, opacity);

			m_monsterGauge->setOpacity(opacity);
			m_monsterGauge->Render();
			
			m_targetMark->setOpacity(opacity);
			m_targetMark->Render();
			
			m_skillButton->setOpacity(opacity);
			m_skillButton->Render();
		
			m_partySlot->setOpacity(opacity);
			m_partySlot->Render();

			m_memberChange->setOpacity(opacity);
			m_memberChange->Render();
			m_memberChange->acceptSceneOpacity(opacity);

			m_exploreBtn->setOpacity(opacity);
			m_exploreBtn->Render();
		}
	}
}