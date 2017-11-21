using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WindowEnemyInfo : MonoBehaviour {

    public GameObject Window_EnemyInfo;

	// Use this for initialization
	void Start () {
        Window_EnemyInfo.SetActive(false);
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnInformation()
    {
        Window_EnemyInfo.SetActive(true);
    }
}
