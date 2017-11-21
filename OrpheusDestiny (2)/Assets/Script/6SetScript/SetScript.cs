using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class SetScript : MonoBehaviour
{
    public GameObject ResourceMessage;

    public Image ITen;
    public Image IOne;

    public Image Max25Ten;
    public Image Max25One;

    public Image Thousand;
    public Image Hundred;
    public Image Ten;
    public Image One;

    public Image SNum;
    public Image LNum;
    public Image ANum;
    public Image RNum;
    public Image VNum;
    public Image WNum;


    private int Max_UnitCount;
    private static int Current_UnitCount;

    public bool UnitLimit;
    public bool ResourceEnough;
    // Use this for initialization

    void Start () {
        SetStageInfo();
        SBattleManager.Instance.SaberCount = 0;
        SBattleManager.Instance.LancerCount = 0;
        SBattleManager.Instance.ArcherCount = 0;
        SBattleManager.Instance.RiderCount = 0;
        SBattleManager.Instance.VeteranCount = 0;
        SBattleManager.Instance.WeaponCount = 0;
        ResourceEnough = true;
        UnitLimit = false;
        Max_UnitCount = 25;
        //ResourceMessage.SetActive(false);
        if (SResource.Instance.Human == 0)
            SResource.Instance.Human = 2500;

    }
	
	// Update is called once per frame
	void Update () {

        if (Max_UnitCount <= Current_UnitCount)
            UnitLimit = true;

        if (Max_UnitCount > Current_UnitCount)
            UnitLimit = false;

        if (!ResourceEnough)
            Warnning();

            Current_UnitCount = SBattleManager.Instance.SaberCount +
            SBattleManager.Instance.LancerCount +
            SBattleManager.Instance.ArcherCount +
           SBattleManager.Instance.RiderCount +
           SBattleManager.Instance.VeteranCount +
           SBattleManager.Instance.WeaponCount;

        NumberUI.Instance.UIUpdate(null, null, Max25Ten, Max25One, 25);
        NumberUI.Instance.UIUpdate(null, null, ITen,IOne, Current_UnitCount);
        NumberUI.Instance.UIUpdate(Thousand, Hundred, Ten, One, SResource.Instance.Human);

        NumberUI.Instance.UIUpdate(null, null, null, SNum, SBattleManager.Instance.SaberCount);
        NumberUI.Instance.UIUpdate(null, null, null, LNum, SBattleManager.Instance.LancerCount);
        NumberUI.Instance.UIUpdate(null, null, null, ANum, SBattleManager.Instance.ArcherCount);
        NumberUI.Instance.UIUpdate(null, null, null, RNum, SBattleManager.Instance.RiderCount);
        NumberUI.Instance.UIUpdate(null, null, null, VNum, SBattleManager.Instance.VeteranCount);
        NumberUI.Instance.UIUpdate(null, null, null, WNum, SBattleManager.Instance.WeaponCount);


    }

    public void IncreaseUnit()
    {
            Current_UnitCount++;
    }

    public void DecreaseUnit()
    {
            Current_UnitCount--;
    }

    public void Warnning()
    {
        ResourceMessage.SetActive(true);
        Invoke("WarningExit",1.0f);
    }

    public void WarningExit()
    {
        ResourceMessage.SetActive(false);
    }

    public void SetStageInfo(int iGoblinCount =4, int iSkeletonCount = 3, int iLimitMonster = 18, int iWave = 5)
    {
        SBattleManager.Instance.GoblinCount = iGoblinCount;
        SBattleManager.Instance.SkeletonCount = iSkeletonCount;
        SBattleManager.Instance.CurrentWave = iWave;
        SBattleManager.Instance.MaxMonster = iLimitMonster;
    }


}
