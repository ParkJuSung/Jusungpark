using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class Twinkle : MonoBehaviour
{
    public float currenttime;
    private float maxtime;

    private float prevx;
    private float prevy;

    private void Start()
    {
        currenttime = 0;
        maxtime = 0.1f;
    }
    void Update()
    {
        currenttime += Time.deltaTime;

        if (currenttime> maxtime)
        {
            Debug.Log("");
            prevx = this.transform.localScale.x;
            prevy = this.transform.localScale.y;
            this.transform.localScale = this.transform.localScale * Random.Range(0.9f,1.1f);
            this.transform.localScale = new Vector3(prevx, prevy, 0);
            currenttime = 0f;
        }

        this.transform.Rotate(new Vector3(0, 0, Time.deltaTime * 45f));
    }
}
