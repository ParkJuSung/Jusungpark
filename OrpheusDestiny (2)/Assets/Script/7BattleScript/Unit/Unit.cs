using System.Collections;
using System.Collections.Generic;
using UnityEngine;


// 유닛 공통 기능담당

public class Unit : MonoBehaviour
{
    public enum Unit_State
    {
        Idle_State,
        Find_State,
        Battle_State,
        Dead_State,
        Wining_State,
        Skill_State,
    }

    public bool firstAttack = true; // 만나자마자 처음떄리기
    public int HP;               // 병사수
    public int ATK;              // 공격력 = 병사수
    public int DEF;              // 방어력= 영웅의 통솔력 + 병사 방어력
    public float Agil;             // 공격속도

    public float RANGE;       // 사정거리
    public float SPEED;       // 이동속도
}
