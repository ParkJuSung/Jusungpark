using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pickedonoff : MonoBehaviour {


    public GameObject Hero;


    // Use this for initialization
    void Start () {
        Hero.SetActive(false);
	}

    // Update is called once per frame
    void Update()
    {
        if (Input.GetButtonDown("Fire1"))
        {
            Hero.SetActive(true);
        }
    }
}
