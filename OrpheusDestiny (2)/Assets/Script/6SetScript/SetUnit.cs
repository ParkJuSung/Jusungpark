using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class SetUnit : SetScript
{
    void Update () {
    }

    public void SaberIncrease()
    {
        if(SBattleManager.Instance.SaberCount<25 && SResource.Instance.Human >=100)
        { 
        SResource.Instance.Human -= 100 ;
        IncreaseUnit();
        SBattleManager.Instance.SaberCount++;
        }
        Debug.Log(SBattleManager.Instance.SaberCount);
    }

    public void SaberDecrease()
    {
        if (SBattleManager.Instance.SaberCount > 0 )
        {
        SResource.Instance.Human += 100;
        DecreaseUnit();
            SBattleManager.Instance.SaberCount--;
        }
        Debug.Log(SBattleManager.Instance.SaberCount);
    }



    public void LancerIncrease()
    {
        if (SBattleManager.Instance.LancerCount < 5 && SResource.Instance.Human >= 100)
        {
            SResource.Instance.Human -= 100;
            IncreaseUnit();
            SBattleManager.Instance.LancerCount++;
            Debug.Log(SBattleManager.Instance.LancerCount);
        }
    }

    public void LancerDecrease()
    {
        if (SBattleManager.Instance.LancerCount > 0)
        {
            SResource.Instance.Human += 100;
            DecreaseUnit();
            SBattleManager.Instance.LancerCount--;
            Debug.Log(SBattleManager.Instance.LancerCount);
        }
    }

    public void ArcherIncrease()
    {
        if (SBattleManager.Instance.ArcherCount < 5 && SResource.Instance.Human >= 100)
        {
            SResource.Instance.Human -= 100;
            IncreaseUnit();
            SBattleManager.Instance.ArcherCount++;
            Debug.Log(SBattleManager.Instance.ArcherCount);
        }
    }

    public void ArcherDecrease()
    {
        if (SBattleManager.Instance.ArcherCount > 0)
        {
            SResource.Instance.Human += 100;
            DecreaseUnit();
            SBattleManager.Instance.ArcherCount--;
            Debug.Log(SBattleManager.Instance.ArcherCount);
        }
    }

    public void RiderIncrease()
    {
        if (SBattleManager.Instance.RiderCount < 5 && SResource.Instance.Human >= 100)
        {
            SResource.Instance.Human -= 100;
            IncreaseUnit();
            SBattleManager.Instance.RiderCount++;
            Debug.Log(SBattleManager.Instance.RiderCount);
        }
    }

    public void RiderDecrease()
    {
        if (SBattleManager.Instance.RiderCount > 0)
        {
            SResource.Instance.Human += 100;
            DecreaseUnit();
            SBattleManager.Instance.RiderCount--;
            Debug.Log(SBattleManager.Instance.RiderCount);
        }
    }

    public void VeteranIncrease()
    {
        if (SBattleManager.Instance.VeteranCount < 5 && SResource.Instance.Human >= 100)
        {
            SResource.Instance.Human -= 100;
            IncreaseUnit();
            SBattleManager.Instance.VeteranCount++;
            Debug.Log(SBattleManager.Instance.VeteranCount);
        }
    }

    public void VeteranDecrease()
    {
        if (SBattleManager.Instance.VeteranCount > 0)
        {
            SResource.Instance.Human += 100;
            DecreaseUnit();
            SBattleManager.Instance.VeteranCount--;
            Debug.Log(SBattleManager.Instance.VeteranCount);
        }
    }

    public void WeaponIncrease()
    {
        if(SBattleManager.Instance.WeaponCount<5 && SResource.Instance.Human >= 100)
        {
            SResource.Instance.Human -= 100;
            IncreaseUnit();
            SBattleManager.Instance.WeaponCount++;
            Debug.Log(SBattleManager.Instance.WeaponCount);
        }
    }

    public void WeaponDecrease()
    {
        if(SBattleManager.Instance.WeaponCount>0)
        {
            SResource.Instance.Human += 100;
            DecreaseUnit();
            SBattleManager.Instance.WeaponCount--;
            Debug.Log(SBattleManager.Instance.WeaponCount);
        }
    }
}
