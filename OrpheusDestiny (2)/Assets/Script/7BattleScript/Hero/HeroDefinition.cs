using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeroDefinition : Unit {

    public enum Hero_List
    {
        Hero1_Knight,
        Hero2_Dancer,
        Hero3_Mage,
        Hero4_Chellinger,
        Hero5_Hero,
        Hero6_Killer,
        Hero7_Monk,
        Hero8_Phantom,
        Hero9_Mummy,
        Veteran,
        Hero_Unity,
        Hero_SpartanKing,
    }

    public enum Skill_List
    {
        Empty,
        Skill_Rush,             // 돌진 : 보병 공격력, 이동속도 증가
        Skill_Windish,          // 이동속도 증가
        Skill_Match,            // 일기토 적 영웅중 제일강한애에 공격받고 공격력만큼 데미지(방무)
        Skill_FireExplosion,    // 파이어볼
        Skill_Heal,             // 힐 : 에너지 낮은 유닛 2마리 회복
        Skill_Retreat,          // 후퇴
        Skill_Thunder,
        Skill_Avatar,
        Skill_Summon,
        Skill_Brave,
        Skill_Cure,
        Skill_Tame,
    }

    public enum Hero_State
    {
        Card,
        Summoned,
        Dead,
    }
    public static List<Skill_List> SkillList = new List<Skill_List>();
}
