using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cube : MonoBehaviour {

    public Transform playerTr;
    public float distance;
    public static bool set = true;
    // Use this for initialization
    void Start () {

        playerTr = GameObject.FindWithTag("Player").GetComponent<Transform>();

    }

    // Update is called once per frame
    void Update () {
        if(!set)
        {
            gameObject.SetActive(false);
        }
    }

    public bool get()
    {

        if (distance < 10)
        {
            SResource.Instance.GOLD += 500;
            set = false;
            return true;
        }
        distance = Vector3.Distance(playerTr.position, gameObject.transform.position);

        return false;
    }
}
