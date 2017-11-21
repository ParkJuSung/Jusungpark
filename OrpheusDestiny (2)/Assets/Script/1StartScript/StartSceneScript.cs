using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;


public class StartSceneScript : MonoBehaviour {


    private float currenttime;
    public bool LoadComplete;
    public GameObject PressAnyTouch;
    public GameObject Effect;

    private bool Uping;

    // Use this for initialization
    void Start () {
        Effect.SetActive(false);
        LoadComplete = false;
        SResource.Instance.SetUser();
        Invoke("Switch", 3f);
        Uping = true;
    }
	
	// Update is called once per frame
	void Update () {
        currenttime += Time.deltaTime;
        if(currenttime>3f)
        {
            Uping = false;
            if (currenttime >= 6f)
            {
                Uping = true;
                currenttime = 0;
            }                
        }

        if (Uping)
            Up();
        else if(!Uping)
            Down();

        if (Input.GetMouseButtonDown(0) && LoadComplete)
        {
            SceneChange();
        }
	}


    void Up()
    {
        this.transform.Translate(new Vector3(0, -1 * Time.deltaTime, 0));
    }

    void Down()
    {
        this.transform.Translate(new Vector3(0, 1 * Time.deltaTime, 0));
    }
    
    void Switch()
    {
        Effect.SetActive(true);
        LoadComplete = true;
    }
    
    void SceneChange()
    {
        SceneManager.LoadScene("3MenuScene");
    }
}
