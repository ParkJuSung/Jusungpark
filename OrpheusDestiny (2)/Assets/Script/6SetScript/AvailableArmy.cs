using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class AvailableArmy : MonoBehaviour {

    public Text AvailableHuman;
    public int totHuman;

	// Use this for initialization
	void Start () {
        Display(0);
    }
	
	// Update is called once per frame
	void Update () {
        SResource.Instance.UI_HUMAN = SResource.Instance.Human * 50;
    }
    
    void Display(int Human)
    {
        totHuman = SResource.Instance.UI_HUMAN;
        AvailableHuman.text = totHuman.ToString();
    }

}
