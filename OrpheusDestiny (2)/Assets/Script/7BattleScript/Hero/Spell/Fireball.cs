using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Fireball : MonoBehaviour {

    public GameObject FireballCollider;
    // Use this for initialization
    void Start () {
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetButtonDown("Fire1"))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

            RaycastHit hitInfo;
            if (Physics.Raycast(ray, out hitInfo, 100f)) 
            {
                Vector3 hitPosition = hitInfo.point;

                Vector3 dir = hitPosition - transform.position;

                Instantiate(FireballCollider, new Vector3(dir.x-12.5f,1,dir.z-12.5f), Quaternion.identity);
            }
        }

  


	}
  
}
