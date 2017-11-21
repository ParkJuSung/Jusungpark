using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Country : MonoBehaviour {

    public GameObject GetInfo;
    int PrevYear;
    
    // Use this for initialization
    void Start () {
        SResource.Instance.TAX = 0;
        GetInfo.SetActive(false);
        PrevYear = SResource.Instance.YEAR;
    }
	
	// Update is called once per frame
	void Update () {
        SResource.Instance.TAX++;
        SResource.Instance.Human++;

        SResource.Instance.COST = SResource.Instance.Human;

        if (PrevYear != SResource.Instance.YEAR)
        {
            SResource.Instance.FOOD -= SResource.Instance.COST;
            PrevYear = SResource.Instance.YEAR;
        }

    }

    public void GetReward()
    {
        GetInfo.SetActive(true);
        Invoke("InfoOff",2f);

    }

    void InfoOff()
    {
        SResource.Instance.GOLD += SResource.Instance.Count_Trade * SResource.Instance.TAX;
        SResource.Instance.FOOD += SResource.Instance.Count_Farm * SResource.Instance.TAX;
        SResource.Instance.IRON += SResource.Instance.Count_Mine * SResource.Instance.TAX;
        GetInfo.SetActive(false);
        SResource.Instance.TAX = 0;
    }
}
