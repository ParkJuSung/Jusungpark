using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class SceneSwitch : MonoBehaviour {

    public void MainScene()
    {
        SceneManager.LoadScene("main");
    }

    public void PlayScene()
    {
        SceneManager.LoadScene("play");
    }

    public void Quit()
    {
        Application.Quit();
    }
}
