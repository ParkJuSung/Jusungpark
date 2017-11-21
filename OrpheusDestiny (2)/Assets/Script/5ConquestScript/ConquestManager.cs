using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class ConquestManager : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void GongSaJung()
    {
        SceneManager.LoadScene("4ShopScene");
    }
    void Open()
    {
        SceneManager.LoadScene("6SetScene");
    }
}
