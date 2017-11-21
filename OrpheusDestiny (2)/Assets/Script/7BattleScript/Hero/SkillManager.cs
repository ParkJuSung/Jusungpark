using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class SkillManager : HeroDefinition {

    public GameObject SkillSlot1;
    public GameObject SkillSlot2;
    public GameObject SkillSlot3;
    public GameObject SkillSlot4;
    public GameObject SkillSlot5;
    public GameObject SkillSlot6;
    public GameObject SkillSlot7;
    public GameObject SkillSlot8;
    public GameObject SkillSlot9;
    public GameObject SkillSlot10;
    public GameObject SkillSlotSurrender;

    public static int iterator;

    public Image CurrentGage;
    public Image EmptyGage;

    public GameObject Card1;
    public GameObject Card2;
    public GameObject Card3;
    public GameObject Card4;
    public GameObject Card5;

    // Use this for initialization
    void Start () {
        SkillSlot1.SetActive(false);
        SkillSlot2.SetActive(false);
        SkillSlot3.SetActive(false);
        SkillSlot4.SetActive(false);
        SkillSlot5.SetActive(false);
        SkillSlot6.SetActive(false);
        SkillSlot7.SetActive(false);
        SkillSlot8.SetActive(false);
        SkillSlot9.SetActive(false);
        SkillSlot10.SetActive(false);
        SkillSlotSurrender.SetActive(true);
        iterator = 0;
            }
	
	// Update is called once per frame
	void Update () {

        CurrentGage.fillAmount = SBattleManager.Instance.GageRatio();

        if (Card1.GetComponent<Hero>().GetCurrentState() == Hero_State.Summoned)
        {
            SkillSlot1.SetActive(true);
            SkillSlot2.SetActive(true);
        }

        if (Card2.GetComponent<Hero>().GetCurrentState() == Hero_State.Summoned)
        {
            SkillSlot3.SetActive(true);
            SkillSlot4.SetActive(true);
        }

        if (Card3.GetComponent<Hero>().GetCurrentState() == Hero_State.Summoned)
        {
            SkillSlot5.SetActive(true);
            SkillSlot6.SetActive(true);

        }

        if (Card4.GetComponent<Hero>().GetCurrentState() == Hero_State.Summoned)
        {
            SkillSlot7.SetActive(true);
            SkillSlot8.SetActive(true);
        }

        if (Card5.GetComponent<Hero>().GetCurrentState() == Hero_State.Summoned)
        {
            SkillSlot9.SetActive(true);
            SkillSlot10.SetActive(true);
        }

        if (SBattleManager.Instance.FillingGage())
            SBattleManager.Instance.currentgage++;
        else
            SBattleManager.Instance.currentgage = 900;

        //Debug.Log(SBattleManager.Instance.GageRatio());
    }
    void InvokeSurrender()
    {
        if(SBattleManager.Instance.currentgage>150)
            SkillSlotSurrender.SetActive(true);
    }
    
}

