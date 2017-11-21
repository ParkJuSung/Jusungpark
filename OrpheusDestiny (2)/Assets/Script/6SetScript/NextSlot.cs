using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class NextSlot : MonoBehaviour {

    public Sprite Hero;
    public Sprite Hero2;


    // Use this for initialization
    void Start () {
	    
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void Next()
    {
        gameObject.GetComponent<Image>().sprite = Hero;
       

    }

    public void Prev()
    {
        gameObject.GetComponent<Image>().sprite = Hero2;
    }
}
