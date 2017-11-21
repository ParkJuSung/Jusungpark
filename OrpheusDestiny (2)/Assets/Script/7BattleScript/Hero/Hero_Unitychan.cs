using System.Collections;
using System.Collections.Generic;
using UnityEngine.AI;
using UnityEngine;

public class Hero_Unitychan : Unit {

    public GameObject target;
    public NavMeshAgent nvAgent; // 네비

    public GameObject SummonPrefab;

    public bool LockOn;

    private int ATKanim;
    Animator mAnimator = null;
    float targetdistance;

    Unit_State Current_State;

    private void Awake()
    {
        Init();
    }

    void Start()
    {
        LockOn = false;

        GameObject Curespell = (GameObject)Instantiate(SummonPrefab, gameObject.transform.position, Quaternion.identity);

        nvAgent = gameObject.GetComponent<NavMeshAgent>();

        mAnimator = gameObject.GetComponent<Animator>(); //애니메이션할 객체 얻기


        mAnimator.SetBool("Isjab", false);
        mAnimator.SetBool("Issamk", false);
        mAnimator.SetBool("Ishikick", false);
        mAnimator.SetBool("Iswalk", true);

        Current_State = Unit_State.Find_State;

        Destroy(Curespell, Curespell.GetComponent<ParticleSystem>().duration + 1f);

        StartCoroutine(SetAnimator());

    }

    // Update is called once per frame
    void Update()
    {
        mAnimator.SetBool("Isjab", false);
        mAnimator.SetBool("Issamk", false);
        mAnimator.SetBool("Ishikick", false);

        CheckAlive();

        if (SBattleManager.Instance.EnemyList.Count == 0)
            Current_State = Unit_State.Wining_State;
    }

    IEnumerator SetAnimator()
    {
        while (true)
        {
            switch (Current_State)
            {
                case Unit_State.Idle_State:
                    break;
                case Unit_State.Find_State:
                    FindTarget();
                    MoveToTarget();
                    break;
                case Unit_State.Battle_State:
                    Battle();
                    yield return new WaitForSeconds(Agil);
                    break;
                case Unit_State.Dead_State:
                    Dead();
                    break;
                case Unit_State.Wining_State:
                    Win();
                    break;
            }
            yield return null;
        }

    }


    void Init()
    {
        HP = 1200;               // 병사수
        ATK = 200;              // 공격력 = 병사수
        DEF = 0;              // 방어력= 영웅의 통솔력 + 병사 방어력
        Agil = 0.92f;             // 공격속도

        RANGE = 0.9f;       // 사정거리
        SPEED = 2;       // 이동속도
        FindTarget();
    }

    void Idle()
    {

    }

    void ATKAnimaton()
    {
        mAnimator.SetBool("Iswalk", false);

        ATKanim = Random.Range(1, 4);
        switch (ATKanim)
        {
            case 1:
                mAnimator.SetBool("Isjab", false);
                mAnimator.SetBool("Issamk", false);
                mAnimator.SetBool("Ishikick", true);
                ATK = 50;
                Agil = 0.92f;
                break;
            case 2:
                mAnimator.SetBool("Isjab", false);
                mAnimator.SetBool("Ishikick", false);
                mAnimator.SetBool("Issamk", true);
                ATK = 70;
                Agil = 1.8f;
                break;
            case 3:
                mAnimator.SetBool("Ishikick", false);
                mAnimator.SetBool("Issamk", false);
                mAnimator.SetBool("Isjab", true);
                ATK = 90;
                Agil = 2f;
                break;
        }
    }
    void Battle()
    {
        mAnimator.SetBool("Iswalk", false);

        ATKAnimaton();

        if (SBattleManager.Instance.EnemyList.Count == 0)
        {
            Current_State = Unit_State.Wining_State;
            return;
        }
        else if (target == null)
        {
            Current_State = Unit_State.Find_State;
            return;
        }

        switch (target.tag)
        {
            case "Goblin":
                target.GetComponent<Monster_Goblin>().SetUnitHp(ATK);
                if (target.GetComponent<Monster_Goblin>().GetUnitHP() <= 0)
                {
                    LockOn = false;
                    Current_State = Unit_State.Find_State;
                }
                break;
            case "Skeleton":
                target.GetComponent<Monster_Skeleton>().SetUnitHp(ATK);
                if (target.GetComponent<Monster_Skeleton>().GetUnitHP() <= 0)
                {
                    LockOn = false;
                    Current_State = Unit_State.Find_State;
                }
                break;
            case "Boss":
                target.GetComponent<Monster_Boss>().SetUnitHp(ATK);
                if (target.GetComponent<Monster_Boss>().GetUnitHP() <= 0)
                {
                    LockOn = false;
                    Current_State = Unit_State.Find_State;
                }
                break;
        }
    }

    void FindTarget() // 적 탐색 함수
    {
        if (SBattleManager.Instance.EnemyList.Count > 0)
        {
            target = SBattleManager.Instance.EnemyList[0];
            for (int EnemyIter = 0; EnemyIter < SBattleManager.Instance.EnemyList.Count; EnemyIter++)
            {
                float distance = Vector3.Distance(SBattleManager.Instance.EnemyList[EnemyIter].transform.position, gameObject.transform.position);
                targetdistance = Vector3.Distance(target.transform.position, gameObject.transform.position);

                if (distance < targetdistance)                                                     //타겟을 바꿔야할 때
                {
                    target = SBattleManager.Instance.EnemyList[EnemyIter];
                    targetdistance = distance;
                }
            }
        }
    }

    void MoveToTarget() // 적한테 이동함수
    {
        if (SBattleManager.Instance.EnemyList.Count > 0)
        {
            nvAgent.destination = target.transform.position;
            mAnimator.SetBool("Iswalk", true);

            switch (target.tag)
            {

                case "Goblin":
                    if (!LockOn)
                    {
                        if (Vector3.Distance(target.transform.position, gameObject.transform.position) <= RANGE)
                            LockOn = true;
                    }
                    else
                        Current_State = Unit_State.Battle_State;
                    break;
                case "Skeleton":
                    if (!LockOn)
                    {
                        if (Vector3.Distance(target.transform.position, gameObject.transform.position) <= RANGE)
                            LockOn = true;
                    }
                    else
                        Current_State = Unit_State.Battle_State;

                    break;
                case "Boss":
                    if (!LockOn)
                    {
                        if (Vector3.Distance(target.transform.position, gameObject.transform.position) <= RANGE)
                            LockOn = true;
                    }
                    else
                        Current_State = Unit_State.Battle_State;

                    break;
            }
        }
    }

    public void Dead()
    {
        SResource.Instance.SOUL = SResource.Instance.SOUL + 100;
        SBattleManager.Instance.HeroList.Remove(gameObject);
        Destroy(gameObject);
    }

    void Win()
    {
        mAnimator.SetBool("Iswalk", false);
        LockOn = false;
        if (SBattleManager.Instance.EnemyList.Count != 0)
        {
            FindTarget();
            Current_State = Unit_State.Find_State;
        }
    }

    public int GetHeroHP()
    {
        return HP;
    }

    public int SetHeroHp(int atk)
    {
        HP = HP - atk;
        return HP;
    }
    void CheckAlive()
    {
        if (HP <= 0)
            Dead();
    }
}
