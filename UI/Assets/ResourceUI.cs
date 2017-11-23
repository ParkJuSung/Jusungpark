using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class ResourceUI : MonoBehaviour {

    public Image GThou;
    public Image GHund;
    public Image GTen;
    public Image Gone;

    public Image MTen;
    public Image Mone;
    public Image STen;
    public Image Sone;
   


    public GameObject Message;

    bool GoldEnough;

    // Use this for initialization
    void Start () {
        // Message.SetActive(false);
        SResource.Instance.TIME = 672;
        StartCoroutine(UpdateTime());
    }

    // Update is called once per frame
    void Update () {

        UpdateGold();
        NumberUI.Instance.UIUpdate(GThou, GHund, GTen, Gone, SResource.Instance.GOLD);
    }

    public IEnumerator UpdateTime()
    {
        while (true)
        {
            SResource.Instance.TIME -= 1;
            NumberUI.Instance.TUIUpdate(MTen, Mone, STen, Sone, SResource.Instance.TIME);
            yield return new WaitForSeconds(1.0f);
        }
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
