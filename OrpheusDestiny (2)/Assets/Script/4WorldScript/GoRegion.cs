using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoRegion : MonoBehaviour {


    public GameObject Window_RegionList;

	// Use this for initialization
	void Start () {
        Window_RegionList.SetActive(false);
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnMouseDown()
    {
        Window_RegionList.SetActive(true);
    }
}
