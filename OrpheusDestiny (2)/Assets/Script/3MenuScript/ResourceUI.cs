using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class ResourceUI : MonoBehaviour {

    public Image GThou;
    public Image GHund;
    public Image GTen;
    public Image Gone;

    public Image FThou;
    public Image FHund;
    public Image FTen;
    public Image Fone;

    public Image IThou;
    public Image IHund;
    public Image ITen;
    public Image IOne;

    public Image LevelT;
    public Image LevelO;

    public GameObject Message;

    bool GoldEnough;

    // Use this for initialization
    void Start () {
        Message.SetActive(false);
    }
	
	// Update is called once per frame
	void Update () {

        UpdateGold();
        UpdateFood();
        UpdateIron();
        NumberUI.Instance.UIUpdate(GThou, GHund, GTen, Gone, SResource.Instance.GOLD);
        NumberUI.Instance.UIUpdate(FThou, FHund, FTen, Fone, SResource.Instance.IRON);
        NumberUI.Instance.UIUpdate(IThou, IHund, ITen, IOne, SResource.Instance.FOOD);
        NumberUI.Instance.UIUpdate(null, null, LevelT, LevelO, SResource.Instance.LEVEL);


    }

    void UpdateGold()
    {
        if (SResource.Instance.GOLD < 0)
            MessageON();
    }

    void UpdateFood()
    {
        if (SResource.Instance.FOOD < 0)
            MessageON();
    }

    void UpdateIron()
    {
        if (SResource.Instance.IRON < 0)
            MessageON();
    }

    void MessageOff()
    {
        Message.SetActive(false);
    }

    void MessageON()
    {
        Message.SetActive(true);
        Invoke("MessageOff",0.5f);
    }


}
