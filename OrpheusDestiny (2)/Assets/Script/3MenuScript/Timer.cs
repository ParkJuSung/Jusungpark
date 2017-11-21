using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Timer : MonoBehaviour {

    public GameObject showtime;
    int time;

    int turnSpeed;
    TimerState NoewState;

    enum TimerState
    {
        Use3_State,
        Use6_State,
        Normal_State
    }


	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
    }

    void Use3()
    {

    }
    void Use6()
    {

    }
}
