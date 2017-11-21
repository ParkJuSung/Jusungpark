using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ButtonWorld : MonoBehaviour
{

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

    }

    public void ButtonPushed()
    {
        Invoke("GoWorldScene",0.5f);
    }
    public void GoWorldScene()
    {
        SceneManager.LoadScene("WorldScene");
    }
}
