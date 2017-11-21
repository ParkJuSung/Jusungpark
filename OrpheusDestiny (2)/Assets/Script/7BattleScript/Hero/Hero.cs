using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class Hero : HeroDefinition
{
    private int EntryCount;// 영웅 등장시간
    public bool Summon;
    
    public GameObject HeroCard;

   public Sprite Hero1_Knight;
   public Sprite Hero2_Dancer; // 비어있음
   public Sprite Hero3_Mage;
   public Sprite Hero4_Chellenger; //비어있음
   public Sprite Hero5_Hero;
   public Sprite Hero6_Killer; // 비어있음
   public Sprite Hero7_Monk;   // 비어있음
   public Sprite Hero8_Phantom;
   public Sprite Hero9_Mummy; // 비어있음
   public  Sprite Hero_SpartanKing;
   public  Sprite Hero_Unity;
   public  Sprite Veteran;

    private Hero_State Current_State;
    public GameObject HeroPrefab;
    public GameObject HeroPrefab_Unity;
    public GameObject HeroPrefab_SpartanKing;


    private int Cost;

    protected Skill_List Slot1;
    protected Skill_List Slot2;
    /// //////////////////////////////////////////////////////////////
    public Hero_List ThisCard;
  /// ///////////////////////////////////////////////////////////

    // Use this for initialization
    void Start () {
        Current_State = Hero_State.Card;
        SetStatus();
        SetImage();
    }

// Update is called once per frame
void Update () {

    }

    public Hero_State GetCurrentState()
    {
        return Current_State;
    }

    private void SetImage()
    {
        switch (ThisCard)
        {
            case Hero_List.Veteran:
                HeroCard.GetComponent<Image>().sprite = Veteran;
                break;

            case Hero_List.Hero1_Knight:
                HeroCard.GetComponent<Image>().sprite = Hero1_Knight;
                break;

            case Hero_List.Hero2_Dancer:
                break;

            case Hero_List.Hero3_Mage:
                HeroCard.GetComponent<Image>().sprite = Hero3_Mage;
                break;

            case Hero_List.Hero4_Chellinger:
                break;

            case Hero_List.Hero5_Hero:
                HeroCard.GetComponent<Image>().sprite = Hero5_Hero;
                break;

            case Hero_List.Hero6_Killer:
                break;

            case Hero_List.Hero7_Monk:
                break;

            case Hero_List.Hero8_Phantom:
                HeroCard.GetComponent<Image>().sprite = Hero8_Phantom;
                break;

            case Hero_List.Hero9_Mummy:
                break;
            case Hero_List.Hero_SpartanKing:
                HeroCard.GetComponent<Image>().sprite = Hero_SpartanKing;
                break;
            case Hero_List.Hero_Unity:
                HeroCard.GetComponent<Image>().sprite = Hero_Unity;
                break;
        }
    }
    private void SetStatus()
    {
        switch (ThisCard)
        {
            case Hero_List.Veteran:
                firstAttack = true; // 만나자마자 처음떄리
                HP = 1200;               // 병사수
                ATK = 100;              // 공격력 = 병사수
                DEF = 0;              // 방어력= 영웅의 통솔력 
                Agil = 0.92f;             // 공격속도

                RANGE = 0.5f;       // 사정거리
                SPEED = 1;       // 이동속도
                Cost = 200;
                break;

            case Hero_List.Hero_Unity:
                firstAttack = true; // 만나자마자 처음떄리
                HP = 1200;               // 병사수
                ATK = 200;              // 공격력 = 병사수
                DEF = 0;              // 방어력= 영웅의 통솔력 
                Agil = 0.92f;             // 공격속도

                RANGE = 0.4f;       // 사정거리
                SPEED = 1;       // 이동속도
                Cost = 200;
                break;

            case Hero_List.Hero_SpartanKing:
                firstAttack = true; // 만나자마자 처음떄리
                HP = 2000;               // 병사수
                ATK = 100;              // 공격력 = 병사수
                DEF = 0;              // 방어력= 영웅의 통솔력 
                Agil = 0.92f;             // 공격속도

                RANGE = 0.5f;       // 사정거리
                SPEED = 1;       // 이동속도
                Cost = 200;
                break;
        }
    }
    public void SummonHero()
    {
        if (Cost < SBattleManager.Instance.currentgage)
        { 
            switch (ThisCard)
        {
            case Hero_List.Veteran:
                    SkillList.Add(Skill_List.Skill_Rush);
                    SkillList.Add(Skill_List.Skill_Heal);

                    SBattleManager.Instance.HeroList.Add(Instantiate(HeroPrefab, new Vector3(3.5f, 0, -6), Quaternion.identity));

                    SBattleManager.Instance.currentgage -= Cost;
                break;

            case Hero_List.Hero1_Knight:
                break;

            case Hero_List.Hero2_Dancer:
                break;

            case Hero_List.Hero3_Mage:
                break;

            case Hero_List.Hero4_Chellinger:
                break;

            case Hero_List.Hero5_Hero:
                break;

            case Hero_List.Hero6_Killer:
                break;

            case Hero_List.Hero7_Monk:
                break;

            case Hero_List.Hero8_Phantom:
                break;

            case Hero_List.Hero9_Mummy:
                break;

            case Hero_List.Hero_Unity:
                    SkillList.Add(Skill_List.Skill_FireExplosion);
                    SkillList.Add(Skill_List.Skill_Avatar);
                    SBattleManager.Instance.HeroList.Add(Instantiate(HeroPrefab_Unity, new Vector3(3.5f, 0, -6), Quaternion.identity));
                    SBattleManager.Instance.currentgage -= Cost;
                break;

            case Hero_List.Hero_SpartanKing:
                    SkillList.Add(Skill_List.Skill_Brave);
                    SkillList.Add(Skill_List.Skill_Tame);
                    SBattleManager.Instance.HeroList.Add(Instantiate(HeroPrefab_SpartanKing, new Vector3(3.5f, 0, -6), Quaternion.identity));
                    SBattleManager.Instance.currentgage -= Cost;
                break;
        }
        
        Current_State = Hero_State.Summoned;
        HeroCard.SetActive(false);
        }
    }
}