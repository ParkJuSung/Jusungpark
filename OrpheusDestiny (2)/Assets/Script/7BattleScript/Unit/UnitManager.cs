using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 유닛 생산 담당

public class UnitManager : Unit {
    //public Unit unitlist = new Unit();
    // 일반 유닛
        int Saber_Count;
        int Lancer_Count;
        int Archer_Count;
        int Rider_Count;
        int Veteran_Count;
        int Weapon_Count;

    public GameObject SaberPrefab;
    public GameObject LancerPrefab;
    public GameObject ArcherPrefab;
    public GameObject RiderPrefab;
    public GameObject VeteranPrefab;
    public GameObject WeaponPrefab;

    public GameObject StealthPrefab;
    public GameObject SpartanKingPrefab;
    public GameObject UnitychanPrefab;

    //몬스터
    int Goblin_Count;
    int Skeleton_Count;
    int Boss_Count;

    public GameObject GoblinPrefab;
    public GameObject SkeletonPrefab;
    public GameObject BossPrefab;

    public GameObject Reward;

    // Use this for initialization
    void Start ()
    {
        Reward.SetActive(false);
        Saber_Count = SBattleManager.Instance.SaberCount;
        Lancer_Count = SBattleManager.Instance.LancerCount;
        Archer_Count = SBattleManager.Instance.ArcherCount;
        Rider_Count = SBattleManager.Instance.RiderCount;
        Veteran_Count = SBattleManager.Instance.VeteranCount;
        Weapon_Count = SBattleManager.Instance.WeaponCount;
        Goblin_Count = SBattleManager.Instance.GoblinCount;
        Skeleton_Count = SBattleManager.Instance.SkeletonCount;
        
        EnemySummon();
        UnitSummon();

    }

	
	// Update is called once per frame
	void Update () {
        if (SBattleManager.Instance.Win)
            Reward.SetActive(true);
        EntryBoss();
        BossSummon();
    }
   
    void UnitSummon()
    {
        for (int i = 0; i < Rider_Count; i++)
        {

            SBattleManager.Instance.UnitList.Add(Instantiate(RiderPrefab, new Vector3(i+1, 0, -8), Quaternion.identity));
        }

        for (int i= 0; i< Saber_Count; i++)
        {
            SBattleManager.Instance.UnitList.Add(Instantiate(SaberPrefab, new Vector3(i+1, 0, -8), Quaternion.identity));
        }

        for (int i = 0; i < Lancer_Count; i++)
        {
            SBattleManager.Instance.UnitList.Add(Instantiate(LancerPrefab, new Vector3(i+1, 0, -8), Quaternion.identity));
        }

        for (int i = 0; i < Archer_Count; i++)
        {
            
            SBattleManager.Instance.UnitList.Add(Instantiate(ArcherPrefab, new Vector3(i+1, 0, -8), Quaternion.identity));
        }
       
        for (int i = 0; i < Veteran_Count; i++)
        {
            
            SBattleManager.Instance.UnitList.Add(Instantiate(VeteranPrefab, new Vector3(0, 0, 0), Quaternion.identity));
        }
        for (int i = 0; i < Weapon_Count; i++)
        {
            SBattleManager.Instance.UnitList.Add(Instantiate(WeaponPrefab, new Vector3(0, 0, 0), Quaternion.identity));
        }
        
    }

    void EnemySummon()
    {
        if (!SBattleManager.Instance.Win)
        {
            if (SBattleManager.Instance.CurrentWave > 0)
            {
                for (int i = 0; i < Skeleton_Count; i++)
                {
                    SBattleManager.Instance.EnemyList.Add(Instantiate(SkeletonPrefab, new Vector3(i + 2.25f, 0, 7.5f), new Quaternion(0, 180, 0, 0)));
                }

                for (int i = 0; i < Goblin_Count; i++)
                {
                    SBattleManager.Instance.EnemyList.Add(Instantiate(GoblinPrefab, new Vector3(i+2.25f, 0, 7.5f),new Quaternion(0,180,0,0)));
                }

           
                SBattleManager.Instance.CurrentWave--;
                Invoke("EnemySummon", 5f);
            }
        }

    }

    void BossSummon()
    {
        if (!SBattleManager.Instance.IsBossSummon)
        {
            if (SBattleManager.Instance.EntrtyBoss)
            {
                SBattleManager.Instance.EnemyList.Add(Instantiate(BossPrefab, new Vector3(4, 0, 7.5f), new Quaternion(0, 180, 0, 0)));
                SBattleManager.Instance.IsBossSummon = true;
            }
        }

    }
    public void EntryBoss()
    {
        if (SBattleManager.Instance.CurrentMonster > SBattleManager.Instance.MaxMonster)
        {
            SBattleManager.Instance.EntrtyBoss = true;
            SBattleManager.Instance.CurrentMonster = 0;
        }
        else
        {
            SBattleManager.Instance.EntrtyBoss = false;
        }
    }
}
