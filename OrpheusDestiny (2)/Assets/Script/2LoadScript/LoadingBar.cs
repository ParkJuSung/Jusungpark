using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine;



public class LoadingBar : MonoBehaviour {

    public Image GageBar;
    float fillspeed;

	// Use this for initialization
	void Start () {
        GageBar.fillAmount = 0;
        fillspeed = 0.1f;
    }

    // Update is called once per frame
    void Update()
    {
        GageBar.fillAmount += Time.deltaTime * fillspeed;

        if (GageBar.fillAmount >= 1)
        {
            SceneManager.LoadScene("MenuScene");
        }
    }
}
