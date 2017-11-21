using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class SBattleManager
{

    private static SBattleManager instance = null;
    public static SBattleManager Instance
    {
        get
        {
            if (instance == null)
                instance = new SBattleManager();
            return instance;
        }
    }
    private SBattleManager()
    {
    }

    public List<GameObject> HeroList = new List<GameObject>();
    public List<GameObject> UnitList = new List<GameObject>(); // 전체 유닛 저장용도
    public List<GameObject> EnemyList = new List<GameObject>();


    public int SaberCount =0;
    public int LancerCount = 0;
    public int ArcherCount = 0;
    public int RiderCount = 0;
    public int VeteranCount = 0;
    public int WeaponCount = 0;

    public int GoblinCount = 0;
    public int SkeletonCount = 0;
    public int DragonCount = 0;
    public int OakCount = 0;
    public int MonsterCount = 0;

    public int CurrentWave;
    public int CurrentMonster;
    public int MaxMonster;
    public bool EntrtyBoss = false;
    public bool IsBossSummon = false;
    public bool Win = false;
    private int maxgage = 900;
    public int currentgage =0;

    public bool FillingGage()
    {
        if(maxgage> currentgage)
        return true;
        else
        return false;
    }

    public float GageRatio()
    {
        return ((float)currentgage / (float)maxgage);
    }
}
