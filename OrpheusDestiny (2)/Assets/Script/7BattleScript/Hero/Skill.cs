using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class Skill : SkillManager {

    public enum Skill_State
    {
        Filling_State,
        Full_State,
        Ban_State,
    }

    public GameObject Effect;
    public Image BanObject;
    private bool Banned;

    private int SkillCost;

    public Skill_List SkillIter;
    public Skill_State Current_State;

    float CurrentTime;

    public Sprite Skill_Rush;
    public Sprite Skill_Windish;
    public Sprite Skill_Match;
    public Sprite Skill_FireExplosion;
    public Sprite Skill_Heal;
    public Sprite Skill_Thunder;
    public Sprite Skill_Avatar;
    public Sprite Skill_Summon;
    public Sprite Skill_Brave;
    public Sprite Skill_Cure;
    public Sprite Skill_Tame;


    public GameObject HealPrefab;
    public GameObject BravePrefab;
    public GameObject AvatarPrefab;
    public GameObject TamePrefab;
    public GameObject FirePrefab;
    public GameObject ExFirePrefab;

    public GameObject FireEffect;
    public GameObject ExFireEffect;
    public GameObject BraveEffect;
    public GameObject HealEffect;
    public GameObject AvatarEffect;
    public GameObject TameEffect;

    public GameObject Target;

    public bool Fire;
    public bool Brave;
    public bool Heal;
    public bool Avatar;
    public bool Tame;

    // Use this for initialization
    void Start () {
        SkillIter = SkillList[iterator];
        iterator++;
        Effect.SetActive(false);
        Current_State = Skill_State.Filling_State;
        SetSkillSlot();
        Banned = false;
        CurrentTime = 3f;
    }

    // Update is called once per frame
    void Update()
    {

        CheckState();

        if (Input.GetButtonDown("Fire1"))
        {
            if (Fire)
            {

                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

                RaycastHit hitInfo;
                if (Physics.Raycast(ray, out hitInfo))
                {
                    Vector3 hitPosition = hitInfo.point;

                    Vector3 dir = hitPosition - transform.position;

                    ExFireEffect = (GameObject)Instantiate(ExFirePrefab, new Vector3(dir.x + 251f, 1, dir.z), Quaternion.identity);
                    Destroy(ExFireEffect, ExFireEffect.GetComponent<ParticleSystem>().duration + 0.5f);

                    StartCoroutine(ExFire(dir));
                    Debug.Log(dir.x);
                    Debug.Log(dir.z);

                    Fire = false;
                }
            }
        }
    }

    void SetSkillSlot()
    {
        switch (SkillIter)
        {
            case Skill_List.Skill_Rush:
                this.GetComponent<Image>().sprite = Skill_Rush;
                break;
            case Skill_List.Skill_Windish:
                this.GetComponent<Image>().sprite = Skill_Windish;
                break;
            case Skill_List.Skill_Match:
                this.GetComponent<Image>().sprite = Skill_Match;
                break;
            case Skill_List.Skill_FireExplosion:
                this.GetComponent<Image>().sprite = Skill_FireExplosion;
                break;
            case Skill_List.Skill_Heal: // 유닛 한종류 힐
                this.GetComponent<Image>().sprite = Skill_Heal;
                break;
            case Skill_List.Skill_Thunder:
                this.GetComponent<Image>().sprite = Skill_Thunder;
                break;
            case Skill_List.Skill_Avatar: //유니티강화
                this.GetComponent<Image>().sprite = Skill_Avatar;
                break;
            case Skill_List.Skill_Summon:
                this.GetComponent<Image>().sprite = Skill_Summon;
                break;
            case Skill_List.Skill_Brave: //유닛강화
                this.GetComponent<Image>().sprite = Skill_Brave;
                break;
            case Skill_List.Skill_Cure:
                this.GetComponent<Image>().sprite = Skill_Cure;
                break;
            case Skill_List.Skill_Tame: //유닛강화
                this.GetComponent<Image>().sprite = Skill_Tame;
                break;
        }
    }

    public void Active()
    {
        if(Current_State == Skill_State.Full_State && SkillCost <= SBattleManager.Instance.currentgage)
        {
            Debug.Log(SkillIter);

            switch (SkillIter)
            {
                case Skill_List.Skill_Rush:
                    break;
                case Skill_List.Skill_Windish:
                    break;
                case Skill_List.Skill_Match:
                    break;
                case Skill_List.Skill_FireExplosion:
                    Fire = true;
                    Debug.Log(Fire);
                    break;
                case Skill_List.Skill_Heal:
                    Heal = true;
                    if (SBattleManager.Instance.UnitList.Count > 0)
                        Target = SBattleManager.Instance.UnitList[0];


                    HealTarget();

                    for (int i = 0; i < SBattleManager.Instance.UnitList.Count; i++)
                    {
                        if (Target.tag == SBattleManager.Instance.UnitList[i].tag)
                        {
                            HealEffect = (GameObject)Instantiate(HealPrefab, SBattleManager.Instance.UnitList[i].transform.position, Quaternion.identity);
                            SBattleManager.Instance.UnitList[i].GetComponent<Unit>().HP = 200;
                            Debug.Log(SBattleManager.Instance.UnitList[i].GetComponent<Unit>().HP);
                            Destroy(HealEffect, HealEffect.GetComponent<ParticleSystem>().duration + 0.1f);
                        }
                    }

               break;
            case Skill_List.Skill_Thunder:
                break;
            case Skill_List.Skill_Avatar:
                    Avatar = true;
                    if (SBattleManager.Instance.UnitList.Count <= 0)
                        return;

                    for (int i = 0; i < SBattleManager.Instance.HeroList.Count; i++)
                    {
                        if (SBattleManager.Instance.HeroList[i].tag == "Unitychan")
                        {
                            AvatarEffect = (GameObject)Instantiate(AvatarPrefab, SBattleManager.Instance.HeroList[i].transform.position, Quaternion.identity);
                            SBattleManager.Instance.HeroList[i].GetComponent<Hero_Unitychan>().ATK += 20;
                            SBattleManager.Instance.HeroList[i].GetComponent<Hero_Unitychan>().HP += 200;
                            SBattleManager.Instance.HeroList[i].GetComponent<Hero_Unitychan>().transform.localScale = new Vector3(1, 1, 1);
                            StartCoroutine(Avatarfun(SBattleManager.Instance.HeroList[i]));
                        }
                    }
                    break;
            case Skill_List.Skill_Summon:
                break;
            case Skill_List.Skill_Brave:
                    Brave = true;
                    if (SBattleManager.Instance.UnitList.Count <= 0)
                        return;
                    for(int i =0;i<SBattleManager.Instance.UnitList.Count;i++)
                    {
                        BraveEffect= (GameObject)Instantiate(BravePrefab, SBattleManager.Instance.UnitList[i].transform.position + new Vector3(0,1,0), Quaternion.identity);

                        SBattleManager.Instance.UnitList[i].GetComponent<Unit>().ATK += 50;
                        SBattleManager.Instance.UnitList[i].GetComponent<Unit>().HP -= 30;

                        Destroy(BraveEffect, BraveEffect.GetComponent<ParticleSystem>().duration + 0.1f);
                    }
                    break;
            case Skill_List.Skill_Cure:
                    break;
            case Skill_List.Skill_Tame:
                    Tame = true;
                    if (SBattleManager.Instance.UnitList.Count <= 0)
                        return;
                    for (int i = 0; i < SBattleManager.Instance.UnitList.Count; i++)
                    {
                        TameEffect = (GameObject)Instantiate(TamePrefab, SBattleManager.Instance.UnitList[i].transform.position, Quaternion.identity);
                        SBattleManager.Instance.UnitList[i].GetComponent<Unit>().ATK += 20;
                        Debug.Log(SBattleManager.Instance.UnitList[i].GetComponent<Unit>().ATK);
                        Destroy(TameEffect, TameEffect.GetComponent<ParticleSystem>().duration + 0.1f);
                    }
                    break;
            }
        InitCoolTime();
        }
    }
    IEnumerator Avatarfun(GameObject unity)
    {
        yield return new WaitForSeconds(3f);
        unity.transform.localScale = new Vector3(0.7f, 0.7f, 0.7f);
        StopCoroutine("Avatarfun");
    }
    void InitCoolTime()
    {
        CurrentTime = 6f;
        Current_State = Skill_State.Filling_State;
    }

    void CheckState()
    {

        if (SkillCost >= SBattleManager.Instance.currentgage)
            Effect.SetActive(true);

        if (Current_State == Skill_State.Filling_State)
            BanObject.fillAmount = (6f-CurrentTime) / 6f;

        if (0 >= CurrentTime)
        {
            CurrentTime = 0;
            Current_State = Skill_State.Full_State;
            BanObject.fillAmount = 0;
        }
        else
            CurrentTime -= Time.deltaTime;
    }
    void CheckHero()
    {

    }

    void HealTarget()
    {

         for (int i = 0; i < SBattleManager.Instance.UnitList.Count; i++)
        {
        if (Target.GetComponent<Unit>().HP > SBattleManager.Instance.UnitList[i].GetComponent<Unit>().HP)
            Target = SBattleManager.Instance.UnitList[i];
        }
    }

    IEnumerator ExFire(Vector3 dir)
    {
        yield return new WaitForSeconds(0.5f);

        FireEffect = Instantiate(FirePrefab, new Vector3(dir.x + 251f, 1, dir.z), Quaternion.identity);
        Destroy(FireEffect, FireEffect.GetComponent<ParticleSystem>().duration + 0.5f);
        for (int i = 0; i < SBattleManager.Instance.EnemyList.Count; i++)
        {

            if (SBattleManager.Instance.EnemyList[i].GetComponent<Unit>().transform.position.x - dir.x + 509 <= 2 ||
                SBattleManager.Instance.EnemyList[i].GetComponent<Unit>().transform.position.z - dir.z <= 2)
            {
                SBattleManager.Instance.EnemyList[i].GetComponent<Unit>().HP -= 500;
            }
        }
        StopCoroutine("ExFire");
    }




}
