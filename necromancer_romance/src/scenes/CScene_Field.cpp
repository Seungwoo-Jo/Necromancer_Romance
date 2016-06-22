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

	CScriptManager::getSkillManager()->AddScript(0, L"좀 궁금한 게 있는데, 우릴 밟아놓은 그 녀석은 이런 숲에서 어딜 가는거야?");
	CScriptManager::getSkillManager()->AddScript(1, L"너도 알다시피 그 남자는 용사라고 불리고 있어.\n대륙 곳곳을 돌아다니며 사도들을 퇴치하고 있다는군.");
	CScriptManager::getSkillManager()->AddScript(2, L"혼자서 사도를 퇴치한다고?\n뭐야, 내가 묻혀있던 사이에 이런 개그가 유행이 된 거냐?\n사도는 신이 남긴 괴물들이잖아.\n인간 혼자선 무리라고.");
	CScriptManager::getSkillManager()->AddScript(3, L"적어도 그 남자의 강함은 진짜였어.\n쫓아가다 보면 사도를 만날지도 모르겠는데.");
	/*
	CScriptManager::getSkillManager()->AddScript(10, L"너 좀 도움이 될 수 없는 거냐? 펀치가 너무 약하잖아.");
	CScriptManager::getSkillManager()->AddScript(11, L"지금 이 몸의 육체미를 무시하는 거냐?\n이 멋지고 상냥한 갈빗대를 보라고.");
	CScriptManager::getSkillManager()->AddScript(12, L"이제 와서 말하는 거지만 넌 모르모트였을 뿐이야.\n죽은 레나타를 발견했을 때,\n내 마법으로 그녀를 살릴 수 있는지 실험을 해야 했지.");
	CScriptManager::getSkillManager()->AddScript(13, L"레나타가 항상 찾아오던 묘비...\n거기에 안장된 유골을 되살려본 게 너야, 존.\n이름도 묘비에 적힌 이름 그대로고.");
	CScriptManager::getSkillManager()->AddScript(14, L"실패작인 널 보고, 난 다른 방법을 찾게 됐지.\n거의 자원봉사하는 심정으로 데리고 다니는 거야.\n밥값 좀 해라.");
	CScriptManager::getSkillManager()->AddScript(15, L"(앞서가는 네로의 뒤통수에 중지를 날린다.)");

	CScriptManager::getSkillManager()->AddScript(100, L"상자 안에 웬 낡아빠진 책이 들어있는데.");
	CScriptManager::getSkillManager()->AddScript(101, L"어디 어디...");
	CScriptManager::getSkillManager()->AddScript(102, L"<쇼아 전쟁>\n작자 미상");
	CScriptManager::getSkillManager()->AddScript(103, L"    한 때 성직자라 자칭하는 무리들은\n생리법칙을 거스르고 죽은 자들을 살려내었다.\n하지만 그들은 멋대로 부활 마법을 사용했을 뿐.\n거기에 신의 뜻은 없었다.");
	CScriptManager::getSkillManager()->AddScript(104, L"금기를 깨트리는 인간들에게 분노한 신은\n전쟁을 일으켜 인류를 학살했으며 성직자를 모두 죽여\n회복과 부활 계통 마법의 맥을 끊는다.");
	CScriptManager::getSkillManager()->AddScript(105, L"그 후 특정 괴물들에게 힘을 나눠주어\n자신의 사도로 삼고 인류를 견제하도록 하였다.");
	CScriptManager::getSkillManager()->AddScript(106, L"이것이, 내가 아는 쇼아 전쟁의 전말이다.\n\n인류에게 영원한 삶이란 과분했던 것일까...");

	CScriptManager::getSkillManager()->AddScript(200, L"이런 망할 숲... 아까부터 계속 늑대만 나오잖아!\n내 썩은 피부 냄새라도 맡은 거냐?\n앙큼한 짐승들 같으니라고!");
	CScriptManager::getSkillManager()->AddScript(201, L"전쟁 전에 이 숲은 성직자들이 관리하던 휴양림이었지.\n신과 가까워질 수 있는 장소라나 뭐라나.");
	CScriptManager::getSkillManager()->AddScript(202, L"종전 후의 잉여 마력 때문에 돌연변이 늑대들이 나타나고\n이젠 숲에 발만 디뎌도 전신에 붉은 반점이 생긴다는 소문이야.");
	*/
	CScriptManager::getSkillManager()->AddScript(800, L"그 남자는 숲을 빠져나간 것 같군.");
	CScriptManager::getSkillManager()->AddScript(801, L"앞으로 지나가려면 이걸 처리하는 수 밖에 없겠는데…");
	CScriptManager::getSkillManager()->AddScript(802, L"너 내 몸 안보여?! 다 죽어가고 있는데 저런 거한테 대신 맞으라고?");
	CScriptManager::getSkillManager()->AddScript(803, L"나도 실물은 처음 본다.");
	CScriptManager::getSkillManager()->AddScript(804, L"진짜 썩을 주인이네!!\n왜 날 관짝에서 꺼낸 거야?? 시체 통조림인줄 아냐고! ");
	CScriptManager::getSkillManager()->AddScript(805, L"싸울 준비 해. 온다.");
	CScriptManager::getSkillManager()->AddScript(806, L"사도가 습격해왔다.");

	CScriptManager::getSkillManager()->AddScript(900, L"지금 사도가 하나 죽었다.\n이젠 이 숲도 오명을 씻을 수 있겠지. ");
	CScriptManager::getSkillManager()->AddScript(901, L"맞아 맞아, 나무는 죄가 없지. ");
	CScriptManager::getSkillManager()->AddScript(902, L"숲을 가로지른다. 남자를 쫓아야 해.");

	CScriptManager::getSkillManager()->AddScript(1000, L"여긴 어디야? 네로.");
	CScriptManager::getSkillManager()->AddScript(1001, L"전쟁 이후 오랫동안 방치돼있던 저택이다.\n지금은 괴물들의 소굴이지만.");
	CScriptManager::getSkillManager()->AddScript(1002, L"뭔가 익숙한 느낌인데… \n사도 말고도 여러 가지 있는 거 아냐?");
	CScriptManager::getSkillManager()->AddScript(1003, L"정확히는 모르지.\n여기에 들어와서 살아남은 사람은 없다고 하니까.");
	CScriptManager::getSkillManager()->AddScript(1004, L"쳇. 정말 진부한 소문이군.\n이미 시체인 나는 어쩔 거냐고.");

	CScriptManager::getSkillManager()->AddScript(1100, L"너희들..");
	CScriptManager::getSkillManager()->AddScript(1101, L"오랜만이야 형씨!\n이번엔 둘 만 있는 게 아니라고? ");
	CScriptManager::getSkillManager()->AddScript(1102, L"질문이 있다.\n네가 그렇게 센 건가? 가장 강한 인간인가?\n대답해봐라, 용사.");
	CScriptManager::getSkillManager()->AddScript(1103, L"‘용사’라고? 그래, 지금은 날 그렇게 부르는 것 같더군.\n진짜 웃긴단 말이야, 사람이란 족속들은..");
	CScriptManager::getSkillManager()->AddScript(1104, L"너… 네크로맨서로군.\n오랜 세월을 살아왔을 터, 정말 날 모르나?");
	CScriptManager::getSkillManager()->AddScript(1105, L"모른다.\n사내 놈들 일일이 기억하지도 않고, 그랬다간 이쪽 업계에선 못 버티니까.");
	CScriptManager::getSkillManager()->AddScript(1106, L"미천한 것.. 나는 쇼아.\n죽은 자들을 되살리며 교주로 칭송 받던 장본인!\n원래 너희들 따윈 말 섞을 자격조차 없단 말이다!");
	CScriptManager::getSkillManager()->AddScript(1107, L"저 자식 무슨 소릴 하는 거야? ");
	CScriptManager::getSkillManager()->AddScript(1108, L"그러고 보니 너..\n그전에 싸웠을 때의 상처가 하나도 없군.");
	CScriptManager::getSkillManager()->AddScript(1109, L"뭐라고?\n사실 나처럼 좀비라던가?\n분명히 내가 손톱으로 긁어줬는데?");
	CScriptManager::getSkillManager()->AddScript(1110, L"지금의 난 부활마법은 없지만, 회복마법은 사용할 수 있다.\n인간 중엔 유일하지.");
	CScriptManager::getSkillManager()->AddScript(1111, L"그럼 진짜야? 저 인간이 진짜 그 쇼아라고?\n책에서나 보던 교주님이라고??");
	CScriptManager::getSkillManager()->AddScript(1112, L"전쟁이 끝나고 신에게 패배한 교주는 행방을 감췄다..\n그리고 그를 따르던 네크로맨서들도.");
	CScriptManager::getSkillManager()->AddScript(1113, L"잘 아는군.\n젊음을 유지하는 마법은 그들밖에 못쓰니까, 유용하게 쓰다 버렸지.");
	CScriptManager::getSkillManager()->AddScript(1114, L"이게 전부 사실이라면..\n확실히, 저게 가장 강한 인간이다. 고로 죽인다.");
	CScriptManager::getSkillManager()->AddScript(1115, L"나를 여기까지 추락하게 한 신… 죽인다.\n신을 따르는 사도들도 모조리 죽일 테다!");
	CScriptManager::getSkillManager()->AddScript(1116, L"날 방해하지 마라!!");

	CScriptManager::getSkillManager()->AddScript(1200, L"이겼다… 이제 가장 강한 인간의 영혼이 내 손에…");
	CScriptManager::getSkillManager()->AddScript(1201, L"큭… 아직… 안 죽었다.\n아무것도 모르는 멍청한 네크로맨서...");
	CScriptManager::getSkillManager()->AddScript(1202, L"기다려 레나타. 드디어 널…");
	CScriptManager::getSkillManager()->AddScript(1203, L"하, 뭐야… 네놈… 그 여잘 품고 있었나?\n그래, 너도 결국 복수에 눈이 멀었을 뿐…");
	CScriptManager::getSkillManager()->AddScript(1204, L"그 계집은.. 대대로 신을 섬기던 가문의 후손…\n꼴 보기도 싫은 그 새하얀 머리카락을 보면 알 수 있지…! ");
	CScriptManager::getSkillManager()->AddScript(1205, L"너 이자식, 지금 무슨 말을!");
	CScriptManager::getSkillManager()->AddScript(1206, L"내가 죽였다.\n내가 사도만 죽인다고 생각했나? 킥킥… 멍청한…..");
	CScriptManager::getSkillManager()->AddScript(1207, L"죽어라. ");
	CScriptManager::getSkillManager()->AddScript(1208, L"윽…");
	CScriptManager::getSkillManager()->AddScript(1209, L"영혼이 목적이 아니었어도, 언젠가 죽여야 할 놈이었군.");
	CScriptManager::getSkillManager()->AddScript(1210, L"후… 젠장… 어쨌든 이걸로 영혼을 손에 넣었다…\n돌아가서 의식을 시작하겠어.");
	CScriptManager::getSkillManager()->AddScript(1211, L"……");

	CScriptManager::getSkillManager()->AddScript(1400, L"이 저택에 이런 방이 있었군…");
	CScriptManager::getSkillManager()->AddScript(1401, L"맞아, 전부 기억났어. 여긴 원래 신이 마법을 연구하던 곳.");
	CScriptManager::getSkillManager()->AddScript(1402, L"자, 인사해 네로. 신님이시다.");
	CScriptManager::getSkillManager()->AddScript(1403, L"육체…");
	CScriptManager::getSkillManager()->AddScript(1404, L"신! 전쟁 때랑 똑같아… 몸이 없어. ");
	CScriptManager::getSkillManager()->AddScript(1405, L"이거 몸 둘 바를 모르겠네! 그렇지? 내 영혼.");
	CScriptManager::getSkillManager()->AddScript(1406, L"남겨뒀던 나의 육체여… 내 기억은 너무 오래돼서 다신 못 떠올릴 줄 알았거늘…");
	CScriptManager::getSkillManager()->AddScript(1407, L"잠깐, 이게 다 무슨 소리야?");
	CScriptManager::getSkillManager()->AddScript(1408, L"그러니까, 사실 이 존님은 신의 육체였다~ 이 말씀이야.");
	CScriptManager::getSkillManager()->AddScript(1409, L"신이라고 자칭하는 저 녀석도, 원랜 고대에 살던 인간이었다고.\n단지 마법이란 힘을 만들어낸 게 화근이지만.");
	CScriptManager::getSkillManager()->AddScript(1410, L"마법의 정점에 오른 나는… 불로불사가 되기 위해 육체를 벗고 스스로 영체가 되었다. ");
	CScriptManager::getSkillManager()->AddScript(1411, L"그 때 남은 육체와 쓸모 없는 정신의 찌꺼기… 그게 ‘저것’이다. ");
	CScriptManager::getSkillManager()->AddScript(1412, L"저거라고 하지 말라고. 네 이름도 사실 ‘존’이잖아?\n묘비가 남아있던 게 신기할 지경이야!");
	CScriptManager::getSkillManager()->AddScript(1413, L"확실히 그 이름은 그리운 느낌이 든다…");
	CScriptManager::getSkillManager()->AddScript(1414, L"정리가 안 되는군…\n레나타를 위해 널 죽이겠어. ");
	CScriptManager::getSkillManager()->AddScript(1415, L"전쟁 때는 졌지만, 지금은 달라.\n그 때의 난 타인에게 흥미가 없었거든…!");
	CScriptManager::getSkillManager()->AddScript(1416, L"어리석은…\n나의 옛 육체를 데려왔다 하더라도 인간은 인간. ");
	CScriptManager::getSkillManager()->AddScript(1417, L"감히 내게 대적할 생각 마라.");

	CScriptManager::getSkillManager()->AddScript(1500, L"레나타!!!!");
	CScriptManager::getSkillManager()->AddScript(1501, L"네로…여긴 어디죠…?");
	CScriptManager::getSkillManager()->AddScript(1502, L"이봐, 신. 아니… 존.\n다 죽어가는 마당에 할 말 있음 해보라고.");
	CScriptManager::getSkillManager()->AddScript(1503, L"저 은색 머리카락은… 그녀의… 후손인가……");
	CScriptManager::getSkillManager()->AddScript(1504, L"그래. 기특하게도 말이지,\n매일 밤 ‘존’의 묘비에 찾아왔던 모양이야.");
	CScriptManager::getSkillManager()->AddScript(1505, L"날 기억해줬구나…\n참 오랜 시간 동안…");
	CScriptManager::getSkillManager()->AddScript(1506, L"성불했군.");
	CScriptManager::getSkillManager()->AddScript(1507, L"전, 분명 금발의 남자에게 찔렸는데…");
	CScriptManager::getSkillManager()->AddScript(1508, L"괜찮아… 아무 말도 하지마…");
	CScriptManager::getSkillManager()->AddScript(1509, L"네로…");
	CScriptManager::getSkillManager()->AddScript(1510, L"나는 존과 함께 묘지기의 생활로 돌아갔다.");
	CScriptManager::getSkillManager()->AddScript(1511, L"레나타는 살아났지만 난 아직 내 마음을 전하지 못한 채다.");
	CScriptManager::getSkillManager()->AddScript(1512, L"매일 밤 그녀의 미소를 보는 것 만으로도, 나는…");
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
		// 스토리 03
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
		// 스토리 04
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
		// 스토리 06
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
		// 스토리 07
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
		// 스토리 08
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

		// 스토리 10
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

		// 스토리 11
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
		// 스토리 12
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

		// 스토리 14
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

		// 스토리 15
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

	// 배틀! 배틀!! 배틀!!!
	if(m_bBattle && m_battleTimer->GetTimer())
	{
		// 전투 준비!!
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

		} // 전투 준비 끝!

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

		// 몬스터 잡았을 때
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